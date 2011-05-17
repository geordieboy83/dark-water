using namespace std;
#pragma once;

#include "UI.h"

int NumberofIsles;
int facesize=18;
extern FTGLPixmapFont* font;
extern Entity* Entities[];
extern report reports[];
extern bool endgame;
extern bool cheats;
extern bool paused;
extern bool pausedbeforeexit;
extern int islandhealth[];
extern GLuint textures[];


void summarise(unsigned int id)
{
	int x;
	if(id==PLAYER1){
		x=WINDOW_X*0.666;
	}

	if(id==PLAYER2){
		x=0;
	}

	if(reports[id].alive&&reports[id].present){
		char s[256];
		if(reports[id].ua) { sprintf(s,"Ultimate Artifact"); font->Render(s,-1,FTPoint(x,WINDOW_Y-8*facesize)); }
		if(reports[id].tf) { sprintf(s,"Transformed"); font->Render(s,-1,FTPoint(x,WINDOW_Y-7*facesize)); }
		if(reports[id].rf) { sprintf(s,"Rapid Fire"); font->Render(s,-1,FTPoint(x,WINDOW_Y-6*facesize)); }
		if(reports[id].dd) { sprintf(s,"Double Damage"); font->Render(s,-1,FTPoint(x,WINDOW_Y-5*facesize)); }
		if(!reports[id].snipe) { sprintf(s,"Snipeshot unavailable"); font->Render(s,-1,FTPoint(x,WINDOW_Y-4*facesize)); }
		if(!reports[id].shot) { sprintf(s,"Shot unavailable"); font->Render(s,-1,FTPoint(x,WINDOW_Y-3*facesize)); }
		sprintf(s,"HP: %d of %d",reports[id].HP, (Player*)Entities[id]->max_HP()); font->Render(s,-1,FTPoint(x,WINDOW_Y-2*facesize)); 
		sprintf(s,"Player %d",id+1); font->Render(s,-1,FTPoint(x,WINDOW_Y-facesize)); 
		


	}


}


void summarisecheats()
{
	//Red text
	glPixelTransferf(GL_GREEN_BIAS, -1.0f);
	glPixelTransferf(GL_BLUE_BIAS, -1.0f);

	font->Render("CHEATS ENABLED");

	FTSimpleLayout gifts;
	gifts.SetFont(font);
	gifts.SetAlignment(FTGL::ALIGN_RIGHT);
	gifts.SetLineLength(WINDOW_X);
	
	int j=0;
	for(int i=FIRST_BOX;i<=LAST_BOX;i++)
	{
		if(((Box*)Entities[i])->alive){
			string text="";
			int effect=((Box*)Entities[i])->effect;
			switch(effect){
				case 1: text+="Health at "; break;
				case 2: text+="Poison at "; break;
				case 3: text+="Transformation at "; break;
				case 4: text+="Blue Screen of Death at "; break;
				case 5: text+="Ultimate Artifact at "; break;
				case 6: text+="Double Damage at "; break;
				case 7: text+="Rapid Fire at "; break;
				case 8: text+="The Plague at "; break;
			}
			char pos[15];
			sprintf(pos,"(%d, %d)", (int)Entities[i]->current.getx(), (int)Entities[i]->current.gety());
			text+=pos;
		
			FTBBox box=font->BBox(text.c_str());
			float boxx=box.Upper().Xf()-box.Lower().Xf(),
			boxy=box.Upper().Yf()-box.Lower().Yf();

			float x=WINDOW_X-boxx, y=-box.Lower().Yf()+j*(facesize+2);
			font->Render(text.c_str(),-1,FTPoint(x,y));
			j++;
		}

		
	}

	//White text
	glPixelTransferf(GL_RED_BIAS, -0.0f);
	glPixelTransferf(GL_GREEN_BIAS, -0.0f);
	glPixelTransferf(GL_BLUE_BIAS, -0.0f);
	
}


void pause()
{
	font->FaceSize(36);
	Vertex origin(WINDOW_X/2, WINDOW_Y/2, 0);
	FTPoint centre=stringseed("GAME PAUSED",origin);
	font->Render("GAME PAUSED",-1,centre);		
}

void beforeexit()
{
	int facesize=24;
	pause();
	font->FaceSize(facesize);
	font->Render("Pressing Esc again will exit",-1,
		stringseed("Pressing Esc again will exit", Vertex(WINDOW_X/2,WINDOW_Y-facesize,0)));
	font->Render("N will start a new game",-1,
		stringseed("N will start a new game", Vertex(WINDOW_X/2,facesize,0)));
}


void gameover()
{
		font->FaceSize(36);
			
		Vertex origin(WINDOW_X/2, WINDOW_Y/2, 0);

		if(!reports[PLAYER2].present){
			if(((Player*)Entities[PLAYER1])->loser){
				FTPoint defeat=stringseed("YOU HAVE BEEN DEFEATED",origin);
				font->Render("YOU HAVE BEEN DEFEATED",-1,defeat);
			}
			else {
				FTPoint defeat=stringseed("YOU ARE VICTORIOUS",origin);
				font->Render("YOU ARE VICTORIOUS",-1,defeat);

			}
		}
		else{
			if(((Player*)Entities[PLAYER1])->loser&&((Player*)Entities[PLAYER2])->loser){
				FTPoint defeat=stringseed("DRAW",origin);
				font->Render("DRAW",-1,defeat);			
			}
			else{	
				FTPoint defeat=stringseed("PLAYER X WINS",origin);
				if(((Player*)Entities[PLAYER1])->loser) font->Render("PLAYER 2 WINS",-1,defeat);
				else if(((Player*)Entities[PLAYER2])->loser) font->Render("PLAYER 1 WINS",-1,defeat);
			}
		}

		int facesize=24;
		font->FaceSize(facesize);
		font->Render("Press Esc to exit...",-1,
			stringseed("Press Esc to exit...", Vertex(WINDOW_X/2,WINDOW_Y-facesize,0)));
		font->Render("... or N to start a new game",-1,
			stringseed("... or N to start a new game", Vertex(WINDOW_X/2,facesize,0)));

}


