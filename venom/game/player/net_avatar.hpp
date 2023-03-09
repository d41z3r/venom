#pragma once
#include <cstdint>

enum class visual_state : std::uint32_t {
	// 0x1: unknown
	// 0x2: unknown
	on_spawn = 0x4, // (1 << 2)
	// 0x8: unknown
	flipped = 0x10, // (1 << 4)
	on_solid = 0x20, // (1 << 5)
	on_fire_damage = 0x40, // (1 << 6)
	on_jump = 0x80, // (1 << 7)
	on_killed = 0x100, // (1 << 8)
	on_punched = 0x200, // (1 << 9)
	on_placed = 0x400, // (1 << 10)
	on_tile_change = 0x800, // (1 << 11)
	on_got_punched = 0x1000, // (1 << 12)
	on_respawned = 0x2000, // (1 << 13)
	on_object_collected = 0x4000, // (1 << 14)
	on_trampoline = 0x8000, // (1 << 15)
	on_damage = 0x10000, // (1 << 16)
	on_slide = 0x20000, // (1 << 17)
	on_parasol = 0x40000, // (1 << 18)
	// 0x80000: used in gravity() and OnJump(), some bcape jump stuff
	on_swim = 0x100000, // (1 << 20)
	on_wall_hang = 0x200000, // (1 << 21)
	on_power_up_punch_start = 0x400000, // (1 << 22)
	on_power_up_punch_end = 0x800000, // (1 << 23)
	// 0x1000000: some tile change stuff
	// 0x2000000: used in AnimatedCapeLogics::CheckHayCartConditions
	// 0x4000000: more OnJump bcape things
	// 0x8000000: unknown
	on_acid_damage = 0x10000000, // (1 << 28)
};

struct net_avatar_t /*: public net_moving_t*/ {

};
