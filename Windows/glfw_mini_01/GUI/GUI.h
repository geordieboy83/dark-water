#pragma once
#include "GUI.Screens.h"

class GUI {
	public:
		GUI();
		~GUI();

		
		bool get_button(string button_id, string layout_id);
		
		SoundSystem* get_sounds() { return Sounds; }
		FontSystem* get_fonts() { return Fonts; }
		UITexturing* get_textures() { return &Textures; }
		UIScreens* get_screens() { return &Screens; }
		UIEvents* get_events() { return &Events; }
		CreditsScreen* get_credits() { return Credits; }
		void update() { Screens.update(); }
		void display() { Screens.display(); }
		bool off_game();
		bool pause_game();
		bool game_over();
		bool in_game();
	private:
		SoundSystem* Sounds;
		FontSystem* Fonts;
		CreditsScreen* Credits;
		UITexturing Textures;
		UIScreens Screens;
		UIEvents Events;
		

		string PATH;
};
