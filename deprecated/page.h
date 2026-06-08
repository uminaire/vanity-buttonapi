#pragma once

static const char* prefix = "QuickMenu";

namespace quickmenu { struct Page; }

namespace nav
{
    static std::vector<Il2Cpp::String*> stack;
    static std::vector<quickmenu::Page*> table;
    static std::map<std::string, UnityEngine::GameObject*> pages;

    static quickmenu::Page* current_page = { };
    static void(*current_func)() = { };
}

static void back_trampoline();

static void activate_page(const std::string& key)
{
    if (!nav::pages.count(key)) return;

    if (auto* obj = nav::pages.at(key)) obj->SetActive(true);
}

template<int N> static void nav_thunk()
{
    if (N >= (int)nav::table.size() || !nav::table[N]) return;

    auto* dest = nav::table[N];

    activate_page(dest->key);

    nav::stack.push_back(dest->pagename);

    globals::buttonapi::quick_menu::controller->UI_PageTranslate(dest->pagename, {}, false, static_cast<int32_t>(transitiontype::Right));

}

static const auto nav_thunks = make_thunk_table(nav_thunk, 32);

namespace quickmenu::util::slider
{
    template<bool* state, float* value, void(*fn)(float) = nullptr, float reset = 0.f>
    struct create
    {
        static constexpr bool* state_ptr = state;
        static constexpr float* value_ptr = value;
        static void set(float v) { *value = v; if constexpr (fn != nullptr) fn(v); }
        static void toggle() { if constexpr (fn != nullptr) fn(*state ? *value : reset); }
    };

}

namespace quickmenu
{


    static void sync_states()
    {
        for (int i = 0; i < cell_count; i++)
        {
            auto* state = cell_switch_state_ptrs[i];



            auto* cs = cell_switch_ptrs[i];


            if (!state || !cs) continue;


            if (cell_switch_states[i] != *state)

            {
                cell_switch_states[i] = *state;


                cs->SendPrivateCellTransition(!*state);


                cs->SendPrivateCellTransition(*state);

                if (cell_linked_slider_ptrs[i])

                    cell_linked_slider_ptrs[i]->get_gameObject()->SetActive(*state);

                if (selector_linked_ptrs[i])

                    selector_linked_ptrs[i]->get_gameObject()->SetActive(*state);


            }



            int s_idx = cell_linked_slider_idx[i];


            if (s_idx >= 0 && cell_linked_slider_value_ptrs[i] && slider_value_ptrs[s_idx] && *state)

            {


                slider_value_ptrs[s_idx]->set_text(Il2Cpp::Utils::to_il2cpp_string(
                    baseutils::format_float(*cell_linked_slider_value_ptrs[i]).c_str()
                ));

            }


            int sel_idx = cell_linked_selector_idx[i];


            if (sel_idx >= 0 && selector_linked_ptrs[i] && selector_out_ptrs[sel_idx])

            {


                int current = *selector_out_ptrs[sel_idx];

                if (selector_current_index[sel_idx] != current)

                {

                    selector_current_index[sel_idx] = current;

                    update_displayed_setting(sel_idx);

                }


            }


        }


    }

    struct Page
    {
        UnityEngine::Transform* pagetransform;
        UnityEngine::Transform* box;
        Il2Cpp::String* pagename;
        UnityEngine::GameObject* gameobject;
        std::string key;

        Page(const char* page_name, const char* title = {}, UnityEngine::Sprite* sprite = {})
        {
            auto* c_src = elements::qm::pro::menu_settings();



           // c_logger->print(encrypt("( quickmenuplacer ) c_src %p"), c_src);

            if (!c_src) return; 

            auto* c_parent = elements::qm::pro::qm_parent();


           // c_logger->print(encrypt("( quickmenuplacer ) qmparent %p"), c_parent);

            if (!c_parent) return;

      
            auto* c_obj = reinterpret_cast<UnityEngine::GameObject*>(UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(c_src->get_gameObject()), c_parent->get_transform()));


            if (!c_obj) return;


            UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(c_obj));



          //  c_logger->print(encrypt("( quickmenuplacer ) c_obj %p"), c_obj);

            c_obj->SetActive(false);

            c_obj->get_transform()->SetSiblingIndex(5);

            auto* c_name = Il2Cpp::Utils::to_il2cpp_string(std::string(prefix) + page_name)
                ;
            auto* c_name_lower = Il2Cpp::Utils::to_lower(c_name);