void summariseplayers()
{
	summarise(PLAYER1);
	if(!reports[PLAYER2].present)summarise(PLAYER2);
}

void summariseisles()
{
	int x=0.333*WINDOW_X;
	char s[256];

	for(int i=FIRST_ISLE;i<=LAST_ISLE;i++)
	{
		if(Entities[i]!=NULL&&Entities[i]->alive&&Entities[i]->present)
		{
			int j=i; j-=FIRST_ISLE; 
			sprintf(s, "Island %d: HP %d of %d", j+1, islandhealth[j],100);
			font->Render(s,-1,FTPoint(x,WINDOW_Y-facesize*(1+j)));
		}
	}


}

void summarise()
{
	if(endgame) {
		gameover();
		return;
	}

	if(paused) {
		pause();
		return;
	}

	if(pausedbeforeexit) {
		beforeexit();
		return;
	}

	font->FaceSize(facesize);
	
	summarise(PLAYER1);
	summarise(PLAYER2);
	summariseisles();
	if(cheats) summarisecheats();
}

void save()
{
	fstream out("..\\Resources\\save", ios::out);

	for(int i=FIRST_PLAYER;i<=LAST_PLAYER;i++){
		out << ((Player*)Entities[i])->alive << " "<<  ((Player*)Entities[i])->present 
			<<" "<<  ((Player*)Entities[i])->HP 
			<<" "<<  ((Player*)Entities[i])->current.getx() <<" "<<  ((Player*)Entities[i])->current.gety() <<" "<<  ((Player*)Entities[i])->current.getz()
			<<" "<<  ((Player*)Entities[i])->rotationangle <<" "<<  ((Player*)Entities[i])->ultimateartifact<< " ";
	}

	for(int i=FIRST_BOX;i<=LAST_BOX;i++){
		{
			out << ((Box*)Entities[i])->alive << " "<< ((Box*)Entities[i])->effect 
				<< " "<< ((Box*)Entities[i])->current.getx() <<" "<<  ((Box*)Entities[i])->current.gety() <<" "<<  ((Box*)Entities[i])->current.getz()<< " ";
		}
	}
	
	out << NumberofIsles << " ";
	
	for(int i=FIRST_ISLE;i<NumberofIsles;i++){
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
		
	for(int i=FIRST_PLAYER;i<=LAST_PLAYER;i++){
		Entities[i]->unmark(Entities[i]->currentquad);		
		Vector v;
		float x,y,z;
		in >> ((Player*)Entities[i])->alive >> ((Player*)Entities[i])->present >> ((Player*)Entities[i])->HP
			>> x >> y >> z
			>> ((Player*)Entities[i])->rotationangle >> ((Player*)Entities[i])->ultimateartifact ;
		((Player*)Entities[i])->set_HP(((Player*)Entities[i])->HP);
		((Player*)Entities[i])->current.set_coords(x,y,z);
		((Player*)Entities[i])->orient();
		((Player*)Entities[i])->quad(((Player*)Entities[i])->current,((Player*)Entities[i])->geometry->get_origin(),((Player*)Entities[i])->currentquad);
		((Player*)Entities[i])->mark(((Player*)Entities[i])->currentquad);

	}
	
	for(int i=FIRST_BOX;i<=LAST_BOX;i++){
		
			Entities[i]->unmark(Entities[i]->currentquad);
			float x, y, z;
			in>> ((Box*)Entities[i])->alive >>((Box*)Entities[i])->effect 
				>>x>>y>>z;
			((Box*)Entities[i])->current.set_coords(x,y,z);
			((Box*)Entities[i])->quad(((Box*)Entities[i])->current,((Box*)Entities[i])->geometry->get_origin(),((Box*)Entities[i])->currentquad);
		((Box*)Entities[i])->mark(((Box*)Entities[i])->currentquad);
		
	}
	
	in>> NumberofIsles;
	

	for(int i=FIRST_ISLE;i<NumberofIsles;i++){
		Entities[i]->unmark(Entities[i]->currentquad);
		if((Island*)Entities[i]!=NULL){
			float x,y,z;
			in >> ((Island*)Entities[i])->alive >> ((Island*)Entities[i])->HP 
				>> x >> y >> z;
			Entities[i]->set_HP(Entities[i]->HP);
			((Island*)Entities[i])->current.set_coords(x,y,z);
			((Island*)Entities[i])->quad(((Island*)Entities[i])->current,((Island*)Entities[i])->geometry->get_origin(),((Island*)Entities[i])->currentquad);
			((Island*)Entities[i])->mark(((Island*)Entities[i])->currentquad);
		}
	}
	in.close();
	cout << "loaded" << endl;
}
