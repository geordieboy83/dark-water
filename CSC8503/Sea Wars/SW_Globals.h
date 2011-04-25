using namespace std;
#pragma once

//#include <GL\glew.h>
#include <GL/glfw.h>
#include <FTGL\ftgl.h>
#include <iostream>
//#include <Courseworx\GLPolygon.h>
#include "SW_Entity.h"
#include <time.h>
#include "../GUI/SoundManager.h"

//#define SW_WINDOW_X 800
//#define SW_WINDOW_Y 600
//#define VIEW_X 500
//#define VIEW_Y 500
//#define VIEW_Z 500

#define SW_WORLD_FROM -960
#define SW_WORLD_TO 960
#define SW_QUADS 320
#define SW_WATERQUADS 4
#define PI 3.1415926535897932384626433832795
#define SW_MOVEMENTFACTOR 0.8
#define SW_ANGLEFACTOR 1
#define SW_DEATHFACTOR 10
#define SW_SNIPERFACTOR 1
#define SW_TRANSFORMFACTOR 5
#define SW_PLAYERPROJECTILESPEED 1.5
#define SW_ISLEPROJECTILESPEED 2

#define SW_PLAYERS 2
#define SW_BOXES 5
#define SW_ISLES 1
#define SW_PROJECTILES 2*SW_PLAYERS+SW_ISLES

#define SW_FIRST_PLAYER 0
#define SW_PLAYER1 SW_FIRST_PLAYER
#define SW_PLAYER2 SW_FIRST_PLAYER+1
#define SW_LAST_PLAYER SW_FIRST_PLAYER+SW_PLAYERS-1

#define SW_FIRST_BOX SW_LAST_PLAYER+1
#define SW_BOX1 SW_FIRST_BOX
#define SW_BOX2 SW_FIRST_BOX+1
#define SW_BOX3 SW_FIRST_BOX+2
#define SW_BOX4 SW_FIRST_BOX+3
#define SW_BOX5 SW_FIRST_BOX+4
#define SW_LAST_BOX SW_FIRST_BOX+SW_BOXES-1

#define SW_FIRST_ISLE SW_LAST_BOX+1
#define SW_ISLE1 SW_FIRST_ISLE
#define SW_LAST_ISLE SW_FIRST_ISLE+SW_ISLES-1

#define SW_FIRST_PROJECTILE SW_LAST_ISLE+1
#define SW_FIRE1 SW_FIRST_PROJECTILE
#define SW_FIRE2 SW_FIRST_PROJECTILE+1
#define SW_FIRE3 SW_FIRST_PROJECTILE+2
#define SW_FIRE4 SW_FIRST_PROJECTILE+3
#define SW_FIRE5 SW_FIRST_PROJECTILE+4
#define SW_LAST_PROJECTILE SW_FIRST_PROJECTILE+SW_PROJECTILES-1

#define SW_PLAYER1FIRE SW_FIRE1
#define SW_PLAYER2FIRE SW_FIRE2
#define SW_PLAYER1SNIPER SW_FIRE3
#define SW_PLAYER2SNIPER SW_FIRE4
#define SW_ISLE1FIRE SW_FIRE5

#define SW_FIRST_PLAYER_PROJECTILE SW_PLAYER1FIRE
#define SW_LAST_PLAYER_PROJECTILE SW_PLAYER2FIRE
#define SW_FIRST_ISLE_PROJECTILE SW_ISLE1FIRE
#define SW_LAST_ISLE_PROJECTILE SW_ISLE1FIRE
#define SW_FIRST_PLAYER_SNIPER SW_PLAYER1SNIPER
#define SW_LAST_PLAYER_SNIPER SW_PLAYER2SNIPER

#define SW_IDS SW_PLAYERS+SW_BOXES+SW_ISLES+SW_PROJECTILES+1+1
#define SW_FREE SW_IDS-2
#define SW_EDGE SW_IDS-1

#define SW_MINIMAP_ISLE SW_LAST_PLAYER+1
#define SW_MINIMAP_BOX SW_MINIMAP_ISLE+1
#define SW_MINIMAP_PROJECTILE SW_MINIMAP_BOX+1
#define SW_MINIMAP_OTHER SW_MINIMAP_PROJECTILE+1
#define SW_MINIMAP_COLOURS SW_PLAYERS+1+1+1+1

// Player controls
#define SW_PLAYER_CONTROLS 9
#define SW_FWD 0
#define SW_LFT 1
#define SW_RT 2
#define SW_SN_UP 3
#define SW_SN_DN 4
#define SW_SN_LFT 5
#define SW_SN_RT 6
#define SW_SN_ON 7
#define SW_FIRE 8

