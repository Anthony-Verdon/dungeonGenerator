#include "classes/SDL/SDL.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <gtkmm.h>

bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    const int width = 160;
    const int height = 160;

    cr->set_source_rgb(1.0, 1.0, 1.0); // White background
    cr->paint();

    const int squareSize = 20; // Size of each square
    const int numRows = 8;
    const int numCols = 8;

    // Draw chessboard
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            int x = col * squareSize;
            int y = row * squareSize;

            // Alternate between black and white squares
            if ((row + col) % 2 == 0) {
                cr->set_source_rgb(0.0, 0.0, 0.0); // Black
            } else {
                cr->set_source_rgb(1.0, 1.0, 1.0); // White
            }

            cr->rectangle(x, y, squareSize, squareSize);
            cr->fill();
        }
    }

    return true;
}
struct window
{
    Gtk::Window *window = NULL;
    Gtk::Button *generateMap = NULL;
    Gtk::FileChooserButton *chooseRulePath = NULL;
    Gtk::FileChooserButton *saveMap = NULL;
};

void buttonClicked()
{
    std::cout << "buttonClicked" << std::endl;
}

void generateMap()
{
DungeonGenerator::generateMap(20, 20, "assets/roads/rules.json");
}

void chooseRuleFile()
{
    std::cout << "here it's open" << std::endl;
}

void saveMap()
{
    std::cout << "here directory selected" << std::endl;
}

int main(int argc, char *argv[])
{
    try
    {
        std::cout << "Gtkmm version : " << gtk_get_major_version() << "."
                                    << gtk_get_minor_version() << "."
                                    << gtk_get_micro_version() << std::endl;

    Gtk::Main kit(argc, argv);
    auto app = Gtk::Application::create("org.gtkmm.example");
    auto builder = Gtk::Builder::create_from_file("../blueprint.glade");

    struct window instance;
    builder->get_widget("mainWindow", instance.window);
    builder->get_widget("generateMap", instance.generateMap);
    instance.generateMap->signal_clicked().connect(&generateMap);
    builder->get_widget("chooseRuleFile", instance.chooseRulePath);
    instance.chooseRulePath->signal_file_set().connect(&chooseRuleFile);
    builder->get_widget("saveMap", instance.saveMap);
    instance.saveMap->signal_file_set().connect(&saveMap);
    
    Gtk::DrawingArea *drawing_area;
    builder->get_widget("drawingArea", drawing_area);
    drawing_area->set_size_request(160, 160);
    drawing_area->signal_draw().connect(&on_draw);
    drawing_area->show();

    Gtk::Main::run(*(instance.window));
    return (EXIT_SUCCESS);
    }
    catch (const std::exception &exception)
    {
        std::cerr << exception.what() << std::endl;
        return (EXIT_FAILURE);
    }
}