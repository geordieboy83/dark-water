#pragma once
#include "GUI.Globals.h"

#define MIN_FONT_SIZE 6
#define MAX_FONT_SIZE 60

class FontSystem {
	public:
		FontSystem(string FontMap);
		~FontSystem();
		void print_centred(string text, string font_id, unsigned int font_size, float x, float y);//Vertex text_centre);
		void print(string text, string font_id, unsigned int font_size, float x=0, float y=0);
		FTFont* get_font(string font_id,unsigned int font_size=20);
		void reset();
	protected:
		bool load(string FontMap);		

		map<string,vector<FTFont*>> FontDB;
};