#pragma once
#include <game/utils/math.hpp>

#include <cstdint>

#pragma pack(push, 1)
class world_object_t {
public:
    void* vtable;
    vec2f_t pos;
    std::uint16_t item_id;
    std::uint8_t count;
    std::uint8_t flags;
    std::uint32_t object_id;
    std::uint8_t pad1[24];
};
#pragma pack(pop)

static_assert(sizeof(world_object_t) == 0x30);