#pragma once

// Class to represent a vertex.

class Vertex
{
	public:
		// Default constructor creates the origin.
		Vertex();

		Vertex(float xcoord, float ycoord, float zcoord);

		virtual ~Vertex();

		// Change vertex coordinates.
		virtual void set_coords(float newx, float newy, float newz);

		// Get methods.
		virtual float getx() const;
		virtual float gety() const;
		virtual float getz() const;

		// Vertex negate functionality;
		virtual void negate();

		// Vertex scale functionality;
		virtual void scale(float a);

		// Vertex translate functionality.
		void translate(Vertex p);
	protected:
		// Vertex coordinates.
		float x;
		float y;
		float z;
};