#pragma once
#include <menu/menu.hpp>

#include <string>
#include <vector>
#include <functional>

namespace ImExtra {
	void VerticalTabs(const std::vector<const char*>& tabs, std::size_t& current_tab, ImVec2 tab_size) noexcept;
	void HorizontalTabs(const std::vector<const char*>& tabs, std::size_t& current_tab) noexcept;
}
