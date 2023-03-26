#include <game/gt.hpp>
#include <utils/memory.hpp>
#include <utils/console.hpp>
#include <utils/random.hpp>

#include <stdexcept>
#include <string>
#include <format>
#include <fstream>

void patch_integrity_check() {
	std::uintptr_t integrity_check = memory::find_pattern("00 3b c1 75 08 85 c9", 3);

	if (integrity_check == 0)
		throw std::runtime_error("integrity check pattern not found");

	if (!memory::patch_bytes(integrity_check, "90 90"))
		throw std::runtime_error("failed to patch integrity check");
}

enum class find_mode {
	normal,
	call,
	load,
	function_start
};

void find_address(auto& dest, std::string_view pattern, find_mode mode, std::intptr_t offset = 0) {
	std::uintptr_t address = memory::find_pattern(pattern, offset);

	switch (mode) {
	case find_mode::call:
		address = memory::get_address_from_call(address);
		break;

	case find_mode::load:
		address = memory::get_address_from_load(address);
		break;

	case find_mode::function_start:
		address = memory::find_function_start(address);
		break;

	default:
		break;
	}

	if (address == 0)
		throw std::runtime_error(std::format("pattern '{}' not found", pattern));

	dest = reinterpret_cast<decltype(dest)>(address);
}

