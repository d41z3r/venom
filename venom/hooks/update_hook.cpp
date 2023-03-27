#include <hooks/hooks.hpp>
#include <menu/menu.hpp>
#include <utils/memory.hpp>

void hooks::app_update_hook(app_t* _this) {
	gt::app_update(_this);

	game_logic_component_t* game_logic = gt::get_game_logic();
	constants_t* constants = gt::get_constants();
	if (game_logic == nullptr || constants == nullptr)
		return;

	net_avatar_t* local_player = game_logic->local_player;
	if (local_player == nullptr)
		return;

	local_player->is_mod = cheats::mod_zoom;

	if (cheats::unlimited_jumps)
		local_player->can_jump = true;

	if (cheats::anti_freeze)
		memory::remove_flag(local_player->flags, player_flag::frozen);
	else if (memory::has_flag(real_state::flags, player_flag::frozen))
		memory::add_flag(local_player->flags, player_flag::frozen);

	if (cheats::ghost_mode)
		memory::add_flag(local_player->flags, player_flag::no_clip);
	else if (!memory::has_flag(real_state::flags, player_flag::no_clip))
		memory::remove_flag(local_player->flags, player_flag::no_clip);

	(cheats::fast_punch) ?
		constants->punch_reload_time.set(0.15f) :
		constants->punch_reload_time.set(0.2f);
}
