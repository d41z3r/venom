#pragma once
#include <cstdint>
#include <list>

#pragma pack(push, 1)
struct inventory_item_t {
	std::uint16_t item_id;
	std::uint8_t count;
	std::uint8_t flags;
};

struct player_items_t {
	void* vftable;
	std::uint8_t pad1[24]; // clothes
	std::list<inventory_item_t> items; // 0x20
	std::uint8_t pad2[8]; // slots
	std::uint32_t backpack_size; // 0x38
	// more
};
#pragma pack(pop)
