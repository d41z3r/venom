#include <hooks/hooks.hpp>
#include <menu/menu.hpp>
#include <utils/console.hpp>
#include <utils/memory.hpp>
#include <game/utils/text_scanner.hpp>
#include <external/minhook/include/MinHook.h>
#include <external/magic_enum/magic_enum.hpp>

#include <stdexcept>
#include <format>
#include <sstream>

void hook_function(auto& function, const auto& hook_function) {
	void* address = function;
	void* original = nullptr;

	if (MH_CreateHook(address, hook_function, &original) != MH_OK)
		throw std::runtime_error("failed to create hook");

	if (MH_EnableHook(address) != MH_OK)
		throw std::runtime_error("failed to enable hook");

	function = reinterpret_cast<decltype(function)>(original);
}

void hooks::install() {
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("failed to initialize minhook");

	hook_function(gt::update, update_hook);
	hook_function(gt::send_packet, send_packet_hook);
	hook_function(gt::send_packet_raw, send_packet_raw_hook);
	hook_function(gt::on_text_game_message, on_text_game_message_hook);
	hook_function(gt::process_tank_update_packet, process_tank_update_packet_hook);
	hook_function(gt::handle_track_packet, handle_track_packet_hook);
	hook_function(gt::on_punched, on_punched_hook);
	hook_function(gt::is_darkened, is_darkened_hook);
	hook_function(gt::is_anzu_platform, is_anzu_platform_hook);
	hook_function(gt::collide, collide_hook);
	hook_function(gt::server_info_http_finish, server_info_http_finish_hook);
	hook_function(gt::get_fruit_bloom_progress_percent, get_fruit_bloom_progress_percent_hook);
	hook_function(gt::can_see_ghosts, can_see_ghosts_hook);
	hook_function(gt::on_touched_deadly, on_touched_deadly_hook);
	hook_function(gt::bumped_bouncy, bumped_bouncy_hook);
	hook_function(gt::handle_tile_damage_vertically, handle_tile_damage_vertically_hook);
	hook_function(gt::handle_tile_damage_horizontally, handle_tile_damage_horizontally_hook);
	hook_function(gt::update_from_net_avatar, update_from_net_avatar_hook);
	hook_function(gt::is_checkpoint, is_checkpoint_hook);
	hook_function(gt::handle_touch_at_world_coordinates, handle_touch_at_world_coordinates_hook);
	hook_function(gt::camera_on_update, camera_on_update_hook);

	hook_function(gt::end_scene, end_scene_hook);
	original_wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(gt::hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&wnd_proc_hook)));

	console::print_good("installed hooks");
}

void hooks::send_packet_hook(net_message_type type, std::string packet, void* peer) {
	using enum net_message_type;

	switch (type) {
	case generic_text: {
		text_scanner_t data(packet);

		if (data.has("game_version")) { // todo: spoof login values
			data.set("country", "ly");
			packet = data.build();
		}

		console::println<console::color::cyan>(std::format("sending generic text: {}", packet));
		break;
	}

	case game_message:
		console::println<console::color::blue>(std::format("sending game message: {}", packet));
		break;

	default:
		console::println<console::color::yellow>(std::format("sending unknown packet: {}", packet));
		break;
	}

	gt::send_packet(type, packet, peer);
}


