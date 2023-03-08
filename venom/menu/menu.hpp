#pragma once
#include <external/imgui/imgui.h>
#include <external/imgui/imgui_internal.h>
#include <external/imgui/imgui_impl_dx9.h>
#include <external/imgui/imgui_impl_win32.h>

namespace menu {
	void setup();
	void render() noexcept;

	inline bool show = true;
}
