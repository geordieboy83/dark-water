#include "Globals.h"

FTGLPixmapFont* font=NULL;
SoundSystem* Audio=NULL;

float grid_x[QUADS], grid_y[QUADS], watergrid_x[WATERQUADS+1], watergrid_y[WATERQUADS+1];
unsigned int world_bounds[QUADS][QUADS];
float minimap_colours[MINIMAP_COLOURS][4]={
	{0,0,1,1},	//PLAYER1
	{1,0,0,1},	//PLAYER2
	{0.3,0.2,0,1},	//MINIMAP_ISLE
	{0,1,0,1},	//MINIMAP_BOX
	{0.5,0,0,1},	//MINIMAP_PROJECTILE
	{0,0,0.5,1},	//MINIMAP_OTHER
};
Entity* Entities[IDS-2];

material materials[]={
	PLAYER1MATERIALS,
	PLAYER2MATERIALS,
	WATERMATERIALS,
	ISLEMATERIALS,
	PL1PRJMATERIALS,
	PL2PRJMATERIALS,
	ISLPRJMATERIALS,
	BOXMATERIALS,
	SWATMATERIALS
};

GLuint textures[TEXTURES];

GLPolygon models[MODELS];

float MAXZ, MINZ;

bool endgame=false;

report reports[PLAYERS]= {{100,false,false,false,false,true,true,true,true,false},{100,false,false,false,false,true,true,true,true,false}};

int islandhealth[ISLES];

float pos[]={WORLD_TO,WORLD_FROM,0};
float ambient0[]={1,1,1,1};
float texx=0, texy=0;
float lightangle=0;

extern int NumberofIsles;


GLuint minimap_colour(GLuint id)
{
	if(FIRST_PLAYER <=id && id <=LAST_PLAYER) return id;
	if(FIRST_ISLE <=id && id <=LAST_ISLE) return MINIMAP_ISLE;
	if(FIRST_BOX <=id && id <=LAST_BOX) return MINIMAP_BOX;
	if(FIRST_PROJECTILE <=id && id <=LAST_PROJECTILE) return MINIMAP_PROJECTILE;
	return MINIMAP_OTHER;	
}

float deg2rad(float angle_in_degrees)
{
	return (float)(angle_in_degrees*PI)/(float)180;
}

void materialise(unsigned int what){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials[what].Ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials[what].Kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,materials[what].Ks);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materials[what].Ns);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materials[what].Ke);
}

void texturise(unsigned int what){
	glBindTexture(GL_TEXTURE_2D, textures[what]);
}

FTPoint stringseed(const char* string, Vertex origin)
{
	FTBBox box=font->BBox(string);
	Vertex low(box.Lower().Xf(),box.Lower().Yf(),box.Lower().Zf());
	Vertex hi(box.Upper().Xf(),box.Upper().Yf(),box.Upper().Zf());
	return FTPoint::FTPoint(
		origin.getx()-(hi.getx()-low.getx())*0.5,
		origin.gety()-(hi.gety()-low.gety())*0.5,
		origin.getz()-(hi.getz()-low.getz())*0.5);
}

unsigned int prj_of_player(unsigned int ID, string what)
{
	switch(ID){
	case PLAYER1:
		if(what=="prj") return PLAYER1FIRE;
		if(what=="sprj") return PLAYER1SNIPER;
	case PLAYER2:
		if(what=="prj") return PLAYER2FIRE;
		if(what=="sprj") return PLAYER2SNIPER;
	default: return IDS+1;
	}
}

float projectilefactor(unsigned int ID)
{
	if(FIRST_PLAYER_PROJECTILE <= ID && ID <=LAST_PLAYER_PROJECTILE) return PLAYERPROJECTILESPEED;
	if(FIRST_ISLE_PROJECTILE <= ID && ID <=LAST_ISLE_PROJECTILE) return ISLEPROJECTILESPEED;
	return 0;
}


void Zlimits()
{
	float bounds[6];
	MAXZ=-INF; MINZ=INF;
	for(int i=0; i<SWATTER; i++)
		if(models[i].get_vertices()!=0){
			models[i].get_boundaries(bounds);
			if(bounds[4]<MINZ) MINZ=bounds[4];
			if(bounds[5]>MAXZ) MAXZ=bounds[5];
		};
	cout << "MINZ: " << MINZ << ", MAXZ: " << MAXZ << endl;

}

void BSOD()
{
	glDisable(GL_LIGHTING);

	glViewport(0,0,WINDOW_X,WINDOW_Y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,1,0,1);
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	
		glBindTexture(GL_TEXTURE_2D, textures[BSODTX]);
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
		glEnd();
		glDisable(GL_TEXTURE_2D);		
		glfwSwapBuffers();
		glfwSleep(10);

	glEnable(GL_LIGHTING);
}

unsigned int txt_of_entity(unsigned int ID)
{
	if(FIRST_ISLE<=ID&&ID<=LAST_ISLE) return ISLTX;
	if(FIRST_PLAYER<=ID&&ID<=LAST_PLAYER) return PLTX;
	if(FIRST_PLAYER_PROJECTILE<=ID&&ID<=LAST_PLAYER_PROJECTILE) return PLPRJTX;
	if(FIRST_ISLE_PROJECTILE<=ID&&ID<=LAST_ISLE_PROJECTILE) return ISLTX;
	if(FIRST_BOX<=ID&&ID<=LAST_BOX) return CRTTX;
	return WTRTX;
}

