using namespace std;
#pragma once
#include "Polygon.h"
#include <GL/glfw.h>

typedef struct{
	string name, map_Ka, map_Kd, map_Ks, map_Tr, map_bump;
	float Ke[4], Ka[4], Kd[4], Ks[4], Ns[1], Tr;
	int id;
} material;

#define INF 500000

class GLPolygon : public Polygon
{
	public:
		GLPolygon();
		~GLPolygon();

		string TYPE;

		//void display();
		void /*shifting_*/display(float shift);

		void bounding();

		void get_boundaries(float* minmax);

		Vertex get_origin();

		void origin();

		void movetocentre();

		bool load(string name);

		bool objload(string name, bool centred);

		int get_creator();
		void set_creator(int crtr);

		virtual bool unload();
		
		GLuint get_list();

		bool objparse(fstream& file);
		void objload(fstream& file);

		void objdisplay(float shift);

		bool chainload(int how_many, const string* filenames, bool centred);
		void chaindesign(float shift);
		void chaindesign(float shift, float *colours);
		void chaindesign(float shift, material *matter);
		void chaindesign(float shift, GLuint *textures);
		void chaindisplay();
		void chainprint();
		void chainscale(float scalar);
		void chaintranslate(Vector v);
		void chaincentre();
		

		GLPolygon* next;

	protected:
		GLuint list;
		int creator;
		
		//material* matter;

		int num_textures;
		int num_normals;
		Vertex *geometry_textures;

		
		
		float minx, miny, minz, maxx, maxy, maxz;
		Vertex centre;
};
