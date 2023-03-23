#pragma once
#include <game/manager/variant_db.hpp>

#include <cstdint>
#include <string>
#include <list>

class entity_component_t;

#pragma pack(push, 1)
class entity_t {
public:
    virtual ~entity_t();

    boost_trackable_signal_t trackable_signal;
    boost_signal_t sig_on_removed;
    std::string name;
    std::list<entity_t*> children;
    std::uint8_t pad2[80];
    std::list<entity_component_t*> components;
    std::uint8_t pad3[80];
    variant_db_t shared_db;
    entity_t* parent;
    bool tagged_for_deletion;
};
#pragma pack(pop)

