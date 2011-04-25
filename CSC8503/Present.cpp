#pragma once
#include "Present.h"

extern GLuint textures[];
extern FTGLPixmapFont font;
extern GLPolygon models[];
extern Random r;
extern float now, previous;
extern float liquid_density;
extern bool grids1;

void Present::update()
{
	if(!used)return;

	// Find the duration of the last frame in seconds
    float duration = now-previous;
    if (duration <= 0.0f) return;


  	// Start with no forces or acceleration.
    box.body.clearAccumulators();


	// Add the forces acting on the boat.
    box.registry->updateForces(duration);

    // Update the boat's physics.
    box.body.integrate(duration);
	
	csphere.calculateInternals();
}


void Present::reset()
{

	Vector3 v=r.randomXZVector(WORLD_TO);

	Vertex vtx=models[BOXMDL].get_origin();
	float bounds[6];
	models[BOXMDL].get_boundaries(bounds);
	
	box.body.setPosition(v.x,-bounds[3]-5,v.z);
	used=true;
	effect=r.randomInt(3)+1;

	float mass=50;
	box.reset_buoyancy(Vector3(0, bounds[2]*0.5,0), bounds[2], 10.0f, 2.0f,liquid_density);

	box.body.setOrientation(1,0,0,0);

    box.body.setVelocity(0,0,0);
    box.body.setRotation(0,0,0);

   	box.body.setMass(mass);
    Matrix3 it;
    it.setBlockInertiaTensor(Vector3(25,25,25), 0.5*mass);
    box.body.setInertiaTensor(it);

    box.body.setDamping(0.8f, 0.8f);

    box.body.setAcceleration(Vector3::GRAVITY);
    box.body.calculateDerivedData();

    box.body.setAwake();
    box.body.setCanSleep(false);

	box.reset_registry();

	csphere.body=&box.body;
	csphere.radius=sqrt(2.0)*0.5*max(abs(bounds[1]-bounds[0]),max(abs(bounds[3]-bounds[2]),abs(bounds[5]-bounds[4])));
	csphere.calculateInternals();


	cout << "Effect " << effect << " at (" << v.x << ", " << v.z << ")" << endl;
	
}

void Present::display()
{
	
	if(!used) return;
	
	Matrix4 transform = box.body.getTransform();
    GLfloat gl_transform[16];
    transform.fillGLArray(gl_transform);
    glPushMatrix();
    glMultMatrixf(gl_transform);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glCallList(self);
	glPopMatrix();

	if(grids1) bspheredisplay(csphere);


	glPopAttrib();
	
}

Present::Present(): used(false), self(models[BOXMDL].get_list()) {}

void Present::reliquidate(string s)
{
	float bounds[6];
	models[BOXMDL].get_boundaries(bounds);

	if(s=="WATER"){
		box.reset_buoyancy(Vector3(0, bounds[2]*0.5,0), bounds[2], 10.0f, 2.0f, 1025);
		box.body.setDamping(0.8f, 0.8f);}
	if(s=="MERCURY"){
		box.reset_buoyancy(Vector3(0, bounds[2]*0.5,0), bounds[2], 10.0f, 2.0f, 13590);
		box.body.setDamping(0.2f, 0.2f);}
	if(s=="PARAFFIN"){
		box.reset_buoyancy(Vector3(0, bounds[2]*0.5,0), bounds[2], 10.0f, 2.0f, 800);
		box.body.setDamping(0.9f, 0.9f);}

	box.reset_registry();


}