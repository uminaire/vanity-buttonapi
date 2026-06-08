namespace quickmenu
{
    static const char* slider_prefix = "Cell_Slider_";


    static UnityEngine::UI::Slider* slider_ptrs[32] = {};


    static TextMeshProEx* slider_value_ptrs[32] = {};


    static int cell_linked_slider_idx[64] = {};  // which slider_idx belongs to cell i


    static void(*slider_user_funcs[32])(float) = {};


    static float slider_minValues[32] = {};
    static float slider_maxValues[32] = {};


    static UnityEngine::Transform* cell_linked_slider_ptrs[32]  = {};
    static float*                  cell_linked_slider_value_ptrs[32] = {};


    static int slider_count = 0;


    template<int N> static void slider_value_thunk()
    {
        if (slider_ptrs[N] && slider_value_ptrs[N])
        {
            float val = slider_ptrs[N]->get_value() * (slider_maxValues[N] - slider_minValues[N]) + slider_minValues[N];

            slider_value_ptrs[N]->set_text(Il2Cpp::Utils::to_il2cpp_string(baseutils::format_float(val).c_str()));

            if (slider_user_funcs[N])

            {
                slider_user_funcs[N](val);
            }
        }
    }


    template<int N> static void cell_slider_visibility_thunk()
    {
        if (cell_linked_slider_ptrs[N])
        {
            bool active = cell_switch_state_ptrs[N] ? *cell_switch_state_ptrs[N] : false;

            cell_linked_slider_ptrs[N]->get_gameObject()->SetActive(active);

            if (active && cell_linked_slider_value_ptrs[N] && slider_value_ptrs[N])
            {
                slider_value_ptrs[N]->set_text(Il2Cpp::Utils::to_il2cpp_string(baseutils::format_float(*cell_linked_slider_value_ptrs[N]).c_str()));
            }
        }
    }


    static const auto slider_value_thunks = make_thunk_table(slider_value_thunk, 64);

    static const auto cell_slider_visibility_thunks = make_thunk_table(cell_slider_visibility_thunk, 64);



    static UnityEngine::Transform* cell_slider(UnityEngine::Transform* parent, const char* name, const char* tooltip, void(*func)(float) = nullptr, float defaultValue = 0.0f, float minValue = 0.0f, float maxValue = 100.0f, bool isDecimal = false, const char* ending = "%")
    {

        auto* single = elements::qm::pro::cell_slider();


        if (!single) return {};

        auto* slider_c = reinterpret_cast<UnityEngine::GameObject*>(UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(single->get_gameObject()), parent));
       
        
        if (!slider_c) return {};



        UnityEngine::Object::DontDestroyOnLoad(reinterpret_cast<UnityEngine::Object*>(slider_c));

        slider_c->SetActive(false);


        reinterpret_cast<UnityEngine::Object*>(slider_c)->set_name(Il2Cpp::Utils::to_il2cpp_string(std::string(slider_prefix) + name));

        auto* slider_t = slider_c->get_transform();


        auto* slider_right_item_container = slider_t->GetChild(0);


        auto* slider_left_item_container = slider_t->GetChild(1);


        auto* text = slider_left_item_container->GetChild(1);


        auto* c_text = text->get_gameObject()->GetComponentInChildrenT<TextMeshProEx>(get_class_TextMeshProEx(), true);


        if (c_text)
        {
            c_text->set_text(Il2Cpp::Utils::to_il2cpp_string(name));
        }

        UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(slider_right_item_container->GetChild(5)->get_gameObject()));
        UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(slider_right_item_container->GetChild(4)->get_gameObject()));
        UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(slider_right_item_container->GetChild(3)->get_gameObject()));
        UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(slider_right_item_container->GetChild(2)->get_gameObject()));


        auto* c_slider = slider_right_item_container->GetChild(0);
       
 
        auto* c_value = slider_right_item_container->GetChild(1)->get_gameObject()->GetComponentInChildrenT<TextMeshProEx>(get_class_TextMeshProEx(), true);



        auto* c_snapextend = c_slider->get_gameObject()->GetComponentInChildrenT<void>(get_class_VRCUISlider(), true);


        if (c_snapextend)
        {


            auto* _slider = reinterpret_cast<UnityEngine::UI::Slider*>(c_snapextend);


            int slider_idx = slider_count++;


            slider_value_ptrs[slider_idx] = c_value;

            slider_ptrs[slider_idx] = _slider;

            slider_user_funcs[slider_idx] = func;

            slider_minValues[slider_idx] = minValue;

            slider_maxValues[slider_idx] = maxValue;

            auto event = unity::reworked::event::create();

            SetField<void*>(c_snapextend, 416, event);


            _slider->Internal_field_Slider_m_OnValueChanged_0 = event;


            auto* onvaluechanged = reinterpret_cast<UnityEngine::Events::UnityEvent*>(_slider->Internal_field_Slider_m_OnValueChanged_0);
           
            if (onvaluechanged)

            {

                onvaluechanged->AddListener(unity::reworked::action::make(slider_value_thunks[slider_idx]));

            }

            if (c_value)
            {
                c_value->set_text(Il2Cpp::Utils::to_il2cpp_string(baseutils::format_float(defaultValue).c_str()));
            }

            return slider_t;
        }

        return {};
    }


    static UnityEngine::Transform* cell_proper_with_slider(UnityEngine::Transform* parent, const char* name, const char* slider_name, const char* tooltip, bool* state, float* value_ptr = {}, void(*slider_func)(float) = {}, float default_value = 0.0f, float min_value = 0.0f, float max_value = 100.0f, bool is_decimal = false, const char* ending = "%", UnityEngine::Sprite* sprite = {}, void(*toggle_func)() = {})
    {

        int idx = cell_count;

        cell_switch_state_ptrs[idx] = state;
        cell_linked_slider_value_ptrs[idx] = value_ptr;


        auto* c_cell = cell_button(parent, name, tooltip, toggle_func, state ? *state : false, sprite);

        auto* c_slider = cell_slider(parent, slider_name, tooltip, slider_func, default_value, min_value, max_value, is_decimal, ending);

        cell_linked_slider_idx[idx] = slider_count - 1;

        if (c_slider)
        {

            cell_linked_slider_ptrs[idx] = c_slider;

            c_slider->get_gameObject()->SetActive(state ? *state : false);


            auto* c_handle = c_cell->get_gameObject()->GetComponentInChildrenT<ToggleButtonHandle>(get_class_ToggleButtonHandle());

            if (c_handle)
            {

                auto* on_value_changed = reinterpret_cast<UnityEngine::Events::UnityEvent*>(c_handle->Internal_field_Toggle_onValueChanged_0);

                on_value_changed->AddListener(unity::reworked::action::make(cell_slider_visibility_thunks[idx]));

            }

        }


        return c_cell;

    }

}