using namespace std;
#pragma once

#include "GLPolygon.h"
#include "Globals.h"

class Entity
{
	public:
		Entity(unsigned int id, bool active);
		virtual ~Entity();
		unsigned int ID;
		bool alive;
		virtual void display();
		virtual void die();
		virtual void set_HP(int hp);
		
		bool present;
		
		float TimeOfDeath;
		int HP;
		GLuint list;
		GLPolygon* geometry;
		float geometry_bounds[6];
		void mark(int* quad_idxs);
		void unmark(int* quad_idxs);
		Vertex current;
		void quad(Vertex position, Vertex origin, int* quad_idxs);
		int currentquad[4];
		virtual void load(string s, string type, bool centered);
		virtual void update();
		virtual void wound(int damage);
		virtual void design(float shift);
		material* stuff;
		//unsigned int colour;

		void chaindesign(float shift);
		void chaindesign(float shift, float *colours);
		void chaindesign(float shift, material *matter);
		void chaindesign(float shift, GLuint *textures);
		bool chainload(int how_many, const string* filenames, bool centred);
		float rotationangle;
		virtual int max_HP();
		int triggered_by;
	private:
		static const int default_hps = 100;
		
};