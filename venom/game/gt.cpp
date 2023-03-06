#include <game/gt.hpp>
#include <utils/memory.hpp>
#include <utils/console.hpp>

#include <stdexcept>
#include <string>
#include <format>

bool patch_integrity_check() noexcept {
	std::uintptr_t integrity_check = memory::find_pattern("00 3b c1 75 08 85 c9", 3);

	if (integrity_check == 0)
		return memory::find_pattern("00 3b c1 90 90 85 c9") != 0; // check if it's already patched

	return memory::patch_bytes(integrity_check, "90 90");
}

enum class find_mode {
	normal,
	call,
	load
};

void find_address(auto& dest, std::string_view pattern, find_mode mode = find_mode::normal, std::intptr_t offset = 0) {
	std::uintptr_t address = memory::find_pattern(pattern, offset);

	switch (mode) {
	case find_mode::call:
		address = memory::get_address_from_call(address);
		break;

	case find_mode::load:
		address = memory::get_address_from_load(address);
		break;

	default:
		break;
	}

	if (address == 0)
		throw std::runtime_error(std::format("pattern '{}' not found", pattern));

	dest = reinterpret_cast<decltype(dest)>(address);
}

void find_addresses() {
	find_address(gt::get_app, "c3 e8 ? ? ? ? 48 8b c8 33 d2", find_mode::call, 1);
	find_address(gt::set_fps_limit, "e8 ? ? ? ? e8 ? ? ? ? 83 e8", find_mode::call);
	find_address(gt::log_to_console, "e8 ? ? ? ? 48 8b c8 e8 ? ? ? ? 90 48 8d 4d ? e8 ? ? ? ? e8", find_mode::call, 8);
	find_address(gt::send_packet, "02 00 00 00 e8 ? ? ? ? 90 48 8d 4c 24 50", find_mode::call, 4);

	find_address(gt::renderer, "48 8b 05 ? ? ? ? 75 ? c6 43", find_mode::load);
}

void gt::setup() {
	using namespace console;

	MODULEINFO module_info = {};
	if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &module_info, sizeof(MODULEINFO)))
		throw std::runtime_error("failed to get module information");

	base_address = reinterpret_cast<std::uintptr_t>(module_info.lpBaseOfDll);
	end_address = base_address + module_info.SizeOfImage;
	if (base_address == 0 || end_address == 0)
		throw std::runtime_error("invalid module address");

	hwnd = FindWindow(nullptr, "Growtopia");
	if (hwnd == nullptr)
		throw std::runtime_error("growtopia window not found");

	if (!patch_integrity_check())
		throw std::runtime_error("failed to patch integrity check");

	print_good("patched integrity check\n");

	find_addresses();
	print_good("found all addresses\n");

	set_fps_limit(get_app(), 0.f);
	print_good("unlocked fps limit\n");
}
