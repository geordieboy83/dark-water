using namespace std;
#pragma once

#include "SW_Island.h"

extern Entity* Entities[];
extern int islandhealth[];

Island::Island(unsigned int id, bool active) : Entity(id, active) {}

void Island::update(){
	int j=ID;
	j-=SW_FIRST_ISLE;
	islandhealth[j]=HP;
	
	if(!alive) return;
	mark(currentquad);
	if(!((SeaWarsBoulder*)Entities[SW_FIRST_ISLE_PROJECTILE+SW_FIRST_ISLE-ID])->alive) fire();
}

void Island::fire()
{
	
	((SeaWarsBoulder*)Entities[SW_FIRST_ISLE_PROJECTILE+SW_FIRST_ISLE-ID])->current.set_coords(
		current.getx(),
		current.gety(),
		geometry_bounds[5]+abs(((SeaWarsBoulder*)Entities[SW_FIRST_ISLE_PROJECTILE+SW_FIRST_ISLE-ID])->geometry_bounds[4]));

	
	float distances[SW_PLAYERS];
	float maxborder=max(
		max(abs(geometry_bounds[0]-geometry->get_origin().getx()), abs(geometry_bounds[1]-geometry->get_origin().getx())),
		max(abs(geometry_bounds[2]-geometry->get_origin().gety()), abs(geometry_bounds[3]-geometry->get_origin().gety())));


	float range=((SeaWarsBoulder*)Entities[SW_FIRST_ISLE_PROJECTILE+SW_FIRST_ISLE-ID])->rangeinsec*30*SW_ISLEPROJECTILESPEED+maxborder;
		
	for(int i=SW_FIRST_PLAYER;i<=SW_LAST_PLAYER;i++){
		distances[i]=INF;
		if(Entities[i]!=NULL&&Entities[i]->alive&&((MovingEntity*)Entities[i])->present){
		Vector v=subtract(current, Entities[i]->current);
		v.magn();
		distances[i]=v.get_magn()-range;}
	};	
	int closest=-1;
	float min=1;
	for(int i=0;i<SW_PLAYERS; i++) if (distances[i]<min) { min=distances[i]; closest=i; }
	if(closest>-1){
		((SeaWarsBoulder*)Entities[SW_FIRST_ISLE_PROJECTILE+SW_FIRST_ISLE-ID])->TravelsTill.set_coords(
			Entities[closest]->current.getx(),
			Entities[closest]->current.gety(),
			-Entities[SW_FIRST_ISLE_PROJECTILE+SW_FIRST_ISLE-ID]->geometry_bounds[5]);
	}
	else{
		Vector v=subtract(current,Vector(0,0,current.getz()));
		//cout << v.getx() << " " << v.gety() << " " << v.getz() << endl;
		v.unit();
		//cout << v.getx() << " " << v.gety() << " " << v.getz() << endl;
		v.scale(range);
		//cout << v.getx() << " " << v.gety() << " " << v.getz() << endl;
		float angle=sw_deg2rad((float)(rand()%36000)/100.0);
		//cout << angle << endl;

		//Vector temp(
		//	v.getx()*cos(angle)-v.gety()*sin(angle),
		//	v.getx()*sin(angle)+v.gety()*cos(angle),
		//	-Entities[FIRST_ISLE_PROJECTILE+FIRST_ISLE-ID]->geometry_bounds[5]
		//	);
		//cout << temp.getx() << " " << temp.gety() << " " <<temp.getz() << endl;// _getch();

		((SeaWarsBoulder*)Entities[SW_FIRST_ISLE_PROJECTILE+SW_FIRST_ISLE-ID])->TravelsTill.set_coords(
			v.getx()*cos(angle)-v.gety()*sin(angle),
			v.getx()*sin(angle)+v.gety()*cos(angle),
			-Entities[SW_FIRST_ISLE_PROJECTILE+SW_FIRST_ISLE-ID]->geometry_bounds[5]);
	}
	((SeaWarsBoulder*)Entities[SW_FIRST_ISLE_PROJECTILE+SW_FIRST_ISLE-ID])->fire();	
}

