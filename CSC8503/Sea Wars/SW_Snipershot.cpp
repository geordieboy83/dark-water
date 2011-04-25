using namespace std;
#pragma once

#include "SW_Snipershot.h"

extern Entity* Entities[];
extern GLPolygon models[];
extern float MAXZ, MINZ;
extern int SW_WINDOW_X, SW_WINDOW_Y;

Snipershot::Snipershot(unsigned int ID, unsigned int owner, bool active) : SeaWarsProjectile(ID, owner,active), ultimateartifact(false)
{
	rangeinsec=default_range_in_sec;
	timetolive=30;
	damage=default_damage;
	/*geometry=new GLPolygon();
	geometry->load("..\\Resources\\cube.txt");
	geometry->bounding();
	geometry->origin();
	geometry->get_boundaries(geometry_bounds);*/
}

/*Snipershot::~Snipershot()
{
	delete geometry;
}*/

void Snipershot::update()
{
	//Inactive projectile
	if(!alive) return;

	float radang;
	float elapsedtime=glfwGetTime()-when;
	if(elapsedtime>timetolive){ alive=false; return; }
	float quadstep=(float)(SW_WORLD_TO-SW_WORLD_FROM)/(float)SW_QUADS;

	//Active and firing
	if(fired){		
		while(!off_edge && fired)
		{
			
			Vector v=route;
			v.scale(quadstep*SW_MOVEMENTFACTOR);
			attempted=add(current,v);
			move();
		}
		return;
	}

}

void Snipershot::fire()
{
	if(!alive){
		alive=true;
		fired=true;
		off_edge=false;
		orient();
		quad(current,geometry->get_origin(),currentquad);
		when=glfwGetTime();
		FiredAt=current;		
				
		route=subtract(sniperview,current);
		route.unit();
		TravelsTill=route;
		TravelsTill.scale(SW_WORLD_TO-SW_WORLD_FROM*sqrt(2.0));
		TravelsTill.magn();
		TravelsTill=add(TravelsTill,current);
		update();
	}
}

void Snipershot::move()
{
	quad(attempted,geometry->get_origin(),attemptedquad);
	if(attempted.getz()>MAXZ||
		attempted.getz()<MINZ||
		attempted.getx()<SW_WORLD_FROM||
		attempted.getx()>SW_WORLD_TO||
		attempted.gety()<SW_WORLD_FROM||
		attempted.gety()>SW_WORLD_TO){
			off_edge=true;
			if(ultimateartifact) ultimateartifact=false;
			return;
	}
	if(can_move()){
		current=attempted;
		quad(current,geometry->get_origin(),currentquad);
		orient();
	}
	else{
		bool flag=(collisions[SW_EDGE]>0);
		int i;
		if (flag)
			for(i=0; i<=SW_IDS-2; i++)
				if(collisions[i]>0&&i!=ID&&i!=whose){
					flag=false;
					break;
				};
		if(flag) {off_edge=true; if(ultimateartifact) ultimateartifact=false;}
		else{

			if(ultimateartifact) {annihilation(); return;}

			for(i=SW_FIRST_PLAYER; i<=SW_LAST_PLAYER; i++){
				
				if(i!=whose&&
					collisions[i]>0&&
					attempted.getz()>=Entities[i]->geometry_bounds[4]&&
					attempted.getz()<=Entities[i]->geometry_bounds[5]) Entities[i]->wound(damage);
			}
			for(i=SW_FIRST_ISLE; i<=SW_LAST_ISLE; i++)
				if(collisions[i]>0&&
					attempted.getz()>=Entities[i]->geometry_bounds[4]&&
					attempted.getz()<=Entities[i]->geometry_bounds[5]) Entities[i]->wound(damage);
			for(i=SW_FIRST_BOX; i<=SW_LAST_BOX; i++) if(collisions[i]>0&&
				attempted.getz()>=Entities[i]->geometry_bounds[4]&&
					attempted.getz()<=Entities[i]->geometry_bounds[5]) Entities[i]->wound(damage);
			fired=false;		
		}
	}
	

}

void Snipershot::annihilation()
{
	float angle=70;
	
	models[SW_SWATTER].get_boundaries(geometry_bounds);
	quad(attempted,models[SW_SWATTER].get_origin(),attemptedquad);
	float handlebounds[6];
	models[SW_SWATTER].next->get_boundaries(handlebounds);
		
	collides();

	while (angle >0){
	glViewport(0,0,SW_WINDOW_X,SW_WINDOW_Y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	
	sw_update_landscape();
	Vector to=subtract(sniperview,current);
	to.scale(100);
	to=add(to,current);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45,16/9,0.1,3*WORLD_TO);	
	//gluLookAt(orientation.getx(), orientation.gety(), geometry_bounds[5],to.getx(),to.gety(),to.getz()+geometry_bounds[5],0,0,1);
	glOrtho(SW_WORLD_FROM,SW_WORLD_TO,SW_WORLD_FROM,SW_WORLD_TO,5*SW_WORLD_FROM,5*SW_WORLD_TO);
	gluLookAt(0,0,7,0,0,0,1,1,0);
	
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	sw_scenery();
	display_world();
		
	glClear(GL_DEPTH_BUFFER_BIT);

	//glBegin(GL_QUADS);
	
	//glEnd();

	
	
	
	glPushMatrix();
	glTranslatef(current.getx(),current.gety(),current.getz());
	//glTranslatef(handlebounds[1],0,0);
	glRotatef(angle,0,1,0);
	//glScalef(-1,-1,-1);
	//glTranslatef(-handlebounds[1],0,0);
	glCallList(models[SW_SWATTER].get_list());
	glPopMatrix();
	
	glfwSwapBuffers();

	angle-=0.5;
	}
	
	for(int i=0;i<SW_IDS-2;i++)if(collisions[i]>0) Entities[i]->wound(200);
	
	geometry->get_boundaries(geometry_bounds);
	
	fired=false;
	when=glfwGetTime();
	ultimateartifact=false;
}