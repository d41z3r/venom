#pragma once
#include <game/manager/variant_db.hpp>

#include <cstdint>
#include <string>
#include <list>

class entity_component_t;

#pragma pack(push, 1)
class entity_t {
public:
    void* vftable;
    std::uint8_t pad1[48];
    std::string name;
    std::list<entity_t*> children;
    std::uint8_t pad2[80];
    std::list<entity_component_t*> components;
    std::uint8_t pad3[80];
    variant_db_t shared_db;
    entity_t* parent;
};
#pragma pack(pop)

