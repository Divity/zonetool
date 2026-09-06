#include "stdafx.hpp"

#include "../IW4/Assets/VertexDecl.hpp"
#include "../IW4/Assets/VertexShader.hpp"
#include "../IW4/Assets/PixelShader.hpp"
#include "IW4/Assets/Techset.hpp"

#include <zlib.h>
#include <unordered_set>

namespace ZoneTool
{
	namespace T4
	{
		namespace
		{
			const std::unordered_map<std::int32_t, std::int32_t> technique_map =
			{
				{TECHNIQUE_DEPTH_PREPASS, IW4::TECHNIQUE_DEPTH_PREPASS},
				{TECHNIQUE_BUILD_FLOAT_Z, IW4::TECHNIQUE_BUILD_FLOAT_Z},
				{TECHNIQUE_BUILD_SHADOWMAP_DEPTH, IW4::TECHNIQUE_BUILD_SHADOWMAP_DEPTH},
				{TECHNIQUE_BUILD_SHADOWMAP_COLOR, IW4::TECHNIQUE_BUILD_SHADOWMAP_COLOR},
				{TECHNIQUE_UNLIT, IW4::TECHNIQUE_UNLIT},
				{TECHNIQUE_EMISSIVE, IW4::TECHNIQUE_EMISSIVE},
				{TECHNIQUE_EMISSIVE_SHADOW, IW4::TECHNIQUE_EMISSIVE_SHADOW},
				{TECHNIQUE_LIT, IW4::TECHNIQUE_LIT},
				{TECHNIQUE_LIT_FADE, IW4::TECHNIQUE_LIT_DFOG},
				{TECHNIQUE_LIT_SUN, IW4::TECHNIQUE_LIT_SUN},
				{TECHNIQUE_LIT_SUN_FADE, IW4::TECHNIQUE_LIT_SUN_DFOG},
				{TECHNIQUE_LIT_SUN_SHADOW, IW4::TECHNIQUE_LIT_SUN_SHADOW},
				{TECHNIQUE_LIT_SUN_SHADOW_FADE, IW4::TECHNIQUE_LIT_SUN_SHADOW_DFOG},
				{TECHNIQUE_LIT_SPOT, IW4::TECHNIQUE_LIT_SPOT},
				{TECHNIQUE_LIT_SPOT_FADE, IW4::TECHNIQUE_LIT_SPOT_DFOG},
				{TECHNIQUE_LIT_SPOT_SHADOW, IW4::TECHNIQUE_LIT_SPOT_SHADOW},
				{TECHNIQUE_LIT_SPOT_SHADOW_FADE, IW4::TECHNIQUE_LIT_SPOT_SHADOW_DFOG},
				{TECHNIQUE_LIT_OMNI, IW4::TECHNIQUE_LIT_OMNI},
				{TECHNIQUE_LIT_OMNI_FADE, IW4::TECHNIQUE_LIT_OMNI_DFOG},
				{TECHNIQUE_LIT_OMNI_SHADOW, IW4::TECHNIQUE_LIT_OMNI_SHADOW},
				{TECHNIQUE_LIT_OMNI_SHADOW_FADE, IW4::TECHNIQUE_LIT_OMNI_SHADOW_DFOG},
				{TECHNIQUE_LIT_INSTANCED, IW4::TECHNIQUE_LIT_INSTANCED},
				{TECHNIQUE_LIT_INSTANCED_SUN, IW4::TECHNIQUE_LIT_INSTANCED_SUN},
				{TECHNIQUE_LIT_INSTANCED_SUN_SHADOW, IW4::TECHNIQUE_LIT_INSTANCED_SUN_SHADOW},
				{TECHNIQUE_LIT_INSTANCED_SPOT, IW4::TECHNIQUE_LIT_INSTANCED_SPOT},
				{TECHNIQUE_LIT_INSTANCED_SPOT_SHADOW, IW4::TECHNIQUE_LIT_INSTANCED_SPOT_SHADOW},
				{TECHNIQUE_LIT_INSTANCED_OMNI, IW4::TECHNIQUE_LIT_INSTANCED_OMNI},
				{TECHNIQUE_LIT_INSTANCED_OMNI_SHADOW, IW4::TECHNIQUE_LIT_INSTANCED_OMNI_SHADOW},
				{TECHNIQUE_LIGHT_SPOT, IW4::TECHNIQUE_LIGHT_SPOT},
				{TECHNIQUE_LIGHT_OMNI, IW4::TECHNIQUE_LIGHT_OMNI},
				{TECHNIQUE_LIGHT_SPOT_SHADOW, IW4::TECHNIQUE_LIGHT_SPOT_SHADOW},
				{TECHNIQUE_FAKELIGHT_NORMAL, IW4::TECHNIQUE_FAKELIGHT_NORMAL},
				{TECHNIQUE_FAKELIGHT_VIEW, IW4::TECHNIQUE_FAKELIGHT_VIEW},
				{TECHNIQUE_SUNLIGHT_PREVIEW, IW4::TECHNIQUE_SUNLIGHT_PREVIEW},
				{TECHNIQUE_CASE_TEXTURE, IW4::TECHNIQUE_CASE_TEXTURE},
				{TECHNIQUE_WIREFRAME_SOLID, IW4::TECHNIQUE_WIREFRAME_SOLID},
				{TECHNIQUE_WIREFRAME_SHADED, IW4::TECHNIQUE_WIREFRAME_SHADED},
				{TECHNIQUE_DEBUG_BUMPMAP, IW4::TECHNIQUE_DEBUG_BUMPMAP},
				{TECHNIQUE_DEBUG_BUMPMAP_INSTANCED, IW4::TECHNIQUE_DEBUG_BUMPMAP_INSTANCED},
			};

