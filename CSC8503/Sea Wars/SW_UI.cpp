using namespace std;
#pragma once;

#include "SW_UI.h"

int NumberofIsles;
extern FTGLPixmapFont font;
extern Entity* Entities[];
extern state//report
	reports[];
extern bool endgame;
extern int islandhealth[];
extern GLuint textures[];
extern int SW_WINDOW_X, SW_WINDOW_Y;

void summarise(unsigned int id)
{
	int facesize=18;
	font.FaceSize(facesize);
	int x;
	if(id==SW_PLAYER1){
		//x=0;
		x=SW_WINDOW_X*0.666;
	}

	if(id==SW_PLAYER2){
		//x=WINDOW_X*0.666;
		x=0;
	}

	if(reports[id].alive&&reports[id].present){
		char s[256];
		if(reports[id].ua) { sprintf(s,"Ultimate Artifact"); font.Render(s,-1,FTPoint(x,SW_WINDOW_Y-8*facesize)); }
		if(reports[id].tf) { sprintf(s,"Transformed"); font.Render(s,-1,FTPoint(x,SW_WINDOW_Y-7*facesize)); }
		if(reports[id].rf) { sprintf(s,"Rapid Fire"); font.Render(s,-1,FTPoint(x,SW_WINDOW_Y-6*facesize)); }
		if(reports[id].dd) { sprintf(s,"Double Damage"); font.Render(s,-1,FTPoint(x,SW_WINDOW_Y-5*facesize)); }
		if(!reports[id].snipe) { sprintf(s,"Snipeshot unavailable"); font.Render(s,-1,FTPoint(x,SW_WINDOW_Y-4*facesize)); }
		if(!reports[id].shot) { sprintf(s,"Shot unavailable"); font.Render(s,-1,FTPoint(x,SW_WINDOW_Y-3*facesize)); }
		sprintf(s,"HP: %d of %d",reports[id].HP, (SeaWarsPlayer*)Entities[id]->max_HP()); font.Render(s,-1,FTPoint(x,SW_WINDOW_Y-2*facesize)); 
		sprintf(s,"Player %d",id+1); font.Render(s,-1,FTPoint(x,SW_WINDOW_Y-facesize)); 
		


	}


}

void gameover()
{
		font.FaceSize(36);
			
		Vertex origin(SW_WINDOW_X/2, SW_WINDOW_Y/2, 0);

		if(!reports[SW_PLAYER2].present){
			if(((SeaWarsPlayer*)Entities[SW_PLAYER1])->loser){
				FTPoint defeat=sw_stringseed("YOU HAVE BEEN DEFEATED",origin);
				font.Render("YOU HAVE BEEN DEFEATED",-1,defeat);
			}
			else {
				FTPoint defeat=sw_stringseed("YOU ARE VICTORIOUS",origin);
				font.Render("YOU ARE VICTORIOUS",-1,defeat);

			}
		}
		else{
		if(((SeaWarsPlayer*)Entities[SW_PLAYER1])->loser&&((SeaWarsPlayer*)Entities[SW_PLAYER2])->loser){
			FTPoint defeat=sw_stringseed("DRAW",origin);
			font.Render("DRAW",-1,defeat);
			return;
		}
		FTPoint defeat=sw_stringseed("PLAYER X WINS",origin);
		if(((SeaWarsPlayer*)Entities[SW_PLAYER1])->loser) font.Render("PLAYER 2 WINS",-1,defeat);
		else if(((SeaWarsPlayer*)Entities[SW_PLAYER2])->loser) font.Render("PLAYER 1 WINS",-1,defeat);
		}

}


void summariseplayers()
{
	summarise(SW_PLAYER1);
	if(!reports[SW_PLAYER2].present)summarise(SW_PLAYER2);
}

void summariseisles()
{
	int facesize=18;
	font.FaceSize(facesize);
	int x=0.333*SW_WINDOW_X;
	char s[256];

	for(int i=SW_FIRST_ISLE;i<=SW_LAST_ISLE;i++)
	{
		if(Entities[i]!=NULL&&Entities[i]->alive&&Entities[i]->present)
		{
			int j=i; j-=SW_FIRST_ISLE; 
			sprintf(s, "Island %d: HP %d of %d", j+1, islandhealth[j],100);
			font.Render(s,-1,FTPoint(x,SW_WINDOW_Y-facesize*(1+j)));
		}
	}


}

