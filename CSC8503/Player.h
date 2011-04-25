#pragma once
#include <GL\glfw.h>
#include <FTGL\ftgl.h>
#include <cyclone\cyclone.h>
#include <Courseworx\Globals.h>
#include "Thing.h"
#include "Projectile.h"

using namespace cyclone;

#define ENGINE 5000
#define TORQUE 50
#define MASS 500
#define AMMO 20

//Class that implements the Player
class Player
{
	public:
		Player(int* keys);
		
		//Is player alive?
		bool dead;
		
		//The boat
		FloatingAeroThing boat;
		
		//Update player state
		void update();		
		
		//Display player
		void display();
		
		//The display list while alive
		GLuint living;

		//The display list when dead
		GLuint carcass;
		
		//Player's drawing materials
		GLuint material_index;
		
		//Hitpoints
		int HP;

		//Initialise player
		void set();

		//Projectiles
		Projectile ammo[AMMO];

		//Fire
		void fire();

		//When did we last fire?
		float LastFired;

		//Bounding sphere
		CollisionSphere csphere;

		//Individual bounding boxes
		CollisionBox hull, mast, sail;

		//Adapt the body to the properties of a new liquid
		void reliquidate(string s);

		//Damage
		void wound(int damage);

		//Apply effect from the giftbox that was picked up
		void affect(unsigned int effect);

		//Have we won?
		bool victor;

		//Getter: Maximum Hitpoints
		int get_maxHP() { return maxHP; }

	private:
		//The actual player depiction
		void draw_self();
		
		//Maximum Hitpoints
		static const int maxHP=200;
		
		//Control keys
		int controls[PLAYER_CONTROLS];
		
		//Keyboard input
		void key();
};