			const std::int32_t iw4_fallback_slots[] =
			{
				IW4::TECHNIQUE_EMISSIVE_DFOG,
				IW4::TECHNIQUE_EMISSIVE_SHADOW_DFOG,
				IW4::TECHNIQUE_LIT_DFOG,
				IW4::TECHNIQUE_LIT_SUN_DFOG,
				IW4::TECHNIQUE_LIT_SUN_SHADOW_DFOG,
				IW4::TECHNIQUE_LIT_SPOT_DFOG,
				IW4::TECHNIQUE_LIT_SPOT_SHADOW_DFOG,
				IW4::TECHNIQUE_LIT_OMNI_DFOG,
				IW4::TECHNIQUE_LIT_OMNI_SHADOW_DFOG,
				IW4::TECHNIQUE_LIT_INSTANCED_DFOG,
				IW4::TECHNIQUE_LIT_INSTANCED_SUN_DFOG,
				IW4::TECHNIQUE_LIT_INSTANCED_SUN_SHADOW_DFOG,
				IW4::TECHNIQUE_LIT_INSTANCED_SPOT_DFOG,
				IW4::TECHNIQUE_LIT_INSTANCED_SPOT_SHADOW_DFOG,
				IW4::TECHNIQUE_LIT_INSTANCED_OMNI_DFOG,
				IW4::TECHNIQUE_LIT_INSTANCED_OMNI_SHADOW_DFOG,
			};

