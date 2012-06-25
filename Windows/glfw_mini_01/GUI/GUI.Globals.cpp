#include "GUI.Globals.h"

FTPoint stringseed(const char* string, Pixel origin,FTFont* font)
{
	FTBBox box=font->BBox(string);
	float x=(box.Upper().Xf()-box.Lower().Xf());
	float y=(box.Upper().Yf()-box.Lower().Yf());

	return FTPoint::FTPoint(origin.x-0.5*x, origin.y-0.5*y);
}

void button_display_inactive(float minx, float maxx, float miny, float maxy)
{
	glColor4f(0,0,1,0.5);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_QUADS);

		glTexCoord2i(0,0);
		glVertex2f(minx, miny);
		glTexCoord2i(1,0);
		glVertex2f(maxx, miny);
		glTexCoord2i(1,1);
		glVertex2f(maxx, maxy);
		glTexCoord2i(0,1);
		glVertex2f(minx, maxy);

	glEnd();
}

void button_display_hovered(float minx, float maxx, float miny, float maxy)
{
	glColor4f(0,1,0,0.5);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_QUADS);

		glTexCoord2i(0,0);
		glVertex2f(minx, miny);
		glTexCoord2i(1,0);
		glVertex2f(maxx, miny);
		glTexCoord2i(1,1);
		glVertex2f(maxx, maxy);
		glTexCoord2i(0,1);
		glVertex2f(minx, maxy);

	glEnd();
}

void button_display_pressed(float minx, float maxx, float miny, float maxy)
{
	glColor4f(1,0,0,0.5);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_QUADS);

		glTexCoord2i(0,0);
		glVertex2f(minx, miny);
		glTexCoord2i(1,0);
		glVertex2f(maxx, miny);
		glTexCoord2i(1,1);
		glVertex2f(maxx, maxy);
		glTexCoord2i(0,1);
		glVertex2f(minx, maxy);

	glEnd();
}

void button_display_active(float minx, float maxx, float miny, float maxy)
{
	glColor4f(1,1,0,0.5);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_QUADS);

		glTexCoord2i(0,0);
		glVertex2f(minx, miny);
		glTexCoord2i(1,0);
		glVertex2f(maxx, miny);
		glTexCoord2i(1,1);
		glVertex2f(maxx, maxy);
		glTexCoord2i(0,1);
		glVertex2f(minx, maxy);

	glEnd();
}

void button_display_active_hovered(float minx, float maxx, float miny, float maxy)
{
	glColor4f(1,0,1,0.5);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_QUADS);

		
		glTexCoord2i(0,0);
		glVertex2f(minx, miny);
		glTexCoord2i(1,0);
		glVertex2f(maxx, miny);
		glTexCoord2i(1,1);
		glVertex2f(maxx, maxy);
		glTexCoord2i(0,1);
		glVertex2f(minx, maxy);

	glEnd();
}

void button_display_active_pressed(float minx, float maxx, float miny, float maxy)
{
	glColor4f(1,1,1,0.5);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_QUADS);

		glTexCoord2i(0,0);
		glVertex2f(minx, miny);
		glTexCoord2i(1,0);
		glVertex2f(maxx, miny);
		glTexCoord2i(1,1);
		glVertex2f(maxx, maxy);
		glTexCoord2i(0,1);
		glVertex2f(minx, maxy);

	glEnd();
}

void button_text_display()
{
	glColor3f(1,1,1);
}

void button_text_hovered()
{
	glColor3f(1,1,0);
}

void button_text_pressed()
{
	glColor3f(1,0,1);
}

void button_text_active()
{
	glColor3f(0.5,0.5,1);
}

void saveGL()
{
	int w,h;
	glfwGetWindowSize(&w,&h);
	   
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
	gluOrtho2D(0,w,0,h);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
}

void restoreGL()
{	
	glPopAttrib();
	glEnable(GL_CULL_FACE);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
