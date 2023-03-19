#pragma once
#include <game/world/world.hpp>
#include <game/world/world_renderer.hpp>
#include <game/player/net_avatar.hpp>
#include <game/player/player_items.hpp>
#include <game/manager/net_object_manager.hpp>

#pragma pack(push, 1)
struct game_logic_component_t {
	std::uint8_t pad1[264];
	world_t* world; // 0x108
	world_renderer_t* world_renderer; // 0x110
	std::uint8_t pad2[72];
	net_object_manager_t net_object_manager; // 0x160
	net_avatar_t* local_player; // 0x1b0
	std::uint8_t pad3[80];
	player_items_t player_items; // 0x208
};
#pragma pack(pop)
