#include <menu/menu.hpp>
#include <utils/memory.hpp>

bool ImGui::Checkbox(const char* label, bool* v, std::uintptr_t address, std::string_view new_bytes, std::string_view original_bytes) {
	bool ret = ImGui::Checkbox(label, v);

	if (ret)
		memory::patch_bytes(address, *v ? new_bytes : original_bytes);

	return ret;
}
