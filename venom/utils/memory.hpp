#pragma once
#include <cstdint>
#include <string_view>
#include <type_traits>

namespace memory {
	template <typename T, typename = void>
	struct get_underlying {
		using type = T;
	};

	template <typename T>
	struct get_underlying<T, std::enable_if_t<std::is_enum_v<T>>> {
		using type = std::underlying_type_t<T>;
	};

	template <typename value_type, typename bit_type>
	inline void remove_bit(value_type& value, bit_type bit) noexcept {
		using type = get_underlying<bit_type>::type;
		value = static_cast<value_type>(static_cast<type>(value) & ~(static_cast<type>(bit)));
	}

	template <typename value_type, typename bit_type>
	inline void set_bit(value_type& value, bit_type bit) noexcept {
		using type = get_underlying<bit_type>::type;
		value = static_cast<value_type>(static_cast<type>(value) | (static_cast<type>(bit)));
	}

	template <typename value_type, typename bit_type>
	inline void toggle_bit(value_type& value, bit_type bit) noexcept {
		using type = get_underlying<bit_type>::type;
		value = static_cast<value_type>(static_cast<type>(value) ^ (static_cast<type>(bit)));
	}

	template <typename value_type, typename bit_type>
	inline bool has_bit(value_type value, bit_type bit) noexcept {
		using type = get_underlying<bit_type>::type;
		return (static_cast<type>(value) & static_cast<type>(bit)) != 0;
	}

	template <typename value_type>
	inline void append_read(value_type& value, std::uint8_t*& data) noexcept {
		value = *reinterpret_cast<value_type*>(data);
		data += sizeof(value_type);
	}

	template <typename size_type = std::uint32_t>
	inline void append_read_string(std::string& str, std::uint8_t*& data) noexcept {
		size_type size;
		append_read(size, data);
		str = std::string{ reinterpret_cast<char*>(data), size };
		data += size;
	}

	bool patch_bytes(std::uintptr_t address, std::string_view bytes) noexcept;
	std::uintptr_t find_pattern(std::string_view pattern, std::intptr_t offset = 0) noexcept;
	std::uintptr_t get_address_from_call(std::uintptr_t address) noexcept;
	std::uintptr_t get_address_from_load(std::uintptr_t address) noexcept;
	std::uintptr_t find_function_start(std::uintptr_t address) noexcept;
}
