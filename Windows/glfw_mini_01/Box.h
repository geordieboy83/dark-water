using namespace std;
#pragma once

#include "Player.h"

class Box : public Entity
{
	public:
		GLuint bsod;
		Box(unsigned int id, bool active);
		~Box();
		void affect(unsigned int who);
		bool affected;
		int effect;
		void update();
		//void die();		
		void reset(Vertex v);
		void display();
		//void activate(Vertex v);
		
	private:
		//void designbsod();
		//void bsod_lab();
		//void bsod_laptop();
		static const int default_hps=1;

};