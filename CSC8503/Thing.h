#pragma once
#include <GL\glfw.h>
#include <FTGL\ftgl.h>
#include <cyclone\cyclone.h>
#include <Courseworx\Globals.h>

using namespace cyclone;

//Class that implements something that floats on a liquid
class FloatingThing
{
	public:
		FloatingThing();
		virtual ~FloatingThing();

		RigidBody body;
		Buoyancy* buoyancy;
		ForceRegistry* registry;

		//Reset the body data
		void reset_body(Vector3 Position, Quaternion Orientation,
			Vector3 Velocity, Vector3 Rotation, real Mass,
			Matrix3 InertiaTensor, real LinearDamping,
			real AngularDamping, Vector3 Acceleration=Vector3::GRAVITY);

		//Reset the buoyancy
		void reset_buoyancy(const Vector3 &cOfB,
            real maxDepth, real volume, real waterHeight,
            real liquidDensity = 1000.0f);

		//Reset the force registry
		virtual void reset_registry();

};

//A thing that floats on a liquid and is also subject to aerodynamics
class FloatingAeroThing : public FloatingThing
{
	public:
		FloatingAeroThing();
		~FloatingAeroThing();
		
		Aero* aerodynamix;

		//Reset the aerodynamic force
		void reset_aero(const Matrix3 &tensor, const Vector3 &position,
             const Vector3 *windspeed);

		//Reset the force registry
		void reset_registry();		

};