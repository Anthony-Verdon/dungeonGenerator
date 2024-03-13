#pragma once

#include <gtkmm.h>
#include "t_point.hpp"

typedef struct s_gtkWindow
{
    Gtk::Window *window = NULL;
    Gtk::Button *generateMap = NULL;
    Gtk::Button *completeMap = NULL;
    Gtk::Button *choosePrefilledMap = NULL;
    Gtk::Entry *width = NULL;
    Gtk::Entry *height = NULL;
    Gtk::Button *chooseRulePath = NULL;
    Gtk::Button *saveMap = NULL;
    Gtk::DrawingArea *drawingArea = NULL;
    t_point startDrawingArea = {0,0};
} t_gtkWindow;