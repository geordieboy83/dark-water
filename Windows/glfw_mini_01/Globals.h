using namespace std;
#pragma once

#include <GL/glfw.h>
#include <FTGL\ftgl.h>
#include <iostream>
#include "Entity.h"
#include <time.h>
#include "GUI\SoundManager.h"

#define WINDOW_X 1024
#define WINDOW_Y 768

#define FX_VOLUME 0.1

#define WORLD_FROM -960
#define WORLD_TO 960
#define QUADS 320
#define WATERQUADS 4
#define PI 3.1415926535897932384626433832795
#define MOVEMENTFACTOR 0.8
#define ANGLEFACTOR 1
#define DEATHFACTOR 10
#define SNIPERFACTOR 1
#define TRANSFORMFACTOR 5
#define PLAYERPROJECTILESPEED 1.5
#define ISLEPROJECTILESPEED 2

#define PLAYERS 2
#define BOXES 5
#define ISLES 1
#define PROJECTILES 2*PLAYERS+ISLES

#define FIRST_PLAYER 0
#define PLAYER1 FIRST_PLAYER
#define PLAYER2 FIRST_PLAYER+1
#define LAST_PLAYER FIRST_PLAYER+PLAYERS-1

#define FIRST_BOX LAST_PLAYER+1
#define BOX1 FIRST_BOX
#define BOX2 FIRST_BOX+1
#define BOX3 FIRST_BOX+2
#define BOX4 FIRST_BOX+3
#define BOX5 FIRST_BOX+4
#define LAST_BOX FIRST_BOX+BOXES-1

#define FIRST_ISLE LAST_BOX+1
#define ISLE1 FIRST_ISLE
#define LAST_ISLE FIRST_ISLE+ISLES-1

#define FIRST_PROJECTILE LAST_ISLE+1
#define FIRE1 FIRST_PROJECTILE
#define FIRE2 FIRST_PROJECTILE+1
#define FIRE3 FIRST_PROJECTILE+2
#define FIRE4 FIRST_PROJECTILE+3
#define FIRE5 FIRST_PROJECTILE+4
#define LAST_PROJECTILE FIRST_PROJECTILE+PROJECTILES-1

#define PLAYER1FIRE FIRE1
#define PLAYER2FIRE FIRE2
#define PLAYER1SNIPER FIRE3
#define PLAYER2SNIPER FIRE4
#define ISLE1FIRE FIRE5

#define FIRST_PLAYER_PROJECTILE PLAYER1FIRE
#define LAST_PLAYER_PROJECTILE PLAYER2FIRE
#define FIRST_ISLE_PROJECTILE ISLE1FIRE
#define LAST_ISLE_PROJECTILE ISLE1FIRE
#define FIRST_PLAYER_SNIPER PLAYER1SNIPER
#define LAST_PLAYER_SNIPER PLAYER2SNIPER

#define IDS PLAYERS+BOXES+ISLES+PROJECTILES+1+1
#define FREE IDS-2
#define EDGE IDS-1

#define MINIMAP_ISLE LAST_PLAYER+1
#define MINIMAP_BOX MINIMAP_ISLE+1
#define MINIMAP_PROJECTILE MINIMAP_BOX+1
#define MINIMAP_OTHER MINIMAP_PROJECTILE+1
#define MINIMAP_COLOURS PLAYERS+1+1+1+1

// Player controls
#define PLAYER_CONTROLS 9
#define FWD 0
#define LFT 1
#define RT 2
#define SN_UP 3
#define SN_DN 4
#define SN_LFT 5
#define SN_RT 6
#define SN_ON 7
#define FIRE 8

#define PLAYER1KEYS {\
	GLFW_KEY_UP, GLFW_KEY_LEFT, GLFW_KEY_RIGHT,\
	GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT,\
	GLFW_KEY_SPACE, GLFW_KEY_RCTRL}

#define PLAYER2KEYS {\
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


#define PLAYER1MATERIALS {"BOAT1","","","","","",{0,0,0,0},{0,0,1,0},{0,0,1,0},{0.27,0.27,0.27,0},{80.0},0,0},\
		{"SAIL1","","","","","",{0,0,0,0},{0.9,0.9,0.9,0},{0.9,0.9,0.9,0},{1,1,1,0},{10.0},0,1}
	
#define PLAYER2MATERIALS {"BOAT2","","","","","",{0,0,0,0},{1,0,0,0},{1,0,0,0},{0.27,0.27,0.27,0},{80.0},0,0},\
	{"SAIL2","","","","","",{0,0,0,0},{0.9,0.9,0.9,0},{0.9,0.9,0.9,0},{1,1,1,0},{10.0},0,1}

#define WATERMATERIALS {"WATER","","","","","",{0,0,0,0},{0,0.3,0.7,0},{0,0.3,0.7,0},{0,0.4,0.9,0},{200.0},0,0}

#define ISLEMATERIALS {"ISLE","","","","","",{0,0,0,0},{0.5882,0.5882,0.5882,0},{0.5882,0.5882,0.5882,0},{0.8190,0.8190,0.8190,0},{47.0},0,0}

#define PL1PRJMATERIALS PLAYER1MATERIALS
#define PL2PRJMATERIALS PLAYER2MATERIALS
#define ISLPRJMATERIALS ISLEMATERIALS

#define BOXMATERIALS {"BOX","","","","","",{0,0,0,0},{1,1,1,0},{1,1,1,0},{0.27,0.27,0.27,0},{67.0},0,0},\
		{"WRAP","","","","","",{0,0,0,0},{0.8196,0,0,0},{0.8196,0,0,0},{0.27,0.27,0.27,0},{67.0},0,1}

#define SWATMATERIALS {"GRID","","","","","",{0.1760,0.2287,0,0},{0,0,0,0},{0.7333,0.9529,0,0},{0.9299,0.8546,0.4292,0},{52.0},0,0},\
		{"HANDLE","","","","","",{0,0,0,0},{0,0,0,0},{0.5880,0.5880,0.5880,0},{0,0,0,0},{10.0},0,1}

#define PL1 0
#define PL2 2
#define WTR 4
#define ISL 5
#define PL1PRJ 6
#define PL2PRJ 8
#define ISLPRJ 10
#define CRT 11
#define SWT 13


#define MODELS 8
#define PLMDL 0
#define ISLEMDL 1
#define PLPRJMDL 2
#define ISLPRJMDL 3
#define BOXMDL 4
#define TPT 5
#define SWATTER 6
#define CUBE 7

#define TEXTURES 9
#define WTRTX 0
#define ISLTX 1
#define PLTX 2
#define PLPRJTX 3
#define ISLPRJTX 4
#define CRTTX 5
#define BSODTX 6
#define LOADTX 7
#define MENUTX 8

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

}report;

GLuint minimap_colour(GLuint id);
float deg2rad(float angle_in_degrees);
void materialise(unsigned int what);
void texturise(unsigned int what);
FTPoint stringseed(const char* string, Vertex origin);
unsigned int prj_of_player(unsigned int ID, string what);
float projectilefactor(unsigned int ID);
void Zlimits();
void BSOD();
void sea(float z);
void global_grid(float z);
unsigned int txt_of_entity(unsigned int ID);
void update_world();
void display_world();
void minimap(GLint x, GLint y, GLsizei width, GLsizei height);
void update_landscape();
void scenery();
Vertex Randomise(string what);
