#include <gtkmm.h>
#include "structs/t_data.hpp"
#include "classes/Texture/Texture.hpp"
#include "classes/DungeonGenerator/DungeonGenerator.hpp"
#include "classes/ruleFileParser/ruleFileParser.hpp"
#include "classes/fileGenerator/fileGenerator.hpp"
#include <iostream>

void generateMap(t_data *data)
{
    if (data->rulepath.empty())
    {
        std::cerr << "no rule file selected" << std::endl;
        return;
    }

    char *end;
    std::string widthEntry = data->window.width->get_buffer()->get_text();
    int width = std::strtol(widthEntry.c_str(), &end, 10);
    if (widthEntry.size() == 0 || end[0] != '\0')
    {
        std::cerr << "invalid width" << std::endl;
        return;
    }
    std::string heightEntry = data->window.height->get_buffer()->get_text();
    int height = std::strtol(heightEntry.c_str(), &end, 10);
    if (heightEntry.size() == 0 || end[0] != '\0')
    {
        std::cerr << "invalid height" << std::endl;
        return;
    }

    if (ruleFileParser::isRuleFileValid(data->rulepath))
    {
        data->map = DungeonGenerator::generateMap(width, height, data->rulepath);
        data->window.drawingArea->queue_draw();
    }
}

void completeMap(t_data *data)
{
    Gtk::FileChooserDialog window("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
    
    window.set_modal(true);
    window.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    window.add_button("_Open", Gtk::RESPONSE_OK);
    window.run();
    
    /*
    need to create something to check if the file is ok
    -> good values
    -> be sure that every defined tile can be next to each other

    maybe create another class for this,
    or update ruleFileParser into fileParser with 2 differents sections
    */
    std::string filename = window.get_filename();
    if (!filename.empty() /* && initMapValid*/)
    {
        data->map = DungeonGenerator::generateMap(filename);
        data->window.drawingArea->queue_draw();
    }
}

void chooseRuleFile(t_data *data)
{
    Gtk::FileChooserDialog window("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
    
    window.set_modal(true);
    window.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    window.add_button("_Open", Gtk::RESPONSE_OK);
    window.run();
    
    std::string filename = window.get_filename();
    if (!filename.empty())
        data->rulepath = filename;
    
}

void saveMap(t_data *data){
    Gtk::FileChooserDialog window("Please choose a folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    
    window.set_modal(true);
    window.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    window.add_button("_Open", Gtk::RESPONSE_OK);
    window.run();
    
    std::string filename = window.get_filename();
    if (!filename.empty())
        fileGenerator::generateFile(data->map, filename);
}

static void drawPixel(const Cairo::RefPtr<Cairo::Context>& cr, int x, int y, float color[3])
{
    cr->set_source_rgb(color[0], color[1], color[2]);
    cr->rectangle(x, y, 1, 1);
    cr->fill();
}

static void drawTexture(const Cairo::RefPtr<Cairo::Context>& cr, const Texture &texture, int startX, int startY, float scaleX, float scaleY)
{
    float texX = 0;
    float stepX = 1.0 / scaleX;
    for (int x = 0; x < texture.getWidth() * scaleX; x++)
    {
        float texY = 0;
        float stepY = 1.0 / scaleY;
        for (int y = 0; y < texture.getHeight() * scaleY; y++)
        {
            std::vector<int> data = texture.getData();
            int pixel = (int)texY * 3 * texture.getWidth() + (int)texX * 3;
            float color[] = {(float)data[pixel + 0] / 255, (float)data[pixel + 1] / 255, (float)data[pixel + 2] / 255};
            drawPixel(cr, startX + x, startY + y, color);
            texY += stepY;
        }
        texX += stepX;
    }
}

bool drawMap(const Cairo::RefPtr<Cairo::Context>& cr, t_data *data) {

    int width = 20;
    if (data->map.width < 20)
        width = data->map.width;
    int height = 20;
    if (data->map.height < 20)
        height = data->map.height;
    for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                std::shared_ptr<Texture> texture =
                    data->map.tileset[data->map.data[data->window.startDrawingArea.y + y][data->window.startDrawingArea.x + x].possiblesTilesID[0]].getTexture();
                drawTexture(cr, *texture, x * 16, y * 16, 1.0, 1.0);
            }
        }
    return true;
}

bool onKeyPressed(GdkEventKey *event, t_data *data)
{
    bool redraw = false;
    std::string keyname = gdk_keyval_name(event->keyval);
    if (keyname == "Escape")
        exit(0);
    else if ((keyname == "z" || keyname == "w") && data->window.startDrawingArea.y > 0)
    {
        data->window.startDrawingArea.y--;
        redraw = true;
    }
    else if (keyname == "s" && data->window.startDrawingArea.y + 20 < data->map.height)
    {
        data->window.startDrawingArea.y++;
        redraw = true;
    }
    else if ((keyname == "a" || keyname == "q") && data->window.startDrawingArea.x > 0)
    {
        data->window.startDrawingArea.x--;
        redraw = true;
    }
    else if (keyname == "d" && data->window.startDrawingArea.x + 20 < data->map.width)
    {
        data->window.startDrawingArea.x++;
        redraw = true;
    }

    if (redraw)
        data->window.drawingArea->queue_draw();
    return (true);
}