#include "SW_Globals.h"

int SW_WINDOW_X=800, SW_WINDOW_Y=600;

extern FTGLPixmapFont font;//("..\\Resources\\TT1141M.ttf");

float grid_x[SW_QUADS], grid_y[SW_QUADS], sw_watergrid_x[SW_WATERQUADS+1], sw_watergrid_y[SW_WATERQUADS+1];
unsigned int world_bounds[SW_QUADS][SW_QUADS];
GLuint bsodlist;
GLuint wtrshdr;
string seashadercode;
float minimap_colours[SW_MINIMAP_COLOURS][4]={
	{0,0,1,1},	//PLAYER1
	{1,0,0,1},	//PLAYER2
	{0.3,0.2,0,1},	//MINIMAP_ISLE
	{0,1,0,1},	//MINIMAP_BOX
	{0.5,0,0,1},	//MINIMAP_PROJECTILE
	{0,0,0.5,1},	//MINIMAP_OTHER
};
Entity* Entities[SW_IDS-2];

material sw_materials[]={
	SW_PLAYER1MATERIALS,
	SW_PLAYER2MATERIALS,
	SW_WATERMATERIALS,
	SW_ISLEMATERIALS,
	SW_PL1PRJMATERIALS,
	SW_PL2PRJMATERIALS,
	SW_ISLPRJMATERIALS,
	SW_BOXMATERIALS,
	SW_SWATMATERIALS
};

GLuint sw_textures[SW_TEXTURES];

GLPolygon sw_models[SW_MODELS];

float MAXZ, MINZ;

//bool singleplayer;
bool endgame=false;

//report
state reports[SW_PLAYERS]= {{100,false,false,false,false,true,true,true,true,false},{100,false,false,false,false,true,true,true,true,false}};

int islandhealth[SW_ISLES];

//float pos[]={0,0,500};
float sw_pos[]={SW_WORLD_TO,SW_WORLD_FROM,0};
float sw_ambient0[]={1,1,1,1};
float sw_texx=0, sw_texy=0;
float sw_lightangle=0;

extern int NumberofIsles;


GLuint minimap_colour(GLuint id)
{
	if(SW_FIRST_PLAYER <=id && id <=SW_LAST_PLAYER) return id;
	if(SW_FIRST_ISLE <=id && id <=SW_LAST_ISLE) return SW_MINIMAP_ISLE;
	if(SW_FIRST_BOX <=id && id <=SW_LAST_BOX) return SW_MINIMAP_BOX;
	if(SW_FIRST_PROJECTILE <=id && id <=SW_LAST_PROJECTILE) return SW_MINIMAP_PROJECTILE;
	return SW_MINIMAP_OTHER;	
}

float sw_deg2rad(float angle_in_degrees)
{
	return (float)(angle_in_degrees*PI)/(float)180;
}

void sw_materialise(unsigned int what){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sw_materials[what].Ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sw_materials[what].Kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,sw_materials[what].Ks);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, sw_materials[what].Ns);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sw_materials[what].Ke);
}

void sw_texturise(unsigned int what){
	glBindTexture(GL_TEXTURE_2D, sw_textures[what]);
}

FTPoint sw_stringseed(const char* string, Vertex origin)
{
	FTBBox box=font.BBox(string);
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
	case SW_PLAYER1:
		if(what=="prj") return SW_PLAYER1FIRE;
		if(what=="sprj") return SW_PLAYER1SNIPER;
	case SW_PLAYER2:
		if(what=="prj") return SW_PLAYER2FIRE;
		if(what=="sprj") return SW_PLAYER2SNIPER;
	default: return SW_IDS+1;
	}
}

float projectilefactor(unsigned int ID)
{
	if(SW_FIRST_PLAYER_PROJECTILE <= ID && ID <=SW_LAST_PLAYER_PROJECTILE) return SW_PLAYERPROJECTILESPEED;
	if(SW_FIRST_ISLE_PROJECTILE <= ID && ID <=SW_LAST_ISLE_PROJECTILE) return SW_ISLEPROJECTILESPEED;
	return 0;
}


void Zlimits()
{
	float bounds[6];
	MAXZ=-INF; MINZ=INF;
	for(int i=0; i<SW_SWATTER; i++)
		if(sw_models[i].get_vertices()!=0){
			sw_models[i].get_boundaries(bounds);
			if(bounds[4]<MINZ) MINZ=bounds[4];
			if(bounds[5]>MAXZ) MAXZ=bounds[5];
		};
	cout << "MINZ: " << MINZ << ", MAXZ: " << MAXZ << endl;

}

void sw_BSOD()
{
	font.FaceSize(72);
	
	//glfwSetWindowSize( 640, 480 );
	//cout << "is list: " << (int)glIsList(bsodlist) << endl; //_getch();
	
	
	glDisable(GL_LIGHTING);

	// IF NOT NVIDIA
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

	//ELSE	
	/*float now=glfwGetTime(), start=now;
	while(now-start<=15){
		glViewport(0,0,640,480);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,1,0,1);
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glCallList(bsodlist);
		if(now-start>7.5) font.Render("THIS",-1,stringseed("THIS",Vertex(320,420,0)));
		if(now-start>9) font.Render("CAN'T",-1,stringseed("CAN'T",Vertex(320,300,0)));
		if(now-start>10.5) font.Render("BE",-1,stringseed("BE",Vertex(320,180,0)));
		if(now-start>12) font.Render("HAPPENING!",-1,stringseed("HAPPENING!",Vertex(320,60,0)));
		glfwSwapBuffers();
		now=glfwGetTime();
	}*/
		
	font.FaceSize(24);	
	//glfwSetWindowSize( SW_WINDOW_X, SW_WINDOW_Y );	
	glEnable(GL_LIGHTING);
	//glClear(GL_COLOR_BUFFER_BIT||GL_DEPTH_BUFFER_BIT);
	
}

