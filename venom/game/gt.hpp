#pragma once
#include <game/app/app.hpp>
#include <game/network/enet_client.hpp>
#include <game/network/game_packet.hpp>
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

	inline std::uintptr_t base_address = 0;
	inline std::uintptr_t end_address = 0;
	inline HWND hwnd = nullptr;

	inline app_t* (*get_app)() = nullptr;
	inline enet_client_t* (*get_client)() = nullptr;

	inline void (*set_fps_limit)(base_app_t* _this, float fps) = nullptr;
	inline void (*log_to_console)(const std::string& text) = nullptr;
	inline void (*send_packet)(net_message_type type, const std::string& packet, void* peer) = nullptr;
	inline void (*send_packet_raw)(net_message_type type, const void* data, std::int32_t data_size, std::uint8_t* unk1, void* peer, std::uint32_t flags) = nullptr;

	inline HRESULT(*end_scene)(IDirect3DDevice9* _this) = nullptr;

	inline renderer_context_d3d9_t* renderer = nullptr;
}
