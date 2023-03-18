#pragma once
#include <game/gt.hpp>

#include <string>
#include <cstdint>
#include <d3d9.h>

namespace hooks {
	void install();

	void send_packet_hook(net_message_type type, const std::string& packet, void* peer);
	void send_packet_raw_hook(net_message_type type, const void* data, std::int32_t data_size, std::uint8_t* unk1, void* peer, std::uint32_t flags);
	void on_text_game_message_hook(game_logic_component_t* _this, const char* packet);
	void process_tank_update_packet_hook(game_logic_component_t* _this, game_packet_t* packet);
	void handle_track_packet_hook(track_handler_component_t* _this, const char* packet);
	void on_punched_hook(net_avatar_t* _this, vec2f_t unk1, net_avatar_t* puncher);
	std::int32_t is_darkened_hook(std::int32_t item_id);
	bool is_anzu_platform_hook();
	bool collide_hook(world_tile_map_t* _this, float unk1, float unk2, float unk3, float unk4, int unk5, bool unk6);
	void server_info_http_finish_hook(variant_list_t* var_list);
	float get_fruit_bloom_progress_percent_hook(tile_t* _this);
	bool can_see_ghosts_hook(std::int32_t item_id);

	HRESULT end_scene_hook(IDirect3DDevice9* _this);
	LRESULT wnd_proc_hook(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	inline WNDPROC original_wnd_proc = nullptr;
}
