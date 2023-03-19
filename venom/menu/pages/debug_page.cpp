#include <menu/menu.hpp>
#include <game/gt.hpp>

#include <format>

void debug_button(const char* name, auto address) {
	std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(address);

	if (ImGui::Button(std::format("copy##{}", name).c_str()))
		ImGui::SetClipboardText(std::format("{:x}", addr).c_str());

	ImGui::SameLine();

	ImGui::Text("%s: 0x%llx", name, addr);
}

void menu::debug_page() noexcept {
	app_t* app = gt::get_app();
	game_logic_component_t* game_logic = gt::get_game_logic();
	enet_client_t* client = gt::get_client();

	debug_button("app", app);
	debug_button("enet client", client);
	debug_button("game logic", game_logic);

	if (game_logic != nullptr) {
		debug_button("world", game_logic->world);
		if (game_logic->world != nullptr) {
			debug_button("world tile map", &game_logic->world->tile_map);
			debug_button("world object map", &game_logic->world->object_map);
		}
		debug_button("world renderer", game_logic->world_renderer);
		debug_button("net object manager", &game_logic->net_object_manager);
		debug_button("local player", game_logic->local_player);
		debug_button("player items", &game_logic->player_items);
	}
}
