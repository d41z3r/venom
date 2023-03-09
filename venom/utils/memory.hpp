#pragma once
#include <cstdint>
#include <string_view>
#include <type_traits>

namespace memory {
	inline void remove_bit(auto& value, auto bit) noexcept {
		value &= ~(static_cast<std::underlying_type_t<decltype(bit)>>(bit));
	}

	inline void set_bit(auto& value, auto bit) noexcept {
		value |= static_cast<std::underlying_type_t<decltype(bit)>>(bit);
	}

	inline void toggle_bit(auto& value, auto bit) noexcept {
		value ^= static_cast<std::underlying_type_t<decltype(bit)>>(bit);
	}

	inline bool has_bit(auto value, auto bit) noexcept {
		return (value & static_cast<std::underlying_type_t<decltype(bit)>>(bit)) != 0;
	}

	bool patch_bytes(std::uintptr_t address, std::string_view bytes) noexcept;
	std::uintptr_t find_pattern(std::string_view pattern, std::intptr_t offset = 0) noexcept;
	std::uintptr_t get_address_from_call(std::uintptr_t address) noexcept;
	std::uintptr_t get_address_from_load(std::uintptr_t address) noexcept;
	std::uintptr_t find_function_start(std::uintptr_t address) noexcept;
}
