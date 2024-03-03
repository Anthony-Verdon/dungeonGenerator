#pragma once

#include <gtkmm.h>

typedef struct s_gtkWindow
{
    Gtk::Window *window = NULL;
    Gtk::Button *generateMap = NULL;
    Gtk::FileChooserButton *chooseRulePath = NULL;
    Gtk::FileChooserButton *saveMap = NULL;
    Gtk::DrawingArea *drawingArea = NULL;
} t_gtkWindow;