            reinterpret_cast<UnityEngine::Object*>(c_obj)->set_name(c_name);

            auto* c_page = c_obj->GetComponentT<UIPage>(get_class_SettingsPage());

            if (!c_page) return;

            c_obj->get_transform()->SetSiblingIndex(5);


            if (!c_page) { c_logger->print("( page ) settings page fucked"); return; }



            auto* c_canvas = c_obj->GetComponentT<UnityEngine::Behaviour>("UnityEngine.Canvas");


            if (!c_canvas) return;



           // c_logger->print(encrypt("( quickmenuplacer ) c_canvas %p"), c_canvas);


            auto* c_raycaster = c_obj->GetComponentT<UnityEngine::Behaviour>("UnityEngine.UI.GraphicRaycaster");

            if (!c_raycaster) return;

        //    c_logger->print(encrypt("( quickmenuplacer ) c_raycaster %p"), c_raycaster);



            auto* c_text = c_obj->GetComponentInChildrenT<TextMeshProEx>(get_class_TextMeshProEx());

            if (c_text)
            {

             //   c_logger->print(encrypt("( quickmenuplacer ) c_text %p"), c_text);


                SetField<VRC::Localization::LocalizableString*>(c_text, 1960, {});


                c_text->set_text(Il2Cpp::Utils::to_il2cpp_string(title ? title : page_name));

                c_text->set_richText(true);

                // c:

            }



            auto* c_transform = c_obj->get_transform();

            auto* c_viewport = c_transform->GetChild(1)->GetChild(0);

