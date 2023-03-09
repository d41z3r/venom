#include <menu/menu.hpp>
#include <game/gt.hpp>

#include <format>

void menu::cheats_page() noexcept {
	ImGui::Checkbox("anti damage", &cheats::anti_damage);
	ImGui::Checkbox("anti zombie", &cheats::anti_zombie);
	ImGui::Checkbox("anti knockback", &cheats::anti_knockback);
	ImGui::Checkbox("fake lag", &cheats::fake_lag); // todo: make this show to our client aswell
	ImGui::Checkbox("night vision", &cheats::night_vision);
	ImGui::Checkbox("block ads", &cheats::block_ads);
	ImGui::Checkbox("walk in air", &cheats::walk_in_air); // todo: add S to go down
	ImGui::Checkbox("super punch", &cheats::super_punch);
}
