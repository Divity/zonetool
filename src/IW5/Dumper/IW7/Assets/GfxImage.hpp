#pragma once

namespace ZoneTool::IW5::IW7Dumper
{
	void dump(GfxImage* asset);

	bool fast_dump_enabled();

	const std::vector<IW7::GfxImage*>& reflection_probes();
	void clear_reflection_probes();

	const std::vector<IW7::GfxImage*>& lightmap_primary_images();
	const std::vector<IW7::GfxImage*>& lightmap_secondary_images();
	void clear_lightmap_images();
}