void hooks::send_packet_raw_hook(net_message_type type, const void* data, std::int32_t data_size, std::uint8_t* unk1, void* peer, std::uint32_t flags) {
	if (type != net_message_type::game_packet || data_size != sizeof(game_packet_t)) // this should never happen
		return;

	game_packet_t* packet = const_cast<game_packet_t*>(static_cast<const game_packet_t*>(data));

	switch (packet->type) {
	case game_packet_type::state:
		if (cheats::ghost_mode)
			return;

		// if u are standing on spike for too long u get ban, this bypasses it
		if (cheats::anti_deadly)
			memory::remove_flag(packet->flags, visual_state::on_solid);

		if (cheats::fake_lag)
			memory::set_flag(packet->flags, visual_state::on_spawn);

		if (cheats::super_punch && memory::has_flag(packet->flags, visual_state::on_punched))
			memory::set_flag(packet->flags, visual_state::on_power_up_punch_end);

		// if you send walk packets in air you will get banned so lets set player velocity as 0 so server thinks we are not walking
		if (cheats::walk_in_air)
			packet->vec2 = { 0.f, 0.f };

		break;

	case game_packet_type::ping_reply:
		packet->byte2 = 0; // jump count
		packet->byte3 = 0; // unknown, when set to 1 we get autoban
		packet->vec1.x = real_state::punch_range * 32.f;
		packet->vec1.y = real_state::build_range * 32.f;

		// local player check because if u are in exit it won't send player speed, gravity, etc.
		if (gt::get_game_logic()->local_player != nullptr) {
			packet->int1 = static_cast<std::int32_t>(real_state::flags);
			packet->vec2.x = real_state::gravity;
			packet->vec2.y = real_state::speed;
		}

		gt::log_to_console("`4venom:`` `ospoofing ping reply``");
		break;

	case game_packet_type::got_punched:
		// this also blocks rapier effect and game generator game damage
		if (cheats::anti_zombie)
			return;
		break;

	case game_packet_type::app_integrity_fail:
		gt::log_to_console(std::format("`4venom:`` `oblocking client hack report`` `5(type {})``", packet->int3));
		return;
		break;

	default:
		break;
	}

	console::println<console::color::green>(std::format("sending game packet '{}'", magic_enum::enum_name(packet->type)));

	gt::send_packet_raw(type, data, data_size, unk1, peer, flags);
}

void hooks::process_tank_update_packet_hook(game_logic_component_t* _this, game_packet_t* packet) {

	switch (packet->type) {
	case game_packet_type::call_function: {
		variant_list_t var_list(packet->get_extra_data());
		console::println(std::format("incoming call function '{}'", var_list.get(0).get_string()));
		break;
	}

	case game_packet_type::set_character_state:
		if (packet->int1 == gt::get_game_logic()->local_player->net_id) {
			vec2f_t old_vec2 = { real_state::speed, real_state::gravity };

			real_state::flags = static_cast<player_flag>(packet->int3);

			real_state::build_range = packet->byte2 - 126;
			real_state::punch_range = packet->byte3 - 126;

			real_state::water_speed = packet->float1;
			real_state::acceleration_speed = packet->vec1.x;
			real_state::speed = packet->vec2.x;
			real_state::gravity = packet->vec2.y;

			real_state::punch_effect = packet->byte1;
			real_state::pupil_color = packet->int2;
			real_state::hair_color = packet->int4;
			real_state::eye_color = packet->int5;

			if (cheats::anti_ghost) {
				memory::remove_flag(packet->flags, 0x800); // mind control
				if (packet->vec2.x == old_vec2.x - 150.f && packet->vec2.y != old_vec2.y)
					packet->vec2 = old_vec2;
			}
		}
		break;

	default:
		break;
	}

	console::println<console::color::red>(std::format("incoming game packet '{}'", magic_enum::enum_name(packet->type)));

	gt::process_tank_update_packet(_this, packet);
}

void hooks::on_text_game_message_hook(game_logic_component_t* _this, const char* packet) {

	gt::on_text_game_message(_this, packet);
}

void hooks::handle_track_packet_hook(track_handler_component_t* _this, const char* packet) {

	gt::handle_track_packet(_this, packet);
}

void hooks::on_punched_hook(net_avatar_t* _this, vec2f_t unk1, net_avatar_t* puncher) {
	if (cheats::anti_knockback)
		return;

	gt::on_punched(_this, unk1, puncher);
}

std::int32_t hooks::is_darkened_hook(std::int32_t item_id) {
	if (cheats::night_vision)
		return 0;

	return gt::is_darkened(item_id);
}

bool hooks::is_anzu_platform_hook() {
	if (cheats::block_ads)
		return false;

	return gt::is_anzu_platform();
}

bool hooks::collide_hook(world_tile_map_t* _this, float unk1, float unk2, float unk3, float unk4, int unk5, bool unk6) {
	if (cheats::walk_in_air && !gt::get_game_logic()->local_player->down_key_state)
		return true;

	return gt::collide(_this, unk1, unk2, unk3, unk4, unk5, unk6);
}

void hooks::server_info_http_finish_hook(variant_list_t* var_list) {
	console::println(var_list->get(1).get_string());
	gt::server_info_http_finish(var_list);
}

float hooks::get_fruit_bloom_progress_percent_hook(tile_t* _this) {
	if (cheats::see_fruits)
		return 1.0f;

	return gt::get_fruit_bloom_progress_percent(_this);
}

