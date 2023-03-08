#include <menu/menu.hpp>
#include <game/gt.hpp>

void menu::cheats_page() noexcept {
	ImGui::Checkbox("anti damage", &cheats::anti_damage);
	ImGui::Checkbox("fake lag", &cheats::fake_lag);
}
