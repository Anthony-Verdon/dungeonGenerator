#pragma once

#include "structs/t_data.hpp"
#include <gtkmm.h>

void generateMap(t_data *data);
void completeMap(t_data *data);
void choosePrefilledMap(t_data *data);
void chooseRuleFile(t_data *data);
void saveMap(t_data *data);
bool drawMap(const Cairo::RefPtr<Cairo::Context>& cr, t_data *data);
bool onKeyPressed(GdkEventKey *event, t_data *data);