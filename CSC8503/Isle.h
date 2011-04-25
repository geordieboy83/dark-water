#pragma once
#include <Courseworx\Globals.h>
#include "Boulder.h"
using namespace cyclone;

#define BOULDERS 20

//The island class
class Isle : public CollisionSphere
{
	public:
		
		Isle();
		
		~Isle() { delete body;}
		
		//Update state
		void update();

		//Display island
		void display();

		//The display list
		GLuint self;

		//Fire
		void fire();

		//Boulders
		Boulder boulders[BOULDERS];

		//Reset the volcano
		void reset();

		//The volcano's coastline bounding sphere
		CollisionSphere coastline;

		//When the last boulder was thrown
		float LastFiredAt;

		//Current height of island.
		float currentheight;

		//Is it active?
		bool active;

		//Is it dead?
		bool dead;

		//Damage
		void wound(int damage);

		//Hitpoints
		int HP;

		//Getter: maximum hitpoints
		int get_maxHP() { return maxHP; }

private:
	//Y-offset so that the island is just under the surface of the sea
	float underwater;
	
	//Maximum hitpoints
	static const int maxHP=100;
};


