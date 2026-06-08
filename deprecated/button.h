#pragma once

namespace quickmenu
{

    static const char* button_prefix = "Button_";
    static const char* toggle_prefix = "ButtonToggle_";


    static bool* toggle_states[32] = {};
    static int   toggle_count      = 0;
    static ToggleButtonHandle* toggle_handle_ptrs[32] = {};


    template<int N> static void toggle_thunk()
    {
        if (toggle_states[N]) *toggle_states[N] = !*toggle_states[N];
    }

    static const auto toggle_thunks = make_thunk_table(toggle_thunk, 64);


    static UnityEngine::Transform* button(UnityEngine::Transform* parent, const char* name, void(*func)(), UnityEngine::Sprite* sprite)
    {

        auto* c_src = elements::qm::pro::button();

        if (!c_src) return {};


        auto* c_obj = reinterpret_cast<UnityEngine::GameObject*>(UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(c_src), parent));

        if (!c_obj) return {};

        UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(c_obj));


        c_obj->SetActive(true);

        reinterpret_cast<UnityEngine::Object*>(c_obj)->set_name(Il2Cpp::Utils::to_il2cpp_string(std::string(button_prefix) + name));


        auto* c_button  = c_obj->GetComponentT<UnityEngine::UI::Button>(get_class_MenuTab());

        auto* c_text    = c_obj->GetComponentInChildrenT<TextMeshProEx>(get_class_TextMeshProEx(), true);

        auto* c_image   = c_obj->get_transform()->GetChild(3)->GetChild(0)->get_gameObject()->GetComponentT<VRC::UI::ImageEx>(get_class_VRC_UI_ImageEx());
        auto* c_tooltip = c_obj->GetComponentT<UnityEngine::UI::Button>(get_class_ToolTip());


        if (c_tooltip)
        {

            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_tooltip));

            c_obj->AddComponentT<void>(reinterpret_cast<Il2Cpp::Class*>(get_class_ToolTip()));

        }


        auto* on_click = reinterpret_cast<UnityEngine::Events::UnityEvent*>(c_button->get_onClick());

        on_click->RemoveAllListeners();

        if (func) on_click->AddListener(unity::reworked::action::make(func));


        if (c_text)
        {

            unity::reworked::vrc::reworked::elements::clear_localizable(c_text);

            c_text->set_text(Il2Cpp::Utils::to_il2cpp_string(name));

            c_text->set_richText(true);

        }


        if (c_image && sprite)
        {

            c_image->set_sprite(sprite);

            c_image->set_overrideSprite({});

        }


        return c_obj->get_transform();

    }


    static UnityEngine::Transform* panel_button(UnityEngine::Transform* parent, const char* name, void(*func)(), UnityEngine::Sprite* sprite)
    {

        auto* c_src = elements::qm::pro::button();

        if (!c_src) return {};


  
        auto* c_obj = reinterpret_cast<UnityEngine::GameObject*>(UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(c_src), parent));

        if (!c_obj) return {};

        UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(c_obj));




        c_obj->SetActive(false);

        reinterpret_cast<UnityEngine::Object*>(c_obj)->set_name(Il2Cpp::Utils::to_il2cpp_string(std::string(button_prefix) + name));


        auto* c_button  = c_obj->GetComponentT<UnityEngine::UI::Button>(get_class_MenuTab());
        auto* c_text    = c_obj->GetComponentInChildrenT<TextMeshProEx>(get_class_TextMeshProEx(), true);
        auto* c_icons   = c_obj->get_transform()->Find(Il2Cpp::Utils::to_il2cpp_string("Icons"));
        auto* c_tooltip = c_obj->GetComponentT<UnityEngine::UI::Button>(get_class_ToolTip());


        if (c_icons)
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_icons->get_gameObject()));


        if (c_tooltip)
        {

            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_tooltip));

            c_obj->AddComponentT<void>(reinterpret_cast<Il2Cpp::Class*>(get_class_ToolTip()));

        }


        auto* on_click = reinterpret_cast<UnityEngine::Events::UnityEvent*>(c_button->get_onClick());

        on_click->RemoveAllListeners();

        if (func) on_click->AddListener(unity::reworked::action::make(func));


        if (c_text)
        {


            unity::reworked::vrc::reworked::elements::clear_localizable(c_text);


            SetField<VRC::Localization::LocalizableString*>(c_text, 1960, {});

            c_text->set_text(Il2Cpp::Utils::to_il2cpp_string(name));

            c_text->set_richText(true);

            c_text->set_alignment(TMPro::TextAlignmentOptions::Center);

            c_text->set_enableWordWrapping(false);


            auto* c_text_transform = reinterpret_cast<UnityEngine::Component*>(c_text)->get_transform();


            auto pos = c_text_transform->get_localPosition();

            pos.y += 4.0f;

            c_text_transform->set_localPosition(pos);


            auto scale = c_text_transform->get_localScale();

            scale.x *= 1.3f;
            scale.y *= 1.3f;
            scale.z *= 1.3f;

            c_text_transform->set_localScale(scale);

        }


        auto* c_layout = c_obj->AddComponentT<void>(reinterpret_cast<Il2Cpp::Class*>(Il2Cpp::Utils::find_klass("UnityEngine.UI.LayoutElement")));

        if (c_layout)
        {

            Il2Cpp::Class* klass  = *reinterpret_cast<Il2Cpp::Class**>(c_layout);
            void*          method = Il2Cpp::API::il2cpp_class_get_method_from_name(klass, "set_flexibleWidth", 1);

            if (method)
            {

                float val    = 1.0f;
                void* args[] = { &val };
                void* exc    = {};

                Il2Cpp::API::il2cpp_runtime_invoke(method, c_layout, args, &exc);

            }

        }


        c_obj->SetActive(true);

        UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(c_obj));

        return c_obj->get_transform();

    }


    static UnityEngine::Transform* panel_separator(UnityEngine::Transform* parent, float height = 10.0f)
    {
        auto c_obj = reinterpret_cast<UnityEngine::GameObject*>(Il2Cpp::API::il2cpp_object_new(get_class_UnityEngine_GameObject()));

        if (!c_obj) return {};

        c_obj->ctor_0();

        reinterpret_cast<UnityEngine::Object*>(c_obj)->set_name(Il2Cpp::Utils::to_il2cpp_string("separator"));

        c_obj->get_transform()->set_parent(parent);

        UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(c_obj));

        auto c_layout = c_obj->AddComponentT<void>(reinterpret_cast<Il2Cpp::Class*>(Il2Cpp::Utils::find_klass("UnityEngine.UI.LayoutElement")));
        if (c_layout)
        {
            Il2Cpp::Class* klass = *reinterpret_cast<Il2Cpp::Class**>(c_layout);

            void* set_height = Il2Cpp::API::il2cpp_class_get_method_from_name(klass, "set_preferredHeight", 1);
            if (set_height)
            {
                void* args[] = { &height };
                void* exc = {};
                Il2Cpp::API::il2cpp_runtime_invoke(set_height, c_layout, args, &exc);
            }

            void* set_flexible = Il2Cpp::API::il2cpp_class_get_method_from_name(klass, "set_flexibleWidth", 1);
            if (set_flexible)
            {
                float val = 1.0f;
                void* args[] = { &val };
                void* exc = {};
                Il2Cpp::API::il2cpp_runtime_invoke(set_flexible, c_layout, args, &exc);
            }
        }

        return c_obj->get_transform();
    }

    static UnityEngine::Transform* toggle_button(UnityEngine::Transform* parent, const char* name, void(*func)(), bool default_state, UnityEngine::Sprite* sprite_on, UnityEngine::Sprite* sprite_off)
    {

        auto* c_src = elements::qm::pro::toggle_button();

        if (!c_src) return {};


        auto* c_obj = reinterpret_cast<UnityEngine::GameObject*>(UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(c_src), parent));

        if (!c_obj) return {};

        UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(c_obj));



        reinterpret_cast<UnityEngine::Object*>(c_obj)->set_name(Il2Cpp::Utils::to_il2cpp_string(std::string(toggle_prefix) + name));


        auto* c_handle    = c_obj->GetComponentT<ToggleButtonHandle>(get_class_ToggleButtonHandle());


        auto* c_text      = c_obj->GetComponentInChildrenT<TextMeshProEx>(get_class_TextMeshProEx(), true);
        auto* c_image_on  = c_obj->get_transform()->GetChild(2)->GetChild(1)->get_gameObject()->GetComponentT<VRC::UI::ImageEx>(get_class_VRC_UI_ImageEx());
        auto* c_image_off = c_obj->get_transform()->GetChild(2)->GetChild(0)->get_gameObject()->GetComponentT<VRC::UI::ImageEx>(get_class_VRC_UI_ImageEx());


        c_handle->Internal_field_ToggleButtonHandle__controlName_0 = Il2Cpp::Utils::to_il2cpp_string(name);


        auto* on_value_changed = reinterpret_cast<UnityEngine::Events::UnityEvent*>(c_handle->Internal_field_Toggle_onValueChanged_0);

        if (func)
        {
            on_value_changed->AddListener(unity::reworked::action::make(func));
        }


        if (c_text)
        {

            unity::reworked::vrc::reworked::elements::clear_localizable(c_text);

            c_text->set_text(Il2Cpp::Utils::to_il2cpp_string(name));

            c_text->set_richText(true);

        }


        if (c_image_on && sprite_on)
        {

            c_image_on->set_sprite(sprite_on);

            c_image_on->set_overrideSprite({});

        }


        if (c_image_off && sprite_off)
        {

            c_image_off->set_sprite(sprite_off);

            c_image_off->set_overrideSprite({});

        }



        return c_obj->get_transform();

    }


    static UnityEngine::Transform* toggle_button(UnityEngine::Transform* parent, const char* name, bool* state, UnityEngine::Sprite* sprite_on = {}, UnityEngine::Sprite* sprite_off = {})
    {
        int idx = toggle_count++;
        toggle_states[idx] = state;

        auto* result = toggle_button(parent, name, reinterpret_cast<void(*)()>(toggle_thunks[idx]), *state, sprite_on, sprite_off);

        if (result)
        {
            auto* c_handle = result->get_gameObject()->GetComponentT<ToggleButtonHandle>(get_class_ToggleButtonHandle());

            toggle_handle_ptrs[idx] = c_handle;
        }

        return result;
    }


}
