using namespace std;
#pragma once

//#define g 5.7

#include "Projectile.h"


class Boulder: public Projectile
{
	public:
		Boulder(unsigned int id,unsigned int owner, bool active);
		void fire();
		void update();
		Vector horizontalvelocity;
		//Vector u0z;
		//Vector gravity;
		float g;
		void display();
		bool can_move();
};
