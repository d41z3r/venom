#include <hooks/hooks.hpp>
#include <game/gt.hpp>
#include <external/minhook/include/MinHook.h>
#include <utils/console.hpp>

#include <stdexcept>
#include <format>

void hook_function(auto& function, const auto& hook_function) {
	void* address = function;
	void* original = nullptr;

	if (MH_CreateHook(address, hook_function, &original) != MH_OK)
		throw std::runtime_error("failed to create hook");

	if (MH_EnableHook(address) != MH_OK)
		throw std::runtime_error("failed to enable hook");

	function = reinterpret_cast<decltype(function)>(original);
}

void hooks::install() {
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("failed to initialize minhook");

	hook_function(gt::send_packet, send_packet_hook);
}

void hooks::send_packet_hook(int type, std::string packet, void* peer) {
	// todo: bunch of fun stuff here

	gt::send_packet(type, packet, peer);
}
