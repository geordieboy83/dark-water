#pragma once
#include <Courseworx\Globals.h>
using namespace cyclone;

//The Projectile class
class Projectile : public cyclone::CollisionSphere
{
public:

	//When was it fired
    unsigned startTime;

	//Is it used?
	bool used;

    Projectile(): used(false) { body = new cyclone::RigidBody; }

    ~Projectile() { delete body; }

	//Display the projectile using input draw materials
    virtual void display(GLuint material_index);

	//Update state    
	void update();

	//Fire (input: who fired it)	
	virtual void fire(CollisionBox& shooter);   
};