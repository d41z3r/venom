#include <menu/menu.hpp>
#include <game/gt.hpp>
#include <utils/console.hpp>

void menu::setup() {
	ImGui::CreateContext();
	ImGui_ImplDX9_Init(gt::renderer->device);
	ImGui_ImplWin32_Init(gt::hwnd);

	console::print_good("initialized imgui\n");
}

void menu::render() noexcept {
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (show) {
		ImGui::Begin("venom");

		enet_client_t* client = gt::get_client();
		if (client != nullptr && client->peer != nullptr) {
			ImGui::Text("connected to %s:%d", client->server_ip, client->server_port);
			ImGui::Text("logon mode is %d", client->lmode);
		}

		static char packet[256];
		ImGui::InputTextMultiline("##packet", packet, IM_ARRAYSIZE(packet));

		if (ImGui::Button("send generic text"))
			gt::send_generic_text(packet);

		ImGui::SameLine();

		if (ImGui::Button("send game message"))
			gt::send_game_message(packet);

		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
