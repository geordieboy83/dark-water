using namespace std;
#pragma once

#include "SW_Box.h"

extern GLuint sw_textures[];
extern Entity* Entities[];
extern FTGLPixmapFont font;
extern int SW_WINDOW_X, SW_WINDOW_Y;

Box::Box(unsigned int id, bool active) :  Entity(id, active), affected(false) {HP=default_hps; designbsod(); alive=false;}

Box::~Box() { if(glIsList(bsod)) glDeleteLists(bsod,1); }

void Box::update()
{
	if(!alive) return;
	
	if(!affected&&triggered_by!=-1){
		die();
		affected=true;
		affect(triggered_by);
		triggered_by=-1;		
		return;
	}
	if(current.getz()<0) current.set_coords(current.getx(),current.gety(),current.getz()+SW_MOVEMENTFACTOR);
	mark(currentquad);
}

void Box::designbsod()
{
	if(!glIsList(bsod)) bsod=glGenLists(1);	
	else glDeleteLists(bsod,1);
	glNewList(bsod,GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	
		glBindTexture(GL_TEXTURE_2D, sw_textures[SW_BSODTX]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBegin(GL_QUADS);
			glTexCoord2i(0,0);
			glVertex2i(0,0);
			glTexCoord2i(1,0);
			glVertex2i(1,0);
			glTexCoord2i(1,1);
			glVertex2i(1,1);
			glTexCoord2i(0,1);
			glVertex2i(0,1);
		glDisable(GL_TEXTURE_2D);
		glEnd();
	glEndList();
}


void Box::affect(GLuint who)
{
	switch(effect){
		//HEALTH
		case 1: Entities[who]->wound(-25); break;
		
		//POISON
		case 2: Entities[who]->wound(25); break;

		//TRANSFORMATION
		case 3: ((SeaWarsPlayer*)Entities[who])->transform(); break;

		//BLUE SCREEN OF DEATH
		case 4: bsod_laptop();  break;

		//ULTIMATE ARTIFACT
		case 5: ((SeaWarsPlayer*)Entities[who])->ultimateartifact=true;
				((SeaWarsPlayer*)Entities[who])->updatedependencies();
				break;

		//DOUBLE DAMAGE
		case 6: ((SeaWarsPlayer*)Entities[who])->doubledamage=true;
				((SeaWarsPlayer*)Entities[who])->ddstart=glfwGetTime();
				((SeaWarsPlayer*)Entities[who])->updatedependencies();
				break;

		//RAPID FIRE
		case 7: ((SeaWarsPlayer*)Entities[who])->rapidfire=true;
				((SeaWarsPlayer*)Entities[who])->rfstart=glfwGetTime();
				((SeaWarsPlayer*)Entities[who])->updatedependencies();
				break;

		//PLAGUE
		case 8: Entities[who]->wound(50); break;

		default: break;
	}
	
}

void Box::reset(Vertex v)
{
	alive=true;
	effect=rand()%8+1;
	affected=false;
	current=v;
	quad(current,geometry->get_origin(),currentquad);
	mark(currentquad);
	cout << "Contains effect " << effect << endl;
	
}

void Box::display()
{
	
	if(!alive) return;
	
	glPushMatrix();		
	glPolygonMode(GL_FRONT,GL_FILL);
	glTranslatef(current.getx(), current.gety(),current.getz());		
	glCallList(list);
	glPopMatrix();
	
}

void Box::bsod_lab()
{
	font.FaceSize(72);
	glfwSetWindowSize( 640, 480 );
	glDisable(GL_LIGHTING);

	float now=glfwGetTime(), start=now;
	while(now-start<=15){
		glViewport(0,0,640,480);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,1,0,1);
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glCallList(bsod);
		if(now-start>7.5) font.Render("THIS",-1,sw_stringseed("THIS",Vertex(320,420,0)));
		if(now-start>9) font.Render("CAN'T",-1,sw_stringseed("CAN'T",Vertex(320,300,0)));
		if(now-start>10.5) font.Render("BE",-1,sw_stringseed("BE",Vertex(320,180,0)));
		if(now-start>12) font.Render("HAPPENING!",-1,sw_stringseed("HAPPENING!",Vertex(320,60,0)));
		glfwSwapBuffers();
		now=glfwGetTime();
	}
	font.FaceSize(24);	
	glfwSetWindowSize( SW_WINDOW_X, SW_WINDOW_Y );	
	glEnable(GL_LIGHTING);

	
}

void Box::bsod_laptop()
{
	//font.FaceSize(72);
	
	//glfwSetWindowSize( 640, 480 );
	
	glDisable(GL_LIGHTING);


	//glViewport(0,0,640,480);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,1,0,1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	
	glBindTexture(GL_TEXTURE_2D, sw_textures[SW_BSODTX]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBegin(GL_QUADS);
		glTexCoord2i(0,0);
		glVertex2i(0,0);
		glTexCoord2i(1,0);
		glVertex2i(1,0);
		glTexCoord2i(1,1);
		glVertex2i(1,1);
		glTexCoord2i(0,1);
		glVertex2i(0,1);
	glDisable(GL_TEXTURE_2D);		
	glfwSwapBuffers();
	glfwSleep(10);
	
	//font.FaceSize(24);	
	//glfwSetWindowSize( SW_WINDOW_X, SW_WINDOW_Y );	
	glEnable(GL_LIGHTING);
}

/*void Box::activate(Vertex v)
{
}*/