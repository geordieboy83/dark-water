#pragma once
#include "Thing.h"
using namespace cyclone;

//The giftbox class
class Present
{
	public:
		Present();

		//Is it used?
		bool used;

		//The actual body
		FloatingThing box;

		//The effect of the box
		int effect;

		//Update state
		void update();

		//Reset the box
		void reset();

		//Display the box
		void display();

		//The display list
		GLuint self;

		//The bounding sphere
		CollisionSphere csphere;

		//Adapt the body to a change of liquid
		void reliquidate(string s);
};