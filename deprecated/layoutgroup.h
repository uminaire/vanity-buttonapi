namespace quickmenu
{

    struct layout_group_page
    {

        UnityEngine::Transform* transform;
        UnityEngine::Transform* container;


        layout_group_page(UnityEngine::Transform* parent, const char* name)
        {

            auto* layout = elements::qm::pro::layout_group();

            if (!layout) return;

            auto* obj = (UnityEngine::Transform*)UnityEngine::Object::Instantiate_2(reinterpret_cast<UnityEngine::Object*>(layout->get_transform()), parent);

            if (!obj) return;

            while (obj->get_childCount() > 0)

            {
                UnityEngine::Object::DestroyImmediate_0(reinterpret_cast<UnityEngine::Object*>(obj->GetChild(0)->get_gameObject()));
            }


            transform = obj;

            container = obj;


        }
    };
}