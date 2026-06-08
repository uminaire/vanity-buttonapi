usage:

auto* c_ship = new quickmenu::Page("Landing", "Geography");

auto* c_landmarks = new quickmenu::Page("Spots", "AspenTree");


quickmenu::create_cell_layout g(c_main->box, "LandPage");

{
    quickmenu::create_panel_layout pg(g, "Panels");

    c_ship->add_panel(pg, "Landmarks", *c_movement, quickmenu::sprites::vanitylogo);

    c_ship->add_separator(pg, 15.0f);
}

{
    quickmenu::create_cell_layout g(c_landmarks->box, "Aspen");

    c_landmarks->add_cell_button(g, "Cell 1", {}, &globals::example);


    c_movement->add_slider<quickmenu::util::slider::create<&globals::bool, &globals::int>>(g, "water", "amount to fill", 1.0f, 0.0f, 10.0f);

   // add_cell_button_with_selector, add_selector etc.
}


