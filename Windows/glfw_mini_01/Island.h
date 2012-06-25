using namespace std;
#pragma once

#include "Boulder.h"

class Island : public Entity
{
	public:
		Island(unsigned int id, bool active);
		void update();
		void fire();
};
