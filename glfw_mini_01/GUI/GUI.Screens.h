#pragma once;

#include "GUI.FontSystem.h"
#include "GUI.Credits.h"
#include "GUI.TextEffect.h"
#include "GUI.Button.h"
#include "GUI.Menu.h"
#include "GUI.ButtonArray.h"
#include "GUI.Layout.h"
#include "GUI.Slider.h"
#include "GUI.List.h"
#include "GUI.Console.h"


#define FONT_FILE "FDB.txt"
#define SOUND_FILE "SDB.txt"
#define MAIN_CONF "main_menu.txt"
#define OPTIONS_CONF "options_screen.txt"
#define SCORE_CONF "high_scores.txt"
#define IN_GAME_CONF "in_game.txt"
#define CREDITS_TEXT "Intro.STR"
#define CREDITS_VIDEO "tyney.avi"

//void design_main_menu(Layout* main_menu);
//void design_options_screen(Layout* options_screen);
////void design_pause_options_screen(Layout* options_screen);
////void design_end_options_screen(Layout* options_screen);
//void design_high_scores(Layout* high_scores);
////void design_pause_high_scores(Layout* high_scores);
////void design_end_high_scores(Layout* high_scores);
//void design_in_game(Layout* in_game);
//void design_pause(Layout* main_menu);
//void design_game_over(Layout* main_menu);

void load_ui_textures(UITexturing *texdb);
void init_events(UIEvents *eventsdb);
void configure_screens();

//void read();
//void emit();
//void readuser();
//void writeuser();
//void readscores();
//void writescores();


void cr();
void quit();
