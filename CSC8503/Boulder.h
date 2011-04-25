#pragma once
#include <Courseworx\Globals.h>
#include "Projectile.h"
using namespace cyclone;

//The boulders fired by the volcano
class Boulder : public Projectile
{
	public:
		Boulder();

		//The display list
		GLuint self;

		//Display
		void display();

		//Launch (and who launches)
		void fire(RigidBody& shooter);
};