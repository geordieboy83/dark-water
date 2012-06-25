using namespace std;
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include "Vector.h"
#include <math.h>

#define PI 3.1415926535897932384626433832795

// Class to represent a polygon.
/*
The polygon is characterised of the following attributes:
- A number of vertices (num_vertices)
- A number of faces (num_faces)
- The upper limit of numbers needed to represent the face with the most vertices (max_cells_per_face).
  This signifies that, in the case of a polygon with 100 vertices and 1024 faces of which one of them has 50 vertices
  and the rest of them have 3 vertices each, then 
  = num_vertices would be 100,
  = num_faces would be 1024 and
  = max_cells_per_face would be 51 (maximum vertices per face + the face header that tells us how many vertices a given face has).

The actual data is accessed via three pointers:
- geometry_vertices points to an array of <num_vertices> Vertex class objects.
- geometry_faces points to a one-dimensional array of <num_faces*max_cells_per_face> integers.
  This gives us the advantage of speed brought about by arrays, but if it be some irregular shape such as the one described above,
  we will end up with an array that is largely sparse.
- geometry_normals points to an array of <num_faces> Vector class objects used to store the unit normal vectors.

There are three flags (bools) describing the polygon status, namely
- loaded: true if there is polygon data in memory,
- outdated: true if unit normals in memory (if any at all) do not correspond to the rest of the polygon data (due to a freshly
  loaded polygon or a rotation)
- silent: if true, messages to the user are suppressed (such as requests to overwrite files).

There is also an array of 3 Vector class objects used to store the "rotation vectors", namely the rows of the 3x3 rotation
matrix used for rotations. For the purposes of this project, axis rotation is considered a sub-case of free rotation.
*/
class Polygon {
	public:
		Polygon();
		~Polygon();

		// Load a geometry file.
		virtual bool load(string name);

		// Reset a polygon.
		bool unload();

		// Save geometry.
		bool save_geometry(string name);

		// Save unit normals.
		bool save_normals(string name);

		// Print geometry to the screen.
		bool print();

		// Translate a polygon by a given vector.
		bool translate(Vector v);

		// Uniform scaling.
		bool scale(float scalar);

		// Rotate given an axis and an angle.
		bool rotate(Vector v, float angle);

		// Unit normal calculation.
		bool normals();

		// Get commands.
		int get_vertices();
		int get_faces();
		int get_max();

		// Set commands.
		void set_vertices(int verts);
		void set_faces(int faces);
		void set_max(int max);

		// Status query.
		bool is_loaded();
		bool is_outdated();

		// Computation of vectors used for rotation.
		void compute_rotation_vectors(Vector u, float theta);

		// Get command.
		Vector get_rotation_vector(char axis);

		// Rotate a given vertex.
		Vertex rotate(Vertex v);

		// Impose silence on the polygon to suppress output to the user.
		void silence(bool on);

	protected:

		// Geometry file parsing.
		bool parse(fstream& file);

		// Geometry file reading.
		void load(fstream& file);

		// Saving geometry vertices.
		void save_vertices(fstream& file);

		// Saving of geometry faces.
		void save_faces(fstream& file);

		// Status
		bool loaded;
		bool outdated;
		bool silent;

		// Size
		int num_vertices;
		int num_faces;
		int max_cells_per_face;

		// Data
		Vertex *geometry_vertices;
		int *geometry_faces;
		Vector *geometry_normals;

		// Rotation vectors
		Vector rotation_vectors[3];	
};