bool hooks::can_see_ghosts_hook(std::int32_t item_id) {
	if (cheats::see_ghosts)
		return true;

	return gt::can_see_ghosts(item_id);
}

void hooks::on_touched_deadly_hook(net_avatar_t* _this, tile_t* tile) {
	if (cheats::anti_deadly)
		return; // todo: use player_state::spikeproof instead of this hook

	gt::on_touched_deadly(_this, tile);
}

void hooks::bumped_bouncy_hook(net_avatar_t* _this, tile_t* unk1, float* unk2, float* unk3) {
	if (cheats::anti_bouncy)
		return;

	gt::bumped_bouncy(_this, unk1, unk2, unk3);
}

void hooks::handle_tile_damage_vertically_hook(net_avatar_t* _this, float* unk1, float* unk2, bool unk3, bool unk4) {
	if (cheats::anti_damage)
		return;

	gt::handle_tile_damage_vertically(_this, unk1, unk2, unk3, unk4);
}

void hooks::handle_tile_damage_horizontally_hook(net_avatar_t* _this, float* unk1, float* unk2, bool unk3, bool unk4) {
	if (cheats::anti_damage)
		return;

	gt::handle_tile_damage_horizontally(_this, unk1, unk2, unk3, unk4);
}

void hooks::update_from_net_avatar_hook(avatar_render_data_t* _this, net_avatar_t* net_avatar) {
	// todo: client sided visual local player state things

	//float original_velocity_x = net_avatar->velocity.x.get();
	//float original_velocity_y = net_avatar->velocity.y.get();

	//net_avatar->velocity.x.set(0.f);
	//net_avatar->velocity.y.set(0.f);

	//gt::update_from_net_avatar(_this, net_avatar);

	//net_avatar->velocity.x.set(original_velocity_x);
	//net_avatar->velocity.y.set(original_velocity_y);

	gt::update_from_net_avatar(_this, net_avatar);
}

bool hooks::is_checkpoint_hook(tile_t* _this) {
	if (cheats::anti_checkpoint)
		return false;

	return gt::is_checkpoint(_this);
}

void hooks::handle_touch_at_world_coordinates_hook(level_touch_component_t* _this, vec2f_t* pos, bool unk1) {
	if (cheats::click_tp && (GetKeyState(VK_CONTROL) & 0x8000)) {
		net_avatar_t* local_player = gt::get_game_logic()->local_player;

		vec2i_t start = local_player->get_tile_pos();
		vec2i_t goal = { static_cast<std::int32_t>(pos->x / 32.f), static_cast<std::int32_t>(pos->y / 32.f) };
		if (start == goal)
			return;

		auto path = gt::find_path(start, goal);
		if (path.empty())
			return;

		std::size_t count = 0;
		for (vec2i_t pos : path) {
			if (++count % 7 == 0 || count == path.size()) {
				game_packet_t packet = {};
				packet.type = game_packet_type::state;
				packet.vec1 = { static_cast<float>(pos.x) * 32.f, static_cast<float>(pos.y) * 32.f };
				gt::send_game_packet(packet);
			}
		}

		local_player->set_pos_at_tile(goal);
		return;
	}

	gt::handle_touch_at_world_coordinates(_this, pos, unk1);
}

void hooks::camera_on_update_hook(world_camera_t* _this, vec2f_t unk1, vec2f_t unk2) {
	if (cheats::click_tp && (GetKeyState(VK_CONTROL) & 0x8000))
		return;

	gt::camera_on_update(_this, unk1, unk2);
}

HRESULT hooks::end_scene_hook(IDirect3DDevice9* _this) {
	menu::render();
	return gt::end_scene(_this);
}

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

LRESULT hooks::wnd_proc_hook(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return TRUE;

	if (msg == WM_KEYUP && wparam == VK_INSERT)
		menu::show = !menu::show;

	const ImGuiIO& io = ImGui::GetIO();

	bool mouse =
		msg == WM_LBUTTONDOWN ||
		msg == WM_RBUTTONDOWN ||
		msg == WM_LBUTTONDBLCLK ||
		msg == WM_RBUTTONDBLCLK ||
		msg == WM_MOUSEWHEEL;

	if (io.WantTextInput || (io.WantCaptureMouse && mouse))
		return TRUE;

	return original_wnd_proc(hwnd, msg, wparam, lparam);
}
