#pragma once
#include "Isle.h"

extern float now,previous;
extern GLPolygon models[];
extern Random r;

Boulder::Boulder() :Projectile()
{
	self=models[ISLPRJMDL].get_list();
	body->setMass(50.0f);

	body->setAcceleration(Vector3::HIGH_GRAVITY);
    body->setDamping(0.99f, 0.8f);

	body->setCanSleep(false);
    body->setAwake();

    cyclone::Matrix3 tensor;
    cyclone::real coeff = 0.4f*body->getMass()*radius*radius;
    tensor.setInertiaTensorCoeffs(coeff,coeff,coeff);
    body->setInertiaTensor(tensor);

	float bounds[6];
	models[ISLPRJMDL].get_boundaries(bounds);
	radius=0.5*max(abs(bounds[1]-bounds[0]),max(abs(bounds[3]-bounds[2]),abs(bounds[5]-bounds[4])));


	
}

void Boulder::fire(RigidBody& shooter)
{
	

	  float angle=r.randomReal(0,2*PI);

	  Vector3 velocity(50,50,0);
	  body->setVelocity(
		  velocity.x*cos(angle),
		  velocity.y,
		  -velocity.x*sin(angle));

	  
      float bounds[6]; 	
	  models[ISLEMDL].get_boundaries(bounds);
      
	  Vector3 position=shooter.getPosition();
	  position=position+Vector3(0,bounds[3],0);

	  body->setPosition(position);
	 
      startTime=glfwGetTime();

       // Clear the force accumulators
       body->calculateDerivedData();
       calculateInternals();

	   used=true;
	   startTime=glfwGetTime();
  

}

void Boulder::display()
{
	if(!used) return;

        // Get the OpenGL transformation
        GLfloat mat[16];
        body->getGLTransform(mat);
		glPushMatrix();

		glEnable(GL_TEXTURE_2D);
        glMultMatrixf(mat);
		texturise(ISLTX);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glCallList(self);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
}