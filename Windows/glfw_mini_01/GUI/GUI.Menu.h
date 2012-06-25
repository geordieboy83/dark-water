using namespace std;

#pragma once

#include <fstream>
#include "GUI.Button.h"

#define MENU_MAX_ENTRIES 10

class Menu {
	public:
		Menu();
		Menu(string menu_id, string menumap, string font_id, unsigned int font_size=10);
		virtual ~Menu();
		void make_entries(unsigned int entries);
		void set_font(string font_id, unsigned int font_size);
		void add_entry_text(unsigned int entry, string Text);
		void set_entry_callback(unsigned int entry, void (*fn)()) { Entries[entry-1].set_callback(fn); }
		Menu* get_submenu(unsigned int which);
		Pixel get_origin() { return origin; }
		void set_origin(Pixel upper_left);
		void set_origin();
		bool update();
		void display();
		void activate() { active=true; }
		void deactivate();
		void set_path(unsigned int path) { PATH = path;}
		unsigned int get_path() {return PATH;}
		bool add(Menu* submenu, unsigned int pathcode);
		bool get_command(string id) { return Commands[id]->get_value(); }
		Button* get_entry(string id) { return Commands[id]; }
		Button* get_entry(unsigned int id) { return &Entries[id]; }
		vector<string> get_commands();
		void get_size(int &x, int &y) { x=size_x; y=size_y; }
		void get_entry_size(int& x, int& y) { if(Entries.size()!=NULL) { Entries[1].get_size(x,y); } else { x=0; y=0; } }
		void set_order(bool left_to_right) { L2R=left_to_right; }
		string get_menumap() { return menumap; }
		string get_ID() { return ID; }
		void set_ID(string id) { ID=id; }
		string get_font() { return font_id; }
		unsigned int get_font_size() { return font_size; }
		void set_texture(GLuint state, string texture_id);
		string get_texture(GLuint state) { return texture_ids[state]; }
		void set_display(GLuint state, void (*fn)(float minx, float maxx, float miny, float maxy));
		bool has_display(GLuint state) { return (displays[state]!=NULL); }
		map<string,bool>* get_flags() { return &flags; }
	protected:
		string menumap;
		string ID;
		virtual bool update_internals();
		virtual void execute();
		bool L2R;
		string font_id;
		bool load_menu(string file);
		void build_map();
		map<string, Button*> finals();
		map<string,Button*> Commands;
		map<string,bool> flags;
		void make_report();
		unsigned int PATH;
		Menu* read_menu(ifstream& file);
		bool is_hovered();
		bool active;
		void adjust_origin();
		Pixel origin;
		vector<Button> Entries;
		vector<Menu*> Submenus;
		FTFont* font;
		void CalculateInternals();
		unsigned int font_size;
		int size_x, size_y;
		string texture_ids[BTN_STATES];
		void (*displays[BTN_STATES])(float minx, float maxx, float miny, float maxy);
};