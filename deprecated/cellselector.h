#pragma once

namespace quickmenu
{

	static const char* selector_prefix = "cell_selector_";

	static const char** selector_names[ 64 ] = { };
	static int          selector_name_counts[ 64 ] = { };
	static int          selector_current_index[ 64 ] = { };
	static int* selector_out_ptrs[ 64 ] = { };
    static int          selector_count = 0;

	static TextMeshProEx* selector_texts[ 64 ] = { };

    static UnityEngine::Transform* selector_linked_ptrs[64] = {};
    static bool* selector_linked_state_ptrs[64] = {};

    static int cell_linked_selector_idx[64] = {}; // 



    static void update_displayed_setting( int idx )
    {
        if ( !selector_texts[ idx ] ) return;

        selector_texts[ idx ]->set_text( Il2Cpp::API::il2cpp_string_new( selector_names[ idx ][ selector_current_index [ idx ] ] ) );
    }

    static void scroll_left(int idx)
    {

        if ( selector_name_counts[ idx ] == 0 ) return;

        selector_current_index[idx] = (selector_current_index[idx] - 1 + selector_name_counts[idx]) % selector_name_counts[idx];
        if (selector_out_ptrs[idx]) *selector_out_ptrs[idx] = selector_current_index[idx];
        update_displayed_setting(idx);
    }

    static void scroll_right(int idx)
    {
        if ( selector_name_counts[ idx ] == 0 ) return;


        selector_current_index[ idx ] = (selector_current_index[ idx ] + 1) % selector_name_counts[ idx ];

        if (selector_out_ptrs[idx]) *selector_out_ptrs[ idx ] = selector_current_index[ idx ];

        update_displayed_setting( idx );
    }


    template<int N> static void scroll_left_thunk() { scroll_left(N); }

    template<int N> static void scroll_right_thunk() { scroll_right(N); }



    static const auto scroll_left_thunks = make_thunk_table(scroll_left_thunk, 64);

    static const auto scroll_right_thunks = make_thunk_table(scroll_right_thunk, 64);


    template<int N> static void selector_visibility_thunk()
    {
        if (!selector_linked_ptrs[N]) return;

        bool active = selector_linked_state_ptrs[N] ? *selector_linked_state_ptrs[N] : false;

        selector_linked_ptrs[N]->get_gameObject()->SetActive(active);
    }

    static const auto selector_visibility_thunks = make_thunk_table(selector_visibility_thunk, 64);


    static UnityEngine::Transform* selector_combo(UnityEngine::Transform* parent, const char* title, const char* names[], int name_count, int* out_index = nullptr)
    {

        int index = selector_count++;

        auto* c_selector = elements::qm::pro::cell_selector();

        if (!c_selector) return {};


        auto* selector_c = reinterpret_cast<UnityEngine::GameObject*>(UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(c_selector->get_gameObject()), parent));

        if (!selector_c) return {};


        UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(selector_c));

        selector_c->SetActive(false);


        reinterpret_cast<UnityEngine::Object*>(selector_c)->set_name(Il2Cpp::Utils::to_il2cpp_string(std::string(selector_prefix) + title));


        auto* selector_transform = selector_c->get_transform();

        auto* selector_left_container = selector_transform->GetChild(1);


        auto* selector_right_container = selector_transform->GetChild(0);


        auto* button_left = selector_right_container->GetChild(0);

        auto* button_right = selector_right_container->GetChild(2);

        auto* option_selection_box = selector_right_container->GetChild(1);

        auto* option_selection_box_text = option_selection_box->GetChild(1);

        auto* c_text = selector_left_container->GetChild(1)->get_gameObject()->GetComponentT<TextMeshProEx>(get_class_TextMeshProEx());


        if (c_text)
        {
            c_text->set_text(Il2Cpp::Utils::to_il2cpp_string(title));
        }

        selector_texts[index] = option_selection_box_text->get_gameObject()->GetComponentT<TextMeshProEx>(get_class_TextMeshProEx());


        selector_names[index] = names;

        selector_name_counts[index] = name_count;

        selector_current_index[index] = 0;

        selector_out_ptrs[index] = out_index;

        auto* button_left_component = reinterpret_cast<UnityEngine::UI::Button*>(button_left->get_gameObject()->GetComponentT<UnityEngine::UI::Button>(get_class_MenuTab()));
      
        if (!button_left_component) return {};

        auto* onleftclick = reinterpret_cast<UnityEngine::Events::UnityEvent*>(button_left_component->get_onClick());

        if (!onleftclick) return {};

        onleftclick->RemoveAllListeners();

        onleftclick->AddListener(unity::reworked::action::make(scroll_left_thunks[index]));

        auto* button_right_component = reinterpret_cast<UnityEngine::UI::Button*>(button_right->get_gameObject()->GetComponentT<UnityEngine::UI::Button>(get_class_MenuTab()));
       
        
        if (!button_right_component) return {};

        auto* onrightclick = reinterpret_cast<UnityEngine::Events::UnityEvent*>(button_right_component->get_onClick());


        if (!onrightclick) return {};


        onrightclick->RemoveAllListeners();
        onrightclick->AddListener(unity::reworked::action::make(scroll_right_thunks[index]));

        update_displayed_setting(index);


        selector_c->SetActive(true);

        return selector_transform;

    }


    static UnityEngine::Transform* cell_proper_with_selector(UnityEngine::Transform* parent, const char* name, const char* selector_title, const char* tooltip,
        bool* state, const char* names[], int name_count, int* out_index = {}, UnityEngine::Sprite* sprite = {})
    {

        int cell_idx = -1;

        auto* c_cell     = cell_proper(parent, name, tooltip, state, sprite, &cell_idx);
        auto* c_selector = selector_combo(parent, selector_title, names, name_count, out_index);

        cell_linked_selector_idx[cell_idx] = selector_count - 1;

        if (c_selector && cell_idx >= 0)
        {

            selector_linked_ptrs[cell_idx]       = c_selector;
            selector_linked_state_ptrs[cell_idx] = state;

            c_selector->get_gameObject()->SetActive(state ? *state : false);


            auto* c_handle = c_cell->get_gameObject()->GetComponentInChildrenT<ToggleButtonHandle>(get_class_ToggleButtonHandle());

            if (c_handle)
            {

                auto* on_value_changed = reinterpret_cast<UnityEngine::Events::UnityEvent*>(c_handle->Internal_field_Toggle_onValueChanged_0);

                on_value_changed->AddListener(unity::reworked::action::make(selector_visibility_thunks[cell_idx]));

            }

        }


        return c_cell;

    }


}