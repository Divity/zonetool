umbra3 = {}

function umbra3:include()
	local folder = DependencyFolder()
	includedirs {
		path.join(folder, "umbra3/interface"),
		path.join(folder, "umbra3/interface/runtime"),
		path.join(folder, "umbra3/interface/optimizer"),
		path.join(folder, "umbra3/source"),
		path.join(folder, "umbra3/source/common"),
		path.join(folder, "umbra3/source/runtime"),
		path.join(folder, "umbra3/source/optimizer"),
		path.join(folder, "umbra3/source/standard"),
	}
end

function umbra3:link()
	self:include()
	links {
		"umbra3"
	}
end

function umbra3:project()
	local folder = DependencyFolder()

	project "umbra3"
		location "%{wks.location}/dep"
		kind "StaticLib"
		language "C++"
		architecture "x86_64"
		characterset "MBCS"

		removebuildoptions { "/std:c++latest" }
		cppdialect "C++14"

		optimize "Speed"
		runtime "Release"
		removedefines { "_DEBUG", "DEBUG" }
		defines { "NDEBUG" }

		files {
			path.join(folder, "umbra3/interface/**.hpp"),
			path.join(folder, "umbra3/source/common/*.cpp"),
			path.join(folder, "umbra3/source/common/*.hpp"),
			path.join(folder, "umbra3/source/common/windows/*.cpp"),
			path.join(folder, "umbra3/source/common/windows/*.inl"),
			path.join(folder, "umbra3/source/standard/*.cpp"),
			path.join(folder, "umbra3/source/standard/*.hpp"),
			path.join(folder, "umbra3/source/runtime/*.cpp"),
			path.join(folder, "umbra3/source/runtime/*.hpp"),
			path.join(folder, "umbra3/source/optimizer/*.cpp"),
			path.join(folder, "umbra3/source/optimizer/*.hpp"),
		}

		removefiles {
			path.join(folder, "umbra3/source/common/umbraMemory.cpp"),
		}

		defines {
			"_CRT_SECURE_NO_WARNINGS",
			"_CRT_NONSTDC_NO_WARNINGS",
			"UMBRA_UNLOCKED",
			"UMBRA_IW7_CELL_EXIT_PORTALS",
		}

		removedefines { "CPU_32BIT" }

		self:include()

		warnings "off"
end
