#include "Universe.h"

extern unsigned int world_bounds[QUADS][QUADS];
extern float grid_x[QUADS], grid_y[QUADS], watergrid_x[WATERQUADS+1], watergrid_y[WATERQUADS+1];
extern Entity* Entities[IDS-2];
extern material materials[];
extern GLPolygon models[];
extern GLuint textures[TEXTURES];
extern float minimap_colours[MINIMAP_COLOURS][4];

void loadingscreen(string s)
{
	extern FTGLPixmapFont* font;
	int size=36;
	font->FaceSize(size);
	
	FTSimpleLayout status;
	status.SetFont(font);
	status.SetAlignment(FTGL::ALIGN_CENTER);
	status.SetLineLength(WINDOW_X);
	FTBBox box=status.BBox(s.c_str());
	float boxx=box.Upper().Xf()-box.Lower().Xf(),
		boxy=box.Upper().Yf()-box.Lower().Yf();
	
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
	glBindTexture(GL_TEXTURE_2D, textures[LOADTX]);
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
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,WINDOW_X,0,WINDOW_Y);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRasterPos2i(0,WINDOW_Y/2+boxy/2-size-status.GetLineSpacing());
	status.Render(s.c_str());
	glRasterPos2i(0,0);

	glfwSwapBuffers();
}




void glLoadModels()
{
	string s="";

	Vector v;
	float bounds[6];
	string names[]={"..\\Resources\\boat\\just-boat.obj","..\\Resources\\boat\\just-sail.obj"};
	
	s+="Players\n";
	loadingscreen(s);

	models[PLMDL].chainload(2,names, false);	
	models[PLMDL].bounding();
	models[PLMDL].origin();
	models[PLMDL].chaincentre();
	models[PLMDL].chainscale(1.5);
	models[PLMDL].bounding();
	models[PLMDL].get_boundaries(bounds);
	v.set_coords(0,0,-bounds[4]-2);
	models[PLMDL].chaintranslate(v);
	models[PLMDL].bounding();
	models[PLMDL].origin();

	s+="Volcanoes\n";
	loadingscreen(s);
		
	models[ISLEMDL].objload("..\\Resources\\volcano\\volcano.obj",true);
	models[ISLEMDL].scale(1.5);
	models[ISLEMDL].bounding();
	models[ISLEMDL].get_boundaries(bounds);
	v.set_coords(0,0,-bounds[4]-1);
	models[ISLEMDL].translate(v);
	models[ISLEMDL].bounding();
	models[ISLEMDL].origin();
	cout << "Isle model loaded." << endl;
	
	s+="Rockets\n";
	loadingscreen(s);
	
	models[PLPRJMDL].objload("..\\Resources\\missile\\missile.obj",false);
	models[PLPRJMDL].scale(15);
	models[PLPRJMDL].bounding();
	models[PLPRJMDL].origin();
	cout << "Player projectile model loaded." << endl;
	
	s+="Boulders\n";
	loadingscreen(s);

	models[ISLPRJMDL].objload("..\\Resources\\stone\\stone.obj",true);
	models[ISLPRJMDL].scale(0.5);
	models[ISLPRJMDL].bounding();
	models[ISLPRJMDL].origin();
	cout << "Isle projectile model loaded." << endl;
	
	s+="Goodies\n";
	loadingscreen(s);	
	
	names[0]="..\\Resources\\crate\\just-box.obj"; names[1]="..\\Resources\\crate\\just-wrap.obj";
	models[BOXMDL].chainload(2,names,true);
	models[BOXMDL].bounding();
	models[BOXMDL].origin();
	cout << "Box model loaded." << endl;
	
	s+="Teapots\n";
	loadingscreen(s);

	models[TPT].load("..\\Resources\\teapot.txt");
	v.set_coords(1,0,0);
	models[TPT].scale(0.5);
	models[TPT].rotate(v,90);
	models[TPT].bounding();
	models[TPT].origin();
	models[TPT].get_boundaries(bounds);
	v.set_coords(0,0,-bounds[4]-12);
	models[TPT].translate(v);
	models[TPT].bounding();
	models[TPT].origin();
	models[TPT].normals();
	cout << "Teapot model loaded." << endl;
	
	s+="Flyswatters\n";
	loadingscreen(s);

	names[0]="..\\Resources\\flyswatter\\just-grid.obj"; names[1]="..\\Resources\\flyswatter\\just-handle.obj";
	models[SWATTER].chainload(2,names,false);
	models[SWATTER].bounding();
	models[SWATTER].origin();
	cout << "Flyswatter model loaded." << endl;

	models[CUBE].load("..\\Resources\\cube.txt");
	models[CUBE].bounding();
	models[CUBE].origin();
	cout << "Cube model loaded." << endl;

	Zlimits();	
}

