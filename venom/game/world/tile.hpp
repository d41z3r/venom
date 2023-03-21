#pragma once
#include <game/utils/math.hpp>

#include <cstdint>

enum class tile_flag : std::uint16_t {
	none = 0x0,
	tile_extra = 0x1,
	locked = 0x2,
	// something
	// something
	seed = 0x10,
	flipped = 0x20,
	open = 0x40,
	public_ = 0x80,
	// something
	silenced = 0x200,
	water = 0x400,
	glue = 0x800,
	fire = 0x1000,
	red = 0x2000,
	green = 0x4000,
	blue = 0x8000
};

#pragma pack(push, 1)
class tile_t {
public:
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