void sea(float z)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	materialise(WTR);
	glEnable(GL_TEXTURE_2D);
	texturise(WTRTX);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	int i,j;
	glBegin(GL_QUADS);
		for(i=0; i< WATERQUADS; i++){
			for(j=0; j< WATERQUADS; j++){
				glTexCoord2f(0+texx,0+texy);
				glNormal3f(0,0,1);
				glVertex3f(watergrid_x[i],watergrid_y[j], z);
				glTexCoord2f(1+texx,0+texy);
				glNormal3f(0,0,1);
				glVertex3f(watergrid_x[i+1], watergrid_y[j], z);
				glTexCoord2f(1+texx,1+texy);
				glNormal3f(0,0,1);
				glVertex3f(watergrid_x[i+1], watergrid_y[j+1], z);
				glTexCoord2f(0+texx,1+texy);
				glNormal3f(0,0,1);
				glVertex3f(watergrid_x[i], watergrid_y[j+1], z);
							
			}
		}
	glEnd();	
	glDisable(GL_TEXTURE_2D);
	return;
}

void global_grid(float z)
{
	glBegin(GL_QUADS);
		for(int i=1; i< QUADS-1; i++)
			for(int j=1; j< QUADS-1; j++){
				glColor3fv(minimap_colours[minimap_colour(world_bounds[i][j])]);
				glVertex3f(grid_x[i],grid_y[j], z);
				glVertex3f(grid_x[i+1], grid_y[j], z);
				glVertex3f(grid_x[i+1], grid_y[j+1], z);
				glVertex3f(grid_x[i], grid_y[j+1], z);				
			}
	glEnd();
	return;
}

void update_world()
{
	for(int i=0; i<IDS-2; i++)	if(Entities[i]!=NULL&&Entities[i]->present) Entities[i]->update();
}

void minimap(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glDisable(GL_LIGHTING);
	glViewport(x,y,width,height);
	glClear(GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(WORLD_FROM*sqrt(2.0),WORLD_TO*sqrt(2.0),WORLD_FROM*sqrt(2.0),WORLD_TO*sqrt(2.0),WORLD_FROM*sqrt(2.0),WORLD_TO*sqrt(2.0));
	gluLookAt(0,0,7,0,0,0,1,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	global_grid(0);
	glEnable(GL_LIGHTING);
}

void update_landscape()
{
	texx+=0.001;
	texy-=0.001;

	lightangle+=0.1;
}

void scenery()
{
	glPushMatrix();
	glRotatef(lightangle,0,-1,0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glPopMatrix();

	sea(0);
}


Vertex Randomise(string what)
{
	Vertex origin;
	Vertex v;
	float bounds[6];
	if(what=="BOX"){models[BOXMDL].get_boundaries(bounds);origin=models[BOXMDL].get_origin();}
	if(what=="ISLE"){models[ISLEMDL].get_boundaries(bounds);origin=models[ISLEMDL].get_origin();}
	bounds[0]-=50; bounds[2]-=50; bounds[1]+=50; bounds[3]+=50;
		
	int wrldtox=grid_x[QUADS-3]-abs(bounds[1]), wrldfrmx=grid_x[2]+abs(bounds[0]);
	int wrldtoy=grid_x[QUADS-3]-abs(bounds[3]), wrldfrmy=grid_y[2]+abs(bounds[2]);
	cout << wrldtox << " " << wrldfrmx << " " << wrldtoy << " " << wrldfrmy << endl;
	
	int quad[4], collisions[IDS];

	bool flag=false;
	while(!flag){
		flag=true;

		v.set_coords(
			rand()%(int)(wrldtox-wrldfrmx)+wrldfrmx,
			rand()%(int)(wrldtoy-wrldfrmy)+wrldfrmy,
		0);

	float minx=v.getx()+min(bounds[0]-origin.getx(), bounds[2]-origin.gety()),
		  miny=v.gety()+min(bounds[0]-origin.getx(), bounds[2]-origin.gety()),
		  maxx=v.getx()+max(bounds[1]-origin.getx(), bounds[3]-origin.gety()),
		  maxy=v.gety()+max(bounds[1]-origin.getx(), bounds[3]-origin.gety()),
		  quadstep=(float)(WORLD_TO-WORLD_FROM)/(float)QUADS;
	quad[0]=(int)floor((float)(minx-WORLD_FROM)/quadstep);
	quad[1]=(int)ceil((float)(maxx-WORLD_FROM)/quadstep);
	quad[2]=(int)floor((float)(miny-WORLD_FROM)/quadstep);
	quad[3]=(int)ceil((float)(maxy-WORLD_FROM)/quadstep);	
	

	int i,j;
	for(i=0; i<IDS; i++) collisions[i]=0;
	for(i=quad[0]; i<quad[1]; i++)
		for(j=quad[2];j<quad[3];j++)
			collisions[world_bounds[i][j]]++;	
	for(i=0; i<IDS-2; i++) if(collisions[i]>0) {flag=false; break;}		

	}

	return v;

}