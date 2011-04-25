
#pragma once

#include <GL/glfw.h>
#include <FTGL\ftgl.h>
#include <iostream>
#include <Courseworx\GLPolygon.h>
#include <cyclone\cyclone.h>
#include <SoundManager.h>


using namespace cyclone;


//#define WINDOW_X 1366 //800
//#define WINDOW_Y 768 //600

#define WORLD_TO 960
#define WORLD_FROM -WORLD_TO
#define WATERQUADS 4
#define PI 3.1415926535897932384626433832795
#define MOVEMENTFACTOR 0.8

#define BOXES 5

// Player controls
#define PLAYER_CONTROLS 4
#define FWD 0
#define LFT 1
#define RT 2
#define FIRE 3

#define PLAYER1KEYS { GLFW_KEY_UP, GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_RCTRL }

/*
typedef struct{
	string name, map_Ka, map_Kd, map_Ks, map_Tr, map_bump;
	float Ke[4], Ka[4], Kd[4], Ks[4], Ns[1], Tr;
	int id;
} material;
*/

#define PLAYER1MATERIALS {"BOAT1","","","","","",{0,0,0,0},{0,0,1,0},{0,0,1,0},{0.27,0.27,0.27,0},{80.0},0,0},\
		{"MAST1","","","","","",{0,0,0,0},{0,0,1,0},{0,0,1,0},{0.27,0.27,0.27,0},{80.0},0,0},\
		{"SAIL1","","","","","",{0,0,0,0},{0.9,0.9,0.9,0},{0.9,0.9,0.9,0},{1,1,1,0},{10.0},0,1}
	
#define WATERMATERIALS {"WATER","","","","","",{0,0,0,0},{0,0.3,0.7,0},{0,0.3,0.7,0},{0,0.4,0.9,0},{200.0},0,0}

#define MERCURYMATERIALS {"WATER","","","","","",{0,0,0,0},{0.3,0.3,0.3,0},{0.3,0.3,0.3,0},{0.9,0.9,0.9,0},{500.0},0,0}

#define PARAFFINMATERIALS {"WATER","","","","","",{0,0,0,0},{0.7,0.7,0.7,0},{0.7,0.7,0.7,0},{0.8,0.8,0.8,0},{50.0},0,0}

#define ISLEMATERIALS {"ISLE","","","","","",{0,0,0,0},{0.5882,0.5882,0.5882,0},{0.5882,0.5882,0.5882,0},{0.8190,0.8190,0.8190,0},{47.0},0,0}

#define BOXMATERIALS {"BOX","","","","","",{0,0,0,0},{1,1,1,0},{1,1,1,0},{0.27,0.27,0.27,0},{67.0},0,0},\
		{"WRAP","","","","","",{0,0,0,0},{0.8196,0,0,0},{0.8196,0,0,0},{0.27,0.27,0.27,0},{67.0},0,1}

#define WTRMTL 0
#define MRCMTL 1
#define PRFMTL 2
#define ISLMTL 3
#define BOXMTL 4
#define PL1MTL 6

#define MODELS 5
#define PLMDL 0
#define ISLEMDL 1
#define ISLPRJMDL 3
#define BOXMDL 4

#define TEXTURES 5
#define WTRTX 0
#define ISLTX 1
#define MRCTX 2
#define PRFTX 3
#define BSODTX 4

float deg2rad(float angle_in_degrees);
void materialise(unsigned int what);
void texturise(unsigned int what);
FTPoint stringseed(const char* string, Vertex origin);
void BSOD();
void sea(float y, string type);
void update_landscape();
void scenery();
double cos2x(double cosx);
double sin2x(double sinx);
void initialise();
void glLoadModels();
void glLoadTextures();
void axes();
float dampen(Vector3 position, float original_drag);
void bboxdisplay(CollisionBox &bbox);
void bspheredisplay(CollisionSphere &csphere);
void glProjection(int width, int height, unsigned int style, RigidBody& body);
