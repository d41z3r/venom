#pragma once
#include <game/world/tile.hpp>
#include <game/utils/math.hpp>

#include <vector>
#include <cstdint>

class world_t;

#pragma pack(push, 1)
class world_tile_map_t {
public:
	inline tile_t* get_tile(std::int32_t x, std::int32_t y) noexcept {
		if (x >= 0 && y >= 0 && size.x > x && size.y > y)
			return &tiles[static_cast<std::size_t>(y * size.x + x)];

		return nullptr;
	}

	inline tile_t* get_tile(vec2i_t pos) noexcept {
		return get_tile(pos.x, pos.y);
	}

	void* vftable;
	vec2i_t size;
	std::uint8_t pad1[8];
	std::vector<tile_t> tiles;
	world_t* parent_world;
};
#pragma pack(pop)