			const std::unordered_map<std::uint32_t, std::uint32_t> code_sampler_map =
			{
				{TEXTURE_SRC_CODE_BLACK, IW4::TEXTURE_SRC_CODE_BLACK},
				{TEXTURE_SRC_CODE_WHITE, IW4::TEXTURE_SRC_CODE_WHITE},
				{TEXTURE_SRC_CODE_IDENTITY_NORMAL_MAP, IW4::TEXTURE_SRC_CODE_IDENTITY_NORMAL_MAP},
				{TEXTURE_SRC_CODE_MODEL_LIGHTING, IW4::TEXTURE_SRC_CODE_MODEL_LIGHTING},
				{TEXTURE_SRC_CODE_LIGHTMAP_PRIMARY, IW4::TEXTURE_SRC_CODE_LIGHTMAP_PRIMARY},
				{TEXTURE_SRC_CODE_LIGHTMAP_SECONDARY, IW4::TEXTURE_SRC_CODE_LIGHTMAP_SECONDARY},
				{TEXTURE_SRC_CODE_SHADOWMAP_SUN, IW4::TEXTURE_SRC_CODE_SHADOWMAP_SUN},
				{TEXTURE_SRC_CODE_SHADOWMAP_SPOT, IW4::TEXTURE_SRC_CODE_SHADOWMAP_SPOT},
				{TEXTURE_SRC_CODE_FEEDBACK, IW4::TEXTURE_SRC_CODE_FEEDBACK},
				{TEXTURE_SRC_CODE_RESOLVED_POST_SUN, IW4::TEXTURE_SRC_CODE_RESOLVED_POST_SUN},
				{TEXTURE_SRC_CODE_RESOLVED_SCENE, IW4::TEXTURE_SRC_CODE_RESOLVED_SCENE},
				{TEXTURE_SRC_CODE_POST_EFFECT_SRC, IW4::TEXTURE_SRC_CODE_POST_EFFECT_0},
				{TEXTURE_SRC_CODE_POST_EFFECT_GODRAYS, IW4::TEXTURE_SRC_CODE_POST_EFFECT_1},
				{TEXTURE_SRC_CODE_POST_EFFECT_0, IW4::TEXTURE_SRC_CODE_POST_EFFECT_0},
				{TEXTURE_SRC_CODE_POST_EFFECT_1, IW4::TEXTURE_SRC_CODE_POST_EFFECT_1},
				{TEXTURE_SRC_CODE_LIGHT_ATTENUATION, IW4::TEXTURE_SRC_CODE_LIGHT_ATTENUATION},
				{TEXTURE_SRC_CODE_OUTDOOR, IW4::TEXTURE_SRC_CODE_OUTDOOR},
				{TEXTURE_SRC_CODE_FLOATZ, IW4::TEXTURE_SRC_CODE_FLOATZ},
				{TEXTURE_SRC_CODE_PROCESSED_FLOATZ, IW4::TEXTURE_SRC_CODE_PROCESSED_FLOATZ},
				{TEXTURE_SRC_CODE_RAW_FLOATZ, IW4::TEXTURE_SRC_CODE_RAW_FLOATZ},
				{TEXTURE_SRC_CODE_HALF_PARTICLE_COLOR, IW4::TEXTURE_SRC_CODE_HALF_PARTICLES},
				{TEXTURE_SRC_CODE_HALF_PARTICLE_DEPTH, IW4::TEXTURE_SRC_CODE_HALF_PARTICLES_Z},
			};

