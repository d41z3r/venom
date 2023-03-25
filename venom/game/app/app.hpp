#pragma once
#include <game/app/base_app.hpp>
#include <game/component/game_logic_component.hpp>
#include <game/component/track_handler_component.hpp>
#include <game/manager/item_info_manager.hpp>
#include <game/manager/tile_sheet_manager.hpp>
#include <game/manager/player_tribute_manager.hpp>
#include <game/manager/variant_db.hpp>

#include <cstdint>

#pragma pack(push, 1)
class app_t : public base_app_t {
public:
    variant_t* get_var(const std::string& key_name) noexcept {
        return var_db.get_var(key_name);
    }

    std::uint8_t pad1[64];
    game_logic_component_t* game_logic; // 0xab0
    track_handler_component_t* track_handler; // 0xab8
    item_info_manager_t item_info_manager; // 0xac0
    tile_sheet_manager_t tile_sheet_manager; // 0xaf8
    player_tribute_manager_t* player_tribute_manager; // 0xb18
    std::uint8_t pad2[1136];
    variant_db_t var_db;
};
#pragma pack(pop)
