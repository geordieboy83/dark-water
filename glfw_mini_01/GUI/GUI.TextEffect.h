#pragma once

#include "GUI.Globals.h"
#include "GUI.FontSystem.h"

class Text {
	public:
		Text(string txt, string font_id, unsigned int font_size=20, Pixel origin=Pixel(-1,1)):
		  text(txt), font(font_id), font_size(font_size), origin(origin), simple(true)
		  {
			  set_colour(1,1,1,1);
			  if(origin.x<0&&origin.y<0){ int w, h; glfwGetWindowSize(&w,&h); origin.set(w/2,h/2); }			 
		  }
		
		string font;
		unsigned int font_size;
		string text;
		Pixel origin;
		Colour text_colour;

		void display();
		void display_simple();
		
		void relative_origin()
		{
			if(!simple) return;
			if(text==""||font=="") return;
			extern FontSystem* GUIFonts;
			FTBBox box=GUIFonts->get_font(font, font_size)->BBox(text.c_str());
			origin.y-=box.Lower().Yf();
		}

		void print_centre() 
		{
			extern FontSystem* GUIFonts; 
			glColor4f(text_colour.r,text_colour.g,text_colour.b,text_colour.a);
			GUIFonts->print_centred(text,font,font_size,origin.x,origin.y); 
		}
		void print_simple() {
			extern FontSystem* GUIFonts; 
			glColor4f(text_colour.r,text_colour.g,text_colour.b,text_colour.a);
			GUIFonts->print(text,font,font_size,origin.x,origin.y); 
		}
		void lowerleft(Pixel ll) { 
			extern FontSystem* GUIFonts; FTBBox box=GUIFonts->get_font(font,font_size)->BBox(text.c_str());
			float x=(box.Upper().Xf()-box.Lower().Xf()), y=(box.Upper().Yf()-box.Lower().Yf());
			origin.set(ll.x+x/2,ll.y+y/2);
		}
		void lowerright(Pixel lr) { 
			extern FontSystem* GUIFonts; FTBBox box=GUIFonts->get_font(font,font_size)->BBox(text.c_str());
			float x=(box.Upper().Xf()-box.Lower().Xf()), y=(box.Upper().Yf()-box.Lower().Yf());
			origin.set(lr.x-x/2,lr.y+y/2);
		}
		void upperleft(Pixel ul) { 
			extern FontSystem* GUIFonts; FTBBox box=GUIFonts->get_font(font,font_size)->BBox(text.c_str());
			float x=(box.Upper().Xf()-box.Lower().Xf()), y=(box.Upper().Yf()-box.Lower().Yf());
			origin.set(ul.x+x/2,ul.y-y/2);
		}
		void upperright(Pixel ur) { 
			extern FontSystem* GUIFonts; FTBBox box=GUIFonts->get_font(font,font_size)->BBox(text.c_str());
			float x=(box.Upper().Xf()-box.Lower().Xf()), y=(box.Upper().Yf()-box.Lower().Yf());
			origin.set(ur.x-x/2,ur.y-y/2);
		}

		void set_colour(float r, float g, float b, float a) { 
			text_colour.r=r; text_colour.g=g; text_colour.b=b; text_colour.a=a; 
		}

		void simplify() { simple=true; }
		void format(FTGL::TextAlignment alignment, float linesize) { 
			simple=false;
			Text::alignment=alignment;
			line_size=linesize;
		}

		bool simple;
		FTGL::TextAlignment alignment;
		int line_size;
};