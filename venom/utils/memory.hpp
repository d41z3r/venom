#pragma once
#include <cstdint>
#include <string_view>

namespace memory {
	bool patch_bytes(std::uintptr_t address, std::string_view bytes) noexcept;
	std::uintptr_t find_pattern(std::string_view pattern, std::intptr_t offset = 0) noexcept;
	std::uintptr_t get_address_from_call(std::uintptr_t address) noexcept;
	std::uintptr_t get_address_from_load(std::uintptr_t address) noexcept;
}
