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

		ImGui::Columns(2, "main columns", true);
		ImGui::SetColumnWidth(0, 135.f);

		static constinit std::size_t current_tab = 0;
		ImExtra::VerticalTabs({
			"cheats", 
			"testpage1",
			"testpage2"
			}, current_tab, {120.f, 40.f});

		ImGui::NextColumn();
		ImGui::BeginChild("page", { 0.f, 0.f }, false);

		switch (current_tab) {
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
