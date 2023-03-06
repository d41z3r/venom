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
	hook_function(gt::send_packet_raw, send_packet_raw_hook);

	console::print_good("installed hooks\n");
}

void hooks::send_packet_hook(net_message_type type, const std::string& packet, void* peer) {
	using enum net_message_type;

	switch (type) {
	case generic_text:
		console::print<console::color::cyan>(std::format("sending generic text: {}\n", packet));
		break;

	case game_message:
		console::print<console::color::blue>(std::format("sending game message: {}\n", packet));
		break;

	default:
		console::print<console::color::yellow>(std::format("sending unknown packet: {}\n", packet));
		break;
	}

	gt::send_packet(type, packet, peer);
}


void hooks::send_packet_raw_hook(net_message_type type, const void* data, std::int32_t data_size, std::uint8_t* unk1, void* peer, std::uint32_t flags) {
	if (type != net_message_type::game_packet || data_size != sizeof(game_packet_t)) // this should never happen
		return;

	const game_packet_t* packet = static_cast<const game_packet_t*>(data);
	console::print<console::color::magenta>(std::format("sending game packet, type: {}\n", static_cast<int>(packet->type)));

	gt::send_packet_raw(type, data, data_size, unk1, peer, flags);
}
