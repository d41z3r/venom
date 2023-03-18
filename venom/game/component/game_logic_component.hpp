#pragma once
#include <game/player/net_avatar.hpp>

#pragma pack(push, 1)
struct game_logic_component_t {
	std::uint8_t pad1[0x1b0];
	net_avatar_t* local_player; // 0x1b0
};
#pragma pack(pop)
