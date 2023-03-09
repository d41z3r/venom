#pragma once
#include <game/app/app.hpp>
#include <game/network/enet_client.hpp>
#include <game/network/game_packet.hpp>
#include <game/component/game_logic_component.hpp>
#include <game/component/track_handler_component.hpp>
#include <game/player/net_avatar.hpp>
#include <game/world/world_tile_map.hpp>
#include <game/utils/math.hpp>
#include <game/renderer/renderer_context.hpp>

#include <cstdint>
#include <string>
#include <functional>
#include <windows.h>
#include <psapi.h>

namespace gt {
	void setup();

	void send_generic_text(const std::string& packet) noexcept;
	void send_game_message(const std::string& packet) noexcept;
	void send_game_packet(const game_packet_t& packet) noexcept;

	void process_game_message(const std::string& packet) noexcept;
	void process_game_packet(const game_packet_t& packet) noexcept;
	//void process_track_packet(const std::string& packet) noexcept;

	inline std::uintptr_t base_address = 0;
	inline std::uintptr_t end_address = 0;
	inline HWND hwnd = nullptr;

	inline app_t* (*get_app)() = nullptr;
	inline enet_client_t* (*get_client)() = nullptr;
	inline game_logic_component_t* (*get_game_logic)() = nullptr;

	inline void (*set_fps_limit)(base_app_t* _this, float fps) = nullptr;
	inline void (*log_to_console)(const std::string& text) = nullptr;
	inline void (*send_packet)(net_message_type type, const std::string& packet, void* peer) = nullptr;
	inline void (*send_packet_raw)(net_message_type type, const void* data, std::int32_t data_size, std::uint8_t* unk1, void* peer, std::uint32_t flags) = nullptr;
	inline void (*on_text_game_message)(game_logic_component_t* _this, const char* packet) = nullptr;
	inline void (*process_tank_update_packet)(game_logic_component_t* _this, game_packet_t* packet) = nullptr;
	inline void (*handle_track_packet)(track_handler_component_t* _this, const char* packet) = nullptr;
	inline void (*on_punched)(net_avatar_t* _this, vec2f_t unk1, net_avatar_t* puncher) = nullptr;
	inline std::int32_t (*is_darkened)(std::int32_t item_id) = nullptr;
	inline bool (*is_anzu_platform)() = nullptr;
	inline bool (*collide)(world_tile_map_t* _this, float unk1, float unk2, float unk3, float unk4, int unk5, bool unk6) = nullptr;

	inline HRESULT(*end_scene)(IDirect3DDevice9* _this) = nullptr;
	inline renderer_context_d3d9_t* renderer = nullptr;

	inline std::uintptr_t touch_bypass_address = 0;
}

