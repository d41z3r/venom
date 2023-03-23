#pragma once
#include <game/manager/variant_db.hpp>

#include <cstdint>
#include <string>

class entity_t;

#pragma pack(push, 1)
class entity_component_t {
public:
	virtual ~entity_component_t();
	virtual void on_add(entity_t* entity);
	virtual void on_remove();

	std::uint8_t sig_trackable[16];
	std::string* name;
	entity_t* parent;
	variant_db_t shared_db;
};
#pragma pack(pop)

