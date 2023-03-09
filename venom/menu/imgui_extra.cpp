#include <menu/imgui_extra.hpp>

void ImExtra::VerticalTabs(const std::vector<const char*>& tabs, std::size_t& current_tab, ImVec2 tab_size) noexcept {
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.f, 0.f });
	ImGui::PushStyleColor(ImGuiCol_Button, { 0.18f, 0.18f, 0.18f, 1.00f });

	for (std::size_t i = 0; i < tabs.size(); ++i) {
		const bool is_current_tab = current_tab == i;

		if (is_current_tab) {
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.27f, 0.27f, 0.27f, 1.00f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.27f, 0.27f, 0.27f, 1.00f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.27f, 0.27f, 0.27f, 1.00f });
		}

		if (ImGui::Button(tabs[i], tab_size))
			current_tab = i;

		const ImVec2 pos = ImGui::GetCursorScreenPos();
		ImGui::GetWindowDrawList()->AddRectFilled(pos, { pos.x + 5.f, pos.y - tab_size.y },
			is_current_tab ? ImColor(0.45f, 0.00f, 1.00f, 1.00f) : ImGui::IsItemHovered() ? ImColor(0.35f, 0.00f, 0.75f, 1.00f) : ImColor(0.18f, 0.05f, 0.39f, 1.00f));

		if (is_current_tab)
			ImGui::PopStyleColor(3);
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
}

void ImExtra::HorizontalTabs(const std::vector<const char*>& tabs, std::size_t& current_tab) noexcept {
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.f, 0.f });
	ImGui::PushStyleColor(ImGuiCol_Button, { 0.18f, 0.18f, 0.18f, 1.00f });

	const float button_width = ImGui::GetContentRegionAvail().x / tabs.size();

	for (std::size_t i = 0; i < tabs.size(); ++i) {
		const bool is_current_tab = current_tab == i;

		if (is_current_tab) {
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.27f, 0.27f, 0.27f, 1.00f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.27f, 0.27f, 0.27f, 1.00f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.27f, 0.27f, 0.27f, 1.00f });
		}

		if (ImGui::Button(tabs[i], { button_width, 30.f }))
			current_tab = i;

		ImGui::SameLine();

		const ImVec2 pos = ImGui::GetCursorScreenPos();
		ImGui::GetWindowDrawList()->AddRectFilled({ pos.x, pos.y + 30.f }, { pos.x - button_width, pos.y + 27.f },
			is_current_tab ? ImColor(0.45f, 0.00f, 1.00f, 1.00f) : ImGui::IsItemHovered() ? ImColor(0.35f, 0.00f, 0.75f, 1.00f) : ImColor(0.18f, 0.05f, 0.39f, 1.00f));

		if (is_current_tab)
			ImGui::PopStyleColor(3);
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleVar();

	ImGui::NewLine();
	ImGui::Dummy({ 0.f, 5.f });
}
