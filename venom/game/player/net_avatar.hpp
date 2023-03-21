#pragma once
#include <game/utils/math.hpp>
#include <game/utils/lock_float.hpp>

#include <cstdint>
#include <memory>

enum class visual_state : std::uint32_t {
	none = 0x0,
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

enum class player_flag : std::uint32_t {
	none = 0x0,
	no_clip = 0x1,
	double_jump = 0x2,
	invisible = 0x4,
	no_hands = 0x8,
	no_face = 0x10,
	no_body = 0x20,
	devil_horns = 0x40,
	golden_halo = 0x80,
	// something
	// something, got when consumed spike juice
	spikeproof = 0x400,
	frozen = 0x800,
	cursed = 0x1000,
	duct_taped = 0x2000,
	bad_smell = 0x4000,
	shiny = 0x8000,
	zombie = 0x10000,
	// something
	shadows = 0x40000,
	irradiated = 0x80000,
	spotlight = 0x100000,
	pineapple_skin_and_flag = 0x200000,
	pineapple_flag = 0x400000,
	// something
	super_supporter = 0x1000000,
	pineapple_aura = 0x2000000,
	bubble = 0x4000000,
	wet = 0x8000000,
	mask1 = 0x10000000,
	mask2 = 0x20000000,
	mask3 = 0x40000000,
	mask4 = 0x80000000
};

#pragma pack(push, 1)
class net_avatar_t /*: public net_moving_t*/ {
public:
	void* vftable;
	vec2f_t pos;
	vec2f_t size;
	vec2f_t encrypted_pos;
	vec2f_t encrypted_size;
	std::string name;
	std::int32_t net_id;
	std::uint8_t pad1[21];
	bool facing_left;
	std::uint8_t pad2[122];
	bool can_jump;
	std::uint8_t pad3[7];
	vec2_t<lock_float_t> velocity;
	std::uint8_t pad4[52];
	std::uint32_t freeze_state;
	std::uint32_t user_id;
	std::uint8_t pad5[16];
	std::string country;
	std::uint8_t pad6[8];
	bool is_invis;
	bool is_mod;
	bool is_smod;
	std::uint8_t pad7[9];
	std::uint32_t bubble_state;
	player_flag flags;
	std::uint8_t pad8[20];
	bool down_key_state;
	std::uint8_t pad9[4];
	std::uint32_t punch_effect;
	std::uint8_t pad10[28];
	lock_float_t gravity;
	lock_float_t acceleration;
	lock_float_t speed;
	float water_speed;
};
#pragma pack(pop)