void find_addresses() { // todo: actually make good patterns instead of just using sigmaker
	// globals
	find_address(gt::get_app, "c3 e8 ? ? ? ? 48 8b c8 33 d2", find_mode::call, 1);
	find_address(gt::get_entity_root, "90 e8 ? ? ? ? 48 8d 54 24 ? 48 8b c8", find_mode::call, 1);
	find_address(gt::get_client, "75 ? e8 ? ? ? ? 48 83 b8", find_mode::call, 2);
	find_address(gt::get_game_logic, "48 8b 80 ? ? ? ? eb", find_mode::function_start);
	find_address(gt::get_item_info_manager, "e8 ? ? ? ? 48 8b c8 8b 57 ? e8 ? ? ? ? 33 f6", find_mode::call);
	find_address(gt::log_to_console, "e8 ? ? ? ? 48 8b c8 e8 ? ? ? ? 90 48 8d 4d ? e8 ? ? ? ? e8", find_mode::call, 8);
	find_address(gt::send_packet, "02 00 00 00 e8 ? ? ? ? 90 48 8d 4c 24 50", find_mode::call, 4);
	find_address(gt::send_packet_raw, "7e ? 8b 94 24", find_mode::function_start);
	find_address(gt::is_darkened, "e8 ? ? ? ? 84 c0 74 ? 48 8b d6 49 8b cd", find_mode::call);
	find_address(gt::can_see_ghosts, "0f b6 44 24 ? eb ? e8", find_mode::function_start);
	find_address(gt::is_anzu_platform, "e8 ? ? ? ? 84 c0 0f 84 ? ? ? ? 80 be", find_mode::call);
	find_address(gt::server_info_http_finish, "48 8d 45 ? 48 89 44 24 ? 44 8d 4b ? 4c 8d 45", find_mode::function_start);

	// app
	find_address(gt::app_update, "90 48 8d 8f ? ? ? ? 45 33 c9", find_mode::function_start);
	find_address(gt::set_fps_limit, "e8 ? ? ? ? e8 ? ? ? ? 83 e8", find_mode::call);
	
	// game logic
	find_address(gt::on_text_game_message, "48 8b d3 e8 ? ? ? ? eb ? 49 8b 4f", find_mode::call, 3);
	find_address(gt::process_tank_update_packet, "48 8b d3 e8 ? ? ? ? eb ? 48 8d 0d", find_mode::call, 3);
	
	// net avatar
	find_address(gt::on_punched, "b8 ? ? ? ? 66 39 83 ? ? ? ? 75 ? 48 8d 83", find_mode::function_start);
	find_address(gt::on_touched_deadly, "e8 ? ? ? ? 32 c0 eb ? cc", find_mode::call);
	find_address(gt::bumped_bouncy, "e8 ? ? ? ? 32 c0 e9 ? ? ? ? bd", find_mode::call);
	find_address(gt::handle_tile_damage_vertically, "e8 ? ? ? ? 32 c0 e9 ? ? ? ? 83 f9 ? 75 ? 4d 8b ce", find_mode::call);
	find_address(gt::handle_tile_damage_horizontally, "e8 ? ? ? ? 32 c0 e9 ? ? ? ? 83 f9 ? 75 ? 4d 8b cf", find_mode::call);

	// tile
	find_address(gt::is_checkpoint, "e8 ? ? ? ? 84 c0 74 ? 0f b7 46", find_mode::call);
	find_address(gt::is_collidable, "e8 ? ? ? ? 84 c0 0f 84 ? ? ? ? 0f b7 5e", find_mode::call);
	find_address(gt::get_fruit_bloom_progress_percent, "e8 ? ? ? ? 0f b6 47 ? 44 0f 28 c0", find_mode::call);

	// others
	find_address(gt::handle_track_packet, "48 8b 88 ? ? ? ? e8 ? ? ? ? eb ? 48 8d 0d", find_mode::call, 7);
	find_address(gt::handle_touch_at_world_coordinates, "66 39 48 ? 0f 84 ? ? ? ? c6 05", find_mode::function_start);
	find_address(gt::camera_on_update, "f3 0f 10 02 f3 41 0f 5e 00", find_mode::function_start);
	find_address(gt::collide, "e8 ? ? ? ? 48 85 c0 74 ? 48 89 07 48 8b cb", find_mode::call);
	find_address(gt::update_from_net_avatar, "e8 ? ? ? ? 49 8b ce e8 ? ? ? ? 48 8b d8", find_mode::call);
	find_address(gt::check_item_for_updates, "48 8d 15 ? ? ? ? e8 ? ? ? ? ff c3 e8", find_mode::call, 7);
	find_address(gt::create_text_label_entity, "48 8b cf e8 ? ? ? ? 48 8b d8 f3 0f 10 54 24", find_mode::call, 3);
	find_address(gt::create_text_button_entity, "e8 ? ? ? ? 4c 8b f0 0f 57 c0 66 0f 7f 45", find_mode::call);
	find_address(gt::get_surface_anim, "e8 ? ? ? ? 48 8b c8 48 85 c0 75 ? 48 8d 55", find_mode::call);

	// just addresses
	find_address(gt::anti_slide_address, "74 4d 48 8b 45 ? 0f b7 58", find_mode::normal);
	find_address(gt::anti_portal_address, "74 ? 41 89 8e", find_mode::normal);
	find_address(gt::anti_water_address, "0f 84 ? ? ? ? 80 be ? ? ? ? ? bf", find_mode::normal);
	find_address(gt::see_locked_doors_address, "40 84 ff 74 ? 4c 89 7d", find_mode::normal, 3);
	find_address(gt::touch_bypass_address, "3d ? ? ? ? 72 ? c6 83", find_mode::normal, 5);
	find_address(gt::enable_pasting_address, "74 ? 83 f9 ? 0f 85 ? ? ? ? 83 7f", find_mode::normal);
	find_address(gt::renderer, "48 8b 05 ? ? ? ? 75 ? c6 43", find_mode::load, 3);
	find_address(gt::constants, "f3 44 0f 10 0d ? ? ? ? f3 44 0f 5c c9", find_mode::load, 5);

	// get end_scene from d3d9 device's vftable
	gt::end_scene = reinterpret_cast<decltype(gt::end_scene)>((*reinterpret_cast<void***>(gt::get_renderer()->device_ex))[42]);
}

void create_watermark() noexcept {
	using namespace random;

	entity_t* watermark = gt::create_text_label_entity(gt::get_entity_root(), "Watermark", 8.f, static_cast<float>(gt::window_size.y - 85), "venom");

	watermark->get_var("color")->set(
		(random_num(0xff) << 24) | // blue
		(random_num(0xff) << 16) | // green
		(random_num(0xff) << 8) |  // red
		0xffu                      // alpha
	);

	watermark->get_var("scale2d")->set(vec2f_t{ 0.5f, 0.5f });
	watermark->get_component_by_name("TextRender")->get_var("font")->set(1u);
	watermark->get_component_by_name("TextRender")->get_var("shadowColor")->set(150u);
}

