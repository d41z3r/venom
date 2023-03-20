#pragma once
#include <game/utils/math.hpp>

#include <cstdint>
#include <string>

enum class variant_type : std::uint32_t {
	unused,
	float32,
	string,
	vec2,
	vec3,
	uint32,
	entity,
	component,
	rect,
	int32
};

#pragma pack(push, 1)
class variant_t {
public:
	variant_type type;
	std::uint8_t unk1[4];
	void* pvoid;

	union {
		std::uint8_t value[16];
		float float_value;
		vec2f_t vec2_value;
		vec3f_t vec3_value;
		std::uint32_t uint_value;
		vec4f_t rect_value;
		std::int32_t int_value;
	};

	std::string string_value;
	std::uint8_t sig_onchanged[16];
};

class variant_list_t {
public:
	void serialize_from_mem(std::uint8_t* data) noexcept {

	}

	std::uint8_t* serialize_to_mem(std::size_t* size_out) noexcept {
		return nullptr;
	}

	inline variant_t& get(std::size_t index) noexcept { return variants[index]; }
	inline const variant_t& get(std::size_t index) const noexcept { return variants[index]; }

	inline variant_t& operator[](std::size_t index) noexcept { return variants[index]; }
	inline const variant_t& operator[](std::size_t index) const noexcept { return variants[index]; }

	variant_t variants[6];
};

#pragma pack(pop)
