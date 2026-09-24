@echo off
setlocal EnableExtensions

set "COD4=D:\SteamLibrary\steamapps\common\Call of Duty 4"
set "IW7=D:\Games\PC\IW7"
set "REPO=D:\Documents\Github\zonetool"
set "DLL=%REPO%\build\bin\Win32\Debug\ZoneTool.dll"

set "MAP="
set "DO_BUILD=0"
set "DO_DUMP=1"
set "FAST=1"

:parse
if "%~1"=="" goto parsed
if /i "%~1"=="-build"  ( set "DO_BUILD=1" & shift & goto parse )
if /i "%~1"=="-nodump" ( set "DO_DUMP=0"  & shift & goto parse )
if /i "%~1"=="-full"   ( set "FAST=0"     & shift & goto parse )
if not defined MAP     ( set "MAP=%~1"    & shift & goto parse )
echo [!] unexpected argument: %~1
exit /b 2
:parsed
if not defined MAP set "MAP=mp_test_h1"
if "%FAST%"=="1" set "ZONETOOL_FAST_DUMP=1"

echo ============================================================
echo  map        %MAP%
echo  build dll  %DO_BUILD%
echo  re-dump    %DO_DUMP%
echo ------------------------------------------------------------
for /f "tokens=1,* delims==" %%A in ('set ZT_ 2^>nul') do echo  env        %%A=%%B
for /f "tokens=1,* delims==" %%A in ('set ZONETOOL_ 2^>nul') do echo  env        %%A=%%B
echo ============================================================

if not exist "%COD4%\zonetool_iw3.exe" echo [!] missing %COD4%\zonetool_iw3.exe & exit /b 1
if not exist "%IW7%\zonetool.exe"      echo [!] missing %IW7%\zonetool.exe      & exit /b 1

if "%DO_BUILD%"=="0" goto skipbuild

set "MSBUILD=C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe"
if not exist "%MSBUILD%" set "MSBUILD=C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
if not exist "%MSBUILD%" echo [!] no MSBuild found & exit /b 1

echo [1/4] building ZoneTool.dll (Debug^|Win32)
"%MSBUILD%" "%REPO%\build\zonetool.sln" /p:Configuration=Debug /p:Platform=Win32 /v:quiet /m /nologo
if errorlevel 1 echo [!] build failed & exit /b 1

echo       deploying to zoneiw3.dll
copy /y "%DLL%" "%COD4%\zoneiw3.dll" >nul
if errorlevel 1 echo [!] deploy failed -- is CoD4 or the dumper running? & exit /b 1

echo       deploying umbra-tomegen.exe
copy /y "%REPO%\build\bin\Win32\Debug\umbra-tomegen.exe" "%COD4%\umbra-tomegen.exe" >nul
if errorlevel 1 echo [!] umbra-tomegen deploy failed & exit /b 1
goto builddone
:skipbuild
echo [1/4] build skipped
:builddone

if "%DO_DUMP%"=="0" goto skipdump

set "DUMPLOG=%TEMP%\iw7-relink-%MAP%.log"
echo [2/4] dumping %MAP% in CoD4  (log: %DUMPLOG%^)
pushd "%COD4%"
"%COD4%\zonetool_iw3.exe" -silent -dumpzone %MAP% iw7 > "%DUMPLOG%" 2>&1
popd

findstr /c:"Zone \"%MAP%\" dumped" "%DUMPLOG%" >nul
if errorlevel 1 (
  echo [!] dump did not report completion -- tail of the log:
  powershell -NoProfile -Command "Get-Content -LiteralPath '%DUMPLOG%' -Tail 15"
  exit /b 1
)
echo       dump ok
findstr /c:"clipmap collision:" "%DUMPLOG%" | findstr /c:"world shape" /c:"trisoup --" /c:"brush basis"
findstr /c:"umbra:" "%DUMPLOG%" | findstr /v /c:"INFO:"
goto dumpdone
:skipdump
echo [2/4] dump skipped -- relinking whatever is already in staging
:dumpdone

echo [3/4] syncing staging
robocopy "%COD4%\dump\%MAP%" "%IW7%\zonetool\%MAP%" /E /NFL /NDL /NJH /NJS /NP >nul
if %ERRORLEVEL% GEQ 8 echo [!] robocopy failed with %ERRORLEVEL% -- NOT relinking & exit /b 1
echo       robocopy exit %ERRORLEVEL% (0-7 is success^)

echo [4/4] building zone
pushd "%IW7%"
"%IW7%\zonetool.exe" -buildzone %MAP%
set "RC=%ERRORLEVEL%"
popd
if not "%RC%"=="0" echo [!] buildzone failed with %RC% & exit /b 1

for %%F in ("%IW7%\zone\%MAP%.ff") do echo  done: %%~fF  %%~zF bytes  %%~tF
endlocal
exit /b 0
