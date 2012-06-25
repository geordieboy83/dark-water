#include "Vertex.h"

// Default constructor creates the origin.
Vertex::Vertex(): x(0), y(0), z(0) {}

Vertex::Vertex(float xcoord, float ycoord, float zcoord): x(xcoord), y(ycoord), z(zcoord) {}

Vertex::~Vertex() {}

// Get methods.
float Vertex::getx() const { return x; }
float Vertex::gety() const { return y; }
float Vertex::getz() const { return z; }

// Change vertex coordinates.
void Vertex::set_coords(float newx, float newy, float newz) {x=newx; y=newy; z=newz; return; }

// Vertex negation functionality.
void Vertex::negate()  { x=-x; y=-y; z=-z; return; }

// Vertex scaling functionality.
void Vertex::scale(float a) {set_coords(a*x, a*y, a*z); return;}

// Vertex translation functionality.
void Vertex::translate(Vertex p) {set_coords(x=x+p.getx(), y=y+p.gety(), z=z+p.getz()); return;}
