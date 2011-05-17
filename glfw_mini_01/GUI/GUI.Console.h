#pragma once;

#include "GUI.Button.h"

void GLFWCALL consolespecial(int key,int action);
void GLFWCALL console( int key, int action );

class Console {
	public:
		Console(string id="",int length=10, string font_id="", unsigned int font_size=20, Pixel lowerleft=Pixel(0,0));
		~Console(){}
		void set_active();
		void set_inactive();
		bool get_active() { return active; }
		void set_ID(string id) { ID=id; }
		string get_ID() { return ID; }
		void set_length(int l) { length=l; }
		int get_length() { return length; }
		bool update();
		void display();
		void set_content(string txt) { content=txt; text.set_text(txt); }
		string get_content() { return content; }
		Button* get_text() { return &text; }
		Button* get_enter() { return &enter; }
		Button* get_cancel() { return &cancel; }
		Button* get_trigger() { return &trigger; }
		void get_size(int &x, int &y) { x=size_x; y=size_y; }
		void centre(float x, float y);
	protected:
		bool update_active();
		bool update_inactive();
		bool active;
		string ID;
		int length;
		FTFont* font;
		string font_id;
		unsigned int font_size;
		Button text;
		Button enter;
		Button cancel;
		Button trigger;
		Pixel origin;
		string content;
		int size_x;
		int size_y;

};