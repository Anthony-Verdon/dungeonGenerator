#pragma once

#include <gtkmm.h>

typedef struct s_gtkWindow
{
    Gtk::Window *window = NULL;
    Gtk::Button *generateMap = NULL;
    Gtk::Button *chooseRulePath = NULL;
    Gtk::Button *saveMap = NULL;
    Gtk::DrawingArea *drawingArea = NULL;
} t_gtkWindow;