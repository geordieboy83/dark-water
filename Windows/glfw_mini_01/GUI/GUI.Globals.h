using namespace std;

#pragma once

#include <GL\glfw.h>
#include <FTGL\ftgl.h>
#include "SoundManager.h"
//#include "../AviVideo.h"
//#include "../PhysicsWorld.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

class Pixel {
	public:
		Pixel(float xx=0, float yy=0): x(xx),y(yy) {}
		float x;
		float y;
		void set(float newx, float newy) { x=newx; y=newy; }
		float distance(Pixel& vtx) { return sqrt((x-vtx.x)*(x-vtx.x)+(y-vtx.y)*(y-vtx.y)); }
};

class Quad {
	public:
		Quad(float lower_left_x, float lower_left_y, float size_x, float size_y, string texture_id="NONE"):
		  lower_left(Pixel(lower_left_x,lower_left_y)),
			upper_right(Pixel(lower_left_x+size_x,lower_left_y+size_y)),
		  texture_id(texture_id) {}
		string texture_id;
		Pixel lower_left;
		Pixel upper_right;
};

typedef struct {
	float r,g,b,a;
} Colour;

typedef struct{
	map<string,GLuint> assets;
	void add(string ID, GLuint texture_id) { assets.insert(assets.begin(), pair<string,GLuint>(ID,texture_id)); }
	GLuint get(string ID) { return assets[ID]; }

} UITexturing;

typedef struct {
	map<string,void (*)()> callbacks;
	void add(string ID, void (*fn)()) { callbacks.insert(callbacks.begin(), pair<string,void (*)()>(ID,fn)); }
	void (*get(string ID))() { return callbacks[ID]; }
} UIEvents;


typedef struct {
	multimap<string,int> scores;
	void add(string player, int score) {
		scores.insert(scores.begin(),pair<string,int>(player,score));
	}
} HighScores;


FTPoint stringseed(const char* string, Pixel origin,FTFont* font);

void button_display_inactive(float minx, float maxx, float miny, float maxy);
void button_display_hovered(float minx, float maxx, float miny, float maxy);
void button_display_pressed(float minx, float maxx, float miny, float maxy);
void button_display_active(float minx, float maxx, float miny, float maxy);
void button_display_active_hovered(float minx, float maxx, float miny, float maxy);
void button_display_active_pressed(float minx, float maxx, float miny, float maxy);
void button_text_display();
void button_text_hovered();
void button_text_pressed();
void button_text_active();

void saveGL();
void restoreGL();