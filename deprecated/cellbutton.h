#pragma once

namespace quickmenu
{
    static const char* const cell_prefix = "Cell_";


    struct create_cell_layout
    {
        UnityEngine::GameObject* object = {};
        UnityEngine::Transform* container = {};
        UnityEngine::Transform* cell_container = {};

        create_cell_layout(UnityEngine::Transform* parent, const char* name)
        {
            auto* c_src = elements::qm::pro::cell_container();
            if (!c_src) return;

            auto* cell = reinterpret_cast<UnityEngine::GameObject*>(UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(c_src->get_gameObject()), parent));
            if (!cell) return;

            UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(cell));
            cell->SetActive(false);

            reinterpret_cast<UnityEngine::Object*>(cell)->set_name(Il2Cpp::Utils::to_il2cpp_string(std::string(cell_prefix) + name));

            auto* c_transform = cell->get_transform();

            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(7)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(6)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(5)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(4)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(3)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(2)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(1)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(0)->get_gameObject()));

            auto* parent_vlg = parent->get_gameObject()->GetComponentT<UnityEngine::UI::LayoutGroup>("UnityEngine.UI.VerticalLayoutGroup");
            if (parent_vlg)
            {
                auto* pad = parent_vlg->get_padding();
                if (pad)
                {
                    pad->set_left(50);
                    pad->set_right(50);
                    parent_vlg->set_padding(pad);
                }
            }

            auto* c_inner_src = elements::qm::pro::cell_container();
            if (c_inner_src)
            {
                auto* inner = reinterpret_cast<UnityEngine::GameObject*>(UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(c_inner_src->get_gameObject()), c_transform));
                if (inner)
                {
                    UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(inner));
                    reinterpret_cast<UnityEngine::Object*>(inner)->set_name(Il2Cpp::Utils::to_il2cpp_string(std::string(cell_prefix) + name + ".inner"));

                    auto* c_inner_transform = inner->get_transform();

                    UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_inner_transform->GetChild(7)->get_gameObject()));
                    UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_inner_transform->GetChild(6)->get_gameObject()));
                    UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_inner_transform->GetChild(5)->get_gameObject()));
                    UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_inner_transform->GetChild(4)->get_gameObject()));
                    UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_inner_transform->GetChild(3)->get_gameObject()));
                    UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_inner_transform->GetChild(2)->get_gameObject()));
                    UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_inner_transform->GetChild(1)->get_gameObject()));

                    inner->SetActive(true);
                    cell_container = c_inner_transform;
                }
            }

            cell->SetActive(true);
            object = cell;
            container = c_transform;
        }

        create_cell_layout(create_cell_layout& parent, const char* name)
            : create_cell_layout(parent.container, name)
        {
        }
    };

    struct create_panel_layout
    {
        UnityEngine::GameObject* object = {};
        UnityEngine::Transform* container = {};

        create_panel_layout(create_cell_layout& parent, const char* name)
        {
            auto* c_src = elements::qm::pro::cell_container();
            if (!c_src) return;

            auto* cell = reinterpret_cast<UnityEngine::GameObject*>(UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(c_src->get_gameObject()), parent.container));
            if (!cell) return;

            UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(cell));
            cell->SetActive(false);

            reinterpret_cast<UnityEngine::Object*>(cell)->set_name(Il2Cpp::Utils::to_il2cpp_string(std::string(cell_prefix) + name));

            auto* c_transform = cell->get_transform();

            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(7)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(6)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(5)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(4)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(3)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(2)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(1)->get_gameObject()));
            UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(c_transform->GetChild(0)->get_gameObject()));

            cell->SetActive(true);
            object = cell;
            container = c_transform;
        }
    };

    static CellSwitch* cell_switch_ptrs[64] = {};
    static bool cell_switch_states[64] = {};
    static ToggleButtonHandle* cell_handle_ptrs[64] = {};


    static bool* cell_switch_state_ptrs[64] = {};
    static int cell_count = 0;

    template<int N> static void cell_thunk()
    {
        auto* cs = cell_switch_ptrs[N];
        if (!cs) return;

        cell_switch_states[N] = !cell_switch_states[N];
        cs->SendPrivateCellTransition(!cell_switch_states[N]);
        cs->SendPrivateCellTransition(cell_switch_states[N]);
    }

    template<int N> static void cell_bool_thunk()
    {
        if (cell_switch_state_ptrs[N])
            *cell_switch_state_ptrs[N] = !*cell_switch_state_ptrs[N];
    }

    static const auto cell_thunks = make_thunk_table(cell_thunk, 64);
    static const auto cell_bool_thunks = make_thunk_table(cell_bool_thunk, 64);

    static UnityEngine::Transform* cell_button(UnityEngine::Transform* parent, const char* name, const char* tooltip, void(*func)() = nullptr, bool default_state = false, UnityEngine::Sprite* sprite = nullptr, int* out_idx = nullptr)
    {
        auto* c_src = elements::qm::pro::cell_button();


        if (!c_src) return nullptr;



        auto* c_cell = reinterpret_cast<UnityEngine::GameObject*>(UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(c_src->get_gameObject()), parent));
        
        
        if (!c_cell) return nullptr;


        UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(c_cell));

        c_cell->SetActive(false);


        reinterpret_cast<UnityEngine::Object*>(c_cell)->set_name(Il2Cpp::Utils::to_il2cpp_string(std::string(cell_prefix) + name));

        auto* c_transform = c_cell->get_transform();

        auto* c_text = c_cell->GetComponentInChildrenT<TextMeshProEx>(get_class_TextMeshProEx(), true);


        if (c_text)
         
            c_text->set_text(Il2Cpp::Utils::to_il2cpp_string(name));

        auto* c_handle = c_cell->GetComponentInChildrenT<ToggleButtonHandle>(get_class_ToggleButtonHandle());


        auto* c_cellswitch = c_cell->GetComponentInChildrenT<CellSwitch>(get_class_CellSwitch());


        if (c_handle && c_cellswitch)
        {


            int index = cell_count++;


            if (out_idx) *out_idx = index;



            cell_switch_ptrs[index] = c_cellswitch;

            cell_handle_ptrs[index] = c_handle;

            cell_switch_states[index] = default_state;


            auto* on_value_changed = reinterpret_cast<UnityEngine::Events::UnityEvent*>(c_handle->Internal_field_Toggle_onValueChanged_0);
            
            
            if (!on_value_changed)
            {

                c_cell->SetActive(true);
                return c_transform;

            }

            on_value_changed->RemoveAllListeners();


            on_value_changed->AddListener(unity::reworked::action::make(cell_thunks[index]));

            on_value_changed->AddListener(unity::reworked::action::make(cell_bool_thunks[index]));

            if (func)

                on_value_changed->AddListener(unity::reworked::action::make(func));

            cell_thunks[index]();
            cell_thunks[index]();


        }

        c_cell->SetActive(true);


        return c_transform;

    }

    static UnityEngine::Transform* cell_proper(UnityEngine::Transform* parent, const char* name, const char* tooltip, bool* state, UnityEngine::Sprite* sprite = {}, int* out_idx = {})
    {


        int index = -1;


        auto* c_transform = cell_button(parent, name, tooltip, nullptr, state ? *state : false, sprite, &index);


        if (index >= 0)
        {


            cell_switch_state_ptrs[index] = state;
            if (out_idx) *out_idx = index;

        }

        return c_transform;
    }
}