using namespace std;
#pragma once

#include "Projectile.h"

class Snipershot : public Projectile
{
	public:
		Snipershot(unsigned int ID, unsigned int owner,bool active);
		//~Snipershot();
		Vector sniperview;
		void update();
		void fire();
		void move();
		Vector route;		
		void annihilation();
		bool ultimateartifact;
	private:
		static const int default_damage=10;
		static const int default_range_in_sec=100;
};