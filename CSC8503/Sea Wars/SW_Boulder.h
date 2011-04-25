using namespace std;
#pragma once

//#define g 5.7

#include "SW_Projectile.h"


class SeaWarsBoulder: public SeaWarsProjectile
{
	public:
		SeaWarsBoulder(unsigned int id,unsigned int owner, bool active);
		void fire();
		void update();
		Vector horizontalvelocity;
		//Vector u0z;
		//Vector gravity;
		float g;
		void display();
		bool can_move();
};
