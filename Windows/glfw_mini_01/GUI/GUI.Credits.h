#pragma once;

#include "GUI.Globals.h"
#include "GUI.TextEffect.h"
#include "GUI.Button.h"

#define CREDITS_ZOOM 0
#define CREDITS_ROLL 1

using namespace std;

class CreditsScreen {
	public:
		//CreditsScreen( string videofile,string creditsfile);
		CreditsScreen(string creditsfile);
		~CreditsScreen() {}
		void set_effect(GLuint texteffect) { effect=texteffect; }
		GLuint get_effect() { return effect; }
		
		
		void set_textfile(string creditsfile) { credits=creditsfile; }
		//void set_videofile(string videofile) { avi=videofile; }
		FTBBox configure_text(FTGL::TextAlignment alignment, FTPolygonFont* fnt, float linesize) { 
			text.SetAlignment(alignment);
			text.SetFont(fnt);
			font=fnt;
			text.SetLineLength(linesize);
			return text.BBox(total.c_str());
		}
		void set_animation(Pixel start, Pixel end, float duration) {
			from=start, to=end, animation_duration=duration;
		}
		void trigger();		
	protected:
		void update_rolling();
		void update_zooming();
		void read_text();
		string credits;
		//string avi;
		GLuint effect;
		float animation_start;
		float animation_duration;
		
		Pixel from, to;
		FTSimpleLayout text;
		vector<string> individual;
		string total;
		FTPolygonFont* font;


};