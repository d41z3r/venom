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

		ImGui::SeparatorText("texture test");
		static int texture_id = 0;
		ImGui::InputInt("texture id", &texture_id);

		const auto& texture = gt::renderer->textures[texture_id];
		ImGui::Image(
			texture.ptr, 
			{ static_cast<float>(texture.width), static_cast<float>(texture.height) },
			{ 0.f, 1.f },
			{ 1.f, 0.f }
		);

		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
