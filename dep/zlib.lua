zlib = {}

function zlib:include()
	includedirs {
		path.join(DependencyFolder(), "zlib"),
		path.join(DependencyFolder(), "zlib/contrib/minizip")
	}
end

function zlib:link()
	self:include()
	links {
		"zlib"
	}
end

function zlib:project()
	local folder = DependencyFolder();

	project "zlib"
	
		location "%{wks.location}/dep"
		kind "StaticLib"
		language "C"
		
		files {
			path.join(folder, "zlib/*.h"),
			path.join(folder, "zlib/*.c"),
			path.join(folder, "zlib/contrib/minizip/unzip.h"),
			path.join(folder, "zlib/contrib/minizip/unzip.c"),
			path.join(folder, "zlib/contrib/minizip/ioapi.h"),
			path.join(folder, "zlib/contrib/minizip/ioapi.c")
		}
		
		defines {
			"_CRT_SECURE_NO_WARNINGS",
			"_CRT_NONSTDC_NO_DEPRECATE"
		}
		
		self:include()

		-- Disable warnings. They do not have any value to us since it is not our code.
		warnings "off"
end
