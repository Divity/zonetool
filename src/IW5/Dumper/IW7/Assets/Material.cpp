#include "stdafx.hpp"
#include <unordered_set>

#include "Converter/IW7/Assets/IwiImage.hpp"
#include "Converter/IW7/Assets/PackedImage.hpp"
#include "IW7/Assets/GfxImage.hpp"
#include "Material.hpp"
#include "GfxImage.hpp"

//#include "IW7/Assets/Material.hpp"

// r0 - replace
// c0 - color map
// n0 - normal map
// s0 - specular map
// p0 - parallax
// a0 - Add
// b0 - Blend
// d0 - Detail
// t0 - transparent ? (means that its replace + alpha test >= 128 meaning either full / no transparency per pixel)
// q0 - (don't know the word, it's a detail map for normals)
// 
// _ct_ = colorTint

namespace ZoneTool
{
	namespace IW7
	{
		enum techset_map_type_e
		{
			regular,
			color_tint,
			//
			packed,
			packed_alpha,
			count,
		};

		struct techset_map_s
		{
			std::string techset[techset_map_type_e::count];
		};

		techset_map_s make_techset_map(const std::string& regular, const std::string& color_tint = {},
			const std::string& packed = {}, const std::string& packed_alpha = {})
		{
			techset_map_s map;
			map.techset[techset_map_type_e::regular] = regular;
			map.techset[techset_map_type_e::color_tint] = color_tint;
			map.techset[techset_map_type_e::packed] = packed;
			map.techset[techset_map_type_e::packed_alpha] = packed_alpha;
			return map;
		}

