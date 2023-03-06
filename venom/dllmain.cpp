#include <game/gt.hpp>
#include <hooks/hooks.hpp>
#include <utils/memory.hpp>
#include <utils/console.hpp>

#include <stdexcept>
#include <windows.h>

void on_injected() noexcept {
	console::setup();
	console::print<console::color::red>("venom, growtopia cheat by cmc\n\n");

	try {
		gt::setup();
		hooks::install();
	}
	catch (const std::runtime_error& error) { 
		console::print_error(error.what()); 
		return; 
	}

	console::print<console::color::green>("\ncheat loaded successfully\n\n");
}

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hmodule);
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(on_injected), nullptr, 0, nullptr);
	}
	return TRUE;
}

