#pragma once
#include <game/app/app.hpp>

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
	inline void (*send_packet)(int type, std::string packet, void* peer) = nullptr;

	inline void* renderer = nullptr; // later needed for imgui and textures
}