void loadingscreen()
{
	
	font.FaceSize(72);
	
	glDisable(GL_LIGHTING);

	glViewport(0,0,SW_WINDOW_X,SW_WINDOW_Y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,1,0,1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	
	glBindTexture(GL_TEXTURE_2D, textures[SW_LOADTX]);
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

		font.Render("Loading...");
		glfwSwapBuffers();
}

void save()
{
	fstream out("..\\Resources\\save", ios::out);

	for(int i=SW_FIRST_PLAYER;i<=SW_LAST_PLAYER;i++){
		out << ((SeaWarsPlayer*)Entities[i])->alive << " "<<  ((SeaWarsPlayer*)Entities[i])->present 
			<<" "<<  ((SeaWarsPlayer*)Entities[i])->HP 
			<<" "<<  ((SeaWarsPlayer*)Entities[i])->current.getx() <<" "<<  ((SeaWarsPlayer*)Entities[i])->current.gety() <<" "<<  ((SeaWarsPlayer*)Entities[i])->current.getz()
			<<" "<<  ((SeaWarsPlayer*)Entities[i])->rotationangle <<" "<<  ((SeaWarsPlayer*)Entities[i])->ultimateartifact<< " ";
	}

	for(int i=SW_FIRST_BOX;i<=SW_LAST_BOX;i++){
		{
			out << ((Box*)Entities[i])->alive << " "<< ((Box*)Entities[i])->effect 
				<< " "<< ((Box*)Entities[i])->current.getx() <<" "<<  ((Box*)Entities[i])->current.gety() <<" "<<  ((Box*)Entities[i])->current.getz()<< " ";
		}
	}
	
	out << NumberofIsles << " ";
	
	for(int i=SW_FIRST_ISLE;i<NumberofIsles;i++){
		if((Island*)Entities[i]!=NULL){
			out <<" "<<  ((Island*)Entities[i])->alive << " "<< ((Island*)Entities[i])->HP 
				<<" "<<  ((Island*)Entities[i])->current.getx() << " "<< ((Island*)Entities[i])->current.gety() << " "<< ((Island*)Entities[i])->current.getz()<< " ";
		}
	}

	

	out.close();

	
}

void load()
{
	fstream in("..\\Resources\\save", ios::in||ios::binary);
	
	if(!in) return;
	
	for(int i=SW_FIRST_PLAYER;i<=SW_LAST_PLAYER;i++){
		Vector v;
		float x,y,z;
		in >> ((SeaWarsPlayer*)Entities[i])->alive >> ((SeaWarsPlayer*)Entities[i])->present >> ((SeaWarsPlayer*)Entities[i])->HP
			>> x >> y >> z
			>> ((SeaWarsPlayer*)Entities[i])->rotationangle >> ((SeaWarsPlayer*)Entities[i])->ultimateartifact ;
		((SeaWarsPlayer*)Entities[i])->current.set_coords(x,y,z);
		((SeaWarsPlayer*)Entities[i])->orient();
		((SeaWarsPlayer*)Entities[i])->quad(((SeaWarsPlayer*)Entities[i])->current,((SeaWarsPlayer*)Entities[i])->geometry->get_origin(),((SeaWarsPlayer*)Entities[i])->currentquad);
		((SeaWarsPlayer*)Entities[i])->mark(((SeaWarsPlayer*)Entities[i])->currentquad);

	}
	
	for(int i=SW_FIRST_BOX;i<=SW_LAST_BOX;i++){
		{
			float x, y, z;
			in>> ((Box*)Entities[i])->alive >>((Box*)Entities[i])->effect 
				>>x>>y>>z;
			((Box*)Entities[i])->current.set_coords(x,y,z);
			((Box*)Entities[i])->quad(((Box*)Entities[i])->current,((Box*)Entities[i])->geometry->get_origin(),((Box*)Entities[i])->currentquad);
		((Box*)Entities[i])->mark(((Box*)Entities[i])->currentquad);
		}
	}
	
	in>> NumberofIsles;
	

	for(int i=SW_FIRST_ISLE;i<NumberofIsles;i++){
		if((Island*)Entities[i]!=NULL){
			float x,y,z;
			in >> ((Island*)Entities[i])->alive >> ((Island*)Entities[i])->HP 
				>> x >> y >> z;
			((Island*)Entities[i])->current.set_coords(x,y,z);
			((Island*)Entities[i])->quad(((Island*)Entities[i])->current,((Island*)Entities[i])->geometry->get_origin(),((Island*)Entities[i])->currentquad);
			((Island*)Entities[i])->mark(((Island*)Entities[i])->currentquad);
		}
	}
	in.close();
	cout << "loaded" << endl;
}
