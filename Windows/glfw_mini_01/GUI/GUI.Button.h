using namespace std;
#pragma once
#include <string>
#include "GUI.Globals.h"
#include "GUI.FontSystem.h"

#define BTN_STATES 6
#define BTN_INACTIVE 0
#define BTN_HOVERED 1
#define BTN_PRESSED 2
#define BTN_ACTIVE 3
#define BTN_HOVERED_ACTIVE 4
#define BTN_PRESSED_ACTIVE 5

#define BTN_BORDER_FACTOR 0.5


class Button {
	public:
		Button(string id="",
			string Text="",
			FTFont* fnt=NULL,
			GLuint fontsize=10,
			Pixel Origin=Pixel(-1,-1),
			int xsize=default_x,
			int ysize=default_y,
			bool unclickable=true,
			bool invisible=false,
			string callback="NONE"
			//void (*callback)()=NULL
			);
		virtual ~Button();
		virtual void display();
		virtual void set_size(int x, int y) { size_x=x; size_y=y; }
		virtual void get_size(int &x, int &y) { x=size_x; y=size_y; }
		virtual void set_origin(Pixel new_origin) { origin=new_origin; }
		virtual void upper_left(Pixel upper_left);
		virtual void lower_left(Pixel lower_left);
		virtual void upper_right(Pixel upper_right);
		virtual void lower_right(Pixel lower_right);
		virtual Pixel get_origin() { return origin; }
		virtual bool update();
		//virtual void force_state(GLuint state)  { Button::state=state; }
		virtual void force_active() { state=BTN_ACTIVE; value=true; }
		virtual GLuint get_state() { return state; }
		virtual bool get_value() { return value; }
		virtual void reset() { value=false; state=BTN_INACTIVE; }
		virtual unsigned int get_font_size() { return font_size; }
		virtual void set_text(string Txt) { text=Txt; }
		virtual string get_text() { return text; }
		virtual void adjust_to_text();
		virtual void reduce_text_to_size();
		virtual void set_font(string font_id, unsigned int font_size);
		virtual FTFont* get_font() { return font; }
		virtual void set_ID(string id) { ID=id; }
		virtual string get_ID() { return ID; }
		bool set_display(GLuint state, void (*fn)(float minx, float maxx, float miny, float maxy));
		bool set_text_display(GLuint state, void (*fn)());
		//void set_texture(GLuint state, GLuint texture_id) { textures[state]=texture_id; }
		void set_texture(GLuint state, string texture_id) { texture_ids[state]=texture_id; }
		void set_callback(void (*fn)()) { fire=fn; }
		void set_callback(string id) {
			if(id=="NONE") {fire=NULL; callback=id; return;}
			extern UIEvents* GUIEvents; fire=GUIEvents->get(id); callback=id; }
		string get_callback() { return callback; }
		bool is_unclickable() { return unclickable; }
		void set_unclickable() { unclickable=true; }
		void set_non_unclickable() { unclickable=false; }
		void set_sticky() { sticky=true; }
		void set_non_sticky() { sticky=false; }
		void invisibility();
		void visibility();
		void (*fire)();
		void set_round() { round = true; radius=min(size_x,size_y); }
		void set_square() { round=false; }
		string get_font_id() { return font_id; }
		bool is_round() { return round; }
		bool is_sticky() { return sticky; }
		bool is_invisible() { return invisible; }
		string get_texture(GLuint state) { return texture_ids[state]; }
		bool has_display(GLuint state) { return (displays[state]!=NULL); }
		void set_textbox(bool is) { textbox=is; if(textbox) force_active(); else reset(); }
		bool is_textbox() { return textbox; }
		//void set_partial_invisibility(bool has) { partially_invisible=has; }
	protected:		
		string ID;
		string font_id;
		bool invisible;
		bool unclickable;
		bool sticky;
		bool round;
		bool textbox;
		int radius;
		//bool partially_invisible;
		//GLuint textures[BTN_STATES];
		void (*displays[BTN_STATES])(float minx, float maxx, float miny, float maxy);
		void (*text_displays[BTN_STATES])();
		string texture_ids[BTN_STATES];
		//string sound_ids[BTN_STATES*3];
		void update_active(bool i_can_has_mouse);
		void update_inactive(bool i_can_has_mouse);
		bool is_hovered();
		void render_text();
		static const int default_x=100, default_y=100;
		GLuint state;
		int size_x, size_y, window_width, window_height;
		Pixel origin;
		bool value;
		string text;
		string callback;
		FTFont* font;
		unsigned int font_size;
};