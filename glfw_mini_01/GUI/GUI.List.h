#pragma once

#include "GUI.Menu.h"

class List : public Menu {
	public:
		List():Menu(){};
		~List() {}
		List(string list_id, string listmap, string font_id, unsigned int font_size=10, unsigned int default_option=1);
		void display();
		void default_entry(unsigned int path);
		string get_selection() { return Entries[0].get_text(); }
		void set_selection(string id);
	protected:
		bool update_internals();
		void execute();
		vector<List*> Sublists;
};