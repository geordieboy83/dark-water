#pragma once

#include "GUI.Button.h"

class Slider {
	public:
		Slider();
		~Slider();
		Slider(string ID, Pixel from, Pixel to, float value, unsigned int states=1, int size_x=100, int size_y=100, float barheightfactor=0.25);
		void set_size(int x, int y) { control.set_size(x,y); }
		bool update();
		void display();
		void set_ID(string id) { ID=id; control.set_ID(id); }
		string get_ID() { return ID; }
		float get_value() { return value; }
		void set_value(float new_val) { 
			value=new_val; 
			Pixel v=control.get_origin();			
			if(states>1){
				value=floor(value*(states-1))/(float)(states-1);
			}
			v.x=from.x+value*(to.x-from.x);
			control.set_origin(v);			
		}
		void set_bar_texture(string tex_id) { bartexture=tex_id; }
		string get_bar_texture() { return bartexture; }
		void set_control_texture(string tex_id) { for(int i=BTN_INACTIVE; i<BTN_STATES; i++) control.set_texture(i,tex_id); }
		string get_control_texture() { return control.get_texture(BTN_INACTIVE); }
		Button* get_control() { return &control; }
		Pixel get_from() { return from; }
		Pixel get_to() { return to; }
		float get_bar_height_factor() { return bar_height_factor; }
		unsigned int get_states() { return states; }
		void set_states(unsigned int new_states) { states=new_states; if(new_states==0) states=1; }
		int get_int() { return value*(states-1); }
		void set_state(int state) {
			if(states==1) return;
			value=(float)state/(states-1); 
			Pixel v=control.get_origin();			
			v.x=from.x+value*(to.x-from.x);
			control.set_origin(v);		
		}
	protected:
		string ID;
		string bartexture;
		float bar_height_factor;
		Button control;
		float value;
		Pixel from, to;
		unsigned int states;
};