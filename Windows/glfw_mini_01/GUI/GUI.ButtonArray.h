#pragma once

#include "GUI.Globals.h"
#include "GUI.Button.h"

class ButtonArray {
	public:
		ButtonArray(string id=""): ID(id), active(""), buttons() {}
		~ButtonArray() {}
		Button* add_button(Button& btn);
		Button* get_button(string button_id) { return &buttons[button_id]; }
		bool update();
		void display();
		string get_active() { return active; }
		void set_active(string id) { 
			if(id=="") return;
			active=id;
			for(map<string,Button>::iterator i= buttons.begin(); i!=buttons.end(); i++)
				if(i->first==id) i->second.force_active();
				else i->second.reset();
		}
		string get_ID() { return ID; }
		void set_ID(string id) { ID=id; }
		vector<string> get_button_ids() { vector<string> result; for(map<string,Button>::iterator i= buttons.begin(); i!=buttons.end(); i++) result.push_back(i->second.get_ID()); return result;}
		void reset() { active=""; buttons.clear(); }
		int number_of_buttons() { return buttons.size(); }
	protected:
		string ID;
		string active;
		map<string,Button> buttons;		
};