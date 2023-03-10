#include <menu/menu.hpp>
#include <game/gt.hpp>
#include <utils/memory.hpp>

void menu::cheats_page() noexcept {
	ImGui::SeparatorText("cheats");

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
