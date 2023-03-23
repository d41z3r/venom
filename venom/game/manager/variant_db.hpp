#pragma once
#include <string>

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>

class variant_t;

#pragma pack(push,1 )
class variant_db_t {
public:
	void* vftable;
	stdext::hash_map<std::string, variant_t*> data;
	std::uint8_t pad[64];
	decltype(data)::iterator next_itor;
};
#pragma pack(pop)
