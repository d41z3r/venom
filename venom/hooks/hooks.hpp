#pragma once
#include <game/gt.hpp>

#include <string>
#include <d3d9.h>

namespace hooks {
	void install();

	void send_packet_hook(net_message_type type, const std::string& packet, void* peer);
	void send_packet_raw_hook(net_message_type type, const void* data, std::int32_t data_size, std::uint8_t* unk1, void* peer, std::uint32_t flags);
	void on_text_game_message_hook(game_logic_component_t* _this, const char* packet);
	void process_tank_update_packet_hook(game_logic_component_t* _this, game_packet_t* packet);
	void handle_track_packet_hook(track_handler_component_t* _this, const char* packet);

	HRESULT end_scene_hook(IDirect3DDevice9* _this);
	LRESULT wnd_proc_hook(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	inline WNDPROC original_wnd_proc = nullptr;
}