            auto* c_right_container = c_transform->GetChild(0)->GetChild(2);


            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_right_container->get_gameObject()));



            auto* c_content = c_viewport->GetChild(0);


            while (c_content->get_childCount() > 0)

                UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_content->GetChild(0)->get_gameObject()));

            if (c_canvas)

                c_canvas->set_enabled(true);


            if (c_raycaster)

                c_raycaster->set_enabled(true);


            if (c_page->Internal_field_UIPage_pageName_0)
            {

                c_page->Internal_field_UIPage_pageName_0 = c_name_lower;
                c_page->Internal_field_Private_UIPage_bool_0 = true; // foldpage
                c_page->Internal_field_UIPage__isModal_0 = false;

            }

            auto* c_oldpages = globals::buttonapi::quick_menu::controller->Internal_field_MenuStateController_Pages_0;

            if (c_oldpages)
            {

                auto* c_newpages = reinterpret_cast<Il2Cpp::WrappedArray<UIPage*>*>(System::Array::CreateInstance_0(reinterpret_cast<Il2Cpp::Type*>(Il2Cpp::Utils::to_system_type(get_class_UIPage())), c_oldpages->max_length + 1));

                if (c_newpages)
                {
                    for (int i = 0; i < c_oldpages->max_length; i++)

                        c_newpages->items[i] = c_oldpages->items[i];

                    c_newpages->items[c_oldpages->max_length] = c_page;
                }
            }
            auto* c_registrar = globals::buttonapi::quick_menu::controller->Internal_field_MenuStateController_Internal_field_PageRegistrar_0;



            if (c_registrar)

            {
                auto* c_list = GetField<void*>(c_registrar, 16);
                auto* c_dict = GetField<void*>(c_registrar, 24);


                if (c_list)

                    unity::reworked::list::add(c_list, c_page);


                if (c_dict)

                    unity::reworked::dictionary::add(c_dict, c_name_lower, c_page);

            }

            auto* c_scrollrect = c_obj->GetComponentInChildrenT<UnityEngine::Component>(get_class_VrcScrollRect(), true);


            if (c_scrollrect)
            {
                SetField<bool>(c_scrollrect, 312, true);


                auto* c_sr_canvas = c_scrollrect->get_gameObject()->GetComponentInChildrenT<UnityEngine::Behaviour>("UnityEngine.Canvas");


                auto* c_sr_raycaster = c_scrollrect->get_gameObject()->GetComponentInChildrenT<UnityEngine::Behaviour>("UnityEngine.UI.GraphicRaycaster");


                if (c_sr_canvas)

                    c_sr_canvas->set_enabled(true);


                if (c_sr_raycaster)

                    c_sr_raycaster->set_enabled(true);

                reinterpret_cast<UnityEngine::Behaviour*>(c_scrollrect)->set_enabled(true);
            }

            auto* c_rectmask = c_obj->GetComponentInChildrenT<void>(get_class_VrcRectMask(), true);


            if (c_rectmask)
            {


                reinterpret_cast<UnityEngine::Behaviour*>(c_rectmask)->set_enabled(true);


                //   SetField<bool>(c_rectmask, 144, true);
               //    SetField<bool>(c_rectmask, 168, true);


            }

            auto* c_header = c_transform->GetChild(0);

            auto* c_left_container = c_header->GetChild(1);

            auto* c_back_button = c_left_container->GetChild(0);



            c_back_button->get_gameObject()->SetActive(true);


            auto* c_back_btn = c_back_button->get_gameObject()->GetComponentT<UnityEngine::UI::Button>(get_class_MenuTab());


            if (c_back_btn)
            {

                auto* c_on_click = reinterpret_cast<UnityEngine::Events::UnityEvent*>(c_back_btn->get_onClick());


                if (c_on_click)
                {

                    c_on_click->RemoveAllListeners();

                    auto* c_action = unity::reworked::action::make(&back_trampoline);

                    if (c_action)

                        c_on_click->AddListener(c_action);


                }
            }

            std::string page_key = std::string(prefix) + page_name;

            key = page_key;

            pagename = c_name_lower;

            pagetransform = c_obj->get_transform();



            gameobject = c_obj;


            box = c_content;

            nav::pages[page_key] = c_obj;

        }
        Page& add_button(const char* name, void(*func)() = {}, UnityEngine::Sprite* sprite = {})
        {
            button(box, name, func, sprite);
            return *this;
        }

        Page& add_button(const char* name, Page& destination, UnityEngine::Sprite* sprite = {})
        {
            int idx = (int)nav::table.size();
            nav::table.push_back(&destination);
            button(box, name, nav_thunks[idx], sprite);
            return *this;
        }

        Page& add_button(layout_group_page& group, const char* name, void(*func)() = {}, UnityEngine::Sprite* sprite = {})
        {
            button(group.container, name, func, sprite);
            return *this;
        }

        Page& add_button(layout_group_page& group, const char* name, Page& destination, UnityEngine::Sprite* sprite = {})
        {
            int idx = (int)nav::table.size();
            nav::table.push_back(&destination);
            button(group.container, name, nav_thunks[idx], sprite);
            return *this;
        }

        Page& add_button(create_cell_layout& group, const char* name, void(*func)() = {}, UnityEngine::Sprite* sprite = {})
        {
            button(group.cell_container, name, func, sprite);
            return *this;
        }

        Page& add_panel(create_cell_layout& group, const char* name, void(*func)() = {}, UnityEngine::Sprite* sprite = {})
        {
            panel_button(group.container, name, func, sprite);
            return *this;
        }

        Page& add_panel(create_panel_layout& group, const char* name, void(*func)() = {}, UnityEngine::Sprite* sprite = {})
        {
            panel_button(group.container, name, func, sprite);
            return *this;
        }

        Page& add_separator(create_cell_layout& group, float height = 10.0f)
        {
            panel_separator(group.container, height);
            return *this;
        }

        Page& add_separator(create_panel_layout& group, float height = 10.0f)
        {
            panel_separator(group.container, height);
            return *this;
        }

        Page& add_panel(create_cell_layout& group, const char* name, Page& destination, UnityEngine::Sprite* sprite = {})
        {
            int idx = (int)nav::table.size();
            nav::table.push_back(&destination);
            panel_button(group.container, name, nav_thunks[idx], sprite);
            return *this;
        }

        Page& add_panel(create_panel_layout& group, const char* name, Page& destination, UnityEngine::Sprite* sprite = {})
        {
            int idx = (int)nav::table.size();
            nav::table.push_back(&destination);
            panel_button(group.container, name, nav_thunks[idx], sprite);
            return *this;
        }


        Page& add_toggle(layout_group_page& group, const char* name, void(*func)() = {}, bool default_state = false, UnityEngine::Sprite* sprite_on = {}, UnityEngine::Sprite* sprite_off = {})
        {
            toggle_button(group.container, name, func, default_state, sprite_on, sprite_off);
            return *this;
        }

        Page& add_toggle(layout_group_page& group, const char* name, bool* state, UnityEngine::Sprite* sprite_on = {}, UnityEngine::Sprite* sprite_off = {})
        {
            toggle_button(group.container, name, state, sprite_on, sprite_off);
            return *this;
        }

        Page& add_cell_button(layout_group_page& group, const char* name, const char* tooltip, void(*func)() = {}, bool* state = {}, UnityEngine::Sprite* sprite = {})
        {
            cell_button(group.container, name, tooltip, func, state, sprite);
            return *this;
        }

        Page& add_cell_button(create_cell_layout& group, const char* name, const char* tooltip, void(*func)() = {}, bool* state = {}, UnityEngine::Sprite* sprite = {})
        {
            cell_button(group.cell_container, name, tooltip, func, state, sprite);
            return *this;
        }

        Page& add_cell_button(create_cell_layout& group, const char* name, const char* tooltip, bool* state = {}, UnityEngine::Sprite* sprite = {})
        {
            cell_proper(group.cell_container, name, tooltip, state, sprite);
            return *this;
        }

        Page& add_cell_slider(layout_group_page& group, const char* name, const char* tooltip, void(*func)(float) = {}, float default_value = 0.0f, float min_value = 0.0f, float max_value = 100.0f, bool is_decimal = false, const char* ending = "%")
        {
            cell_slider(group.container, name, tooltip, func, default_value, min_value, max_value, is_decimal, ending);
            return *this;
        }

        Page& add_cell_slider(create_cell_layout& group, const char* name, const char* tooltip, void(*func)(float) = {}, float default_value = 0.0f, float min_value = 0.0f, float max_value = 100.0f, bool is_decimal = false, const char* ending = "%")
        {
            cell_slider(group.cell_container, name, tooltip, func, default_value, min_value, max_value, is_decimal, ending);
            return *this;
        }

        template<typename S>
        Page& add_slider(create_cell_layout& group, const char* name, const char* slider_name, float default_value = 0.f, float min_value = 0.f, float max_value = 100.f, bool is_decimal = false, const char* ending = "%", UnityEngine::Sprite* sprite = {})
        {
            cell_proper_with_slider(group.cell_container, name, slider_name, {}, S::state_ptr, S::value_ptr, S::set, default_value, min_value, max_value, is_decimal, ending, sprite, S::toggle);
            return *this;
        }

        Page& add_cell_button_with_slider(create_cell_layout& group, const char* name, const char* slider_name, const char* tooltip, bool* state, float* value_ptr = {},
            void(*slider_func)(float) = {}, float default_value = 0.0f, float min_value = 0.0f, float max_value = 100.0f,
            bool is_decimal = false, const char* ending = "%", UnityEngine::Sprite* sprite = {}, void(*toggle_func)() = {})
        {
            cell_proper_with_slider(group.cell_container, name, slider_name, tooltip, state, value_ptr, slider_func, default_value, min_value, max_value, is_decimal, ending, sprite, toggle_func);
            return *this;
        }

        Page& add_cell_button_with_selector(create_cell_layout& group, const char* name, const char* selector_title, const char* tooltip, bool* state, int* out_index,
            const char* names[], int name_count, UnityEngine::Sprite* sprite = {})
        {
            cell_proper_with_selector(group.cell_container, name, selector_title, tooltip, state, names, name_count, out_index, sprite);
            return *this;
        }

        Page& add_selector(layout_group_page& group, const char* selector_title, const char* names[], int name_count, int* out_index = nullptr)
        {
            selector_combo(group.container, selector_title, names, name_count, out_index);
            return *this;
        }

        Page& add_selector(create_cell_layout& group, const char* selector_title, const char* names[], int name_count, int* out_index = nullptr)
        {
            selector_combo(group.cell_container, selector_title, names, name_count, out_index);
            return *this;
        }
    };

    static void navigate(Page& page)
    {
        int idx = (int)nav::table.size();
        nav::table.push_back(&page);
        nav_thunks[idx]();
    }
}

static void back_trampoline()
{
    if (nav::stack.size() > 1)
    {
        nav::stack.pop_back();

        globals::buttonapi::quick_menu::controller->UI_PageTranslate(nav::stack.back(), {}, false, static_cast<int32_t>(transitiontype::Left));
    }
    else
    {
        nav::stack.clear();

        globals::buttonapi::quick_menu::controller->UI_PageTranslate(Il2Cpp::Utils::to_il2cpp_string("QuickMenuLaunchpad"), {}, false, static_cast<int32_t>(transitiontype::Left));
    }
}

static void handler()
{
    if (!nav::current_page) return;

    nav::stack.clear();

    activate_page(nav::current_page->key);

    nav::stack.push_back(nav::current_page->pagename);

    if (nav::current_func)
        nav::current_func();

    globals::buttonapi::quick_menu::controller->UI_PageTranslate(nav::current_page->pagename, {}, false, static_cast<int32_t>(transitiontype::Right));
}


