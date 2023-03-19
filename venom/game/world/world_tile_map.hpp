#pragma once
#include <game/world/tile.hpp>
#include <game/utils/math.hpp>

#include <vector>
#include <cstdint>

struct world_t;

#pragma pack(push, 1)
struct world_tile_map_t {
	void* vftable;
	vec2i_t size;
	std::uint8_t pad1[8];
	std::vector<tile_t> tiles;
	world_t* parent_world;
};
#pragma pack(pop)
