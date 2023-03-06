#pragma once
#include <string>

namespace hooks {
	void install();

	void send_packet_hook(int type, std::string packet, void* peer);
}