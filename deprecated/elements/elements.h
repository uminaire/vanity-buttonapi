#pragma once

namespace elements
{

	namespace qm


	{
		namespace pro

		{



			static UnityEngine::GameObject* selected_user_menu()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new("CanvasGroup/Container/Window/QMParent/Body/Menu_SelectedUser_Local/ScrollRect/Viewport/VerticalLayoutGroup/Buttons_UserActions"));
				
				if (!c)
				{
					c_logger->print(encrypt("selected_user_menu invalid"));
					return {};

			
				}

				return c;
			}

			static UnityEngine::GameObject* clear_panel()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new("CanvasGroup/Container/Window/Panel_QM_Widget/Panel_QM_DebugInfo"));
				if (!c)
				{
					c_logger->print(encrypt("clear_panel invalid"));
					return {};

				}
				return c;
			}


			static UnityEngine::GameObject* launch_calendar()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new("CanvasGroup/Container/Window/QMParent/Body/Menu_QM_Launchpad/Header_H1/RightItemContainer/Button_QM_Calendar"));
				if (!c)
				{
					c_logger->print(encrypt("launch_calendar invalid"));
					return {};

				}
				return c;
			}

			static UnityEngine::GameObject* launch_calendarparent()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new("CanvasGroup/Container/Window/QMParent/Body/Menu_QM_Launchpad/Header_H1/RightItemContainer"));
				if (!c)
				{
					c_logger->print(encrypt("launch_calendarparent invalid"));
					return {};

				}
				return c;
			}



			static UnityEngine::GameObject* cell_container()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new(encrypt("CanvasGroup/Container/Window/QMParent/Body/Menu_QM_GeneralSettings/Panel_QM_ScrollRect/Viewport/VerticalLayoutGroup/Sharing/QM_Settings_Panel/VerticalLayoutGroup/")));

				if (!c)
				{
					c_logger->print(encrypt("cell_container invalid"));
					return {};

				}

				return c;

			}

			static UnityEngine::GameObject* cell_button()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new(encrypt("CanvasGroup/Container/Window/QMParent/Body/Menu_QM_AudioSettings/Panel_QM_ScrollRect/Viewport/VerticalLayoutGroup/Microphone/QM_Settings_Panel/VerticalLayoutGroup/NoiseSuppression")));

				if (!c)
				{
					c_logger->print(encrypt("cell_button invalid"));
					return {};

				}

				return c;

			}

			static UnityEngine::GameObject* cell_selector()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new(encrypt("CanvasGroup/Container/Window/QMParent/Body/Menu_QM_GeneralSettings/Panel_QM_ScrollRect/Viewport/VerticalLayoutGroup/UIElements/QM_Settings_Panel/VerticalLayoutGroup/NameplateVisibility")));

				if (!c)
				{
					c_logger->print(encrypt("cell_selector invalid"));

					return {};

				}

				return c;

			}

			static UnityEngine::GameObject* cell_slider()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new(encrypt("CanvasGroup/Container/Window/QMParent/Body/Menu_QM_GeneralSettings/Panel_QM_ScrollRect/Viewport/VerticalLayoutGroup/DisplayAndVisualAdjustments/QM_Settings_Panel/VerticalLayoutGroup/ScreenBrightness")));

				if (!c)
				{
					c_logger->print(encrypt("cell_selector invalid"));

					return {};

				}

				return c;

			}

			static UnityEngine::GameObject* layout_group()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new(encrypt("Container/Window/QMParent/Body/Menu_DevTools/Scrollrect/Viewport/VerticalLayoutGroup/Buttons")));

				if (!c)
				{
					c_logger->print(encrypt("layout_group invalid"));

					return {};

				}

				return c;

			}

			static UnityEngine::GameObject* button()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new(encrypt("CanvasGroup/Container/Window/QMParent/Body/Menu_Camera/Scrollrect/Viewport/VerticalLayoutGroup/Buttons/Button_GalleryCamera")));

				if (!c)
				{
					c_logger->print(encrypt("button invalid"));

					return {};

				}

				return c;

			}

			static UnityEngine::GameObject* toggle_button()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new(encrypt("CanvasGroup/Container/Window/QMParent/Body/Menu_DevTools/Scrollrect/Viewport/VerticalLayoutGroup/Buttons/Button_Tag")));

				if (!c)
				{
					c_logger->print(encrypt("toggle_button invalid"));

					return {};

				}

				return c;

			}

			static UnityEngine::GameObject* menu_settings()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new(encrypt("Container/Window/QMParent/Body/Menu_QM_GeneralSettings")));

				if (!c)
				{
					c_logger->print(encrypt("menu_settings invalid"));

					return {};

				}

				return c;

			}


			static UnityEngine::GameObject* menu_launchpad()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new(encrypt("Container/Window/QMParent/Body/Menu_QM_Launchpad")));

				if (!c)
				{
					c_logger->print(encrypt("menu_settings invalid"));

					return {};

				}

				return c;

			}

			static UnityEngine::GameObject* qm_parent()
			{

				auto c = globals::buttonapi::quick_menu::container->Find(Il2Cpp::API::il2cpp_string_new(encrypt("Container/Window/QMParent/Body")));

				if (!c)
				{
					c_logger->print(encrypt("menu_settings invalid"));

					return {};

				}

				return c;

			}


		}



		namespace utils

		{

			static void clean_children(UnityEngine::RectTransform* rect) {

				for (int i = rect->get_childCount() - 1; i >= 0; i--) {

					auto* child = rect->GetChild(i);

					if (!child) continue;

					UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(child->get_gameObject()));

				}
			}


			static void disable_style_element(UnityEngine::GameObject* c_qmobj)
			{
				if (!c_qmobj) return;

				auto* c_style = c_qmobj->GetComponentT<UnityEngine::Behaviour>("VRC.UI.Core.Styles.StyleElement");

				if (c_style)

					c_style->set_enabled(false);

			}





			UnityEngine::Transform* place_textmesh_internal(UnityEngine::Transform* parent, const char* string)
			{
				auto* button = elements::qm::pro::button();

				if (!button) return {};

				auto* c_button = button->GetComponentInChildrenT<UnityEngine::Component>(get_class_TextMeshProEx(), true);

				if (!c_button) return {};

				auto* c_object = reinterpret_cast<UnityEngine::GameObject*>(UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(c_button->get_gameObject()), parent));

				if (!c_object) return {};


				auto* c_text = c_object->GetComponentInChildrenT<TextMeshProEx>(get_class_TextMeshProEx(), true);


				if (!c_text) return {};


				if (c_text)
				{

					unity::reworked::vrc::reworked::elements::clear_localizable(reinterpret_cast<TextMeshProEx*>(c_text));

					c_text->set_text(Il2Cpp::Utils::to_il2cpp_string(string));

					c_text->set_richText(true);

					c_text->set_alignment(TMPro::TextAlignmentOptions::TopLeft);

					c_text->set_fontSize(100.0f);

					c_text->set_enableWordWrapping(false);

					elements::qm::utils::disable_style_element(c_object);


					c_text->set_color(unity::reworked::visual::utils::make_color(1.0f, 1.0f, 1.0f, 1.0f));


					c_text->set_fontSize({ 30.0f });
				}


				auto* c_recttransform = reinterpret_cast<UnityEngine::RectTransform*>(c_object->get_transform());


				if (!c_recttransform) return {};


				c_recttransform->set_anchorMin({ 0, 0 });
				c_recttransform->set_anchorMax({ 1, 1 });


				c_recttransform->set_offsetMin({ 10.0f, 0.0f });
				c_recttransform->set_offsetMax({ 0.0f, 0.0f });


				c_recttransform->set_anchoredPosition({ -400.0f, 0.0f });

				c_object->SetActive(true);

				return c_object->get_transform();

			}



			UnityEngine::Transform* place_text(UnityEngine::Transform* c_parent, const char* c_text, ImVec4 c_color, UnityEngine::Vector2 c_anchor_min, UnityEngine::Vector2 c_anchor_max, UnityEngine::Vector2 c_size, UnityEngine::Vector2 c_position)
			{
				auto* c_txt = place_textmesh_internal(c_parent, c_text);


				if (!c_txt) return nullptr;

				auto* c_recttransform = reinterpret_cast<UnityEngine::RectTransform*>(c_txt);

				c_recttransform->set_anchorMin(c_anchor_min);

				c_recttransform->set_anchorMax(c_anchor_max);


				c_recttransform->set_sizeDelta(c_size);

				c_recttransform->set_anchoredPosition(c_position);



				auto* c_tmp = c_txt->get_gameObject()->GetComponentInChildrenT<TextMeshProEx>(get_class_TextMeshProEx(), true);


				if (c_tmp)

					c_tmp->set_color(unity::reworked::visual::utils::make_color(c_color.x, c_color.y, c_color.z, c_color.w));


				return c_txt;


			}





		}



	}
}