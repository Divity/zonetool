UmbraTomeGen = {}

function UmbraTomeGen:project()
    local folder = ProjectFolder();

    project "umbra-tomegen"
        kind "ConsoleApp"
        language "C++"
        architecture "x86_64"
        characterset "MBCS"
        removebuildoptions { "/std:c++latest" }
        cppdialect "C++17"

        optimize "Speed"
        runtime "Release"
        removedefines { "_DEBUG", "DEBUG" }
        defines { "NDEBUG" }

        files {
            path.join(folder, "UmbraTomeGen/**.hpp"),
            path.join(folder, "UmbraTomeGen/**.cpp"),
            path.join(folder, "X64/Utils/Umbra/UmbraScene.hpp"),
        }

        removedefines { "CPU_32BIT" }

        umbra3:link()
end
