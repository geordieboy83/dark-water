#pragma once
#include "Isle.h"

extern GLPolygon models[];
extern Random r;
extern bool grids1,grids2;

Isle::Isle() : self(models[ISLEMDL].get_list()), active(false), dead(false), HP(maxHP)
{
	body=new RigidBody;
	coastline.body=body;

	body->setInverseMass(0);
	body->setVelocity(0,0,0);
	body->setAcceleration(0,0,0);

	float bounds[6];
	models[ISLEMDL].get_boundaries(bounds);

	radius=0.5*max(abs(bounds[1]-bounds[0]),max(abs(bounds[3]-bounds[2]),abs(bounds[5]-bounds[4])));
	coastline.radius=radius+200;
	underwater=-bounds[3];

	LastFiredAt=-1;

}

void Isle::reset()
{
	Vector3 v=r.randomXZVector(WORLD_TO);
	body->setPosition(v);
	body->calculateDerivedData();
	calculateInternals();
	coastline.calculateInternals();
	currentheight=1.5*underwater;
	active=true;
	dead=false;
	HP=maxHP;

	printf("Volcano at (%.3f, %.3f)\n",v.x,v.z);
}

void Isle::update()
{
	for(int i=0; i<BOULDERS; i++) if(boulders[i].used) boulders[i].update();
	
	if(!active) return;

	if(dead){
		currentheight-=MOVEMENTFACTOR; 
		if(currentheight<underwater) active=false;
		return;
	}
	if (currentheight < 0) currentheight+=MOVEMENTFACTOR;
	else fire();
}

void Isle::display()
{
	Vector3 position=body->getPosition();
	float x=position.x+r.randomBinomial(10);
	float z=position.z+r.randomBinomial(10);
	
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	if(currentheight<0) glTranslatef(x,currentheight,z);
	else glTranslatef(position.x,0,position.z);
	
	
	texturise(ISLTX);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glCallList(self);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	if(grids1) bspheredisplay((CollisionSphere)*this);
	if(grids2) bspheredisplay(coastline);
	
	for(int i=0; i<BOULDERS; i++) if(boulders[i].used) boulders[i].display();

}

void Isle::fire()
{

	float now=glfwGetTime();
	if(now-LastFiredAt<1.5) return;
	int i;
	for (i=0; i<BOULDERS; i++)
    {
		if (!boulders[i].used) break;
    }

    // If we didn't find a round, then exit - we can't fire.
    if (i >= BOULDERS) return;

	boulders[i].fire(*body);
	LastFiredAt=now;
}

void Isle::wound(int damage)
{
	HP-=damage;
	if(HP <= 0) dead=true;
}

