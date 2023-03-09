#include <menu/menu.hpp>
#include <game/gt.hpp>
#include <utils/console.hpp>

void menu::setup() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplDX9_Init(gt::renderer->device);
	ImGui_ImplWin32_Init(gt::hwnd);

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

		cheats_page();

		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
