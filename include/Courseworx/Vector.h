#pragma once
#include "Vertex.h"
#include <math.h>

// Class to represent a position vector. Extends Vertex class.
class Vector: public Vertex
	{
		public:
			// Null vector.
			Vector();

			Vector(float xcoord, float ycoord, float zcoord);
			
			// Vector from vertex.
			Vector(Vertex p);

			virtual ~Vector();

			// Vector remake functionality.
			virtual void set_coords(float newx, float newy, float newz);

			// Get method.
			virtual float get_magn() const;

			// Calculate magnitude;
			virtual void magn();

			// Vector scaling functionality.
			virtual void scale(float a);

			// Convert into unit vector.
			virtual void unit();
		protected:
			float magnitude;
	};


// Vector addition functionality.
Vector add (Vector p, Vector q);

// Vector subtraction functionality.
Vector subtract (Vector p, Vector q);

// Vector dot product functionality.
float dot(Vector p, Vector q);

// Angle between vectors calculation functionality.
float angle(Vector p, Vector q);

// Vector cross product functionality.
Vector cross(Vector p, Vector q);

// Unit normal calculation given two vectors.
Vector normal(Vector p, Vector q);

// Unit normal calculation given three position vectors.
Vector normal(Vector p, Vector q, Vector r);
