#include <hooks/hooks.hpp>
#include <menu/menu.hpp>
#include <utils/memory.hpp>

void hooks::update_hook(app_t* _this) {
	gt::update(_this);

	game_logic_component_t* game_logic = gt::get_game_logic();
	if (game_logic == nullptr)
		return;

	net_avatar_t* local_player = game_logic->local_player;
	if (local_player == nullptr)
		return;


	local_player->is_mod = cheats::mod_zoom;

	if (cheats::unlimited_jumps)
		local_player->can_jump = true;

	if (cheats::ghost_mode)
		memory::set_bit(local_player->flags, player_flag::no_clip);
	else if (!memory::has_bit(real_state::flags, player_flag::no_clip))
		memory::remove_bit(local_player->flags, player_flag::no_clip);
		
}
