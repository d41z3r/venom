#pragma once
#include <game/utils/math.hpp>

#include <cstdint>

enum class tile_flag : std::uint16_t {
	none = 0x0
};

#pragma pack(push, 1)
struct tile_t {
	std::uint8_t pad1[4];
	std::uint16_t foreground;
	std::uint16_t background;
	tile_flag flags;
	vec2_t<std::uint8_t> pos;

	//28,tile_extra_t*?

	std::uint8_t pad2[148];
};
#pragma pack(pop)

static_assert(sizeof(tile_t) == 0xA0);
