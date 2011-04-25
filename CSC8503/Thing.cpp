#include "Thing.h"
using namespace cyclone;


FloatingThing::~FloatingThing()
{
	if(registry !=NULL) delete registry;
	if(buoyancy !=NULL) delete buoyancy;
}


FloatingThing::FloatingThing(): body(), buoyancy(NULL), registry(NULL) {};

void FloatingThing::reset_body(Vector3 Position, Quaternion Orientation,
			Vector3 Velocity, Vector3 Rotation, real Mass,
			Matrix3 InertiaTensor, real LinearDamping,
			real AngularDamping, Vector3 Acceleration)
{
	body.setPosition(Position);
	body.setOrientation(Orientation);
	body.setVelocity(Velocity);
	body.setRotation(Rotation);
	body.setMass(Mass);
	body.setInertiaTensor(InertiaTensor);
	body.setDamping(LinearDamping,AngularDamping);
	body.setAcceleration(Acceleration);
	body.calculateDerivedData();
}

void FloatingThing::reset_registry()
{
	if(registry!=NULL)delete registry;
	registry=new ForceRegistry;
	registry->add(&body,buoyancy);
}

void FloatingThing::reset_buoyancy(const Vector3 &cOfB,
            real maxDepth, real volume, real waterHeight,
            real liquidDensity)
{
	if(buoyancy!=NULL) delete buoyancy;
	buoyancy=new Buoyancy(cOfB, maxDepth, volume, waterHeight, liquidDensity);
}

/******************************************************************************/

FloatingAeroThing::FloatingAeroThing() : FloatingThing(), aerodynamix(NULL) {}

FloatingAeroThing::~FloatingAeroThing() { if(aerodynamix!=NULL) delete aerodynamix; }

void FloatingAeroThing::reset_aero(const Matrix3 &tensor, const Vector3 &position,
             const Vector3 *windspeed)
{
	if(aerodynamix!=NULL) delete aerodynamix;
	aerodynamix=new Aero(tensor, position, windspeed);
}

void FloatingAeroThing::reset_registry()
{
	FloatingThing::reset_registry();
	registry->add(&body, aerodynamix);
}

