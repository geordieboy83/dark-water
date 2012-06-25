#include "Vector.h"

// A null vector. The origin.
Vector::Vector():Vertex(),magnitude(0) {}

Vector::Vector(float xcoord, float ycoord, float zcoord): Vertex(xcoord, ycoord, zcoord) { magn(); }

// Create a vector from a vertex.
Vector::Vector(Vertex p): Vertex(p.getx(),p.gety(),p.getz()) { magn(); }

Vector::~Vector() {}

// Remake vector.
void Vector::set_coords(float newx, float newy, float newz) { Vertex::set_coords(newx, newy, newz); magn(); }

// Calculate magnitude.
void Vector::magn() { magnitude=sqrt(x*x+y*y+z*z); return; }

// Scale.
void Vector::scale(float a) { Vertex::scale(a); magn(); return; }

// Convert into unit vector.
void Vector::unit() { if (magnitude==0) return; scale(1/magnitude); magnitude=1; return; }

float Vector::get_magn() const { return magnitude; }

// Add two vectors.
Vector add (Vector p, Vector q)
{
	return Vector::Vector(p.getx()+q.getx(),p.gety()+q.gety(),p.getz()+q.getz());
}

// Subtract two vectors.
Vector subtract (Vector p, Vector q)
{
	return Vector::Vector(p.getx()-q.getx(),p.gety()-q.gety(),p.getz()-q.getz());
}


// Dot product.
float dot(Vector p, Vector q)
{
	return p.getx()*q.getx()+p.gety()*q.gety()+p.getz()*q.getz();
}


// Angle between two vectors.
float angle(Vector p, Vector q)
{
	return acos(dot(p,q)/(p.get_magn()*q.get_magn()));
}


// Two vector cross product.
Vector cross(Vector p, Vector q)
{
	return Vector::Vector((p.gety()*q.getz()-p.getz()*q.gety()),(p.getz()*q.getx()-p.getx()*q.getz()),(p.getx()*q.gety()-p.gety()*q.getx()));
}

// Unit normal from two vectors.
Vector normal(Vector p, Vector q)
{
	float scalar=p.get_magn()*q.get_magn()*sin(angle(p,q));
	Vector v=cross(p,q);
	v.scale(scalar);
	return v;
}

// Unit normal from three position vectors.
Vector normal(Vector p, Vector q, Vector r)
{
	Vector v=cross(subtract(p,q), subtract(q,r));
	v.unit();
	return v;
}