			const std::unordered_map<std::int32_t, std::int32_t> code_const_map =
			{
				{CONST_SRC_CODE_LIGHT_POSITION, IW4::CONST_SRC_CODE_LIGHT_POSITION},
				{CONST_SRC_CODE_LIGHT_DIFFUSE, IW4::CONST_SRC_CODE_LIGHT_DIFFUSE},
				{CONST_SRC_CODE_LIGHT_SPECULAR, IW4::CONST_SRC_CODE_LIGHT_SPECULAR},
				{CONST_SRC_CODE_LIGHT_SPOTDIR, IW4::CONST_SRC_CODE_LIGHT_SPOTDIR},
				{CONST_SRC_CODE_LIGHT_SPOTFACTORS, IW4::CONST_SRC_CODE_LIGHT_SPOTFACTORS},
				{CONST_SRC_CODE_NEARPLANE_ORG, IW4::CONST_SRC_CODE_NEARPLANE_ORG},
				{CONST_SRC_CODE_NEARPLANE_DX, IW4::CONST_SRC_CODE_NEARPLANE_DX},
				{CONST_SRC_CODE_NEARPLANE_DY, IW4::CONST_SRC_CODE_NEARPLANE_DY},
				{CONST_SRC_CODE_SHADOWMAP_POLYGON_OFFSET, IW4::CONST_SRC_CODE_SHADOWMAP_POLYGON_OFFSET},
				{CONST_SRC_CODE_RENDER_TARGET_SIZE, IW4::CONST_SRC_CODE_RENDER_TARGET_SIZE},
				{CONST_SRC_CODE_LIGHT_FALLOFF_PLACEMENT, IW4::CONST_SRC_CODE_LIGHT_FALLOFF_PLACEMENT},
				{CONST_SRC_CODE_DOF_EQUATION_VIEWMODEL_AND_FAR_BLUR, IW4::CONST_SRC_CODE_DOF_EQUATION_VIEWMODEL_AND_FAR_BLUR},
				{CONST_SRC_CODE_DOF_EQUATION_SCENE, IW4::CONST_SRC_CODE_DOF_EQUATION_SCENE},
				{CONST_SRC_CODE_DOF_LERP_SCALE, IW4::CONST_SRC_CODE_DOF_LERP_SCALE},
				{CONST_SRC_CODE_DOF_LERP_BIAS, IW4::CONST_SRC_CODE_DOF_LERP_BIAS},
				{CONST_SRC_CODE_DOF_ROW_DELTA, IW4::CONST_SRC_CODE_DOF_ROW_DELTA},
				{CONST_SRC_CODE_PARTICLE_CLOUD_COLOR, IW4::CONST_SRC_CODE_PARTICLE_CLOUD_COLOR},
				{CONST_SRC_CODE_GAMETIME, IW4::CONST_SRC_CODE_GAMETIME},
				{CONST_SRC_CODE_PIXEL_COST_FRACS, IW4::CONST_SRC_CODE_PIXEL_COST_FRACS},
				{CONST_SRC_CODE_PIXEL_COST_DECODE, IW4::CONST_SRC_CODE_PIXEL_COST_DECODE},
				{CONST_SRC_CODE_COLOR_MATRIX_R, IW4::CONST_SRC_CODE_COLOR_MATRIX_R},
				{CONST_SRC_CODE_COLOR_MATRIX_G, IW4::CONST_SRC_CODE_COLOR_MATRIX_G},
				{CONST_SRC_CODE_COLOR_MATRIX_B, IW4::CONST_SRC_CODE_COLOR_MATRIX_B},
				{CONST_SRC_CODE_SHADOWMAP_SWITCH_PARTITION, IW4::CONST_SRC_CODE_SHADOWMAP_SWITCH_PARTITION},
				{CONST_SRC_CODE_SHADOWMAP_SCALE, IW4::CONST_SRC_CODE_SHADOWMAP_SCALE},
				{CONST_SRC_CODE_ZNEAR, IW4::CONST_SRC_CODE_ZNEAR},
				{CONST_SRC_CODE_LIGHTING_LOOKUP_SCALE, IW4::CONST_SRC_CODE_LIGHTING_LOOKUP_SCALE},
				{CONST_SRC_CODE_DEBUG_BUMPMAP, IW4::CONST_SRC_CODE_DEBUG_BUMPMAP},
				{CONST_SRC_CODE_MATERIAL_COLOR, IW4::CONST_SRC_CODE_MATERIAL_COLOR},
				{CONST_SRC_CODE_FOG, IW4::CONST_SRC_CODE_FOG},
				{CONST_SRC_CODE_GLOW_SETUP, IW4::CONST_SRC_CODE_GLOW_SETUP},
				{CONST_SRC_CODE_GLOW_APPLY, IW4::CONST_SRC_CODE_GLOW_APPLY},
				{CONST_SRC_CODE_COLOR_BIAS, IW4::CONST_SRC_CODE_COLOR_BIAS},
				{CONST_SRC_CODE_COLOR_TINT_BASE, IW4::CONST_SRC_CODE_COLOR_TINT_BASE},
				{CONST_SRC_CODE_COLOR_TINT_DELTA, IW4::CONST_SRC_CODE_COLOR_TINT_DELTA},
				{CONST_SRC_CODE_OUTDOOR_FEATHER_PARMS, IW4::CONST_SRC_CODE_OUTDOOR_FEATHER_PARMS},
				{CONST_SRC_CODE_ENVMAP_PARMS, IW4::CONST_SRC_CODE_ENVMAP_PARMS},
				{CONST_SRC_CODE_CLIP_SPACE_LOOKUP_SCALE, IW4::CONST_SRC_CODE_CLIP_SPACE_LOOKUP_SCALE},
				{CONST_SRC_CODE_CLIP_SPACE_LOOKUP_OFFSET, IW4::CONST_SRC_CODE_CLIP_SPACE_LOOKUP_OFFSET},
				{CONST_SRC_CODE_DEPTH_FROM_CLIP, IW4::CONST_SRC_CODE_DEPTH_FROM_CLIP},
				{CONST_SRC_CODE_CODE_MESH_ARG_0, IW4::CONST_SRC_CODE_CODE_MESH_ARG_0},
				{CONST_SRC_CODE_CODE_MESH_ARG_1, IW4::CONST_SRC_CODE_CODE_MESH_ARG_1},
				{CONST_SRC_CODE_BASE_LIGHTING_COORDS, IW4::CONST_SRC_CODE_BASE_LIGHTING_COORDS},
				{CONST_SRC_CODE_POSTFX_FADE_EFFECT, IW4::CONST_SRC_CODE_POSTFX_FADE_EFFECT},
				{CONST_SRC_CODE_VIEWPORT_DIMENSIONS, IW4::CONST_SRC_CODE_VIEWPORT_DIMENSIONS},
				{CONST_SRC_CODE_FRAMEBUFFER_READ, IW4::CONST_SRC_CODE_FRAMEBUFFER_READ},
				{CONST_SRC_CODE_VIEW_MATRIX, IW4::CONST_SRC_CODE_VIEW_MATRIX},
				{CONST_SRC_CODE_INVERSE_VIEW_MATRIX, IW4::CONST_SRC_CODE_INVERSE_VIEW_MATRIX},
				{CONST_SRC_CODE_TRANSPOSE_VIEW_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_VIEW_MATRIX},
				{CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_MATRIX, IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_MATRIX},
				{CONST_SRC_CODE_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_PROJECTION_MATRIX},
				{CONST_SRC_CODE_INVERSE_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_INVERSE_PROJECTION_MATRIX},
				{CONST_SRC_CODE_TRANSPOSE_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_PROJECTION_MATRIX},
				{CONST_SRC_CODE_INVERSE_TRANSPOSE_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_PROJECTION_MATRIX},
				{CONST_SRC_CODE_VIEW_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_VIEW_PROJECTION_MATRIX},
				{CONST_SRC_CODE_INVERSE_VIEW_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_INVERSE_VIEW_PROJECTION_MATRIX},
				{CONST_SRC_CODE_TRANSPOSE_VIEW_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_VIEW_PROJECTION_MATRIX},
				{CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_VIEW_PROJECTION_MATRIX},
				{CONST_SRC_CODE_SHADOW_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_SHADOW_LOOKUP_MATRIX},
				{CONST_SRC_CODE_INVERSE_SHADOW_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_INVERSE_SHADOW_LOOKUP_MATRIX},
				{CONST_SRC_CODE_TRANSPOSE_SHADOW_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_SHADOW_LOOKUP_MATRIX},
				{CONST_SRC_CODE_INVERSE_TRANSPOSE_SHADOW_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_SHADOW_LOOKUP_MATRIX},
				{CONST_SRC_CODE_WORLD_OUTDOOR_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_WORLD_OUTDOOR_LOOKUP_MATRIX},
				{CONST_SRC_CODE_INVERSE_WORLD_OUTDOOR_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_INVERSE_WORLD_OUTDOOR_LOOKUP_MATRIX},
				{CONST_SRC_CODE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX},
				{CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX, IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_OUTDOOR_LOOKUP_MATRIX},
				{CONST_SRC_CODE_FILTER_TAP_0, IW4::CONST_SRC_CODE_FILTER_TAP_0},
				{CONST_SRC_CODE_FILTER_TAP_1, IW4::CONST_SRC_CODE_FILTER_TAP_1},
				{CONST_SRC_CODE_FILTER_TAP_2, IW4::CONST_SRC_CODE_FILTER_TAP_2},
				{CONST_SRC_CODE_FILTER_TAP_3, IW4::CONST_SRC_CODE_FILTER_TAP_3},
				{CONST_SRC_CODE_FILTER_TAP_4, IW4::CONST_SRC_CODE_FILTER_TAP_4},
				{CONST_SRC_CODE_FILTER_TAP_5, IW4::CONST_SRC_CODE_FILTER_TAP_5},
				{CONST_SRC_CODE_FILTER_TAP_6, IW4::CONST_SRC_CODE_FILTER_TAP_6},
				{CONST_SRC_CODE_FILTER_TAP_7, IW4::CONST_SRC_CODE_FILTER_TAP_7},
				{CONST_SRC_CODE_SUN_POSITION, IW4::CONST_SRC_CODE_LIGHT_POSITION},
				{CONST_SRC_CODE_SUN_DIFFUSE, IW4::CONST_SRC_CODE_LIGHT_DIFFUSE},
				{CONST_SRC_CODE_SUN_SPECULAR, IW4::CONST_SRC_CODE_LIGHT_SPECULAR},
				{CONST_SRC_CODE_FOG_COLOR, IW4::CONST_SRC_CODE_FOG_COLOR_LINEAR},
				{CONST_SRC_CODE_PARTICLE_CLOUD_MATRIX, IW4::CONST_SRC_CODE_PARTICLE_CLOUD_MATRIX0},
				{CONST_SRC_CODE_WORLD_MATRIX, IW4::CONST_SRC_CODE_WORLD_MATRIX0},
				{CONST_SRC_CODE_INVERSE_WORLD_MATRIX, IW4::CONST_SRC_CODE_INVERSE_WORLD_MATRIX0},
				{CONST_SRC_CODE_TRANSPOSE_WORLD_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_WORLD_MATRIX0},
				{CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_MATRIX, IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_MATRIX0},
				{CONST_SRC_CODE_WORLD_VIEW_MATRIX, IW4::CONST_SRC_CODE_WORLD_VIEW_MATRIX0},
				{CONST_SRC_CODE_INVERSE_WORLD_VIEW_MATRIX, IW4::CONST_SRC_CODE_INVERSE_WORLD_VIEW_MATRIX0},
				{CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_MATRIX0},
				{CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX, IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX0},
				{CONST_SRC_CODE_WORLD_VIEW_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_WORLD_VIEW_PROJECTION_MATRIX0},
				{CONST_SRC_CODE_INVERSE_WORLD_VIEW_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_INVERSE_WORLD_VIEW_PROJECTION_MATRIX0},
				{CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX0},
				{CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX, IW4::CONST_SRC_CODE_INVERSE_TRANSPOSE_WORLD_VIEW_PROJECTION_MATRIX0},
			};

