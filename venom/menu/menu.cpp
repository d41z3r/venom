#include <menu/menu.hpp>
#include <game/gt.hpp>
#include <utils/console.hpp>

#include <array>

void menu::setup() {
	ImGui::CreateContext();
	ImGui_ImplDX9_Init(gt::renderer->device);
	ImGui_ImplWin32_Init(gt::hwnd);

	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	style.FramePadding = { 4.f, 4.f };
	style.WindowBorderSize = 0.f;

	colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.08f, 0.10f, 1.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.35f, 0.00f, 0.78f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.35f, 0.00f, 0.78f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.35f, 0.00f, 0.78f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.35f, 0.00f, 0.78f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.45f, 0.00f, 1.00f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.35f, 0.00f, 0.78f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.40f, 0.00f, 0.90f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.45f, 0.00f, 1.00f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);

	console::print_good("initialized imgui");
}

void menu::render() noexcept {
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (show) {
		ImGui::ShowDemoWindow();

		ImGui::SetNextWindowPos({ 10.f, 10.f }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ 550.f, 350.f }, ImGuiCond_Once);

		ImGui::Begin("venom", &show, ImGuiWindowFlags_NoCollapse);

		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, 100.f);

		static constexpr std::array pages = { "cheats", "testpage1", "testpage2" };
		static constinit std::size_t current_page = 0;

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.f, 0.f });
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.4f, 0.5f });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.18f, 0.18f, 0.18f, 1.00f });

		for (std::size_t i = 0; i < pages.size(); ++i) {
			const bool is_current_page = current_page == i;

			if (is_current_page) {
				ImGui::PushStyleColor(ImGuiCol_Button, { 0.27f, 0.27f, 0.27f, 1.00f });
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.27f, 0.27f, 0.27f, 1.00f });
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.27f, 0.27f, 0.27f, 1.00f });
			}

			if (ImGui::Button(pages[i], { 100.f, 40.f }))
				current_page = i;

			const ImVec2 pos = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddRectFilled(pos, { pos.x + 5.f, pos.y - 40.f },
				is_current_page ? ImColor(0.35f, 0.10f, 0.78f, 1.00f) : ImColor(0.18f, 0.05f, 0.39f, 1.00f));

			if (is_current_page)
				ImGui::PopStyleColor(3);
		}

		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);

		ImGui::NextColumn();
		ImGui::BeginChild("page", { 0.f, 0.f }, true);

		switch (current_page) {
		case 0: cheats_page(); break;

		default:
			ImGui::TextColored({ 1.f, 0.f, 0.f, 1.f }, "this page doesn't exist");
			break;
		}

		ImGui::EndChild();
		ImGui::EndColumns();
		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
