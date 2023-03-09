#include <menu/menu.hpp>
#include <game/gt.hpp>
#include <utils/memory.hpp>

#include <format>
#include <array>

void main_page() noexcept {
	ImGui::Columns(3, "cheat columns", false);
	ImGui::Checkbox("anti damage", &cheats::anti_damage);
	ImGui::Checkbox("anti zombie", &cheats::anti_zombie);
	ImGui::Checkbox("anti knockback", &cheats::anti_knockback);

	ImGui::NextColumn();

	ImGui::Checkbox("fake lag", &cheats::fake_lag); // todo: make this show to our client aswell
	ImGui::Checkbox("night vision", &cheats::night_vision);
	ImGui::Checkbox("block ads", &cheats::block_ads);

	ImGui::NextColumn();

	ImGui::Checkbox("walk in air", &cheats::walk_in_air); // todo: add S to go down
	ImGui::Checkbox("super punch", &cheats::super_punch);

	// with this u can keep holding punch and it won't stop punching, normally stops after 11 seconds
	if (ImGui::Checkbox("touch bypass", &cheats::touch_bypass)) // todo: better way to do this and better name for this
		memory::patch_bytes(gt::touch_bypass_address, cheats::touch_bypass ? "eb" : "72");

	ImGui::EndColumns();
}

void menu::cheats_page() noexcept {
	static constinit std::size_t current_tab = 0;

	ImExtra::HorizontalTabs({
		"main",
		"testpage1",
		"testpage2"
		}, current_tab);

	switch (current_tab) {
	case 0: main_page(); break;

	default:
		ImGui::TextColored({ 1.f, 0.f, 0.f, 1.f }, "this page doesn't exist");
		break;
	}
}
