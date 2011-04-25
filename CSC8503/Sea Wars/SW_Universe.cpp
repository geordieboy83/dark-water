#include "SW_Universe.h"

extern unsigned int world_bounds[SW_QUADS][SW_QUADS];
extern float grid_x[SW_QUADS], grid_y[SW_QUADS], sw_watergrid_x[SW_WATERQUADS+1], sw_watergrid_y[SW_WATERQUADS+1];
extern Entity* Entities[SW_IDS-2];
extern material sw_materials[];
extern GLPolygon sw_models[];
extern GLuint sw_textures[SW_TEXTURES];
extern GLuint bsodlist;
extern GLuint wtrshdr;
extern float minimap_colours[SW_MINIMAP_COLOURS][4];

void sw_glLoadModels()
{
	Vector v;
	float bounds[6];
	string names[]={"..\\Resources\\boat\\just-boat.obj","..\\Resources\\boat\\just-sail.obj"};
	
	sw_models[SW_PLMDL].chainload(2,names, false);	
	sw_models[SW_PLMDL].bounding();
	sw_models[SW_PLMDL].origin();
	sw_models[SW_PLMDL].chaincentre();
	sw_models[SW_PLMDL].chainscale(1.5);
	sw_models[SW_PLMDL].bounding();
	sw_models[SW_PLMDL].get_boundaries(bounds);
	v.set_coords(0,0,-bounds[4]-2);
	sw_models[SW_PLMDL].chaintranslate(v);
	sw_models[SW_PLMDL].bounding();
	sw_models[SW_PLMDL].origin();

		
	sw_models[SW_ISLEMDL].objload("..\\Resources\\volcano\\volcano.obj",true);
	sw_models[SW_ISLEMDL].scale(1.5);
	sw_models[SW_ISLEMDL].bounding();
	sw_models[SW_ISLEMDL].get_boundaries(bounds);
	v.set_coords(0,0,-bounds[4]-1);
	sw_models[SW_ISLEMDL].translate(v);
	sw_models[SW_ISLEMDL].bounding();
	sw_models[SW_ISLEMDL].origin();
	cout << "Isle model loaded." << endl;
	
	sw_models[SW_PLPRJMDL].objload("..\\Resources\\missile\\missile.obj",false);
	sw_models[SW_PLPRJMDL].scale(15);
	sw_models[SW_PLPRJMDL].bounding();
	sw_models[SW_PLPRJMDL].origin();
	cout << "Player projectile model loaded." << endl;
	
	sw_models[SW_ISLPRJMDL].objload("..\\Resources\\stone\\stone.obj",true);
	sw_models[SW_ISLPRJMDL].scale(0.5);
	sw_models[SW_ISLPRJMDL].bounding();
	sw_models[SW_ISLPRJMDL].origin();
	cout << "Isle projectile model loaded." << endl;
	
	names[0]="..\\Resources\\crate\\just-box.obj"; names[1]="..\\Resources\\crate\\just-wrap.obj";
	sw_models[SW_BOXMDL].chainload(2,names,true);
	sw_models[SW_BOXMDL].bounding();
	sw_models[SW_BOXMDL].origin();
	cout << "Box model loaded." << endl;
	
	sw_models[SW_TPT].load("..\\Resources\\teapot.txt");
	v.set_coords(1,0,0);
	sw_models[SW_TPT].scale(0.5);
	sw_models[SW_TPT].rotate(v,90);
	sw_models[SW_TPT].bounding();
	sw_models[SW_TPT].origin();
	sw_models[SW_TPT].get_boundaries(bounds);
	v.set_coords(0,0,-bounds[4]-12);
	sw_models[SW_TPT].translate(v);
	sw_models[SW_TPT].bounding();
	sw_models[SW_TPT].origin();
	sw_models[SW_TPT].normals();
	cout << "Teapot model loaded." << endl;
	
	names[0]="..\\Resources\\flyswatter\\just-grid.obj"; names[1]="..\\Resources\\flyswatter\\just-handle.obj";
	sw_models[SW_SWATTER].chainload(2,names,false);
	sw_models[SW_SWATTER].bounding();
	sw_models[SW_SWATTER].origin();
	cout << "Flyswatter model loaded." << endl;

	sw_models[SW_CUBE].load("..\\Resources\\cube.txt");
	sw_models[SW_CUBE].bounding();
	sw_models[SW_CUBE].origin();
	cout << "Cube model loaded." << endl;

	Zlimits();	
}

