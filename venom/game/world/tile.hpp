#pragma once
#include <game/world/tile_extra.hpp>
#include <game/utils/math.hpp>

#include <cstdint>

enum class tile_flag : std::uint16_t {
	none = 0x0,
	extra_data = 0x1,
	locked = 0x2,
	unk_0x4 = 0x4,
	unk_0x8 = 0x8,
	seed = 0x10,
	flipped = 0x20,
	open = 0x40,
	public_ = 0x80,
	unk_0x100 = 0x100,
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
	vec2f_t get_world_pos() const noexcept {
		return { 
			static_cast<float>(pos.x) * 32.f,
			static_cast<float>(pos.y) * 32.f
		};
	}

	std::uint8_t pad1[4];
	std::uint16_t foreground; // 0x4
	std::uint16_t background; // 0x6
	tile_flag flags; // 0x8
	vec2_t<std::uint8_t> pos; // 0xa
	std::uint8_t pad2[12];
	rectf_t collision_rect; // 0x18
	tile_extra_t* extra; // 0x28
	std::uint8_t pad3[112];
};
#pragma pack(pop)

static_assert(sizeof(tile_t) == 0xA0);
