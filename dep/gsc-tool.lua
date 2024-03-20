gsctool = {}

local function get_dep_folder()
    local folder = DependencyFolder();
    folder = folder .. "gsc-tool/"
    return folder
end

function gsctool:include()
    local folder = get_dep_folder()
    
    includedirs {
        path.join(folder, "gsc-tool/include"),
    }
end

function gsctool:link()
    self:include()
    links {"xsk-gsc-iw5", "xsk-gsc-utils"}
end

function gsctool:project()
    project "xsk-gsc-utils"
    kind "StaticLib"
    language "C++"
    warnings "Off"

    local folder = get_dep_folder()
    
    files { 
        path.join(folder, "include/xsk/utils/**.h"),
        path.join(folder, "src/utils/**.cpp")
    }

    local depfolder = DependencyFolder();
    includedirs {
        path.join(folder, "include"),
        path.join(depfolder, "zlib"),
    }

    project "xsk-gsc-iw5"
    kind "StaticLib"
    language "C++"
    warnings "Off"

    filter "action:vs*"
        buildoptions "/Zc:__cplusplus"
    filter {}

    files {
        path.join(folder, "include/xsk/stdinc.hpp"),
 
        path.join(folder, "include/xsk/gsc/engine/iw5.hpp"),
        path.join(folder, "src/gsc/engine/iw5.cpp"),

        path.join(folder, "src/gsc/engine/iw5_code.cpp"),
        path.join(folder, "src/gsc/engine/iw5_func.cpp"),
        path.join(folder, "src/gsc/engine/iw5_meth.cpp"),
        path.join(folder, "src/gsc/engine/iw5_token.cpp"), path.join(folder, "src/gsc/*.cpp"),

        path.join(folder, "src/gsc/common/*.cpp"),
        path.join(folder, "include/xsk/gsc/common/*.hpp")
    }

    includedirs {
        path.join(folder, "include")
    }
end