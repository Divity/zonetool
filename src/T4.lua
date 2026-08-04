T4 = {}

function T4:include()
    includedirs {
        path.join(ProjectFolder(), "T4")
    }
end

function T4:link()
    self:include()
	links {
		"T4"
	}
end

function T4:project()
    local folder = ProjectFolder();

    project "T4"
        kind "StaticLib"
        language "C++"
        
        pchheader "stdafx.hpp"
        pchsource(path.join(folder, "T4/stdafx.cpp"))

        files {
            path.join(folder, "T4/**.h"),
            path.join(folder, "T4/**.hpp"),
            path.join(folder, "T4/**.cpp")
        }

        self:include()
        ZoneUtils:include()
        
        zstd:include()
        zlib:include()
end