void glLoadTextures()
{
	glGenTextures(1, &textures[WTRTX]);	
	glBindTexture(GL_TEXTURE_2D, textures[WTRTX]);
	glfwLoadTexture2D("..\\Resources\\Water.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &textures[ISLTX]);	
	glBindTexture(GL_TEXTURE_2D, textures[ISLTX]);
	glfwLoadTexture2D("..\\Resources\\volcano\\Map__1_Cellular.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &textures[BSODTX]);	
	glBindTexture(GL_TEXTURE_2D, textures[BSODTX]);
	glfwLoadTexture2D("..\\Resources\\BSOD.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &textures[LOADTX]);	
	glBindTexture(GL_TEXTURE_2D, textures[LOADTX]);
	glfwLoadTexture2D("..\\Resources\\Loading.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void initialise()
{
	for(int i=0; i< QUADS; i++){grid_x[i]=WORLD_FROM+i*(float)(WORLD_TO-WORLD_FROM)/(float)QUADS; grid_y[i]=grid_x[i];}
	for(int i=0; i<= WATERQUADS; i++){watergrid_x[i]=2.6*(grid_x[1]+i*(float)(grid_x[QUADS-2]-grid_x[1])/(float)WATERQUADS); watergrid_y[i]=watergrid_x[i];}
	for(int i=0; i<IDS-2; i++) Entities[i]=NULL;
	world_bounds[QUADS-1][QUADS-1]=EDGE;
	for(int i=0; i<QUADS-1;i++){		
		world_bounds[i][0]=EDGE;
		world_bounds[i][QUADS-1]=EDGE;
		world_bounds[0][i]=EDGE;
		world_bounds[QUADS-1][i]=EDGE;
		for(int j=1; j<QUADS-1; j++) world_bounds[i][j]=FREE;
	}
	glLoadModels();
}

void InitialiseIsles()
{
	for(int i=0; i<ISLES; i++){

	int j=ISLE1+i;
	Entities[j]=new Island(j,true);
	Entities[j]->geometry=&models[ISLEMDL];	
	Entities[j]->geometry->get_boundaries(Entities[j]->geometry_bounds);
	Entities[j]->current=Randomise("ISLE");
	Entities[j]->quad(Entities[j]->current,Entities[j]->geometry->get_origin(),Entities[j]->currentquad);
	Entities[j]->mark(Entities[j]->currentquad);
	Entities[j]->stuff=&materials[ISL];
	Entities[j]->chaindesign(0,&materials[ISL]);

	int k=FIRST_ISLE_PROJECTILE+i;
	Entities[k]=new Boulder(k,j,true);
	Entities[k]->geometry=&models[ISLPRJMDL];	
	Entities[k]->geometry->get_boundaries(Entities[k]->geometry_bounds);
	Entities[k]->stuff=&materials[ISL];
	Entities[k]->chaindesign(0,&materials[ISL]);
	}
}

void glInitialise()
{
	models[SWATTER].chaindesign(0,&materials[SWT]);
	
	glClearColor(0,0.3,0.8,1);
	
	InitialisePlayers();
	InitialiseMissiles();
	InitialiseSnipers();
	InitialiseIsles();
	InitialisePresents();
		
}



void lasers()
{

	glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_COLOR,GL_ONE_MINUS_SRC_COLOR);
		
		for(int i=FIRST_PLAYER;i<=LAST_PLAYER;i++)
			if(Entities[i]!=NULL&
				Entities[i]->present&&
				((Player*)Entities[i])->sniper){
					glLineWidth(5);
					glBegin(GL_LINES);
						glColor4fv(minimap_colours[i]);
						glVertex3f(
							((Player*)Entities[i])->orientation.getx(),
							((Player*)Entities[i])->orientation.gety(),
							((Player*)Entities[i])->orientation.getz()+((Player*)Entities[i])->geometry_bounds[5]-1);				
						
						Vector to=subtract(((Player*)Entities[i])->sniperview, ((Player*)Entities[i])->current);
						to.scale(100);
						to=add(to,((Player*)Entities[i])->current);
						glVertex3f(
							to.getx(),
							to.gety(),
							to.getz()+((Player*)Entities[i])->geometry_bounds[5]-1);
					glEnd();
					glLineWidth(1);
			}
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);

}

void display_world()
{
	for(int i=0; i<IDS-2; i++)
		if(Entities[i]!=NULL){
			unsigned int texid=txt_of_entity(i);
			bool flag=glIsTexture(texid);
			if(flag){
				glEnable(GL_TEXTURE_2D);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glBindTexture(GL_TEXTURE_2D, textures[texid]);				
			}
			Entities[i]->display();
			if(flag) glDisable(GL_TEXTURE_2D);
		}
		
		
		
		
}

void InitialisePresents()
{
	for(int i=0; i<BOXES; i++){
		int j=BOX1+i;
	Entities[j]=new Box(j,true);
	Entities[j]->geometry=&models[BOXMDL];
	Entities[j]->geometry->get_boundaries(Entities[j]->geometry_bounds);
	Entities[j]->stuff=&materials[CRT];
	//Entities[j]->chaindesign(0,&materials[CRT]);
	((Box*)Entities[j])->reset(Randomise("BOX"));
	}
}

void InitialisePlayers()
{
	int keys[PLAYER_CONTROLS]=PLAYER1KEYS;	
	Entities[PLAYER1]=new Player(PLAYER1,keys,true);
	Entities[PLAYER1]->geometry=&models[PLMDL];
	Entities[PLAYER1]->stuff=&materials[PL1];
	Entities[PLAYER1]->geometry->get_boundaries(Entities[PLAYER1]->geometry_bounds);
	Entities[PLAYER1]->current.set_coords(700,-700,0);
	Entities[PLAYER1]->rotationangle=-135;
	Entities[PLAYER1]->quad(Entities[PLAYER1]->current,Entities[PLAYER1]->geometry->get_origin(),Entities[PLAYER1]->currentquad);
	Entities[PLAYER1]->mark(Entities[PLAYER1]->currentquad);
	Entities[PLAYER1]->chaindesign(0,&materials[PL1]);
	((Player*)Entities[PLAYER1])->orient();
	((Player*)Entities[PLAYER1])->alternate=&models[TPT];

	int keys2[PLAYER_CONTROLS]=PLAYER2KEYS;
	Entities[PLAYER2]=new Player(PLAYER2,keys2,true);
	Entities[PLAYER2]->geometry=&models[PLMDL];
	Entities[PLAYER2]->stuff=&materials[PL2];
	Entities[PLAYER2]->geometry->get_boundaries(Entities[PLAYER2]->geometry_bounds);
	Entities[PLAYER2]->current.set_coords(-700,700,0);
	Entities[PLAYER1]->rotationangle=45;
	Entities[PLAYER2]->quad(Entities[PLAYER2]->current,Entities[PLAYER2]->geometry->get_origin(),Entities[PLAYER2]->currentquad);
	Entities[PLAYER2]->mark(Entities[PLAYER2]->currentquad);
	Entities[PLAYER2]->chaindesign(0,&materials[PL2]);
	((Player*)Entities[PLAYER2])->orient();
	((Player*)Entities[PLAYER2])->alternate=&models[TPT];

}

void InitialiseMissiles()
{
	Entities[PLAYER1FIRE]= new Projectile(PLAYER1FIRE,PLAYER1,true);
	Entities[PLAYER1FIRE]->geometry=&models[PLPRJMDL];
	Entities[PLAYER1FIRE]->geometry->get_boundaries(Entities[PLAYER1FIRE]->geometry_bounds);
	Entities[PLAYER1FIRE]->stuff=&materials[PL1PRJ];
	Entities[PLAYER1FIRE]->chaindesign(0,&materials[PL1PRJ]);

	Entities[PLAYER2FIRE]= new Projectile(PLAYER2FIRE,PLAYER2,true);
	Entities[PLAYER2FIRE]->geometry=&models[PLPRJMDL];
	Entities[PLAYER2FIRE]->geometry->get_boundaries(Entities[PLAYER2FIRE]->geometry_bounds);
	Entities[PLAYER2FIRE]->stuff=&materials[PL2PRJ];
	Entities[PLAYER2FIRE]->chaindesign(0,&materials[PL2PRJ]);
}
void InitialiseSnipers()
{
	float now=glfwGetTime();

	Entities[PLAYER1SNIPER]=new Snipershot(PLAYER1SNIPER,PLAYER1,true);
	Entities[PLAYER1SNIPER]->geometry=&models[CUBE];
	Entities[PLAYER1SNIPER]->geometry->get_boundaries(Entities[PLAYER1SNIPER]->geometry_bounds);
	((Snipershot*)Entities[PLAYER1SNIPER])->when=now;


	Entities[PLAYER2SNIPER]=new Snipershot(PLAYER2SNIPER,PLAYER2,true);
	Entities[PLAYER2SNIPER]->geometry=&models[CUBE];
	Entities[PLAYER2SNIPER]->geometry->get_boundaries(Entities[PLAYER2SNIPER]->geometry_bounds);
	((Snipershot*)Entities[PLAYER2SNIPER])->when=now;


}
