#pragma once

namespace ZoneTool
{
	namespace T4
	{
		class ITechset
		{
		public:
			static void dump(MaterialTechniqueSet* asset, ZoneMemory* mem);
			static void dump_statebits(const std::string& techset, char* statebits);

			static IW4::VertexDecl* dump_vertex_decl(const std::string& name, MaterialVertexDeclaration* vertex, ZoneMemory* mem);
			static IW4::VertexShader* dump_vertex_shader(MaterialVertexShader* shader, ZoneMemory* mem);
			static IW4::PixelShader* dump_pixel_shader(MaterialPixelShader* shader, ZoneMemory* mem);
		};
	}
}
