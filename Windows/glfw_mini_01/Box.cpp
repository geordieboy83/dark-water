using namespace std;
#pragma once

#include "Box.h"

extern GLuint textures[];
extern Entity* Entities[];

Box::Box(unsigned int id, bool active) :  Entity(id, active), affected(false)
{
	HP=default_hps;
	alive=false;
}

Box::~Box() {}

void Box::update()
{
	if(!alive) return;
	
	if(!affected&&triggered_by!=-1){
		die();
		affected=true;
		affect(triggered_by);
		triggered_by=-1;		
		return;
	}
	if(current.getz()<0) current.set_coords(current.getx(),current.gety(),current.getz()+MOVEMENTFACTOR);
	mark(currentquad);
}

void Box::affect(GLuint who)
{
	extern SoundSystem* Audio;

	switch(effect){
		//HEALTH
		case 1:
			Entities[who]->wound(-25);
			if(Audio) Audio->ambient("GIFT_YES");
			break;
		
		//POISON
		case 2:
			if(Audio) Audio->ambient("GIFT_NO");
			Entities[who]->wound(25);
			break;

		//TRANSFORMATION
		case 3:
			if(Audio) Audio->ambient("GIFT_TPT");
			((Player*)Entities[who])->transform();
			break;

		//BLUE SCREEN OF DEATH
		case 4:
			BSOD();
			//bsod_laptop();
			break;

		//ULTIMATE ARTIFACT
		case 5: 
			if(Audio) Audio->ambient("GIFT_ULTIMATE");
			((Player*)Entities[who])->ultimateartifact=true;
			((Player*)Entities[who])->updatedependencies();
			break;

		//DOUBLE DAMAGE
		case 6:
			if(Audio) Audio->ambient("GIFT_ULTIMATE");
			((Player*)Entities[who])->doubledamage=true;
			((Player*)Entities[who])->ddstart=glfwGetTime();
			((Player*)Entities[who])->updatedependencies();
			break;

		//RAPID FIRE
		case 7: 
			if(Audio) Audio->ambient("GIFT_ULTIMATE");
			((Player*)Entities[who])->rapidfire=true;
			((Player*)Entities[who])->rfstart=glfwGetTime();
			((Player*)Entities[who])->updatedependencies();
			break;

		//PLAGUE
		case 8: 
			if(Audio) Audio->ambient("GIFT_NO");
			Entities[who]->wound(50);
			break;

		default: break;
	}
	
}

void Box::reset(Vertex v)
{
	alive=true;
	effect=rand()%8+1;
	affected=false;
	current=v;
	quad(current,geometry->get_origin(),currentquad);
	mark(currentquad);
	chaindesign(0,stuff);
	cout << "Contains effect " << effect << endl;
	
}

void Box::display()
{	
	if(!alive) return;
	
	glPushMatrix();		
	glPolygonMode(GL_FRONT,GL_FILL);
	glTranslatef(current.getx(), current.gety(),current.getz());		
	glCallList(list);
	glPopMatrix();
	
}
