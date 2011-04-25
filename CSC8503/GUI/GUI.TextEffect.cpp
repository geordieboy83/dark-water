#include "GUI.TextEffect.h"

extern FontSystem* GUIFonts;
FTSimpleLayout FormattedText;

void Text::display(){
			if(simple) print_centre();
			else {
				FormattedText.SetAlignment(alignment);
				FormattedText.SetFont(GUIFonts->get_font(font,font_size));
				FormattedText.SetLineLength(line_size);
				FTBBox b=FormattedText.BBox(text.c_str());
				float sizex=b.Upper().Xf()-b.Lower().Xf(),sizey=b.Upper().Yf()-b.Lower().Yf();
				float x=b.Upper().Xf()+b.Lower().Xf(),y=b.Upper().Yf()+b.Lower().Yf();
				Pixel textorigin(0.5*x,0.5*y);
				glColor4f(text_colour.r,text_colour.g,text_colour.b,text_colour.a);
				glPushMatrix();
				glLoadIdentity();
				glTranslatef(origin.x-textorigin.x,origin.y-textorigin.y,0);
				FormattedText.Render(text.c_str());
				glPopMatrix();
			}
		}

void Text::display_simple(){
			if(simple) print_simple();
			else {
				FormattedText.SetAlignment(alignment);
				FormattedText.SetFont(GUIFonts->get_font(font,font_size));
				FormattedText.SetLineLength(line_size);
				glColor4f(text_colour.r,text_colour.g,text_colour.b,text_colour.a);
				glPushMatrix();
				glLoadIdentity();
				glTranslatef(origin.x, origin.y, 0);
				FormattedText.Render(text.c_str());
				glPopMatrix();
			 }
		}