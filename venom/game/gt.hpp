#pragma once
#include <game/app/app.hpp>
#include <game/network/enet_client.hpp>
#include <game/network/game_packet.hpp>
#include <game/component/game_logic_component.hpp>
#include <game/component/track_handler_component.hpp>
#include <game/component/level_touch_component.hpp>
#include <game/manager/item_info_manager.hpp>
#include <game/player/avatar_render_data.hpp>
#include <game/player/net_avatar.hpp>
#include <game/world/world_tile_map.hpp>
#include <game/utils/math.hpp>
#include <game/utils/variant.hpp>
#include <game/renderer/renderer_context.hpp>

#include <cstdint>
#include <string>
#include <vector>
#include <functional>
#include <windows.h>
#include <psapi.h>

namespace gt {
	void setup();
	void close_mutexes();

	void send_generic_text(const std::string& packet) noexcept;
	void send_game_message(const std::string& packet) noexcept;
	void send_game_packet(const game_packet_t& packet) noexcept;

	void process_game_message(const std::string& packet) noexcept;
	void process_game_packet(const game_packet_t& packet) noexcept;
	//void process_call_function(const variant_list_t& var_list, std::int32_t net_id = -1, std::int32_t delay = 0) noexcept;
	//void process_track_packet(const std::string& packet) noexcept;

	std::vector<vec2i_t> find_path(vec2i_t start, vec2i_t goal) noexcept;

	inline std::uintptr_t base_address = 0;
	inline std::uintptr_t end_address = 0;
	inline HWND hwnd = nullptr;

	inline app_t* (*get_app)() = nullptr;
	inline enet_client_t* (*get_client)() = nullptr;
	inline game_logic_component_t* (*get_game_logic)() = nullptr;
	inline item_info_manager_t* (*get_item_info_manager)() = nullptr;

	inline void (*update)(app_t* _this) = nullptr;
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
	inline void (*server_info_http_finish)(variant_list_t* var_list) = nullptr;
	inline float (*get_fruit_bloom_progress_percent)(tile_t* _this) = nullptr;
	inline bool (*can_see_ghosts)(std::int32_t item_id) = nullptr;
	inline void (*on_touched_deadly)(net_avatar_t* _this, tile_t* tile) = nullptr;
	inline void (*bumped_bouncy)(net_avatar_t* _this, tile_t* unk1, float* unk2, float* unk3) = nullptr;
	inline void (*handle_tile_damage_vertically)(net_avatar_t* _this, float* unk1, float* unk2, bool unk3, bool unk4) = nullptr;
	inline void (*handle_tile_damage_horizontally)(net_avatar_t* _this,float* unk1, float* unk2, bool unk3, bool unk4) = nullptr;
	inline void (*update_from_net_avatar)(avatar_render_data_t* _this, net_avatar_t* net_avatar) = nullptr;
	inline bool (*is_checkpoint)(tile_t* _this) = nullptr;
	inline void (*handle_touch_at_world_coordinates)(level_touch_component_t* _this, vec2f_t* pos, bool unk1) = nullptr;
	inline void (*camera_on_update)(world_camera_t* _this, vec2f_t unk1, vec2f_t unk2) = nullptr;
	inline bool (*is_collidable)(tile_t* _this, std::int32_t user_id, world_t* world, bool unk1) = nullptr;

	inline HRESULT (*end_scene)(IDirect3DDevice9* _this) = nullptr;
	inline renderer_context_d3d9_t* renderer = nullptr;

	inline std::uintptr_t anti_slide_address = 0;
	inline std::uintptr_t anti_portal_address = 0;
	inline std::uintptr_t anti_water_address = 0;
	inline std::uintptr_t see_locked_doors_address = 0;
	inline std::uintptr_t touch_bypass_address = 0;
	inline std::uintptr_t enable_pasting_address = 0;
}

// this for storing the real values gt server sends us
namespace real_state {
	inline player_flag flags = player_flag::none;

	inline std::uint8_t build_range = 2;
	inline std::uint8_t punch_range = 2;

	inline float speed = 250.f;
	inline float gravity = 1000.f;
	inline float water_speed = 125.f;
	inline float acceleration_speed = 0.f;

	inline std::uint8_t punch_effect = 0;
	inline std::uint32_t pupil_color = 0;
	inline std::uint32_t hair_color = 0;
	inline std::uint32_t eye_color = 0;
};
