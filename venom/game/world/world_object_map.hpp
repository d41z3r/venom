#pragma once
#include <game/world/world_object.hpp>

#include <list>

#pragma pack(push, 1)
struct world_object_map_t {
    void* vftable;
    std::uint8_t pad1[72];
    std::list<world_object_t> objects;
};
#pragma pack(pop)
