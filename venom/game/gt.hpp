#pragma once
#include <game/app/app.hpp>
#include <game/network/game_packet.hpp>

#include <cstdint>
#include <string>
#include <functional>
#include <windows.h>
#include <psapi.h>

namespace gt {
	void setup();

	inline std::uintptr_t base_address = 0;
	inline std::uintptr_t end_address = 0;
	inline HWND hwnd = nullptr;

	inline app_t* (*get_app)() = nullptr;
	inline void (*set_fps_limit)(base_app_t* _this, float fps) = nullptr;
	inline void (*log_to_console)(const std::string& text) = nullptr;
	inline void (*send_packet)(net_message_type type, const std::string& packet, void* peer) = nullptr;
	inline void (*send_packet_raw)(net_message_type type, const void* data, std::int32_t data_size, std::uint8_t* unk1, void* peer, std::uint32_t flags) = nullptr;

	inline void* renderer = nullptr; // later needed for imgui and textures
}