#define SW_PLAYER1KEYS {\
	GLFW_KEY_UP, GLFW_KEY_LEFT, GLFW_KEY_RIGHT,\
	GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT,\
	GLFW_KEY_SPACE, GLFW_KEY_RCTRL}

#define SW_PLAYER2KEYS {\
	'W', 'A', 'D',\
	'W', 'S', 'A', 'D',\
	'Z', GLFW_KEY_LCTRL}

/*

typedef struct{
	string name, map_Ka, map_Kd, map_Ks, map_Tr, map_bump;
	float Ke[4], Ka[4], Kd[4], Ks[4], Ns[1], Tr;
	int id;
} material;

*/


#define SW_PLAYER1MATERIALS {"BOAT1","","","","","",{0,0,0,0},{0,0,1,0},{0,0,1,0},{0.27,0.27,0.27,0},{80.0},0,0},\
		{"SAIL1","","","","","",{0,0,0,0},{0.9,0.9,0.9,0},{0.9,0.9,0.9,0},{1,1,1,0},{10.0},0,1}
	
#define SW_PLAYER2MATERIALS {"BOAT2","","","","","",{0,0,0,0},{1,0,0,0},{1,0,0,0},{0.27,0.27,0.27,0},{80.0},0,0},\
	{"SAIL2","","","","","",{0,0,0,0},{0.9,0.9,0.9,0},{0.9,0.9,0.9,0},{1,1,1,0},{10.0},0,1}

#define SW_WATERMATERIALS {"WATER","","","","","",{0,0,0,0},{0,0.3,0.7,0},{0,0.3,0.7,0},{0,0.4,0.9,0},{200.0},0,0}

#define SW_ISLEMATERIALS {"ISLE","","","","","",{0,0,0,0},{0.5882,0.5882,0.5882,0},{0.5882,0.5882,0.5882,0},{0.8190,0.8190,0.8190,0},{47.0},0,0}

#define SW_PL1PRJMATERIALS SW_PLAYER1MATERIALS
#define SW_PL2PRJMATERIALS SW_PLAYER2MATERIALS
#define SW_ISLPRJMATERIALS SW_ISLEMATERIALS

#define SW_BOXMATERIALS {"BOX","","","","","",{0,0,0,0},{1,1,1,0},{1,1,1,0},{0.27,0.27,0.27,0},{67.0},0,0},\
		{"WRAP","","","","","",{0,0,0,0},{0.8196,0,0,0},{0.8196,0,0,0},{0.27,0.27,0.27,0},{67.0},0,1}

#define SW_SWATMATERIALS {"GRID","","","","","",{0.1760,0.2287,0,0},{0,0,0,0},{0.7333,0.9529,0,0},{0.9299,0.8546,0.4292,0},{52.0},0,0},\
		{"HANDLE","","","","","",{0,0,0,0},{0,0,0,0},{0.5880,0.5880,0.5880,0},{0,0,0,0},{10.0},0,1}

#define SW_PL1 0
#define SW_PL2 2
#define SW_WTR 4
#define SW_ISL 5
#define SW_PL1PRJ 6
#define SW_PL2PRJ 8
#define SW_ISLPRJ 10
#define SW_CRT 11
#define SW_SWT 13


#define SW_MODELS 8
#define SW_PLMDL 0
#define SW_ISLEMDL 1
#define SW_PLPRJMDL 2
#define SW_ISLPRJMDL 3
#define SW_BOXMDL 4
#define SW_TPT 5
#define SW_SWATTER 6
#define SW_CUBE 7

#define SW_TEXTURES 9
#define SW_WTRTX 0
#define SW_ISLTX 1
#define SW_PLTX 2
#define SW_PLPRJTX 3
#define SW_ISLPRJTX 4
#define SW_CRTTX 5
#define SW_BSODTX 6
#define SW_LOADTX 7
#define SW_MENUTX 8

typedef struct{
	int HP;
	bool dd;
	bool ua;
	bool tf;
	bool rf;
	bool snipe;
	bool shot;
	bool alive;
	bool present;
	bool sniperviewpt;

}state;//report;

GLuint minimap_colour(GLuint id);
float sw_deg2rad(float angle_in_degrees);
void sw_materialise(unsigned int what);
void sw_texturise(unsigned int what);
FTPoint sw_stringseed(const char* string, Vertex origin);
unsigned int prj_of_player(unsigned int ID, string what);
float projectilefactor(unsigned int ID);
void Zlimits();
void sw_BSOD();
void sea(float z);
void global_grid(float z);
unsigned int txt_of_entity(unsigned int ID);
void update_world();
void display_world();
void minimap(GLint x, GLint y, GLsizei width, GLsizei height);
void sw_update_landscape();
void sw_scenery();
Vertex Randomise(string what);
