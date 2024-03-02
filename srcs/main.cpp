#include "classes/SDL/SDL.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <gtkmm.h>

struct window
{
    Gtk::Window *window = NULL;
    Gtk::Button *generateMap = NULL;
    Gtk::FileChooserButton *chooseRulePath = NULL;
    Gtk::FileChooserButton *saveMap = NULL;
    Gtk::Image *image = NULL;
    Glib::RefPtr<Gdk::Pixbuf> m_image;
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

    struct window window;
    builder->get_widget("mainWindow", window.window);
    builder->get_widget("generateMap", window.generateMap);
    window.generateMap->signal_clicked().connect(&generateMap);
    builder->get_widget("chooseRuleFile", window.chooseRulePath);
    window.chooseRulePath->signal_file_set().connect(&chooseRuleFile);
    builder->get_widget("saveMap", window.saveMap);
    window.saveMap->signal_file_set().connect(&saveMap);

    builder->get_widget("map", window.image);
    window.image->set("../dungeonGenerator/picture.ppm");
    Gtk::Main::run(*(window.window));
    return (EXIT_SUCCESS);
    }
    catch (const std::exception &exception)
    {
        std::cerr << exception.what() << std::endl;
        return (EXIT_FAILURE);
    }
}