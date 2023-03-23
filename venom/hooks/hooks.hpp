#pragma once
#include <game/gt.hpp>

#include <string>
#include <cstdint>
#include <d3d9.h>

namespace hooks {
	void install();

	void app_update_hook(app_t* _this);
	void send_packet_hook(net_message_type type, std::string packet, void* peer); // it's actually const std::string& packet, but we want to modify it
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
	void on_touched_deadly_hook(net_avatar_t* _this, tile_t* tile);
	void bumped_bouncy_hook(net_avatar_t* _this, tile_t* unk1, float* unk2, float* unk3);
	void handle_tile_damage_vertically_hook(net_avatar_t* _this, float* unk1, float* unk2, bool unk3, bool unk4);
	void handle_tile_damage_horizontally_hook(net_avatar_t* _this, float* unk1, float* unk2, bool unk3, bool unk4);
	void update_from_net_avatar_hook(avatar_render_data_t* _this, net_avatar_t* net_avatar);
	bool is_checkpoint_hook(tile_t* _this);
	void handle_touch_at_world_coordinates_hook(level_touch_component_t* _this, vec2f_t* pos, bool unk1);
	void camera_on_update_hook(world_camera_t* _this, vec2f_t unk1, vec2f_t unk2);

	HRESULT end_scene_hook(IDirect3DDevice9* _this);
	LRESULT wnd_proc_hook(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	inline WNDPROC original_wnd_proc = nullptr;
}