			std::string generate_name_for_vertex_decl(MaterialVertexDeclaration* vertexDecl)
			{
				auto hash = crc32(0, reinterpret_cast<const Bytef*>(vertexDecl->routing.data),
					sizeof(MaterialStreamRouting) * 16);
				hash = crc32(hash, reinterpret_cast<const Bytef*>(&vertexDecl->streamCount), 1);

				return "t4_vertexdecl_"s + std::to_string(hash);
			}

		}

		IW4::VertexDecl* ITechset::dump_vertex_decl(const std::string& name, MaterialVertexDeclaration* vertex, ZoneMemory* mem)
		{
			auto* asset = mem->Alloc<IW4::VertexDecl>();

			asset->name = mem->StrDup(va("t4/%s", name.data()));
			asset->hasOptionalSource = 0;
			asset->streamCount = vertex->streamCount;

			memset(asset->declarations, 0, sizeof asset->declarations);

			auto kept = 0;
			for (auto i = 0; i < vertex->streamCount && kept < 13; i++)
			{
				const auto source = vertex->routing.data[i].source;
				const auto dest = vertex->routing.data[i].dest;

				if (source >= STREAM_SRC_OPTIONAL_BEGIN || dest > STREAM_DST_TEXCOORD_7)
				{
					static std::unordered_set<std::uint32_t> reported_streams;
					if (reported_streams.insert((source << 8) | dest).second)
					{
						ZONETOOL_WARNING("Vertex stream source %u -> dest %u needs stream 1, which IW4 unbinds for world/static-model draws, dropping it (first seen in %s).",
							source, dest, name.data());
					}
					continue;
				}

				asset->streams[kept].source = source;
				asset->streams[kept].dest = dest;
				kept++;
			}

			asset->streamCount = static_cast<char>(kept);

			if (vertex->streamCount > 13)
			{
				ZONETOOL_ERROR("Vertexdecl %s has more than 13 streams.", name.data());
			}

			IW4::IVertexDecl::dump(asset);

			return asset;
		}