void gt::setup() {
	using namespace console;

	MODULEINFO module_info = {};
	if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &module_info, sizeof(MODULEINFO)))
		throw std::runtime_error("failed to get module information");

	base_address = reinterpret_cast<std::uintptr_t>(module_info.lpBaseOfDll);
	end_address = base_address + module_info.SizeOfImage;
	if (base_address == 0 || end_address == 0)
		throw std::runtime_error("invalid module address");

	hwnd = FindWindow(nullptr, "Growtopia");
	if (hwnd == nullptr)
		throw std::runtime_error("growtopia window not found");

	RECT rect = {};
	if (!GetWindowRect(gt::hwnd, &rect))
		throw std::runtime_error("failed to get window size");

	window_size.x = rect.left - rect.right;
	window_size.y = rect.bottom - rect.top;

	patch_integrity_check();
	print_good("patched integrity check");

	close_mutexes();
	print_good("closed mutexes");

	find_addresses();
	print_good("found addresses");

	set_fps_limit(get_app(), 0.f);
	print_good("unlocked fps limit");

	create_watermark();
	print_good("created watermark");

	gt::get_app()->get_var("move_down_primary")->set(83u);   // S key
	gt::get_app()->get_var("move_down_secondary")->set(40u); // arrow down key
}

renderer_context_d3d9_t* gt::get_renderer() noexcept {
	return *renderer;
}

constants_t* gt::get_constants() noexcept {
	return constants;
}

void gt::send_generic_text(const std::string& packet) noexcept {
	enet_client_t* client = gt::get_client();
	if (client == nullptr || client->peer == nullptr)
		return;

	send_packet(net_message_type::generic_text, packet, client->peer);
}

void gt::send_game_message(const std::string& packet) noexcept {
	enet_client_t* client = gt::get_client();
	if (client == nullptr || client->peer == nullptr)
		return;

	send_packet(net_message_type::game_message, packet, client->peer);
}

void gt::send_game_packet(const game_packet_t& packet) noexcept {
	enet_client_t* client = gt::get_client();
	if (client == nullptr || client->peer == nullptr)
		return;

	send_packet_raw(net_message_type::game_packet, &packet, sizeof(game_packet_t), nullptr, client->peer, 0x1);
}

void gt::process_game_message(const std::string& packet) noexcept {
	game_logic_component_t* game_logic = gt::get_game_logic();
	if (game_logic == nullptr)
		return;

	on_text_game_message(game_logic, packet.c_str());
}

void gt::process_game_packet(const game_packet_t& packet) noexcept {
	game_logic_component_t* game_logic = gt::get_game_logic();
	if (game_logic == nullptr)
		return;

	process_tank_update_packet(game_logic, const_cast<game_packet_t*>(&packet));
}

void gt::process_call_function(const variant_list_t& var_list, std::int32_t net_id, std::int32_t delay) noexcept {
	game_logic_component_t* game_logic = gt::get_game_logic();
	if (game_logic == nullptr)
		return;

	std::uint32_t data_size = 0;
	std::uint8_t* data = var_list.serialize_to_mem(&data_size);

	game_packet_t* packet = static_cast<game_packet_t*>(std::malloc(sizeof(game_packet_t) + data_size));
	std::memset(&*packet, 0, sizeof(game_packet_t) + data_size);

	packet->type = game_packet_type::call_function;
	packet->flags = 0x8; // game_packet_flag::extra_data
	packet->int1 = net_id;
	packet->int3 = delay;
	packet->extra_data_size = data_size;

	std::memcpy(packet->get_extra_data(), data, data_size);

	process_tank_update_packet(game_logic, packet);

	std::free(packet);
	delete[] data;
}

void gt::process_track_packet(const std::string& packet) noexcept {
	app_t* app = gt::get_app();
	if (app == nullptr || app->track_handler == nullptr)
		return;

	handle_track_packet(app->track_handler, packet.c_str());
}

std::uint32_t gt::hash_data(std::uint8_t* data, std::size_t data_size) noexcept {
	std::uint32_t hash = 0x55555555;

	for (std::size_t i = 0; i < data_size; ++i)
		hash = (hash >> 27) + (hash << 5) + static_cast<std::uint32_t>(*data++);

	return hash;
}

std::uint32_t gt::hash_string(const std::string& str) noexcept {
	return hash_data(
		reinterpret_cast<std::uint8_t*>(const_cast<char*>(str.data())),
		str.size()
	);
}

std::uint32_t gt::get_file_hash(const std::string& filename) noexcept {
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	if (!file.is_open())
		return 0;

	std::size_t file_size = static_cast<std::size_t>(file.tellg());
	file.seekg(0, std::ios::beg);

	std::uint8_t* file_data = new std::uint8_t[file_size];
	file.read(reinterpret_cast<char*>(file_data), file_size);
	file.close();

	std::uint32_t hash = hash_data(file_data, file_size);

	delete[] file_data;

	return hash;
}
