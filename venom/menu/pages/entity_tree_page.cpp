#include <menu/menu.hpp>
#include <game/gt.hpp>
#include <external/magic_enum/magic_enum.hpp>

#include <format>

entity_t* selected_entity = nullptr;

void imgui_entity(entity_t* entity) {
	bool this_selected = selected_entity == entity;

	if (entity->children.empty()) {
		ImGui::Bullet();
		ImGui::Selectable(entity->name.c_str(), this_selected);

		if (ImGui::IsItemClicked())
			selected_entity = entity;
	}
	else {
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		if (this_selected)
			flags |= ImGuiTreeNodeFlags_Selected;

		bool open = ImGui::TreeNodeEx(entity->name.c_str(), flags);

		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			selected_entity = entity;

		if (open) {
			for (entity_t* child : entity->children)
				imgui_entity(child);

			ImGui::TreePop();
		}
	}
}

void imgui_variant_db(const variant_db_t& var_db) {
	for (const auto& [name, variant] : var_db.data) {
		if (ImGui::TreeNode(std::format("{} ({})", name, magic_enum::enum_name(variant->get_type())).c_str())) {

			switch (variant->get_type()) {
			case variant_type::float32:
				ImGui::InputFloat("value", &variant->float_value);
				break;

			case variant_type::string: {
				char* text = const_cast<char*>(variant->string_value.c_str());
				ImGui::InputText("value", text, 256);
				variant->string_value = text;
				break;
			}

			case variant_type::vec2:
				ImGui::InputFloat("x value", &variant->vec2_value.x);
				ImGui::InputFloat("y value", &variant->vec2_value.y);
				break;

			case variant_type::vec3:
				ImGui::InputFloat("x value", &variant->vec3_value.x);
				ImGui::InputFloat("y value", &variant->vec3_value.y);
				ImGui::InputFloat("z value", &variant->vec3_value.z);
				break;

			case variant_type::rect:
				ImGui::InputFloat("x value", &variant->rect_value.x);
				ImGui::InputFloat("y value", &variant->rect_value.y);
				ImGui::InputFloat("z value", &variant->rect_value.z);
				ImGui::InputFloat("w value", &variant->rect_value.w);
				break;

			case variant_type::uint32:
			case variant_type::int32:
				ImGui::InputInt("value", &variant->int_value);
				break;

			default:
				ImGui::TextColored({ 1.f, 0.f, 0.f, 1.f }, "unknown variant type");
				break;
			}

			ImGui::TreePop();
		}
	}
}

// pretty messy and buggy atm, i will fix later
void menu::entity_tree_page() noexcept {
	ImGui::Columns(2, "entity columns", false);

	imgui_entity(gt::get_entity_root());

	ImGui::NextColumn();

	if (selected_entity != nullptr) {
		ImGui::SeparatorText(selected_entity->name.c_str());

		if (selected_entity->parent != nullptr)
			ImGui::Text("parent: %s", selected_entity->parent->name.c_str());

		if (ImGui::TreeNode("variants")) {
			imgui_variant_db(selected_entity->shared_db);
			ImGui::TreePop();
		}

		if (!selected_entity->components.empty()) {
			if (ImGui::TreeNode("components")) {
				for (entity_component_t* component : selected_entity->components) {
					std::string text = std::format("{} (0x{:x})", component->name->c_str(), reinterpret_cast<std::uintptr_t>(component));
					if (component->shared_db.data.empty()) {
						ImGui::BulletText(text.c_str());
					}
					else {
						if (ImGui::TreeNode(text.c_str())) {
							imgui_variant_db(component->shared_db);
							ImGui::TreePop();
						}
					}
				}
				ImGui::TreePop();
			}

		}
	}

	ImGui::EndColumns();
}