		IW4::VertexShader* ITechset::dump_vertex_shader(MaterialVertexShader* shader, ZoneMemory* mem)
		{
			auto* asset = mem->Alloc<IW4::VertexShader>();

			asset->name = mem->StrDup(va("t4/%s", shader->name));
			asset->shader = shader->prog.vs;
			asset->codeLen = shader->prog.loadDef.programSize;
			asset->bytecode = PDWORD(shader->prog.loadDef.program);

			IW4::IVertexShader::dump(asset);

			return asset;
		}

		IW4::PixelShader* ITechset::dump_pixel_shader(MaterialPixelShader* shader, ZoneMemory* mem)
		{
			auto* asset = mem->Alloc<IW4::PixelShader>();

			asset->name = mem->StrDup(va("t4/%s", shader->name));
			asset->shader = shader->prog.ps;
			asset->codeLen = shader->prog.loadDef.programSize;
			asset->bytecode = PDWORD(shader->prog.loadDef.program);

			IW4::IPixelShader::dump(asset);

			return asset;
		}

		void ITechset::dump_statebits(const std::string& techset, char* statebits)
		{
			char iw4_statebits[48];
			memset(iw4_statebits, 0xFF, sizeof iw4_statebits);

			for (auto i = 0; i < TECHNIQUE_COUNT; i++)
			{
				const auto itr = technique_map.find(i);
				if (itr != technique_map.end())
				{
					iw4_statebits[itr->second] = statebits[i];
				}
			}

			for (auto slot : iw4_fallback_slots)
			{
				if (iw4_statebits[slot] == static_cast<char>(0xFF))
				{
					iw4_statebits[slot] = iw4_statebits[slot - 1];
				}
			}

			IW4::ITechset::dump_statebits(techset, iw4_statebits);
		}

