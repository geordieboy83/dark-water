using namespace std;
#pragma once

#include "SW_Entity.h"

class MovingEntity : public Entity
{
	public:
		MovingEntity(unsigned int id, bool active);
		~MovingEntity();
		virtual bool can_move();
		Vertex attempted;
		int attemptedquad[4];
		Vector orientation;
		//float rotationangle;
		unsigned int collisions[SW_IDS];
		virtual void collides();
		void orient();
		virtual void move();
		virtual void load(string s, string type, bool centered);		
};