using namespace std;
#pragma once

#include "Snipershot.h"

extern Entity* Entities[];
extern GLPolygon models[];
extern float MAXZ, MINZ;
extern SoundSystem* Audio;

Snipershot::Snipershot(unsigned int ID, unsigned int owner, bool active) : Projectile(ID, owner,active), ultimateartifact(false)
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
	float quadstep=(float)(WORLD_TO-WORLD_FROM)/(float)QUADS;

	//Active and firing
	if(fired){		
		while(!off_edge && fired)
		{
			
			Vector v=route;
			v.scale(quadstep*MOVEMENTFACTOR);
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
		TravelsTill.scale(WORLD_TO-WORLD_FROM*sqrt(2.0));
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
		attempted.getx()<WORLD_FROM||
		attempted.getx()>WORLD_TO||
		attempted.gety()<WORLD_FROM||
		attempted.gety()>WORLD_TO){
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
		bool flag=(collisions[EDGE]>0);
		int i;
		if (flag)
			for(i=0; i<=IDS-2; i++)
				if(collisions[i]>0&&i!=ID&&i!=whose){
					flag=false;
					break;
				};
		if(flag) {off_edge=true; if(ultimateartifact) ultimateartifact=false;}
		else{

			if(ultimateartifact) {annihilation(); return;}

			for(i=FIRST_PLAYER; i<=LAST_PLAYER; i++){
				
				if(i!=whose&&
					collisions[i]>0&&
					attempted.getz()>=Entities[i]->geometry_bounds[4]&&
					attempted.getz()<=Entities[i]->geometry_bounds[5]){
						if(Audio) Audio->ambient("IMPACT");
						Entities[i]->wound(damage);
				}
			}
			for(i=FIRST_ISLE; i<=LAST_ISLE; i++)
				if(collisions[i]>0&&
					attempted.getz()>=Entities[i]->geometry_bounds[4]&&
					attempted.getz()<=Entities[i]->geometry_bounds[5]){
						if(Audio) Audio->ambient("IMPACT");
						Entities[i]->wound(damage);
				}
			for(i=FIRST_BOX; i<=LAST_BOX; i++) if(collisions[i]>0&&
				attempted.getz()>=Entities[i]->geometry_bounds[4]&&
					attempted.getz()<=Entities[i]->geometry_bounds[5]){ 
						if(Audio) Audio->ambient("IMPACT");
						Entities[i]->wound(damage);
				}
			fired=false;		
		}
	}
	

}

void Snipershot::annihilation()
{
	if(Audio) Audio->ambient("ANNIHILATE");
	
	float angle=70;
	
	models[SWATTER].get_boundaries(geometry_bounds);
	quad(attempted,models[SWATTER].get_origin(),attemptedquad);
	float handlebounds[6];
	models[SWATTER].next->get_boundaries(handlebounds);
		
	collides();

	while (angle >0){
		glViewport(0,0,WINDOW_X,WINDOW_Y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	
		update_landscape();
		Vector to=subtract(sniperview,current);
		to.scale(100);
		to=add(to,current);	

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(WORLD_FROM,WORLD_TO,WORLD_FROM,WORLD_TO,5*WORLD_FROM,5*WORLD_TO);
		gluLookAt(0,0,7,0,0,0,1,1,0);
	
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		scenery();
		display_world();
		
		glClear(GL_DEPTH_BUFFER_BIT);

		
		glPushMatrix();
		glTranslatef(current.getx(),current.gety(),current.getz());
		glRotatef(angle,0,1,0);
		glCallList(models[SWATTER].get_list());
		glPopMatrix();
	
		glfwSwapBuffers();

		angle-=0.5;
	}
	
	for(int i=0;i<IDS-2;i++)if(collisions[i]>0){
		if(Audio) Audio->ambient("IMPACT");
		Entities[i]->wound(200);
	}
	
	geometry->get_boundaries(geometry_bounds);
	
	fired=false;
	when=glfwGetTime();
	ultimateartifact=false;
}