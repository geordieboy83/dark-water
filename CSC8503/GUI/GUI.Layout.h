#pragma once

#include "GUI.ButtonArray.h"
#include "GUI.Menu.h"
#include "GUI.Slider.h"
#include "GUI.TextEffect.h"
#include "GUI.List.h"
#include "GUI.Console.h"

class Layout;



typedef struct {
	Button* tab_header;
	Layout* tab_layout;
} Tab;

typedef struct {	
	string trigger_id;
	Layout* target;
	Layout* source;
	void switch_layout();
	void update();
} LayoutSwitch;


class Layout{
	public:
		Layout(string id="", bool active=true) :
		active(active), ID(id), on_activation(NULL), on_deactivation(NULL), has_bgm(false), bgm_playing(false)
		{ tabs.set_ID("TABS"); }
		~Layout();
		bool update();
		void display();
		
		Button* add_button(Button& btn) { buttons.push_back(btn); return &buttons.back(); }
		ButtonArray* add_buttonarray(ButtonArray& btnarr) { buttonarrays.push_back(btnarr); return &buttonarrays.back(); }
		Menu* add_static_menu(Menu* menu) { menus_static.push_back(menu); return menus_static.back(); }
		Menu* add_floating_menu(Menu* menu) { menus_floating.push_back(menu); return menus_floating.back(); }
		Slider* add_slider(Slider& slider) { sliders.push_back(slider); return &sliders.back(); }
		Quad* add_quad(float LLx, float LLy, float size_x, float size_y, string texture_id="") { quads.push_back(Quad(LLx,LLy,size_x, size_y, texture_id)); return &quads.back(); }
		Console* add_console(Console& console) { consoles.push_back(console); return &consoles.back(); }
		void set_active(bool state) { active=state; 
			if(state) { if(on_activation!=NULL) on_activation(); }
			else if(on_deactivation!=NULL) on_deactivation(); }
		void add_tab(string id, Layout& tab=Layout());
		void add_tab(Button& head, Layout& tab);
		void get_tab(string ID, Button* btn, Layout* tab) { btn=tabs.get_button(ID); tab=&tabbed_layouts[ID]; }
		Tab get_tab(string ID) { Tab result; result.tab_header=tabs.get_button(ID); result.tab_layout=&tabbed_layouts[ID]; return result; }
		void activate_tab(string ID);
		bool is_active() { return active; }
		void set_ID(string id) { ID = id; }
		Text* add_text(Text& txt) { texts.push_back(txt); return &texts.back(); }
		bool report_boolean(string id) { return booleans[id]; }
		string report_string(string id) { return strings[id]; }
		float report_float(string id) { return floats[id]; }
		int report_int(string id) { return ints[id]; }
		void set_event_on_activation(void (*fn)()) { on_activation=fn; }
		void set_event_on_deactivation(void (*fn)()) { on_deactivation=fn; }
		ButtonArray* get_array(string id) { 
			ButtonArray *res=NULL;
			for(int i=0;i<buttonarrays.size();i++) {
				if(buttonarrays[i].get_ID()==id) {
					res=&buttonarrays[i];
					break;
				}
			}
			return res;
		}
		
		Slider* get_slider(string id) { 
			Slider *res=NULL;
			for(int i=0;i<sliders.size();i++) {
				if(sliders[i].get_ID()==id) {
					res=&sliders[i];
					break;
				}
			}
			return res;
		}

		Console* get_console(string id) { 
			Console *res=NULL;
			for(int i=0;i<consoles.size();i++) {
				if(consoles[i].get_ID()==id) {
					res=&consoles[i];
					break;
				}
			}
			return res;
		}



		Menu* get_menu(string id, bool floating) { 
			Menu *res=NULL;
			if(floating)
				for(int i=0;i<menus_floating.size();i++) {
					if(menus_floating[i]->get_ID()==id) {
						res=menus_floating[i];
						break;
					}
				}
			else
				for(int i=0;i<menus_static.size();i++) {
				if(menus_static[i]->get_ID()==id) {
					res=menus_static[i];
					break;
				}
			}
			return res;
		}
		LayoutSwitch* add_switch(string id, string target);