void sw_glLoadTextures()
{
	glGenTextures(1, &sw_textures[SW_WTRTX]);	
	glBindTexture(GL_TEXTURE_2D, sw_textures[SW_WTRTX]);
	glfwLoadTexture2D("..\\Resources\\Water.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &sw_textures[SW_ISLTX]);	
	glBindTexture(GL_TEXTURE_2D, sw_textures[SW_ISLTX]);
	glfwLoadTexture2D("..\\Resources\\volcano\\Map__1_Cellular.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &sw_textures[SW_BSODTX]);	
	glBindTexture(GL_TEXTURE_2D, sw_textures[SW_BSODTX]);
	glfwLoadTexture2D("..\\Resources\\BSOD.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &sw_textures[SW_LOADTX]);	
	glBindTexture(GL_TEXTURE_2D, sw_textures[SW_LOADTX]);
	glfwLoadTexture2D("..\\Resources\\Loading.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void sw_initialise()
{
	for(int i=0; i< SW_QUADS; i++){grid_x[i]=SW_WORLD_FROM+i*(float)(SW_WORLD_TO-SW_WORLD_FROM)/(float)SW_QUADS; grid_y[i]=grid_x[i];}
	for(int i=0; i<= SW_WATERQUADS; i++){sw_watergrid_x[i]=2.6*(grid_x[1]+i*(float)(grid_x[SW_QUADS-2]-grid_x[1])/(float)SW_WATERQUADS); sw_watergrid_y[i]=sw_watergrid_x[i];}
	for(int i=0; i<SW_IDS-2; i++) Entities[i]=NULL;
	world_bounds[SW_QUADS-1][SW_QUADS-1]=SW_EDGE;
	for(int i=0; i<SW_QUADS-1;i++){		
		world_bounds[i][0]=SW_EDGE;
		world_bounds[i][SW_QUADS-1]=SW_EDGE;
		world_bounds[0][i]=SW_EDGE;
		world_bounds[SW_QUADS-1][i]=SW_EDGE;
		for(int j=1; j<SW_QUADS-1; j++) world_bounds[i][j]=SW_FREE;
	}
	sw_glLoadModels();
}

void InitialiseIsles()
{
	for(int i=0; i<SW_ISLES; i++){

	int j=SW_ISLE1+i;
	Entities[j]=new Island(j,true);
	Entities[j]->geometry=&sw_models[SW_ISLEMDL];	
	Entities[j]->geometry->get_boundaries(Entities[j]->geometry_bounds);
	Entities[j]->current=Randomise("ISLE");
	Entities[j]->quad(Entities[j]->current,Entities[j]->geometry->get_origin(),Entities[j]->currentquad);
	Entities[j]->mark(Entities[j]->currentquad);
	Entities[j]->stuff=&sw_materials[SW_ISL];
	Entities[j]->chaindesign(0,&sw_materials[SW_ISL]);

	int k=SW_FIRST_ISLE_PROJECTILE+i;
	Entities[k]=new SeaWarsBoulder(k,j,true);
	Entities[k]->geometry=&sw_models[SW_ISLPRJMDL];	
	Entities[k]->geometry->get_boundaries(Entities[k]->geometry_bounds);
	Entities[k]->stuff=&sw_materials[SW_ISL];
	Entities[k]->chaindesign(0,&sw_materials[SW_ISL]);
	}
}

void sw_glInitialise()
{
	if(!glIsList(bsodlist)) bsodlist=glGenLists(1);
	else glDeleteLists(bsodlist,1);
	glNewList(bsodlist,GL_COMPILE);
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

	sw_models[SW_SWATTER].chaindesign(0,&sw_materials[SW_SWT]);
	
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
		
		for(int i=SW_FIRST_PLAYER;i<=SW_LAST_PLAYER;i++)
			if(Entities[i]!=NULL&
				Entities[i]->present&&
				((SeaWarsPlayer*)Entities[i])->sniper){
					glLineWidth(5);
					glBegin(GL_LINES);
						glColor4fv(minimap_colours[i]);
						glVertex3f(
							((SeaWarsPlayer*)Entities[i])->orientation.getx(),
							((SeaWarsPlayer*)Entities[i])->orientation.gety(),
							((SeaWarsPlayer*)Entities[i])->orientation.getz()+((SeaWarsPlayer*)Entities[i])->geometry_bounds[5]-1);				
						
						Vector to=subtract(((SeaWarsPlayer*)Entities[i])->sniperview, ((SeaWarsPlayer*)Entities[i])->current);
						to.scale(100);
						to=add(to,((SeaWarsPlayer*)Entities[i])->current);
						glVertex3f(
							to.getx(),
							to.gety(),
							to.getz()+((SeaWarsPlayer*)Entities[i])->geometry_bounds[5]-1);
					glEnd();
					glLineWidth(1);
			}
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);

}

void display_world()
{
	for(int i=0; i<SW_IDS-2; i++)
		if(Entities[i]!=NULL){
			unsigned int texid=txt_of_entity(i);
			bool flag=glIsTexture(texid);
			if(flag){
				glEnable(GL_TEXTURE_2D);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glBindTexture(GL_TEXTURE_2D, sw_textures[texid]);				
			}
			Entities[i]->display();
			if(flag) glDisable(GL_TEXTURE_2D);
		}
		
		
		
		
}

void InitialisePresents()
{
	for(int i=0; i<SW_BOXES; i++){
		int j=SW_BOX1+i;
	Entities[j]=new Box(j,true);
	Entities[j]->geometry=&sw_models[SW_BOXMDL];
	Entities[j]->geometry->get_boundaries(Entities[j]->geometry_bounds);
	Entities[j]->stuff=&sw_materials[SW_CRT];
	Entities[j]->chaindesign(0,&sw_materials[SW_CRT]);
	((Box*)Entities[j])->reset(Randomise("BOX"));
	}
}

void InitialisePlayers()
{
	int keys[SW_PLAYER_CONTROLS]=SW_PLAYER1KEYS;	
	Entities[SW_PLAYER1]=new SeaWarsPlayer(SW_PLAYER1,keys,true);
	Entities[SW_PLAYER1]->geometry=&sw_models[SW_PLMDL];
	Entities[SW_PLAYER1]->stuff=&sw_materials[SW_PL1];
	Entities[SW_PLAYER1]->geometry->get_boundaries(Entities[SW_PLAYER1]->geometry_bounds);
	Entities[SW_PLAYER1]->current.set_coords(700,-700,0);
	Entities[SW_PLAYER1]->rotationangle=-135;
	Entities[SW_PLAYER1]->quad(Entities[SW_PLAYER1]->current,Entities[SW_PLAYER1]->geometry->get_origin(),Entities[SW_PLAYER1]->currentquad);
	Entities[SW_PLAYER1]->mark(Entities[SW_PLAYER1]->currentquad);
	Entities[SW_PLAYER1]->chaindesign(0,&sw_materials[SW_PL1]);
	((SeaWarsPlayer*)Entities[SW_PLAYER1])->orient();
	((SeaWarsPlayer*)Entities[SW_PLAYER1])->alternate=&sw_models[SW_TPT];

	int keys2[SW_PLAYER_CONTROLS]=SW_PLAYER2KEYS;
	Entities[SW_PLAYER2]=new SeaWarsPlayer(SW_PLAYER2,keys2,true);
	Entities[SW_PLAYER2]->geometry=&sw_models[SW_PLMDL];
	Entities[SW_PLAYER2]->stuff=&sw_materials[SW_PL2];
	Entities[SW_PLAYER2]->geometry->get_boundaries(Entities[SW_PLAYER2]->geometry_bounds);
	Entities[SW_PLAYER2]->current.set_coords(-700,700,0);
	Entities[SW_PLAYER2]->rotationangle=45;
	Entities[SW_PLAYER2]->quad(Entities[SW_PLAYER2]->current,Entities[SW_PLAYER2]->geometry->get_origin(),Entities[SW_PLAYER2]->currentquad);
	Entities[SW_PLAYER2]->mark(Entities[SW_PLAYER2]->currentquad);
	Entities[SW_PLAYER2]->chaindesign(0,&sw_materials[SW_PL2]);
	((SeaWarsPlayer*)Entities[SW_PLAYER2])->orient();
	((SeaWarsPlayer*)Entities[SW_PLAYER2])->alternate=&sw_models[SW_TPT];

}

void InitialiseMissiles()
{
	Entities[SW_PLAYER1FIRE]= new SeaWarsProjectile(SW_PLAYER1FIRE,SW_PLAYER1,true);
	Entities[SW_PLAYER1FIRE]->geometry=&sw_models[SW_PLPRJMDL];
	Entities[SW_PLAYER1FIRE]->geometry->get_boundaries(Entities[SW_PLAYER1FIRE]->geometry_bounds);
	Entities[SW_PLAYER1FIRE]->stuff=&sw_materials[SW_PL1PRJ];
	Entities[SW_PLAYER1FIRE]->chaindesign(0,&sw_materials[SW_PL1PRJ]);

	Entities[SW_PLAYER2FIRE]= new SeaWarsProjectile(SW_PLAYER2FIRE,SW_PLAYER2,true);
	Entities[SW_PLAYER2FIRE]->geometry=&sw_models[SW_PLPRJMDL];
	Entities[SW_PLAYER2FIRE]->geometry->get_boundaries(Entities[SW_PLAYER2FIRE]->geometry_bounds);
	Entities[SW_PLAYER2FIRE]->stuff=&sw_materials[SW_PL2PRJ];
	Entities[SW_PLAYER2FIRE]->chaindesign(0,&sw_materials[SW_PL2PRJ]);
}
void InitialiseSnipers()
{
	float now=glfwGetTime();

	Entities[SW_PLAYER1SNIPER]=new Snipershot(SW_PLAYER1SNIPER,SW_PLAYER1,true);
	Entities[SW_PLAYER1SNIPER]->geometry=&sw_models[SW_CUBE];
	Entities[SW_PLAYER1SNIPER]->geometry->get_boundaries(Entities[SW_PLAYER1SNIPER]->geometry_bounds);
	((Snipershot*)Entities[SW_PLAYER1SNIPER])->when=now;


	Entities[SW_PLAYER2SNIPER]=new Snipershot(SW_PLAYER2SNIPER,SW_PLAYER2,true);
	Entities[SW_PLAYER2SNIPER]->geometry=&sw_models[SW_CUBE];
	Entities[SW_PLAYER2SNIPER]->geometry->get_boundaries(Entities[SW_PLAYER2SNIPER]->geometry_bounds);
	((Snipershot*)Entities[SW_PLAYER2SNIPER])->when=now;


}
