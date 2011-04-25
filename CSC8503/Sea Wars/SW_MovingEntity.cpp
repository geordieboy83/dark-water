#include "SW_MovingEntity.h"

#pragma once

extern unsigned int world_bounds[SW_QUADS][SW_QUADS];


MovingEntity::MovingEntity(unsigned int id, bool active): Entity(id, active), attempted(), /*rotationangle(0),*/ orientation() {}

MovingEntity::~MovingEntity() {
}

void MovingEntity::collides()
{
	int i,j;
	for(i=0; i<SW_IDS; i++) collisions[i]=0;
	for(i=attemptedquad[0]; i<attemptedquad[1]; i++)
		for(j=attemptedquad[2];j<attemptedquad[3];j++)
			collisions[world_bounds[i][j]]++;
	return;
}

bool MovingEntity::can_move()
{
	int i;
	collides();
	if(collisions[SW_EDGE]>0) return false;
	for(i=SW_FIRST_PLAYER; i<=SW_LAST_PLAYER; i++) if(i!=ID&&collisions[i]>0) return false;
	for(i=SW_FIRST_ISLE; i<=SW_LAST_ISLE; i++) if(collisions[i]>0) return false;
	return true;
}

void MovingEntity::orient()
{
	orientation.set_coords(
			geometry_bounds[1]*cos(sw_deg2rad(rotationangle))+current.getx(),
			geometry_bounds[1]*sin(sw_deg2rad(rotationangle))+current.gety(),			
			0);
}

void MovingEntity::move(){
	quad(attempted,geometry->get_origin(),attemptedquad);
	if(can_move()){
		unmark(currentquad);
		current=attempted;
		//mark(attemptedquad);
		quad(current,geometry->get_origin(),currentquad);
		mark(currentquad);
	}
	orient();
}

void MovingEntity::load(string s, string type, bool centered)
{
	Entity::load(s,type,centered);
	orient();
}