unsigned int txt_of_entity(unsigned int ID)
{
	if(SW_FIRST_ISLE<=ID&&ID<=SW_LAST_ISLE) return SW_ISLTX;
	if(SW_FIRST_PLAYER<=ID&&ID<=SW_LAST_PLAYER) return SW_PLTX;
	if(SW_FIRST_PLAYER_PROJECTILE<=ID&&ID<=SW_LAST_PLAYER_PROJECTILE) return SW_PLPRJTX;
	//if(FIRST_ISLE_PROJECTILE<=ID&&ID<=LAST_ISLE_PROJECTILE) return ISLPRJTX;
	if(SW_FIRST_ISLE_PROJECTILE<=ID&&ID<=SW_LAST_ISLE_PROJECTILE) return SW_ISLTX;
	if(SW_FIRST_BOX<=ID&&ID<=SW_LAST_BOX) return SW_CRTTX;
	return SW_WTRTX;
}

void sea(float z)
{
	//glUseProgram(wtrshdrhandle);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	sw_materialise(SW_WTR);
	glEnable(GL_TEXTURE_2D);
	sw_texturise(SW_WTRTX);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	int i,j;
	glBegin(GL_QUADS);
		for(i=0; i< SW_WATERQUADS; i++){
			for(j=0; j< SW_WATERQUADS; j++){
				glTexCoord2f(0+sw_texx,0+sw_texy);
				glNormal3f(0,0,1);
				glVertex3f(sw_watergrid_x[i],sw_watergrid_y[j], z);
				glTexCoord2f(1+sw_texx,0+sw_texy);
				glNormal3f(0,0,1);
				glVertex3f(sw_watergrid_x[i+1], sw_watergrid_y[j], z);
				glTexCoord2f(1+sw_texx,1+sw_texy);
				glNormal3f(0,0,1);
				glVertex3f(sw_watergrid_x[i+1], sw_watergrid_y[j+1], z);
				glTexCoord2f(0+sw_texx,1+sw_texy);
				glNormal3f(0,0,1);
				glVertex3f(sw_watergrid_x[i], sw_watergrid_y[j+1], z);
							
			}
		}
	glEnd();	
	glDisable(GL_TEXTURE_2D);
	//glUseProgram(0);
	return;
}

void global_grid(float z)
{
	glBegin(GL_QUADS);
		for(int i=1; i< SW_QUADS-1; i++)
			for(int j=1; j< SW_QUADS-1; j++){
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
	for(int i=0; i<SW_IDS-2; i++)	if(Entities[i]!=NULL&&Entities[i]->present) Entities[i]->update();
}

void minimap(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glDisable(GL_LIGHTING);
	glViewport(x,y,width,height);
	glClear(GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(SW_WORLD_FROM*sqrt(2.0),SW_WORLD_TO*sqrt(2.0),SW_WORLD_FROM*sqrt(2.0),SW_WORLD_TO*sqrt(2.0),SW_WORLD_FROM*sqrt(2.0),SW_WORLD_TO*sqrt(2.0));
	gluLookAt(0,0,7,0,0,0,1,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	global_grid(0);
	glEnable(GL_LIGHTING);
}

void sw_update_landscape()
{
	sw_texx+=0.001;
	sw_texy-=0.001;

	sw_lightangle+=0.1;
	//ambient0[0]=0.5*(1+cos(lightangle)); ambient0[1]=ambient0[0]; ambient0[2]=ambient0[0];
	
	
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
}

void sw_scenery()
{
	glPushMatrix();
	glRotatef(sw_lightangle,0,-1,0);
	glLightfv(GL_LIGHT0, GL_POSITION, sw_pos);
	glPopMatrix();

	sea(0);
}


Vertex Randomise(string what)
{
	Vertex origin;
	Vertex v;
	float bounds[6];
	if(what=="BOX"){sw_models[SW_BOXMDL].get_boundaries(bounds);origin=sw_models[SW_BOXMDL].get_origin();}
	if(what=="ISLE"){sw_models[SW_ISLEMDL].get_boundaries(bounds);origin=sw_models[SW_ISLEMDL].get_origin();}
	bounds[0]-=50; bounds[2]-=50; bounds[1]+=50; bounds[3]+=50;
		
	int wrldtox=grid_x[SW_QUADS-3]-abs(bounds[1]), wrldfrmx=grid_x[2]+abs(bounds[0]);
	int wrldtoy=grid_x[SW_QUADS-3]-abs(bounds[3]), wrldfrmy=grid_y[2]+abs(bounds[2]);
	cout << wrldtox << " " << wrldfrmx << " " << wrldtoy << " " << wrldfrmy << endl;
	
	int quad[4], collisions[SW_IDS];

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
		  quadstep=(float)(SW_WORLD_TO-SW_WORLD_FROM)/(float)SW_QUADS;
	quad[0]=(int)floor((float)(minx-SW_WORLD_FROM)/quadstep);
	quad[1]=(int)ceil((float)(maxx-SW_WORLD_FROM)/quadstep);
	quad[2]=(int)floor((float)(miny-SW_WORLD_FROM)/quadstep);
	quad[3]=(int)ceil((float)(maxy-SW_WORLD_FROM)/quadstep);	
	

	int i,j;
	for(i=0; i<SW_IDS; i++) collisions[i]=0;
	for(i=quad[0]; i<quad[1]; i++)
		for(j=quad[2];j<quad[3];j++)
			collisions[world_bounds[i][j]]++;	
	for(i=0; i<SW_IDS-2; i++) if(collisions[i]>0) {flag=false; break;}		

	}

	return v;

}