		Button* get_button(string id) { for(int i=0; i<buttons.size(); i++) if(buttons[i].get_ID()==id)	return &buttons[i]; }

		bool save_configuration(string filename);
		bool load_configuration(string filename);
		bool load_configuration(ifstream& filename);
		void reset();
		string get_ID() { return ID; }
		map<string,bool>* get_bools() { return &booleans; }
		map<string,string>* get_strings() { return &strings; }
		map<string,float>* get_floats() { return &floats; }
		map<string,int>* get_ints() { return &ints; }

		void compile_report();

		void set_bgm(bool has) {
			has_bgm=has; 
		}
		void set_bgm_id(string ID) {
			BGM_ID=ID; 
			has_bgm=true;
		}
		string get_bgm_ID() { return BGM_ID; }
		bool bgm_state() { return has_bgm; }
		void play_bgm();
		void stop_bgm();

	protected:
		void (*on_activation)();
		void (*on_deactivation)();
		string ID;
		bool active;
		bool save(ofstream& out);
		void save_text(ofstream& out, Text* t);
		void save_slider(ofstream& out, Slider* sl);
		void save_quad(ofstream& out, Quad* q);
		void save_button(ofstream& out, Button* b);
		void save_buttonarray(ofstream& out, ButtonArray* ba);
		void save_menu(ofstream& out, Menu* m);
		void save_list(ofstream& out, List* l);
		void save_tab(ofstream& out, Tab* t);
		void save_switch(ofstream& out, LayoutSwitch* lsw);
		bool load(ifstream& in);
		Text load_text(ifstream& in, float xfactor, float yfactor);
		Slider load_slider(ifstream& in, float xfactor, float yfactor);
		Quad load_quad(ifstream& in, float xfactor, float yfactor);
		Button load_button(ifstream& in, float xfactor, float yfactor);
		ButtonArray load_buttonarray(ifstream& in, float xfactor, float yfactor);
		Menu* load_menu(ifstream& in, float xfactor, float yfactor);		
		LayoutSwitch load_switch(ifstream& in);
		void load_tab(ifstream& in, float xfactor, float yfactor);
		bool fail() { reset(); return false; }
		bool update_internals();		
		void display_quad(int index);
		vector<Menu*> menus_floating;
		vector<Menu*> menus_static;
		vector<ButtonArray> buttonarrays;
		vector<Button> buttons;
		vector<Quad> quads;
		ButtonArray tabs;
		map<string,Layout> tabbed_layouts;
		vector<Slider> sliders;
		vector<Text> texts;
		vector<LayoutSwitch> switches;
		vector<Console> consoles;
		
		ALuint BGM;
		bool has_bgm;
		string BGM_ID;
		bool bgm_playing;

		map<string,bool> booleans;
		map<string,string> strings;
		map<string,float> floats;
		map<string,int> ints;
};

typedef struct {
	map<string,Layout> screens;
	Layout* current;
	void activate(string id) {
		current=NULL;
		for(map<string,Layout>::iterator i=screens.begin(); i!=screens.end(); i++){
			if(i->first==id) { 
				i->second.set_active(true);
				current=&i->second;
				
			}
			else{
				i->second.set_active(false);
			}
		}
	}
	void deactivate(string id) { screens[id].set_active(false); }
	Layout* get(string id) { return &screens[id]; }
	Layout* add(string id, bool active=true) { 
		screens.insert(screens.begin(), pair<string, Layout>(id,Layout(id,active)));
		return &screens[id];
	}
	void update() { current->update(); }
	void display() { 
		if(current==NULL||!current->is_active()) return;
		saveGL();
		int w,h; glfwGetWindowSize(&w,&h);
		glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluOrtho2D(0,w,0,h);
		glMatrixMode(GL_MODELVIEW);
		current->display();
		restoreGL(); 
	}
	string get_string(string id) { if(current==NULL) return ""; return current->report_string(id); }
	bool get_bool(string id) { if(current==NULL) return false; return current->report_boolean(id); }
	float get_float(string id) { if(current==NULL) return -1; return current->report_float(id); }
	int get_int(string id) { if(current==NULL) return -1; return current->report_int(id); }	
} UIScreens;
