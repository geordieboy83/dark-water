#pragma once
#include "Projectile.h"

extern float now,previous;


void Projectile::update()
{
	if(used)
        {
			float duration=now-previous;

            // Run the physics
            body->integrate(duration);
            calculateInternals();

            // Check if the particle is now invalid
            if (body->getPosition().y < 0.0f ||
                glfwGetTime()-startTime>20)
                
            {
                // We simply set the shot type to be unused, so the
                // memory it occupies can be reused by another shot.				
                used=false;
            }
        }
}


void Projectile::display(GLuint material_index)
{
	if(!used) return;

        // Get the OpenGL transformation
        GLfloat mat[16];
        body->getGLTransform(mat);
		glPushMatrix();
        glMultMatrixf(mat);
		GLUquadricObj* bullet=gluNewQuadric();
		gluQuadricOrientation(bullet,GLU_OUTSIDE);
		gluQuadricDrawStyle(bullet,GLU_FILL);
		gluQuadricNormals(bullet,GLU_TRUE);
		materialise(material_index);
		gluSphere(bullet,radius,30,30);
		gluDeleteQuadric(bullet);
        glPopMatrix();
}

void Projectile::fire(CollisionBox& shooter)
{
	
	  body->setMass(5.0f);

	  Matrix4 transform=shooter.body->getTransform();

	  body->setVelocity(transform.transformDirection(Vector3(100.0f, 0.0f, 0.0f)));
	  body->setAcceleration(Vector3::GRAVITY);
      body->setDamping(0.99f, 0.8f);
      radius = 5.0f;
       
      body->setCanSleep(false);
      body->setAwake();

      cyclone::Matrix3 tensor;
      cyclone::real coeff = 0.4f*body->getMass()*radius*radius;
      tensor.setInertiaTensorCoeffs(coeff,coeff,coeff);
      body->setInertiaTensor(tensor);

	  Vector3 position=shooter.body->getPosition();
	  position=position+transform.transformDirection(Vector3(shooter.halfSize.x+radius, shooter.halfSize.y, 0.0f));
		
	  body->setPosition(position);
	  startTime=glfwGetTime();

       // Clear the force accumulators
       body->calculateDerivedData();
       calculateInternals();

	   used=true;
 }