		void ITechset::dump(MaterialTechniqueSet* asset, ZoneMemory* mem)
		{
			if (!asset || !asset->name)
			{
				return;
			}

			auto* iw4_techset = mem->Alloc<IW4::MaterialTechniqueSet>();

			iw4_techset->name = mem->StrDup(va("t4/%s", asset->name));
			iw4_techset->pad = MTL_WORLDVERT_TEX_1_NRM_1;

			unsigned char required_texcoords = 1;
			unsigned char required_normals = 1;

			for (auto i = 0; i < TECHNIQUE_COUNT; i++)
			{
				const auto itr = technique_map.find(i);
				if (itr == technique_map.end() || !asset->techniques[i])
				{
					continue;
				}

				auto* t4_technique = asset->techniques[i];

				const auto size = sizeof(IW4::MaterialTechniqueHeader)
					+ (sizeof(IW4::MaterialPass) * t4_technique->passCount);

				auto* technique = mem->ManualAlloc<IW4::MaterialTechnique>(size);
				memcpy(technique, t4_technique, size);

				iw4_techset->techniques[itr->second] = technique;

				technique->hdr.name = mem->StrDup(va("t4/%s", t4_technique->name));

				if ((technique->hdr.flags & MTL_TECHFLAG_DECL_HAS_OPTIONAL_SOURCE) == MTL_TECHFLAG_DECL_HAS_OPTIONAL_SOURCE)
				{
					technique->hdr.flags &= ~MTL_TECHFLAG_DECL_HAS_OPTIONAL_SOURCE;
					technique->hdr.flags |= 0x40;
				}

				for (auto pass = 0; pass < t4_technique->passCount; pass++)
				{
					auto* t4_pass = &t4_technique->passArray[pass];
					auto* pass_def = &technique->pass[pass];

					if (t4_pass->pixelShader)
					{
						pass_def->pixelShader = dump_pixel_shader(t4_pass->pixelShader, mem);
					}

					if (t4_pass->vertexDecl)
					{
						pass_def->vertexDecl = dump_vertex_decl(
							generate_name_for_vertex_decl(t4_pass->vertexDecl), t4_pass->vertexDecl, mem);

						for (auto stream = 0; stream < t4_pass->vertexDecl->streamCount; stream++)
						{
							switch (t4_pass->vertexDecl->routing.data[stream].source)
							{
							case STREAM_SRC_TEXCOORD_1:
								required_texcoords = max(required_texcoords, 2);
								break;
							case STREAM_SRC_TEXCOORD_2:
								required_texcoords = max(required_texcoords, 3);
								break;
							case STREAM_SRC_NORMAL_TRANSFORM_0:
								required_normals = max(required_normals, 2);
								break;
							case STREAM_SRC_NORMAL_TRANSFORM_1:
								required_normals = max(required_normals, 3);
								break;
							default:
								break;
							}
						}
					}

					if (t4_pass->vertexShader)
					{
						pass_def->vertexShader = dump_vertex_shader(t4_pass->vertexShader, mem);
					}

					const auto arg_count = pass_def->perPrimArgCount + pass_def->perObjArgCount + pass_def->stableArgCount;
					if (arg_count > 0)
					{
						pass_def->argumentDef = mem->Alloc<IW4::ShaderArgumentDef>(arg_count);
						memcpy(pass_def->argumentDef, t4_pass->args, sizeof(IW4::ShaderArgumentDef) * arg_count);
					}

					auto rebound_literal = false;

					for (auto arg = 0; arg < arg_count; arg++)
					{
						auto* arg_def = &pass_def->argumentDef[arg];

						if (arg_def->type == MTL_ARG_CODE_PIXEL_SAMPLER)
						{
							const auto sampler = code_sampler_map.find(arg_def->u.codeSampler);
							if (sampler != code_sampler_map.end())
							{
								arg_def->u.codeSampler = sampler->second;
							}
							else
							{
								static std::unordered_set<std::uint32_t> reported_samplers;
								if (reported_samplers.insert(arg_def->u.codeSampler).second)
								{
									ZONETOOL_WARNING("Code sampler %u has no IW4 equivalent (first seen in techset %s).",
										arg_def->u.codeSampler, asset->name);
								}

								arg_def->u.codeSampler = IW4::TEXTURE_SRC_CODE_BLACK;
							}
						}
						else if (arg_def->type == MTL_ARG_CODE_VERTEX_CONST || arg_def->type == MTL_ARG_CODE_PIXEL_CONST)
						{
							const auto constant = code_const_map.find(arg_def->u.codeConst.index);
							if (constant != code_const_map.end())
							{
								arg_def->u.codeConst.index = static_cast<std::uint16_t>(constant->second);
							}
							else
							{
								static std::unordered_set<std::uint16_t> reported;
								if (reported.insert(arg_def->u.codeConst.index).second)
								{
									ZONETOOL_WARNING("Constant %u has no IW4 equivalent, binding zero literal (first seen in techset %s).",
										arg_def->u.codeConst.index, asset->name);
								}

								arg_def->type = (arg_def->type == MTL_ARG_CODE_VERTEX_CONST)
									? MTL_ARG_LITERAL_VERTEX_CONST
									: MTL_ARG_LITERAL_PIXEL_CONST;
								arg_def->u.literalConst = mem->Alloc<float>(4);
								rebound_literal = true;
							}
						}
					}

					if (rebound_literal)
					{
						auto* group = pass_def->argumentDef;
						for (const auto count : {pass_def->perPrimArgCount, pass_def->perObjArgCount,
							pass_def->stableArgCount})
						{
							std::stable_sort(group, group + count,
								[](const IW4::ShaderArgumentDef& a, const IW4::ShaderArgumentDef& b)
								{
									return a.type < b.type;
								});
							group += count;
						}
					}
				}
			}

			if (required_normals > 1 && required_texcoords < 2)
			{
				required_texcoords = 2;
			}
			if (required_normals > 2 && required_texcoords < 3)
			{
				required_texcoords = 3;
			}

			{
				static const unsigned char world_vert_format_base[6] = {0, 0, 1, 3, 6, 9};
				const auto format = static_cast<unsigned char>(
					world_vert_format_base[required_texcoords] + (required_normals - 1));

				(void)format;
			}

			for (auto slot : iw4_fallback_slots)
			{
				if (!iw4_techset->techniques[slot])
				{
					iw4_techset->techniques[slot] = iw4_techset->techniques[slot - 1];
				}
			}

			IW4::ITechset::dump(iw4_techset);
		}
	}
}
