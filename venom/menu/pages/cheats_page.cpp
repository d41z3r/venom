#include <menu/menu.hpp>
#include <game/gt.hpp>
#include <utils/memory.hpp>

void menu::cheats_page() noexcept {
	ImGui::Columns(3, "cheat columns", false);
	ImGui::Checkbox("anti deadly", &cheats::anti_deadly);
	ImGui::Checkbox("anti bouncy", &cheats::anti_bouncy);
	ImGui::Checkbox("anti damage", &cheats::anti_damage);
	ImGui::Checkbox("anti checkpoint", &cheats::anti_checkpoint);
	ImGui::Checkbox("anti zombie", &cheats::anti_zombie);
	ImGui::Checkbox("anti knockback", &cheats::anti_knockback);

	ImGui::NextColumn();

	ImGui::Checkbox("night vision", &cheats::night_vision);
	ImGui::Checkbox("see fruits", &cheats::see_fruits);
	ImGui::Checkbox("see ghosts", &cheats::see_ghosts);
	ImGui::Checkbox("fake lag", &cheats::fake_lag); // todo: make this show to our client aswell
	ImGui::Checkbox("ghost mode", &cheats::ghost_mode);
	ImGui::Checkbox("mod zoom", &cheats::mod_zoom);

	ImGui::NextColumn();

	ImGui::Checkbox("walk in air", &cheats::walk_in_air); // todo: set save.dat move_down hotkeys on startup
	ImGui::Checkbox("unlimited jumps", &cheats::unlimited_jumps);
	ImGui::Checkbox("super punch", &cheats::super_punch);
	ImGui::Checkbox("block ads", &cheats::block_ads);

	// with this u can keep holding punch and it won't stop punching, normally stops after 11 seconds
	if (ImGui::Checkbox("touch bypass", &cheats::touch_bypass)) // todo: better way to do this and better name for this
		memory::patch_bytes(gt::touch_bypass_address, cheats::touch_bypass ? "eb" : "72");

	// this is a moderator feature, but instead of setting local_player->is_mod to true
	// we do this because then you can paste everywhere, not only in world
	if (ImGui::Checkbox("enable pasting", &cheats::enable_pasting)) // todo: better way to do this
		memory::patch_bytes(gt::enable_pasting_address, cheats::enable_pasting ? "75" : "74");

	ImGui::EndColumns();
}