		std::unordered_map<std::string, techset_map_s> mapped_techsets =
		{
			//
			//
			//

			{"mc_ambient_r0c0",             {"mo_l_sm_replace_i0c0"}},
			{"mc_ambient_t0c0",             {"mo_l_sm_atest_i0c0"}},
			{"mc_l_b0c0",                   {"mo_l_sm_ndw_blend_i0c0"}},
			{"mc_l_b0c0d0",                 {"mo_l_sm_ndw_blend_i0c0"}},
			{"mc_l_b0c0d0n0",               {"mo_l_sm_ndw_blend_i0c0n0"}},
			{"mc_l_b0c0d0n0s0",             {"mo_l_sm_ndw_blend_i0c0s0n0", "", "", "mo_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"mc_l_b0c0d0s0",               {"mo_l_sm_ndw_blend_i0c0s0"}},
			{"mc_l_b0c0n0",                 {"mo_l_sm_ndw_blend_i0c0n0"}},
			{"mc_l_b0c0n0s0",               {"mo_l_sm_ndw_blend_i0c0s0n0", "", "", "mo_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"mc_l_b0c0s0",                 {"mo_l_sm_ndw_blend_i0c0s0"}},
			{"mc_l_flag_t0c0",              {"mo_l_sm_atest_i0c0"}},
			{"mc_l_flag_t0c0n0",            {"mo_l_sm_atest_i0c0n0"}},
			{"mc_l_flag_t0c0n0s0",          {"mo_l_sm_atest_i0c0s0n0", "", "", "mo_l_sm_atest_i0c0s0n0pa0"}},
			{"mc_l_flag_t0c0s0",            {"mo_l_sm_atest_i0c0s0"}},
			{"mc_l_r0c0",                   {"mo_l_sm_replace_i0c0"}},
			{"mc_l_r0c0d0",                 {"mo_l_sm_replace_i0c0"}},
			{"mc_l_r0c0d0n0",               {"mo_l_sm_replace_i0c0n0d0"}},
			{"mc_l_r0c0d0n0s0",             {"mo_l_sm_replace_i0c0s0n0d0", "", "mo_l_sm_replace_i0c0s0n0d0p0"}},
			{"mc_l_r0c0d0s0",               {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_r0c0n0",                 {"mo_l_sm_replace_i0c0n0"}},
			{"mc_l_r0c0n0s0",               {"mo_l_sm_replace_i0c0s0n0", "", "mo_l_sm_replace_i0c0s0n0p0"}},
			{"mc_l_r0c0s0",                 {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_scroll_b0c0",            {"mo_l_sm_ndw_blend_i0c0"}},
			{"mc_l_scroll_b0c0d0",          {"mo_l_sm_ndw_blend_i0c0"}},
			{"mc_l_scroll_b0c0d0n0",        {"mo_l_sm_ndw_blend_i0c0n0"}},
			{"mc_l_scroll_b0c0d0n0s0",      {"mo_l_sm_ndw_blend_i0c0s0n0", "", "", "mo_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"mc_l_scroll_b0c0d0s0",        {"mo_l_sm_ndw_blend_i0c0s0"}},
			{"mc_l_scroll_b0c0n0",          {"mo_l_sm_ndw_blend_i0c0n0"}},
			{"mc_l_scroll_b0c0n0s0",        {"mo_l_sm_ndw_blend_i0c0s0n0", "", "", "mo_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"mc_l_scroll_b0c0s0",          {"mo_l_sm_ndw_blend_i0c0s0"}},
			{"mc_l_scroll_r0c0",            {"mo_l_sm_replace_i0c0"}},
			{"mc_l_scroll_r0c0d0",          {"mo_l_sm_replace_i0c0"}},
			{"mc_l_scroll_r0c0d0n0",        {"mo_l_sm_replace_i0c0n0d0"}},
			{"mc_l_scroll_r0c0d0n0s0",      {"mo_l_sm_replace_i0c0s0n0d0", "", "mo_l_sm_replace_i0c0s0n0d0p0"}},
			{"mc_l_scroll_r0c0d0s0",        {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_scroll_r0c0n0",          {"mo_l_sm_replace_i0c0n0"}},
			{"mc_l_scroll_r0c0n0s0",        {"mo_l_sm_replace_i0c0s0n0", "", "mo_l_sm_replace_i0c0s0n0p0"}},
			{"mc_l_scroll_r0c0s0",          {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_scroll_t0c0",            {"mo_l_sm_atest_i0c0"}},
			{"mc_l_scroll_t0c0d0",          {"mo_l_sm_atest_i0c0"}},
			{"mc_l_scroll_t0c0d0n0",        {"mo_l_sm_atest_i0c0n0"}},
			{"mc_l_scroll_t0c0d0n0s0",      {"mo_l_sm_atest_i0c0s0n0", "", "", "mo_l_sm_atest_i0c0s0n0pa0"}},
			{"mc_l_scroll_t0c0d0s0",        {"mo_l_sm_atest_i0c0s0"}},
			{"mc_l_scroll_t0c0n0",          {"mo_l_sm_atest_i0c0n0"}},
			{"mc_l_scroll_t0c0n0s0",        {"mo_l_sm_atest_i0c0s0n0", "", "", "mo_l_sm_atest_i0c0s0n0pa0"}},
			{"mc_l_scroll_t0c0s0",          {"mo_l_sm_atest_i0c0s0"}},
			{"mc_l_skin_r0c0",              {"mo_l_sm_replace_i0c0"}},
			{"mc_l_skin_r0c0d0",            {"mo_l_sm_replace_i0c0"}},
			{"mc_l_skin_r0c0d0n0",          {"mo_l_sm_replace_i0c0n0d0"}},
			{"mc_l_skin_r0c0d0n0s0",        {"mo_l_sm_replace_i0c0s0n0d0", "", "mo_l_sm_replace_i0c0s0n0d0p0"}},
			{"mc_l_skin_r0c0d0s0",          {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_skin_r0c0n0",            {"mo_l_sm_replace_i0c0n0"}},
			{"mc_l_skin_r0c0n0s0",          {"mo_l_sm_replace_i0c0s0n0", "", "mo_l_sm_replace_i0c0s0n0p0"}},
			{"mc_l_skin_r0c0s0",            {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_sm_b0c0",                {"mo_l_sm_ndw_blend_i0c0"}},
			{"mc_l_sm_b0c0d0",              {"mo_l_sm_ndw_blend_i0c0"}},
			{"mc_l_sm_b0c0d0n0",            {"mo_l_sm_ndw_blend_i0c0n0"}},
			{"mc_l_sm_b0c0d0n0s0",          {"mo_l_sm_ndw_blend_i0c0s0n0", "", "", "mo_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"mc_l_sm_b0c0d0s0",            {"mo_l_sm_ndw_blend_i0c0s0"}},
			{"mc_l_sm_b0c0n0",              {"mo_l_sm_ndw_blend_i0c0n0"}},
			{"mc_l_sm_b0c0n0s0",            {"mo_l_sm_ndw_blend_i0c0s0n0", "", "", "mo_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"mc_l_sm_b0c0n0s0p0",          {"mo_l_sm_ndw_blend_i0c0s0n0", "", "", "mo_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"mc_l_sm_b0c0p0",              {"mo_l_sm_ndw_blend_i0c0"}},
			{"mc_l_sm_b0c0s0",              {"mo_l_sm_ndw_blend_i0c0s0"}},
			{"mc_l_sm_flag_t0c0",           {"mo_l_sm_atest_i0c0"}},
			{"mc_l_sm_flag_t0c0n0",         {"mo_l_sm_atest_i0c0n0"}},
			{"mc_l_sm_flag_t0c0n0s0",       {"mo_l_sm_atest_i0c0s0n0", "", "", "mo_l_sm_atest_i0c0s0n0pa0"}},
			{"mc_l_sm_flag_t0c0s0",         {"mo_l_sm_atest_i0c0s0"}},
			{"mc_l_sm_r0c0",                {"mo_l_sm_replace_i0c0"}},
			{"mc_l_sm_r0c0d0",              {"mo_l_sm_replace_i0c0"}},
			{"mc_l_sm_r0c0d0n0",            {"mo_l_sm_replace_i0c0n0d0"}},
			{"mc_l_sm_r0c0d0n0s0",          {"mo_l_sm_replace_i0c0s0n0d0", "", "mo_l_sm_replace_i0c0s0n0d0p0"}},
			{"mc_l_sm_r0c0d0s0",            {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_sm_r0c0n0",              {"mo_l_sm_replace_i0c0n0"}},
			{"mc_l_sm_r0c0n0s0",            {"mo_l_sm_replace_i0c0s0n0", "", "mo_l_sm_replace_i0c0s0n0p0"}},
			{"mc_l_sm_r0c0n0s0p0",          {"mo_l_sm_replace_i0c0s0n0", "", "mo_l_sm_replace_i0c0s0n0p0"}},
			{"mc_l_sm_r0c0s0",              {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_sm_r0c0s0p0",            {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_sm_scroll_b0c0",         {"mo_l_sm_ndw_blend_i0c0"}},
			{"mc_l_sm_scroll_b0c0d0",       {"mo_l_sm_ndw_blend_i0c0"}},
			{"mc_l_sm_scroll_b0c0d0n0",     {"mo_l_sm_ndw_blend_i0c0n0"}},
			{"mc_l_sm_scroll_b0c0d0n0s0",   {"mo_l_sm_ndw_blend_i0c0s0n0", "", "", "mo_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"mc_l_sm_scroll_b0c0d0s0",     {"mo_l_sm_ndw_blend_i0c0s0"}},
			{"mc_l_sm_scroll_b0c0n0",       {"mo_l_sm_ndw_blend_i0c0n0"}},
			{"mc_l_sm_scroll_b0c0n0s0",     {"mo_l_sm_ndw_blend_i0c0s0n0", "", "", "mo_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"mc_l_sm_scroll_b0c0s0",       {"mo_l_sm_ndw_blend_i0c0s0"}},
			{"mc_l_sm_scroll_r0c0",         {"mo_l_sm_replace_i0c0"}},
			{"mc_l_sm_scroll_r0c0d0",       {"mo_l_sm_replace_i0c0"}},
			{"mc_l_sm_scroll_r0c0d0n0",     {"mo_l_sm_replace_i0c0n0d0"}},
			{"mc_l_sm_scroll_r0c0d0n0s0",   {"mo_l_sm_replace_i0c0s0n0d0", "", "mo_l_sm_replace_i0c0s0n0d0p0"}},
			{"mc_l_sm_scroll_r0c0d0s0",     {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_sm_scroll_r0c0n0",       {"mo_l_sm_replace_i0c0n0"}},
			{"mc_l_sm_scroll_r0c0n0s0",     {"mo_l_sm_replace_i0c0s0n0", "", "mo_l_sm_replace_i0c0s0n0p0"}},
			{"mc_l_sm_scroll_r0c0s0",       {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_sm_scroll_t0c0",         {"mo_l_sm_atest_i0c0"}},
			{"mc_l_sm_scroll_t0c0d0",       {"mo_l_sm_atest_i0c0"}},
			{"mc_l_sm_scroll_t0c0d0n0",     {"mo_l_sm_atest_i0c0n0"}},
			{"mc_l_sm_scroll_t0c0d0n0s0",   {"mo_l_sm_atest_i0c0s0n0", "", "", "mo_l_sm_atest_i0c0s0n0pa0"}},
			{"mc_l_sm_scroll_t0c0d0s0",     {"mo_l_sm_atest_i0c0s0"}},
			{"mc_l_sm_scroll_t0c0n0",       {"mo_l_sm_atest_i0c0n0"}},
			{"mc_l_sm_scroll_t0c0n0s0",     {"mo_l_sm_atest_i0c0s0n0", "", "", "mo_l_sm_atest_i0c0s0n0pa0"}},
			{"mc_l_sm_scroll_t0c0s0",       {"mo_l_sm_atest_i0c0s0"}},
			{"mc_l_sm_skin_r0c0",           {"mo_l_sm_replace_i0c0"}},
			{"mc_l_sm_skin_r0c0d0",         {"mo_l_sm_replace_i0c0"}},
			{"mc_l_sm_skin_r0c0d0n0",       {"mo_l_sm_replace_i0c0n0d0"}},
			{"mc_l_sm_skin_r0c0d0n0s0",     {"mo_l_sm_replace_i0c0s0n0d0", "", "mo_l_sm_replace_i0c0s0n0d0p0"}},
			{"mc_l_sm_skin_r0c0d0s0",       {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_sm_skin_r0c0n0",         {"mo_l_sm_replace_i0c0n0"}},
			{"mc_l_sm_skin_r0c0n0s0",       {"mo_l_sm_replace_i0c0s0n0", "", "mo_l_sm_replace_i0c0s0n0p0"}},
			{"mc_l_sm_skin_r0c0s0",         {"mo_l_sm_replace_i0c0s0"}},
			{"mc_l_sm_t0c0",                {"mo_l_sm_atest_i0c0"}},
			{"mc_l_sm_t0c0d0",              {"mo_l_sm_atest_i0c0"}},
			{"mc_l_sm_t0c0d0n0",            {"mo_l_sm_atest_i0c0n0"}},
			{"mc_l_sm_t0c0d0n0s0",          {"mo_l_sm_atest_i0c0s0n0", "", "", "mo_l_sm_atest_i0c0s0n0pa0"}},
			{"mc_l_sm_t0c0d0s0",            {"mo_l_sm_atest_i0c0s0"}},
			{"mc_l_sm_t0c0n0",              {"mo_l_sm_atest_i0c0n0"}},
			{"mc_l_sm_t0c0n0s0",            {"mo_l_sm_atest_i0c0s0n0", "", "", "mo_l_sm_atest_i0c0s0n0pa0"}},
			{"mc_l_sm_t0c0s0",              {"mo_l_sm_atest_i0c0s0"}},
			{"mc_l_t0c0",                   {"mo_l_sm_atest_i0c0"}},
			{"mc_l_t0c0d0",                 {"mo_l_sm_atest_i0c0"}},
			{"mc_l_t0c0d0n0",               {"mo_l_sm_atest_i0c0n0"}},
			{"mc_l_t0c0d0n0s0",             {"mo_l_sm_atest_i0c0s0n0", "", "", "mo_l_sm_atest_i0c0s0n0pa0"}},
			{"mc_l_t0c0d0s0",               {"mo_l_sm_atest_i0c0s0"}},
			{"mc_l_t0c0n0",                 {"mo_l_sm_atest_i0c0n0"}},
			{"mc_l_t0c0n0s0",               {"mo_l_sm_atest_i0c0s0n0", "", "", "mo_l_sm_atest_i0c0s0n0pa0"}},
			{"mc_l_t0c0s0",                 {"mo_l_sm_atest_i0c0s0"}},
			{"wc_ambient_r0c0",             {"wc_l_sm_replace_i0c0"}},
			{"wc_ambient_t0c0",             {"wc_l_sm_atest_i0c0"}},
			{"wc_l_b0c0",                   {"wc_l_sm_ndw_blend_i0c0"}},
			{"wc_l_b0c0d0",                 {"wc_l_sm_ndw_blend_i0c0"}},
			{"wc_l_b0c0d0n0",               {"wc_l_sm_ndw_blend_i0c0n0"}},
			{"wc_l_b0c0d0n0s0",             {"wc_l_sm_ndw_blend_i0c0s0n0", "", "", "wc_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"wc_l_b0c0d0s0",               {"wc_l_sm_ndw_blend_i0c0s0"}},
			{"wc_l_b0c0n0",                 {"wc_l_sm_ndw_blend_i0c0n0"}},
			{"wc_l_b0c0n0s0",               {"wc_l_sm_ndw_blend_i0c0s0n0", "", "", "wc_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"wc_l_b0c0s0",                 {"wc_l_sm_ndw_blend_i0c0s0"}},
			{"wc_l_flag_t0c0",              {"wc_l_sm_atest_i0c0"}},
			{"wc_l_flag_t0c0n0",            {"wc_l_sm_atest_i0c0"}},
			{"wc_l_flag_t0c0n0s0",          {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_flag_t0c0s0",            {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_r0c0",                   {"wc_l_sm_replace_i0c0"}},
			{"wc_l_r0c0d0",                 {"wc_l_sm_replace_i0c0"}},
			{"wc_l_r0c0d0n0",               {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_r0c0d0n0s0",             {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_r0c0d0s0",               {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_r0c0n0",                 {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_r0c0n0s0",               {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_r0c0s0",                 {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_scroll_b0c0",            {"wc_l_sm_ndw_blend_i0c0"}},
			{"wc_l_scroll_b0c0d0",          {"wc_l_sm_ndw_blend_i0c0"}},
			{"wc_l_scroll_b0c0d0n0",        {"wc_l_sm_ndw_blend_i0c0n0"}},
			{"wc_l_scroll_b0c0d0n0s0",      {"wc_l_sm_ndw_blend_i0c0s0n0", "", "", "wc_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"wc_l_scroll_b0c0d0s0",        {"wc_l_sm_ndw_blend_i0c0s0"}},
			{"wc_l_scroll_b0c0n0",          {"wc_l_sm_ndw_blend_i0c0n0"}},
			{"wc_l_scroll_b0c0n0s0",        {"wc_l_sm_ndw_blend_i0c0s0n0", "", "", "wc_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"wc_l_scroll_b0c0s0",          {"wc_l_sm_ndw_blend_i0c0s0"}},
			{"wc_l_scroll_r0c0",            {"wc_l_sm_replace_i0c0"}},
			{"wc_l_scroll_r0c0d0",          {"wc_l_sm_replace_i0c0"}},
			{"wc_l_scroll_r0c0d0n0",        {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_scroll_r0c0d0n0s0",      {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_scroll_r0c0d0s0",        {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_scroll_r0c0n0",          {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_scroll_r0c0n0s0",        {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_scroll_r0c0s0",          {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_scroll_t0c0",            {"wc_l_sm_atest_i0c0"}},
			{"wc_l_scroll_t0c0d0",          {"wc_l_sm_atest_i0c0"}},
			{"wc_l_scroll_t0c0d0n0",        {"wc_l_sm_atest_i0c0"}},
			{"wc_l_scroll_t0c0d0n0s0",      {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_scroll_t0c0d0s0",        {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_scroll_t0c0n0",          {"wc_l_sm_atest_i0c0"}},
			{"wc_l_scroll_t0c0n0s0",        {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_scroll_t0c0s0",          {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_skin_r0c0",              {"wc_l_sm_replace_i0c0"}},
			{"wc_l_skin_r0c0d0",            {"wc_l_sm_replace_i0c0"}},
			{"wc_l_skin_r0c0d0n0",          {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_skin_r0c0d0n0s0",        {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_skin_r0c0d0s0",          {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_skin_r0c0n0",            {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_skin_r0c0n0s0",          {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_skin_r0c0s0",            {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_sm_b0c0",                {"wc_l_sm_ndw_blend_i0c0"}},
			{"wc_l_sm_b0c0d0",              {"wc_l_sm_ndw_blend_i0c0"}},
			{"wc_l_sm_b0c0d0n0",            {"wc_l_sm_ndw_blend_i0c0n0"}},
			{"wc_l_sm_b0c0d0n0s0",          {"wc_l_sm_ndw_blend_i0c0s0n0", "", "", "wc_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"wc_l_sm_b0c0d0s0",            {"wc_l_sm_ndw_blend_i0c0s0"}},
			{"wc_l_sm_b0c0n0",              {"wc_l_sm_ndw_blend_i0c0n0"}},
			{"wc_l_sm_b0c0n0s0",            {"wc_l_sm_ndw_blend_i0c0s0n0", "", "", "wc_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"wc_l_sm_b0c0s0",              {"wc_l_sm_ndw_blend_i0c0s0"}},
			{"wc_l_sm_flag_t0c0",           {"wc_l_sm_atest_i0c0"}},
			{"wc_l_sm_flag_t0c0n0",         {"wc_l_sm_atest_i0c0"}},
			{"wc_l_sm_flag_t0c0n0s0",       {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_sm_flag_t0c0s0",         {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_sm_r0c0",                {"wc_l_sm_replace_i0c0"}},
			{"wc_l_sm_r0c0d0",              {"wc_l_sm_replace_i0c0"}},
			{"wc_l_sm_r0c0d0n0",            {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_sm_r0c0d0n0s0",          {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_sm_r0c0d0s0",            {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_sm_r0c0n0",              {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_sm_r0c0n0s0",            {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_sm_r0c0s0",              {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_sm_scroll_b0c0",         {"wc_l_sm_ndw_blend_i0c0"}},
			{"wc_l_sm_scroll_b0c0d0",       {"wc_l_sm_ndw_blend_i0c0"}},
			{"wc_l_sm_scroll_b0c0d0n0",     {"wc_l_sm_ndw_blend_i0c0n0"}},
			{"wc_l_sm_scroll_b0c0d0n0s0",   {"wc_l_sm_ndw_blend_i0c0s0n0", "", "", "wc_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"wc_l_sm_scroll_b0c0d0s0",     {"wc_l_sm_ndw_blend_i0c0s0"}},
			{"wc_l_sm_scroll_b0c0n0",       {"wc_l_sm_ndw_blend_i0c0n0"}},
			{"wc_l_sm_scroll_b0c0n0s0",     {"wc_l_sm_ndw_blend_i0c0s0n0", "", "", "wc_l_sm_ndw_blend_i0c0s0n0pa0"}},
			{"wc_l_sm_scroll_b0c0s0",       {"wc_l_sm_ndw_blend_i0c0s0"}},
			{"wc_l_sm_scroll_r0c0",         {"wc_l_sm_replace_i0c0"}},
			{"wc_l_sm_scroll_r0c0d0",       {"wc_l_sm_replace_i0c0"}},
			{"wc_l_sm_scroll_r0c0d0n0",     {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_sm_scroll_r0c0d0n0s0",   {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_sm_scroll_r0c0d0s0",     {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_sm_scroll_r0c0n0",       {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_sm_scroll_r0c0n0s0",     {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_sm_scroll_r0c0s0",       {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_sm_scroll_t0c0",         {"wc_l_sm_atest_i0c0"}},
			{"wc_l_sm_scroll_t0c0d0",       {"wc_l_sm_atest_i0c0"}},
			{"wc_l_sm_scroll_t0c0d0n0",     {"wc_l_sm_atest_i0c0"}},
			{"wc_l_sm_scroll_t0c0d0n0s0",   {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_sm_scroll_t0c0d0s0",     {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_sm_scroll_t0c0n0",       {"wc_l_sm_atest_i0c0"}},
			{"wc_l_sm_scroll_t0c0n0s0",     {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_sm_scroll_t0c0s0",       {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_sm_skin_r0c0",           {"wc_l_sm_replace_i0c0"}},
			{"wc_l_sm_skin_r0c0d0",         {"wc_l_sm_replace_i0c0"}},
			{"wc_l_sm_skin_r0c0d0n0",       {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_sm_skin_r0c0d0n0s0",     {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_sm_skin_r0c0d0s0",       {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_sm_skin_r0c0n0",         {"wc_l_sm_replace_i0c0n0"}},
			{"wc_l_sm_skin_r0c0n0s0",       {"wc_l_sm_replace_i0c0s0n0", "", "wc_l_sm_replace_i0c0s0n0p0"}},
			{"wc_l_sm_skin_r0c0s0",         {"wc_l_sm_replace_i0c0s0"}},
			{"wc_l_sm_t0c0",                {"wc_l_sm_atest_i0c0"}},
			{"wc_l_sm_t0c0d0",              {"wc_l_sm_atest_i0c0"}},
			{"wc_l_sm_t0c0d0n0",            {"wc_l_sm_atest_i0c0"}},
			{"wc_l_sm_t0c0d0n0s0",          {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_sm_t0c0d0s0",            {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_sm_t0c0n0",              {"wc_l_sm_atest_i0c0"}},
			{"wc_l_sm_t0c0n0s0",            {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_sm_t0c0s0",              {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_t0c0",                   {"wc_l_sm_atest_i0c0"}},
			{"wc_l_t0c0d0",                 {"wc_l_sm_atest_i0c0"}},
			{"wc_l_t0c0d0n0",               {"wc_l_sm_atest_i0c0"}},
			{"wc_l_t0c0d0n0s0",             {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_t0c0d0s0",               {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_t0c0n0",                 {"wc_l_sm_atest_i0c0"}},
			{"wc_l_t0c0n0s0",               {"wc_l_sm_atest_i0c0s0"}},
			{"wc_l_t0c0s0",                 {"wc_l_sm_atest_i0c0s0"}},
			//
			{"mc_effect_falloff_add_nofog",				make_techset_map("eq_effect_falloff_add_lin_nofog_ndw_nocast")},
			{"mc_effect_zfeather_falloff_add_nofog",	make_techset_map("eq_effect_zfeather_falloff_add_lin_nofog_ndw_nocast")},
			{"mc_effect_zfeather_falloff_add_nofog_eyeoffset",	make_techset_map("eq_effect_zfeather_falloff_add_lin_nofog_eyeoffset_ndw_nocast")},
			
			{"mc_unlit",								make_techset_map("mo_unlit_replace_lin", "mo_unlit_replace_lin_ct")},
			{"mc_unlit_replace",						make_techset_map("mo_unlit_replace_lin", "mo_unlit_replace_lin_ct")},
			{"mc_unlit_alphatest",						make_techset_map("mo_unlit_atest_lin_ct", "mo_unlit_atest_lin_ct")},
			
			{"wc_unlit_add",							make_techset_map("w_unlit_add_lin_ndw", "w_unlit_add_lin_ct_ndw")},
			{"wc_unlit_multiply",						make_techset_map("w_unlit_multiply_lin_ndw")},
			{"wc_unlit_falloff_add",					make_techset_map("w_unlit_falloff_add_lin_ndw")},

			{"mc_shadowcaster",							make_techset_map("m_shadowcaster")},
			{"mc_shadowcaster_atest",					make_techset_map("m_shadowcaster")},
			{"wc_shadowcaster",							make_techset_map("w_shadowcaster")},

			{"distortion_scale_zfeather",				make_techset_map("eq_distortion_scale_zfeather")},

			{"wc_sky",									make_techset_map("w_sky")},

			{"2d",										make_techset_map("2d", "2d|_ct")},

			{"effect",									make_techset_map("eq_effect_blend_lin_ndw_nocast")},
			{"effect_nofog",							make_techset_map("eq_effect_blend_lin_nofog_ndw_nocast")},
			{"effect_zfeather_add",						make_techset_map("eq_effect_zfeather_add_lin_ct_ndw_nocast")},
			{"effect_zfeather_add_nofog_eyeoffset",		make_techset_map("eq_effect_zfeather_add_lin_nofog_eyeoffset_ndw_nocast")},
			{"effect_zfeather_add_nofog",				make_techset_map("eq_effect_zfeather_add_lin_nofog_ndw_nocast")},

			{"distortion_scale",						make_techset_map("eq_distortion_scale")},

			//

			{"mc_unlit_add",							make_techset_map("mo_unlit_add_lin_ndw", "mo_unlit_add_lin_ct_ndw")},
			{"mc_unlit_blend",							make_techset_map("mo_unlit_blend_lin_ndw", "mo_unlit_blend_lin_ct_ndw")},
			{"mc_unlit_screen",							make_techset_map("mo_unlit_add_lin_ndw", "mo_unlit_add_lin_ct_ndw")},
			{"mc_unlit_falloff_blend",					make_techset_map("mo_unlit_blend_lin_ndw", "mo_unlit_blend_lin_ct_ndw")},

			{"wc_unlit_blend",							make_techset_map("w_unlit_blend_lin_ndw", "w_unlit_blend_lin_ct_ndw")},
			{"wc_unlit_replace",						make_techset_map("w_unlit_replace_lin", "w_unlit_replace_lin_ct")},
			{"wc_unlit_screen",							make_techset_map("w_unlit_add_lin_ndw", "w_unlit_add_lin_ct_ndw")},
			{"wc_unlit_falloff_blend",					make_techset_map("w_unlit_blend_lin_ndw", "w_unlit_blend_lin_ct_ndw")},
			{"wc_unlit_distfalloff_replace",			make_techset_map("w_unlit_replace_lin", "w_unlit_replace_lin_ct")},

			{"mc_objective",							make_techset_map("mo_unlit_add_lin_ndw_custom_objective")},

			{"mc_tools",								make_techset_map("mo_tools_r0c0")},
			{"wc_tools",								make_techset_map("wc_tools_r0c0")},
			{"wc_default",								make_techset_map("w_default")},

			{"wc_l_a0c0",								make_techset_map("w_l_ndw_add_i0c0_nocast")},

			{"m_l_b0c0n0s0",							make_techset_map("m_l_sm_ndw_blend_i0c0s0n0")},

			{"mc_effect_blend_nofog",					make_techset_map("eq_effect_blend_lin_nofog_ndw_nocast")},
			{"mc_effect_falloff_add_lin_nofog",			make_techset_map("eq_effect_falloff_add_lin_nofog_ndw_nocast")},
			{"mc_effect_zfeather_falloff_add_lin_nofog_eyeoffset",
														make_techset_map("eq_effect_zfeather_falloff_add_lin_nofog_eyeoffset_ndw_nocast")},
			{"mc_effect_zfeather_falloff_screen_nofog_eyeoffset",
														make_techset_map("eq_effect_zfeather_add_lin_nofog_eyeoffset_ndw_nocast")},

			{"zfeather_play",							make_techset_map("eq_effect_zfeather_blend_lin_ndw_nocast")},
		};

		std::unordered_map<std::string, techset_map_s> mapped_techsets_effect_vertlit =
		{
			{"effect",									make_techset_map("ev_effect_blend_lin_ct_ndw_nocast")},
		};

		enum MaterialType : std::uint8_t
		{
			MTL_TYPE_DEFAULT = 0x0, // ""
			MTL_TYPE_MODEL = 1, // "m"
			MLT_TYPE_MODEL_UNK2 = 2,
			MTL_TYPE_MODEL_UNK3 = 3,
			MTL_TYPE_MODEL_UNK4 = 4,
			MTL_TYPE_MODEL_UNK5 = 5,
			MTL_TYPE_MODEL_UNK6 = 6,
			MTL_TYPE_MODEL_UNK7 = 7,
			MTL_TYPE_MODEL_UNK8 = 8,
			MTL_TYPE_MODEL_UNK9 = 9,
			MTL_TYPE_MODEL_UNK10 = 10,
			MTL_TYPE_MODEL_UNK11 = 11,
			MTL_TYPE_MODEL_UNK12 = 12,
			MTL_TYPE_MODEL_UNK13 = 13,
			MTL_TYPE_MODEL_UNK14 = 14,
			MTL_TYPE_MODEL_UNK15 = 15,
			MTL_TYPE_MODEL_LMAP = 16, // "ml"
			MTL_TYPE_MODEL_LMAP_VERTCOL = 17, // "mlc"
			MTL_TYPE_MODEL_UNK18 = 18,
			MTL_TYPE_MODEL_UNK19 = 19,
			MTL_TYPE_MODEL_UNK20 = 20,
			MTL_TYPE_MODEL_UNK21 = 21,
			MTL_TYPE_MODEL_IMPACT = 22, // "mim"
			MTL_TYPE_MODEL_SELFVIS = 23, // "mo"
			MTL_TYPE_MODEL_VERTCOL_SELFVIS = 24, // "mco"
			MTL_TYPE_MODEL_UNK25 = 25, // "mvo"
			MTL_TYPE_MODEL_UNK26 = 26, // "mvco"
			MTL_TYPE_MODEL_UNK27 = 27,
			MTL_TYPE_MODEL_SECONDUV_SELFVIS = 28, // "m2o"
			MTL_TYPE_MODEL_SECONDUV_VERTCOL_SELFVIS = 29, // "m2co"
			MTL_TYPE_MODEL_UNK30 = 30, // "mop"
			MTL_TYPE_MODEL_UNK31 = 31, // "m2op"
			MTL_TYPE_MODEL_UNK32 = 32,
			MTL_TYPE_MODEL_UNK33 = 33,
			MTL_TYPE_MODEL_UNK34 = 34,
			MTL_TYPE_MODEL_UNK35 = 35,
			MTL_TYPE_MODEL_UNK36 = 36,
			MTL_TYPE_MODEL_UNK37 = 37, // "mopw"
			MTL_TYPE_MODEL_UNK38 = 38, // "m2opw"
			MTL_TYPE_MODEL_UNK39 = 39, // "m2copw"
			MTL_TYPE_MODEL_UNK40 = 40, // "mcopw"
			MTL_TYPE_MODEL_UNK41 = 41, // "mvopw"
			MTL_TYPE_MODEL_UNK42 = 42,
			MTL_TYPE_MODEL_UNK43 = 43,
			MTL_TYPE_MODEL_SUBDIV = 44, // "ms"
			MTL_TYPE_MODEL_UNK45 = 45,
			MTL_TYPE_MODEL_UNK46 = 46,
			MTL_TYPE_MODEL_UNK47 = 47, // "msa"
			MTL_TYPE_MODEL_UNK48 = 48,
			MTL_TYPE_MODEL_UNK49 = 49,
			MTL_TYPE_MODEL_UNK50 = 50,
			MTL_TYPE_MODEL_UNK51 = 51,
			MTL_TYPE_MODEL_UNK52 = 52,
			MTL_TYPE_MODEL_SUBDIV_VERTCOL_SELFVIS = 53, // "msco"
			MTL_TYPE_MODEL_UNK54 = 54, // "mszo"
			MTL_TYPE_MODEL_UNK55 = 55, // "msvo"
			MTL_TYPE_MODEL_UNK56 = 56, // "msvco"
			MTL_TYPE_MODEL_SUBDIV_SELFVIS = 57, // "mso"
			MTL_TYPE_MODEL_UNK58 = 58, // "msop"
			MTL_TYPE_MODEL_UNK59 = 59,
			MTL_TYPE_MODEL_UNK60 = 60,
			MTL_TYPE_MODEL_UNK61 = 61,
			MTL_TYPE_MODEL_UNK62 = 62,
			MTL_TYPE_MODEL_UNK63 = 63, // "msopw"
			MTL_TYPE_MODEL_UNK64 = 64, // "mscopw"
			MTL_TYPE_MODEL_UNK65 = 65,
			MTL_TYPE_MODEL_UNK66 = 66,
			MTL_TYPE_MODEL_UNK67 = 67,
			MTL_TYPE_WORLD = 68, // "w"
			MTL_TYPE_WORLD_VERTCOL = 69, // "wc"
			MTL_TYPE_WORLD_IMPACT = 70, // "wim"
			MTL_TYPE_EFFECT_LMAP = 71, // "el"
			MTL_TYPE_EFFECT_VERTLIT = 72, // "ev"
			MTL_TYPE_EFFECT_QUAD = 73, // "eq"
		};

		std::string prefixes[] =
		{
			"mo",
			"ev",
			"eq",
			"particle",
		};

		std::uint8_t prefixes_types[] =
		{
			MTL_TYPE_MODEL_SELFVIS,
			MTL_TYPE_EFFECT_VERTLIT,
			MTL_TYPE_EFFECT_QUAD,
			MTL_TYPE_EFFECT_LMAP,
		};

		std::string material_prefix_for(const std::string& prefix)
		{
			return prefix == "particle" ? "el" : prefix;
		}

		std::string get_packed_techset(const std::string& techset, const bool effect_vertlit)
		{
			if (techset.ends_with("_sat") && !mapped_techsets.contains(techset))
			{
				return get_packed_techset(techset.substr(0, techset.size() - 4), effect_vertlit);
			}

			const auto& table = effect_vertlit ? mapped_techsets_effect_vertlit : mapped_techsets;
			const auto it = table.find(techset);
			if (it != table.end() && !it->second.techset[techset_map_type_e::packed].empty())
			{
				return it->second.techset[techset_map_type_e::packed];
			}

			if (effect_vertlit)
			{
				const auto regular = mapped_techsets.find(techset);
				if (regular != mapped_techsets.end())
				{
					return regular->second.techset[techset_map_type_e::packed];
				}
			}

			return {};
		}

		std::string get_packed_alpha_techset(const std::string& techset, const bool effect_vertlit)
		{
			if (techset.ends_with("_sat") && !mapped_techsets.contains(techset))
			{
				return get_packed_alpha_techset(techset.substr(0, techset.size() - 4), effect_vertlit);
			}

			const auto& table = effect_vertlit ? mapped_techsets_effect_vertlit : mapped_techsets;
			const auto it = table.find(techset);
			if (it != table.end() && !it->second.techset[techset_map_type_e::packed_alpha].empty())
			{
				return it->second.techset[techset_map_type_e::packed_alpha];
			}

			if (effect_vertlit)
			{
				const auto regular = mapped_techsets.find(techset);
				if (regular != mapped_techsets.end())
				{
					return regular->second.techset[techset_map_type_e::packed_alpha];
				}
			}

			return {};
		}

		const std::unordered_set<std::string> stock_effect_techsets =
		{
			"eq_effect_add_lin_ct_ndw_nocast",
			"eq_effect_add_lin_ct_nofog_ndw_nocast",
			"eq_effect_add_lin_ndw_nocast",
			"eq_effect_add_lin_nofog_ndw_nocast",
			"eq_effect_blend_lin_ct_ndw_nocast",
			"eq_effect_blend_lin_ndw_nocast",
			"eq_effect_blend_lin_nofog_ndw_nocast",
			"eq_effect_zfeather_add_lin_ct_eyeoffset_ndw_nocast",
			"eq_effect_zfeather_add_lin_ct_ndw_nocast",
			"eq_effect_zfeather_add_lin_ct_nofog_eyeoffset_ndw_nocast",
			"eq_effect_zfeather_add_lin_ct_nofog_ndw_nocast",
			"eq_effect_zfeather_add_lin_eyeoffset_ndw_nocast",
			"eq_effect_zfeather_add_lin_ndw_nocast",
			"eq_effect_zfeather_add_lin_nofog_eyeoffset_ndw_nocast",
			"eq_effect_zfeather_add_lin_nofog_ndw_nocast",
			"eq_effect_zfeather_blend_lin_ct_ndw_nocast",
			"eq_effect_zfeather_blend_lin_ct_nofog_ndw_nocast",
			"eq_effect_zfeather_blend_lin_eyeoffset_ndw_nocast",
			"eq_effect_zfeather_blend_lin_ndw_nocast",
			"eq_effect_zfeather_blend_lin_nofog_eyeoffset_ndw_nocast",
			"eq_effect_zfeather_blend_lin_nofog_ndw_nocast",
			"eq_effect_zfeather_outdoor_blend_lin_ndw_nocast",
			"ev_effect_add_lin_ct_ndw_nocast",
			"ev_effect_add_lin_nofog_ndw_nocast",
			"ev_effect_blend_lin_ct_ndw_nocast",
			"ev_effect_blend_lin_ndw_nocast",
			"ev_effect_blend_lin_nofog_ndw_nocast",
			"ev_effect_zfeather_add_lin_ndw_nocast",
			"ev_effect_zfeather_blend_lin_ct_ndw_nocast",
			"ev_effect_zfeather_blend_lin_ndw_nocast",
			"particle_cloud_add_ct_lin",
			"particle_cloud_add_lin",
			"particle_cloud_blend_ct_lin",
			"particle_cloud_blend_lin",
			"particle_cloud_outdoor_add_lin",
			"particle_cloud_outdoor_blend_lin",
			"particle_cloud_spark_add_ct_lin",
			"particle_cloud_spark_add_lin",
			"particle_cloud_spark_blend_ct_lin",
		};

		std::string map_effect_techset_by_features(const std::string& techset, const bool effect_vertlit, const bool color_tint)
		{
			std::vector<std::string> parts;
			for (std::size_t start = 0, end; start <= techset.size(); start = end + 1)
			{
				end = techset.find('_', start);
				if (end == std::string::npos) end = techset.size();
				parts.emplace_back(techset.substr(start, end - start));
			}

			const auto has = [&](const char* part) { return std::find(parts.begin(), parts.end(), part) != parts.end(); };

			const bool is_cloud = techset.starts_with("particle_cloud");
			if (!is_cloud && !techset.starts_with("effect"))
			{
				return {};
			}

			const bool add = has("add");
			const bool nofog = has("nofog");
			const bool eyeoffset = has("eyeoffset");
			const bool outdoor = has("outdoor");

			if (is_cloud)
			{
				const bool spark = has("spark") || has("sparkf");
				for (const auto tint : { color_tint, false })
				{
					for (const auto keep_variant : { true, false })
					{
						std::string name = "particle_cloud";
						if (keep_variant && spark) name += "_spark";
						else if (keep_variant && outdoor) name += "_outdoor";
						name += (add || spark) ? "_add" : "_blend";
						name += tint ? "_ct_lin" : "_lin";
						if (stock_effect_techsets.contains(name)) return name;
					}
				}
				return {};
			}

			const bool zfeather = has("zfeather");
			const std::string blend = add ? "add" : "blend";

			const char* prefix = effect_vertlit ? "ev" : "eq";
			for (const auto tint : { color_tint, false })
			{
				for (auto drop = 0; drop < 5; drop++)
				{
					const bool use_outdoor = outdoor && drop < 1;
					const bool use_eyeoffset = eyeoffset && drop < 2;
					const bool use_nofog = nofog && drop < 3;
					const bool use_zfeather = zfeather && drop < 4;

					std::string name = std::string(prefix) + "_effect";
					if (use_zfeather) name += "_zfeather";
					if (use_outdoor) name += "_outdoor";
					name += "_" + blend + "_lin";
					if (tint) name += "_ct";
					if (use_nofog) name += "_nofog";
					if (use_eyeoffset) name += "_eyeoffset";
					name += "_ndw_nocast";

					if (stock_effect_techsets.contains(name)) return name;
				}
			}

			return effect_vertlit ? map_effect_techset_by_features(techset, false, color_tint) : std::string{};
		}

		std::vector<std::string> degrade_techset(const std::string& techset)
		{
			static const std::string_view modifiers[] =
			{
				"_sat", "_lin", "_nocast", "_nofog", "_ua", "_eyeoffset"
			};

			static const std::string_view droppable[] = { "p0", "q0" };

			std::vector<std::string> out;
			auto name = techset;

			for (auto changed = true; changed;)
			{
				changed = false;
				for (const auto mod : modifiers)
				{
					if (name.size() > mod.size() && name.ends_with(mod))
					{
						name.resize(name.size() - mod.size());
						changed = true;
					}
				}
			}
			out.emplace_back(name);

			if (const auto at = name.find("_ua_"); at != std::string::npos)
			{
				name.erase(at, 3);
				out.emplace_back(name);
			}

			for (const auto sm : { std::string_view("_l_hsm_"), std::string_view("_l_sm_") })
			{
				if (const auto at = name.find(sm); at != std::string::npos)
				{
					name.replace(at, sm.size(), "_l_");
					out.emplace_back(name);
					break;
				}
			}

			for (const auto slot : droppable)
			{
				for (auto at = name.find(slot); at != std::string::npos; at = name.find(slot))
				{
					name.erase(at, slot.size());
				}
				out.emplace_back(name);
			}

			return out;
		}

		std::string get_mapped_techset(const std::string& techset, const bool effect_vertlit, const bool color_tint)
		{
			if (!effect_vertlit)
			{
				const auto it = mapped_techsets.find(techset);
				if (it != mapped_techsets.end())
				{
					auto tech = it->second.techset[color_tint ? techset_map_type_e::color_tint : techset_map_type_e::regular];
					return tech.empty() ? it->second.techset[techset_map_type_e::regular] : tech;
				}
			}
			else
			{
				const auto it = mapped_techsets_effect_vertlit.find(techset);
				if (it != mapped_techsets_effect_vertlit.end())
				{
					auto tech = it->second.techset[color_tint ? techset_map_type_e::color_tint : techset_map_type_e::regular];
					return tech.empty() ? it->second.techset[techset_map_type_e::regular] : tech;
				}

				const auto regular = mapped_techsets.find(techset);
				if (regular != mapped_techsets.end())
				{
					auto tech = regular->second.techset[color_tint ? techset_map_type_e::color_tint : techset_map_type_e::regular];
					return tech.empty() ? regular->second.techset[techset_map_type_e::regular] : tech;
				}
			}

			for (const auto& candidate : degrade_techset(techset))
			{
				if (candidate != techset && mapped_techsets.contains(candidate))
				{
					return get_mapped_techset(candidate, effect_vertlit, color_tint);
				}
			}

			if (auto effect = map_effect_techset_by_features(techset, effect_vertlit, color_tint); !effect.empty())
			{
				return effect;
			}

			return "2d";
		}

		std::unordered_map<std::string, std::string> prefix_cache;

		std::string resolve_material_name(const std::string& name)
		{
			const auto renamed = prefix_cache.find(name);
			if (renamed != prefix_cache.end())
			{
				return renamed->second;
			}

			return name;
		}

		std::string replace_material_prefix(const std::string& name, const std::string& techset, const bool effect_vertlit, const bool color_tint)
		{
			if (prefix_cache.contains(name))
			{
				return prefix_cache[name];
			}

			std::string new_tech = get_mapped_techset(techset, effect_vertlit, color_tint);

			for (const auto& prefix : prefixes)
			{
				if (new_tech.starts_with(prefix + "_"))
				{
					const auto slash_pos = name.find('/');
					const size_t replace_len = (slash_pos == std::string::npos) ? 0 : slash_pos + 1;
					const std::string replacement = material_prefix_for(prefix) + "/";

					std::string replaced = name;
					replaced.replace(0, replace_len, replacement);

					prefix_cache[name] = replaced;

					zonetool::filesystem::csv_register_rename("material", name, replaced);

					return replaced;
				}
			}

			return name;
		}

		std::uint8_t get_material_type_from_techset(std::string techset) // iw7_techset
		{
			if (!techset.empty())
			{
				for (auto prefix_idx = 0; prefix_idx < std::size(prefixes); prefix_idx++)
				{
					const auto prefix = prefixes[prefix_idx];
					const auto type = prefixes_types[prefix_idx];

					if (techset.starts_with(prefix + "_"))
					{
						return type;
					}
				}
			}

			return IW7::MTL_TYPE_DEFAULT;
		}

		IW7::TextureSemantic surf_flags_conversion_table[13]
		{
			IW7::TextureSemantic::TS_2D,
			IW7::TextureSemantic::TS_FUNCTION,
			IW7::TextureSemantic::TS_COLOR_MAP,
			IW7::TextureSemantic::TS_DETAIL_MAP,
			IW7::TextureSemantic::TS_UNUSED_4,
			IW7::TextureSemantic::TS_NORMAL_MAP,
			IW7::TextureSemantic::TS_UNUSED_6,
			IW7::TextureSemantic::TS_UNUSED_7,
			IW7::TextureSemantic::TS_SPECULAR_MAP,
			IW7::TextureSemantic::TS_UNUSED_4,
			IW7::TextureSemantic::TS_UNUSED_4,
			IW7::TextureSemantic::TS_UNUSED_4, // WATER_MAP
			IW7::TextureSemantic::TS_DISPLACEMENT_MAP,
		}; IW5::TextureSemantic;

		std::uint8_t convert_semantic(std::uint8_t from)
		{
			return surf_flags_conversion_table[from];
		}

		namespace
		{
			std::string get_IW7_techset(std::string name, std::string matname, bool* result, bool effect_vertlit = false, bool has_ct = false)
			{
				auto iw7_techset = get_mapped_techset(name, effect_vertlit, has_ct);

				*result = true;
				if (name != "2d" && iw7_techset == "2d")
				{
					ZONETOOL_ERROR("Could not find mapped IW7 techset for techset \"%s\" (material: %s)%s",
						name.data(),
						matname.data(),
						effect_vertlit ? " (EFFECT_VERTLIT)" : "");
					*result = false;
				}

				return iw7_techset;
			}

			std::unordered_map<std::uint8_t, std::uint8_t> mapped_sortkeys =
			{
				{0, 2},
				{1, 2},		// Opaque
				{2, 3},     // Sky
				{3, 4},
				{4, 5},
				{5, 6},
				{6, 7},
				{7, 8},
				{8, 9},
				{9, 10},
				{10, 11},
				{11, 12},
				{12, 13},
				{13, 14},
				{14, 15},
				{15, 16},
				{16, 17},
				{17, 18},
				{19, 20},
				{20, 21},
				{24, 25},
				{25, 26},
				{26, 27},
				{27, 28},
				{28, 29},
				{29, 30},
				{30, 31},
				{31, 32},
				{32, 33},
				{33, 34},
				{34, 2},
				{43, 36},
				{44, 36},
				{45, 36},
				{46, 36},
				{48, 35},
				{49, 35},
				{50, 35},
				{51, 35},
				{53, 35},
				{54, 41},	// 2D
			};

			std::unordered_map<std::string, std::uint8_t> mapped_sortkeys_by_techset =
			{
				
			};

			std::uint8_t get_IW7_sortkey(std::uint8_t sortkey, std::string matname, std::string IW7_techset)
			{
				if (mapped_sortkeys_by_techset.find(IW7_techset) != mapped_sortkeys_by_techset.end())
				{
					return mapped_sortkeys_by_techset[IW7_techset];
				}

				if (mapped_sortkeys.contains(sortkey))
				{
					return mapped_sortkeys[sortkey];
				}

				ZONETOOL_ERROR("Could not find mapped IW7 sortkey for sortkey: %d (material: %s)", sortkey, matname.data());

				return sortkey;
			}

			std::unordered_map<std::uint8_t, std::uint8_t> mapped_camera_regions =
			{
				{IW5::CAMERA_REGION_LIT_OPAQUE, IW7::CAMERA_REGION_LIT_OPAQUE},
				{IW5::CAMERA_REGION_LIT_TRANS, IW7::CAMERA_REGION_LIT_TRANS},
				{IW5::CAMERA_REGION_EMISSIVE, IW7::CAMERA_REGION_NONE},
				{IW5::CAMERA_REGION_NONE, IW7::CAMERA_REGION_NONE},
			};

			std::unordered_map<std::string, std::uint8_t> mapped_camera_regions_by_techset =
			{
			};

			std::uint8_t get_IW7_camera_region(std::uint8_t camera_region, std::string matname, std::string IW7_techset)
			{
				if (IW7_techset.find("_tools_") != std::string::npos)
				{
					return IW7::CAMERA_REGION_NONE_2;
				}

				if (mapped_camera_regions_by_techset.find(IW7_techset) != mapped_camera_regions_by_techset.end())
				{
					return mapped_camera_regions_by_techset[IW7_techset];
				}

				if (mapped_camera_regions.contains(camera_region))
				{
					return mapped_camera_regions[camera_region];
				}

				ZONETOOL_ERROR("Could not find mapped IW7 camera region for camera region: %d (material: %s)", camera_region, matname.data());

				return camera_region;
			}

			std::unordered_map<std::string, std::uint8_t> mapped_render_flags_by_techset =
			{
				{"2d", 0x1},
			};

			std::int32_t get_render_flags_by_techset(std::string IW7_techset)
			{
				std::int32_t flags = 0;

				if (mapped_render_flags_by_techset.find(IW7_techset) != mapped_render_flags_by_techset.end())
				{
					flags |= mapped_render_flags_by_techset[IW7_techset];
				}

				if (IW7_techset.starts_with("eq_") || IW7_techset.starts_with("ev_"))
				{
					flags |= 0x1;
				}

				return flags;
			}
		}
	}

	namespace IW5::IW7Dumper
	{
		std::string clean_name(const std::string& name)
		{
			auto new_name = name;

			for (auto i = 0u; i < name.size(); i++)
			{
				switch (new_name[i])
				{
				case '*':
					new_name[i] = '_';
					break;
				}
			}

			return new_name;
		}

		namespace
		{
			//
			//
			//
			//
			//
			//
			//
			//
			constexpr unsigned int slot_hash_colour = 2695565377;
			constexpr unsigned int slot_hash_normal = 1507003663;
			constexpr unsigned int slot_hash_spec   = 887934131;
			constexpr unsigned int slot_hash_detail = 3948059469;

			std::string packed_source_hash(const char* name)
			{
				if (!name || !*name)
				{
					return "00000000";
				}

				std::uint32_t hash = 0;
				for (const auto* c = name; *c; ++c)
				{
					hash = hash * 33 + static_cast<std::uint8_t>(*c);
				}

				return va("%08x", hash);
			}

			std::string packed_cs_name_for(const GfxImage* colour, const GfxImage* spec)
			{
				return va("%s_%s_packed_cs", colour->name,
					spec && spec->name && *spec->name ? spec->name : "00000000");
			}

			std::string packed_a_name_for(const GfxImage* colour)
			{
				return va("%s_%s_packed_a", colour->name, packed_source_hash(nullptr).data());
			}

			std::string packed_ng_name_for(const GfxImage* normal, const GfxImage* spec)
			{
				return va("%s_%s_packed_ng", normal->name,
					packed_source_hash(spec ? spec->name : nullptr).data());
			}

			//
			std::unordered_map<std::string, std::string> packed_cs_cache;
			std::unordered_map<std::string, std::string> packed_ng_cache;
			std::unordered_map<std::string, std::string> packed_a_cache;

			std::string packed_cache_key(const GfxImage* primary, const GfxImage* secondary)
			{
				return zonetool::filesystem::get_fastfile() + "|" + primary->name + "|" +
					(secondary ? secondary->name : "");
			}

			struct lazy_spec
			{
				GfxImage* source = nullptr;
				IW7Converter::decoded_image image;
				bool tried = false;
				bool ok = false;

				const IW7Converter::decoded_image* get()
				{
					if (!tried)
					{
						tried = true;
						ok = source && IW7Converter::decode_source(source, image);
					}

					return ok ? &image : nullptr;
				}
			};

			std::string dump_packed_cs(GfxImage* colour, lazy_spec& spec)
			{
				if (!colour || !colour->name)
				{
					return {};
				}

				const auto key = packed_cache_key(colour, spec.source);
				const auto cached = packed_cs_cache.find(key);
				if (cached != packed_cs_cache.end())
				{
					return cached->second;
				}

				std::string name;

				allocator mem;
				IW7Converter::decoded_image colour_image;
				if (IW7Converter::decode_source(colour, colour_image))
				{
					const auto* spec_image = spec.get();
					name = packed_cs_name_for(colour, spec_image ? spec.source : nullptr);

					if (fast_dump_enabled())
					{
					}
					else if (auto* built = IW7Converter::build_packed_cs(name.data(), colour_image,
						spec_image, mem))
					{
						IW7::IGfxImage::dump(built);
					}
					else
					{
						name.clear();
					}
				}

				packed_cs_cache[key] = name;
				return name;
			}

			std::string dump_packed_a(GfxImage* colour)
			{
				if (!colour || !colour->name)
				{
					return {};
				}

				const auto key = packed_cache_key(colour, nullptr);
				const auto cached = packed_a_cache.find(key);
				if (cached != packed_a_cache.end())
				{
					return cached->second;
				}

				std::string name;

				allocator mem;
				IW7Converter::decoded_image colour_image;
				if (IW7Converter::decode_source(colour, colour_image))
				{
					name = packed_a_name_for(colour);

					if (fast_dump_enabled())
					{
					}
					else if (auto* built = IW7Converter::build_packed_a(name.data(), colour_image, mem))
					{
						IW7::IGfxImage::dump(built);
					}
					else
					{
						name.clear();
					}
				}

				packed_a_cache[key] = name;
				return name;
			}

			std::string dump_packed_ng(GfxImage* normal, lazy_spec& spec)
			{
				if (!normal || !normal->name)
				{
					return {};
				}

				const auto key = packed_cache_key(normal, spec.source);
				const auto cached = packed_ng_cache.find(key);
				if (cached != packed_ng_cache.end())
				{
					return cached->second;
				}

				std::string name;

				allocator mem;
				IW7Converter::decoded_image normal_image;
				if (IW7Converter::decode_source(normal, normal_image))
				{
					const auto* spec_image = spec.get();
					name = packed_ng_name_for(normal, spec_image ? spec.source : nullptr);

					if (fast_dump_enabled())
					{
					}
					else if (auto* built = IW7Converter::build_packed_ng(name.data(), normal_image,
						spec_image, mem))
					{
						IW7::IGfxImage::dump(built);
					}
					else
					{
						name.clear();
					}
				}

				packed_ng_cache[key] = name;
				return name;
			}

			//
			//

			//
			//
			std::string iw7_map_base(const std::string& name)
			{
				auto base = name;

				if (!base.empty() && base.front() == '~')
				{
					base.erase(0, 1);
					const auto cut = base.find_first_of("-&");
					if (cut != std::string::npos)
					{
						base.resize(cut);
					}
				}

				static const char* const suffixes[] = { "_spec", "_spc", "_sg", "_s" };
				for (const auto* suffix : suffixes)
				{
					const auto len = std::strlen(suffix);
					if (base.size() > len && base.compare(base.size() - len, len, suffix) == 0)
					{
						base.resize(base.size() - len);
						break;
					}
				}

				return base;
			}

			std::unordered_map<std::string, std::string> unpacked_sg_cache;

			std::string dump_unpacked_sg(GfxImage* spec)
			{
				if (!spec || !spec->name)
				{
					return {};
				}

				const auto key = packed_cache_key(spec, nullptr);
				const auto cached = unpacked_sg_cache.find(key);
				if (cached != unpacked_sg_cache.end())
				{
					return cached->second;
				}

				std::string name;

				allocator mem;

				auto* converted = IW7Converter::convert_resident(spec, mem);
				if (!converted)
				{
					converted = IW7Converter::convert_iwi(spec->name, spec->semantic, mem);
				}

				if (converted)
				{
					name = iw7_map_base(spec->name) + "_sg";

					converted->name = mem.duplicate_string(name);
					converted->semantic = IW7::TextureSemantic::TS_SPECULAR_MAP;

					IW7::IGfxImage::dump(converted);
				}

				unpacked_sg_cache[key] = name;
				return name;
			}
		}

		bool has_color_tint(const Material* asset)
		{
			static constexpr float identity[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

			for (int i = 0; i < asset->constantCount; ++i)
			{
				const auto& constant = asset->constantTable[i];
				if (constant.nameHash == 3054254906u)
				{
					return !std::equal(std::begin(constant.literal), std::end(constant.literal), std::begin(identity));
				}
			}

			return false;
		}

		void dump(Material* asset, bool geotrail)
		{
			if (asset)
			{
				const auto has_ct = has_color_tint(asset);

				auto new_name = IW7::replace_material_prefix(asset->name, asset->techniqueSet ? asset->techniqueSet->name : "", geotrail, has_ct);
				auto c_name = clean_name(new_name);

				const auto path = "materials\\"s + new_name + ".json"s;
				auto file = zonetool::filesystem::file(path);

				ordered_json matdata;

				//matdata["name"] = new_name;

				std::string techset;
				std::string iw7_techset;
				if (asset->techniqueSet)
				{
					techset = asset->techniqueSet->name;

					bool result = false;
					iw7_techset = IW7::get_IW7_techset(techset, asset->name, &result, geotrail, has_ct);
					if (!result)
					{
						//ZONETOOL_ERROR("Not dumping material \"%s\"", asset->name);
						//return;
					}
					matdata["techniqueSet->original"] = techset;
					matdata["techniqueSet->name"] = iw7_techset;
				}

				//
				//
				//
				//
				//
				//
				const auto packed_alpha_techset = IW7::get_packed_alpha_techset(techset, geotrail);
				const auto packed_techset = packed_alpha_techset.empty()
					? IW7::get_packed_techset(techset, geotrail)
					: packed_alpha_techset;
				const auto wants_alpha = !packed_alpha_techset.empty();
				const auto packable = !packed_techset.empty();

				GfxImage* src_colour = nullptr;
				GfxImage* src_normal = nullptr;
				GfxImage* src_spec = nullptr;
				GfxImage* src_detail = nullptr;
				for (auto i = 0; i < asset->textureCount; i++)
				{
					if (asset->textureTable[i].semantic == 11 || !asset->textureTable[i].u.image)
					{
						continue;
					}
					switch (asset->textureTable[i].nameHash)
					{
					case slot_hash_colour: src_colour = asset->textureTable[i].u.image; break;
					case slot_hash_normal: src_normal = asset->textureTable[i].u.image; break;
					case slot_hash_spec:   src_spec   = asset->textureTable[i].u.image; break;
					case slot_hash_detail: src_detail = asset->textureTable[i].u.image; break;
					default: break;
					}
				}


				lazy_spec spec{ src_spec };
				const auto packed_cs_name = dump_packed_cs(src_colour, spec);
				const auto packed_ng_name = dump_packed_ng(src_normal, spec);

				//
				//
				const auto unpacked_sg_name = dump_unpacked_sg(src_spec);

				const auto packed_a_name = wants_alpha ? dump_packed_a(src_colour) : std::string{};

				const auto packed_wants_detail = packed_techset.find("d0") != std::string::npos;
				const auto packed = packable && !packed_cs_name.empty() && !packed_ng_name.empty()
					&& (!wants_alpha || !packed_a_name.empty())
					&& (!packed_wants_detail || src_detail != nullptr);
				if (packed)
				{
					iw7_techset = packed_techset;
					matdata["techniqueSet->name"] = iw7_techset;
				}


				//
				{
					auto game_flags = asset->info.gameFlags;
					if (game_flags & 0x40)
					{
						game_flags = static_cast<decltype(game_flags)>((game_flags & ~0x40) | 0x80);
					}
					matdata["gameFlags"] = game_flags;
				}
				matdata["unkFlags"] = 0; // idk
				matdata["sortKey"] = IW7::get_IW7_sortkey(asset->info.sortKey, asset->name, iw7_techset);
				matdata["renderFlags"] = IW7::get_render_flags_by_techset(iw7_techset); // idk

				matdata["textureAtlasRowCount"] = asset->info.textureAtlasRowCount;
				matdata["textureAtlasColumnCount"] = asset->info.textureAtlasColumnCount;
				matdata["textureAtlasFrameBlend"] = 0;
				matdata["textureAtlasAsArray"] = 0;

				matdata["surfaceTypeBits"] = asset->info.surfaceTypeBits; // convert
				// hashIndex;

				//
				//
				{
					auto state_flags = asset->stateFlags;
					const auto is_2d = iw7_techset.compare(0, 2, "2d") == 0;
					if (!is_2d)
					{
						state_flags = static_cast<decltype(state_flags)>(state_flags & ~0x40);
					}
					matdata["stateFlags"] = state_flags;
				}
				matdata["cameraRegion"] = IW7::get_IW7_camera_region(asset->cameraRegion, asset->name, iw7_techset);
				matdata["materialType"] = IW7::get_material_type_from_techset(iw7_techset);
				matdata["assetFlags"] = 0; // IW7::MTL_ASSETFLAG_NONE;

				// fixes
				if (matdata["cameraRegion"].get<uint8_t>() == 4 && matdata["sortKey"].get<uint8_t>() != 41)
				{
					matdata["cameraRegion"] = 11;
				}

				ordered_json constant_table = ordered_json::array();
				for (int i = 0; i < asset->constantCount && techset != "2d"; i++)
				{
					ordered_json table;
					std::string constant_name = asset->constantTable[i].name;
					const auto constant_hash = asset->constantTable[i].nameHash;

					if (constant_name.size() > 12)
					{
						constant_name.resize(12);
					}

					if (constant_hash == 1033475292) // envMapParms
					{
						continue;
					}

					table["name"] = constant_name.data();
					table["nameHash"] = constant_hash;

					nlohmann::json literal_entry;
					literal_entry[0] = asset->constantTable[i].literal[0];
					literal_entry[1] = asset->constantTable[i].literal[1];
					literal_entry[2] = asset->constantTable[i].literal[2];
					literal_entry[3] = asset->constantTable[i].literal[3];
					table["literal"] = literal_entry;

					constant_table[constant_table.size()] = table;
				}

#define CONSTANT_TABLE_ADD_IF_NOT_FOUND(CONST_NAME, CONST_HASH, LITERAL_1, LITERAL_2, LITERAL_3, LITERAL_4) \
				bool has_const = false; \
				std::size_t insert_position = constant_table.size(); \
				for (std::size_t i = 0; i < constant_table.size(); i++) \
				{ \
					if (constant_table[i]["nameHash"].get<std::size_t>() == CONST_HASH) \
					{ \
						has_const = true; \
						break; \
					} \
					if (constant_table[i]["nameHash"].get<std::size_t>() > CONST_HASH) \
					{ \
						insert_position = i; \
						break; \
					} \
				} \
				if (!has_const) \
				{ \
					ordered_json table; \
					table["name"] = CONST_NAME; \
					table["nameHash"] = CONST_HASH; \
					nlohmann::json literal_entry; \
					literal_entry[0] = LITERAL_1; \
					literal_entry[1] = LITERAL_2; \
					literal_entry[2] = LITERAL_3; \
					literal_entry[3] = LITERAL_4; \
					table["literal"] = literal_entry; \
					constant_table.insert(constant_table.begin() + insert_position, table); \
				}

				if (iw7_techset.find("s0") != std::string::npos)
				{
					CONSTANT_TABLE_ADD_IF_NOT_FOUND("reflectionRa", 3344177073u, 8096.0f, 0.0f, 0.0f, 0.0f);
				}
				if (iw7_techset.find("_lin") != std::string::npos)
				{
					CONSTANT_TABLE_ADD_IF_NOT_FOUND("textureAtlas", 1128936273u,
						static_cast<float>(asset->info.textureAtlasColumnCount), static_cast<float>(asset->info.textureAtlasRowCount), 1.0f, 1.0f);
				}

				matdata["constantTable"] = constant_table;

				ordered_json material_images;
				for (auto i = 0; i < asset->textureCount; i++)
				{
					ordered_json image;
					if (asset->textureTable[i].semantic == 11)
					{
						auto* water = asset->textureTable[i].u.water;
						if (water->image && water->image->name)
						{
							image["image"] = water->image->name;
						}
						else
						{
							image["image"] = "";
						}
					}
					else
					{
						if (asset->textureTable[i].u.image && asset->textureTable[i].u.image->name)
						{
							image["image"] = asset->textureTable[i].u.image->name;
						}
						else
						{
							image["image"] = "";
						}
					}

					//
					const auto iw5_semantic = asset->textureTable[i].semantic;

					//
					if (asset->textureTable[i].nameHash == slot_hash_detail)
					{
						asset->textureTable[i].semantic = IW7::TextureSemantic::TS_DETAIL_MAP;
					}
					else if (packed && iw5_semantic == 2)
					{
						image["image"] = packed_cs_name;
						asset->textureTable[i].semantic = IW7::TextureSemantic::TS_COLOR_SPECULAR_MAP;
					}
					else if (packed && iw5_semantic == 5)
					{
						image["image"] = packed_ng_name;
						asset->textureTable[i].semantic = IW7::TextureSemantic::TS_NORMAL_OCCLUSSION_GLOSS_MAP;
					}
					else if (packed && iw5_semantic == 8)
					{
						continue;
					}
					else if (iw5_semantic == 8 && !unpacked_sg_name.empty())
					{
						image["image"] = unpacked_sg_name;
						asset->textureTable[i].semantic = IW7::convert_semantic(iw5_semantic);
					}
					else
					{
						asset->textureTable[i].semantic = IW7::convert_semantic(iw5_semantic);
					}

					image["semantic"] = asset->textureTable[i].semantic;
					image["samplerState"] = asset->textureTable[i].samplerState == 11 ? 19 : asset->textureTable[i].samplerState; // convert? ( should be fine )
					image["lastCharacter"] = asset->textureTable[i].nameEnd;
					image["firstCharacter"] = asset->textureTable[i].nameStart;
					image["typeHash"] = asset->textureTable[i].nameHash;

					// add image data to material
					material_images.push_back(image);
				}

#define IMAGE_ADD_IF_NOT_FOUND(IMAGE, SEMANTIC, SAMPLER_STATE, LAST_CHARACTER, FIRST_CHARACTER, HASH) \
				bool has_image = false; \
				std::size_t insert_position = material_images.size(); \
				for (std::size_t i = 0; i < material_images.size(); i++) \
				{ \
					if (material_images[i]["typeHash"].get<std::size_t>() == HASH) \
					{ \
						has_image = true; \
						break; \
					} \
					if (material_images[i]["typeHash"].get<std::size_t>() > HASH) \
					{ \
						insert_position = i; \
						break; \
					} \
				} \
				if (!has_image) \
				{ \
					ordered_json image; \
					image["image"] = IMAGE; \
					image["semantic"] = SEMANTIC; \
					image["samplerState"] = SAMPLER_STATE; \
					image["lastCharacter"] = LAST_CHARACTER; \
					image["firstCharacter"] = FIRST_CHARACTER; \
					image["typeHash"] = HASH; \
					material_images.insert(material_images.begin() + insert_position, image); \
				}

				//
				struct required_slot
				{
					const char* image;
					std::uint8_t semantic;
					std::uint8_t sampler;
					std::uint8_t last_character;
					std::uint8_t first_character;
					unsigned int hash;
				};

				static const required_slot slot_colour  { "$white", 2, 19, 112, 99, 2695565377 };
				static const required_slot slot_normal  { "$identitynormalmap", 5, 1, 112, 110, 1507003663 };
				static const required_slot slot_spec    { "$white", 8, 19, 112, 115, 887934131 };
				static const required_slot slot_occl    { "$white", 9, 19, 112, 115, 2771134132 };
				static const required_slot slot_layer1  { "$black", 2, 19, 49, 99, 3054311504 };
				static const required_slot slot_detail  { "$gray", 3, 19, 112, 100, slot_hash_detail };

				static const std::unordered_map<std::string, std::vector<required_slot>> required_slots =
				{
					{"mo_l_sm_atest_i0c0",                    {slot_colour, slot_normal}},
					{"mo_l_sm_atest_i0c0n0",                  {slot_colour, slot_normal}},
					{"mo_l_sm_atest_i0c0s0",                  {slot_colour, slot_normal, slot_spec}},
					{"mo_l_sm_atest_i0c0s0n0",                {slot_colour, slot_normal, slot_spec}},
					{"mo_l_sm_ndw_blend_i0c0",                {slot_colour, slot_normal}},
					{"mo_l_sm_ndw_blend_i0c0n0",              {slot_colour, slot_normal}},
					{"mo_l_sm_ndw_blend_i0c0s0",              {slot_colour, slot_normal, slot_spec}},
					{"mo_l_sm_ndw_blend_i0c0s0n0",            {slot_colour, slot_normal, slot_spec}},
					{"mo_l_sm_replace_i0c0",                  {slot_colour, slot_normal}},
					{"mo_l_sm_replace_i0c0n0",                {slot_colour, slot_normal}},
					{"mo_l_sm_replace_i0c0n0d0",              {slot_colour, slot_detail, slot_normal}},
					{"mo_l_sm_replace_i0c0s0",                {slot_colour, slot_normal, slot_spec}},
					{"mo_l_sm_replace_i0c0s0n0",              {slot_colour, slot_normal, slot_spec}},
					{"mo_l_sm_replace_i0c0s0n0d0",            {slot_colour, slot_detail, slot_normal, slot_spec}},
					{"wc_l_sm_atest_i0c0",                    {slot_colour, slot_normal}},
					{"wc_l_sm_atest_i0c0s0",                  {slot_colour, slot_normal, slot_spec}},
					{"wc_l_sm_ndw_blend_i0c0",                {slot_colour, slot_normal}},
					{"wc_l_sm_ndw_blend_i0c0n0",              {slot_colour, slot_normal}},
					{"wc_l_sm_ndw_blend_i0c0s0",              {slot_colour, slot_normal, slot_spec}},
					{"wc_l_sm_ndw_blend_i0c0s0n0",            {slot_colour, slot_normal, slot_spec}},
					{"wc_l_sm_replace_i0c0",                  {slot_colour, slot_normal}},
					{"wc_l_sm_replace_i0c0n0",                {slot_colour, slot_normal}},
					{"wc_l_sm_replace_i0c0s0",                {slot_colour, slot_normal, slot_spec}},
					{"wc_l_sm_replace_i0c0s0n0",              {slot_colour, slot_normal, slot_spec, slot_occl}},

					{"mo_l_sm_replace_i0c0s0n0p0",      {}},
					{"w_l_sm_replace_r0c0_m1c1",        {slot_colour, slot_normal, slot_layer1}},
					{"w_l_sm_replace_r0c0nl0_m1c1",     {slot_colour, slot_normal, slot_layer1}},
					{"w_l_sm_blend_b0c0sl0ol0_m1c1",    {slot_colour, slot_normal, slot_spec, slot_occl, slot_layer1}},
				};

				const auto required = required_slots.find(iw7_techset);
				if (required != required_slots.end())
				{
					for (const auto& slot : required->second)
					{
						auto insert_at = material_images.size();
						auto present = false;
						for (std::size_t i = 0; i < material_images.size(); i++)
						{
							const auto hash = material_images[i]["typeHash"].get<std::size_t>();
							if (hash == slot.hash)
							{
								present = true;
								break;
							}
							if (hash > slot.hash)
							{
								insert_at = i;
								break;
							}
						}
						if (present)
						{
							continue;
						}

						ordered_json entry;
						entry["image"] = slot.image;
						entry["semantic"] = slot.semantic;
						entry["samplerState"] = slot.sampler;
						entry["lastCharacter"] = slot.last_character;
						entry["firstCharacter"] = slot.first_character;
						entry["typeHash"] = slot.hash;
						material_images.insert(material_images.begin() + insert_at, entry);
					}
				}
				else if (iw7_techset.find("n0") != std::string::npos)
				{
					IMAGE_ADD_IF_NOT_FOUND("$identitynormalmap", 5, 1, 112, 110, 1507003663);
				}

				//
				if (packed && wants_alpha && !packed_a_name.empty())
				{
					constexpr unsigned int alpha_hash = 2771134132;

					auto insert_at = material_images.size();
					auto present = false;
					for (std::size_t i = 0; i < material_images.size(); i++)
					{
						const auto hash = material_images[i]["typeHash"].get<std::size_t>();
						if (hash == alpha_hash)
						{
							present = true;
							break;
						}
						if (hash > alpha_hash)
						{
							insert_at = i;
							break;
						}
					}

					if (!present)
					{
						ordered_json entry;
						entry["image"] = packed_a_name;
						entry["semantic"] = IW7::TextureSemantic::TS_ALPHA_REVEAL_THICKNESS_MAP;
						entry["samplerState"] = 19;
						entry["lastCharacter"] = 112;
						entry["firstCharacter"] = 115;
						entry["typeHash"] = alpha_hash;
						material_images.insert(material_images.begin() + insert_at, entry);
					}
				}

				matdata["textureTable"] = material_images;

				auto str = matdata.dump(4, ' ', true, nlohmann::detail::error_handler_t::replace);

				matdata.clear();

				file.open("wb");
				file.write(str);
				file.close();
			}
		}
	}
}