//using namespace std;


//#include <GL\glfw.h>
//#include <FTGL\ftgl.h>
//#include <cyclone\cyclone.h>
//#include <iostream>
//#include <Courseworx\Globals.h>
//#include "Player.h"
//#include "Present.h"
//#include "Projectile.h"
//#include "Isle.h"

#include "Psysixmain.h"

using namespace cyclone;

extern GLPolygon models[MODELS];
extern material materials[];
extern FTGLPixmapFont font;
extern int WINDOW_X, WINDOW_Y;

//Wind speed
Vector3 windspeed;

//Default liquid: sea water
float liquid_density=1025;

//For randomisation
Random r; 

//For Delta-t
float previous, now;

//The occupants of the world
Player* Plr;
Isle* Isl;
Present* Gifts[BOXES];

//Number of opponents left
int NumberOfIsles=3;

//Time since last giftbox emerged
float BoxingTime;

//The current liquid
extern string SEA_TYPE;

//Camera position
unsigned int camera=3;

//Whether we draw bounding spheres/boxes
bool grids1=false, grids2=false;

//Whether the player is near a volcano
bool flag=false;

//Creating the occupants of the world
void setup()
{
	//Initialise player
	int keys1[]=PLAYER1KEYS;
	Plr=new Player(keys1);
	Plr->set();

	//Create and assign player display list
	models[PLMDL].chaindesign(0,&materials[PL1MTL]); Plr->living=models[PLMDL].get_list();	
	int j=PL1MTL;

	//Create and assign player death display list
	GLPolygon* current=&models[PLMDL];
	Plr->carcass=glGenLists(1);
	glNewList(Plr->carcass,GL_COMPILE);		
		glPushAttrib(GL_POLYGON_BIT);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glLineWidth(1);
		while(current!=NULL){			
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials[j].Ka);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials[j].Kd);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materials[j].Ks);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materials[j].Ns);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materials[j].Ke);
			current->objdisplay(0);
			current=current->next;
			j++;
		}
		glPopAttrib();
	glEndList();

	//Player draw material assignment
	Plr->material_index=PL1MTL;
	

	//Design, assign and initialise the island and its boulders
	models[ISLEMDL].chaindesign(0,&materials[ISLMTL]);
	models[ISLPRJMDL].chaindesign(0,&materials[ISLMTL]);
	Isl=new Isle();
	Isl->reset();
	
	//Design and initialise the giftboxes
	models[BOXMDL].chaindesign(0,&materials[BOXMTL]);	
	for(int i=0; i<BOXES; i++) Gifts[i]=new Present();
}

//General hotkeys
void key()
{
	//Sea of sea water
	if(glfwGetKey(GLFW_KEY_F1)){
		liquid_density=1025;
		SEA_TYPE="WATER";
		Plr->reliquidate("WATER");
		for(int i=0; i<BOXES; i++) Gifts[i]->reliquidate("WATER");
	}

	//Sea of mercury
	if(glfwGetKey(GLFW_KEY_F2)){
		liquid_density=13590;
		SEA_TYPE="MERCURY";
		Plr->reliquidate("MERCURY");
		for(int i=0; i<BOXES; i++) Gifts[i]->reliquidate("MERCURY");
	}

	//Sea of paraffin
	if(glfwGetKey(GLFW_KEY_F3)){
		liquid_density=800;
		SEA_TYPE="PARAFFIN";
		Plr->reliquidate("PARAFFIN");
		for(int i=0; i<BOXES; i++) Gifts[i]->reliquidate("PARAFFIN");
	}

	//Top-down view
	if(glfwGetKey(GLFW_KEY_F4)){
		camera=0;
	}
	
	//Isometric view 1
	if(glfwGetKey(GLFW_KEY_F5)){
		camera=1;
	}

	//Isometric view 2
	if(glfwGetKey(GLFW_KEY_F6)){
		camera=2;
	}

	//Isometric view 3
	if(glfwGetKey(GLFW_KEY_F7)){
		camera=3;
	}

	//Enable bounding sphere depiction
	if(glfwGetKey(GLFW_KEY_F8)){
		grids1=true;
	}

	//Enable player bounding box / island coastline sphere depiction
	if(glfwGetKey(GLFW_KEY_F9)){
		grids2=true;
	}
	
	//Disable bounding primitive depiction
	if(glfwGetKey(GLFW_KEY_F10)){
		grids1=false;
		grids2=false;
	}
}


//Collision detection and resolution
void generateContacts()
{
   
	// Set up the collision data structure. As in Millington's demo.
	CollisionData cData;
	//100 possible contacts. Doesn't really matter, because we are not interested in them.
	Contact cts[100];
	cData.contactArray=&cts[0];
	cData.reset(100);	
    cData.friction = (cyclone::real)0.9;
    cData.restitution = (cyclone::real)0.1;
    cData.tolerance = (cyclone::real)0.1;

	//If collision data stracture is full, we can't detect other contacts.
	if (!cData.hasMoreContacts()) return;
	
	//Is the player within the volcano's coastline?
	if(CollisionDetector::boxAndSphere(Plr->hull,Isl->coastline,&cData)){
		flag=true;	//Yes.

		//If the volcano is alive and not in the process of emerging
		if(!Isl->dead&&Isl->currentheight>=0){	   
			//If the player touches the volcano itself
			if(CollisionDetector::boxAndSphere(Plr->hull,*Isl,&cData))
				Plr->dead=true; //Dies.
			//If the player does not touch the volcano, but is still within its coastline.
			else{
				//Half speed.
				real damp=Plr->boat.body.getLinearDamping();
				damp=real_pow(0.5f,(float)(now-previous));
				Vector3 vel=Plr->boat.body.getVelocity();
				Plr->boat.body.setVelocity(vel.x*damp,vel.y,vel.z*damp);
			}
	   }
    }
	else flag=false; //The player is not near the volcano

	//All projectiles of the player...
	for(int i=0; i<AMMO; i++)
		//...that have been fired...
		if(Plr->ammo[i].used)
			//...wound the island if they touch it and expire.
			if(IntersectionTests::sphereAndSphere(Plr->ammo[i],*Isl)){
				Isl->wound(20);
				Plr->ammo[i].used=false;
		   };

	//All boulders of the volcano...
	for(int i=0; i<BOULDERS; i++)
		//...that have been launched...
		if(Isl->boulders[i].used)
			//...and crash into the player...
			if(IntersectionTests::sphereAndSphere(Plr->csphere,Isl->boulders[i]))
				//...either on the hull, the mast or the sail...
				if(CollisionDetector::boxAndSphere(Plr->hull,Isl->boulders[i],&cData)||
				   CollisionDetector::boxAndSphere(Plr->mast,Isl->boulders[i],&cData)||
				   CollisionDetector::boxAndSphere(Plr->sail,Isl->boulders[i],&cData)){
					   //...wound the player and expire.
					   Plr->wound(35);
					   Isl->boulders[i].used=false;
		   };

   	//All giftboxes...
	for(int i=0;i<BOXES; i++)
		//...that are in use...
		if(Gifts[i]->used)
			//...if touched by the player...
			if(CollisionDetector::boxAndSphere(Plr->hull,Gifts[i]->csphere,&cData)){
				//...are picked up, affect them and expire.
				Plr->affect(Gifts[i]->effect);
				Gifts[i]->used=false;
	}
}

//The giftbox mechanism
void reinforcements()
{
	//If no giftbox has emerged in the past 30 seconds...
	if(now-BoxingTime<30) return;
	//...find an empty one...
	int i;
	for (i=0; i<BOXES; i++)	if (!Gifts[i]->used) break;
    if (i >= BOXES) return; //No empty boxes.
	//Reset and launch the box.
	Gifts[i]->reset();
	//We cannot attempt this for another 30 seconds.
	BoxingTime=glfwGetTime();	
}

//Displays text on the screen.
void report()
{
	
	char buffer[256];
	Vector3 pos=Plr->boat.body.getPosition();

	font.FaceSize(24);
	
	//Red text
	glPixelTransferf(GL_GREEN_BIAS, -1.0f);
	glPixelTransferf(GL_BLUE_BIAS, -1.0f);
	
	//If near the edge of the world
	sprintf(buffer,"UNCHARTED WATERS!");
	if(WORLD_TO-200 < pos.x || WORLD_FROM+200 >pos.x|| WORLD_TO-200 < pos.z || WORLD_FROM+200 >pos.z)
		font.Render(buffer,-1,stringseed(buffer,Vertex(WINDOW_X*0.5,25,0)));	

	//If within the volcano's coastline
	if(flag){
		sprintf(buffer,"VOLCANO NEARBY!");
		font.Render(buffer,-1,stringseed(buffer,Vertex(WINDOW_X*0.5,25,0)));}
	
	//White text
	glPixelTransferf(GL_RED_BIAS, -0.0f);
	glPixelTransferf(GL_GREEN_BIAS, -0.0f);
	glPixelTransferf(GL_BLUE_BIAS, -0.0f);
	
	
	//Player health, opponent health, player position and speed
	
	sprintf(buffer,"You: %d", Plr->HP);
	font.Render(buffer,-1,FTPoint(10,WINDOW_Y-30));
	if(!Plr->victor){
		sprintf(buffer,"They: %d", Isl->HP+(NumberOfIsles-1)*Isl->get_maxHP());
		font.Render(buffer,-1,FTPoint(10,WINDOW_Y-60));
	}
	
	font.FaceSize(16);
		
	sprintf(buffer, "Your position: (%.1f, %.1f, %.1f)", pos.x,	pos.y, pos.z);
	
	font.Render(buffer,-1,FTPoint(WINDOW_X*0.666,WINDOW_Y-30));

    sprintf(buffer,"Your speed: %.1f",Plr->boat.body.getVelocity().magnitude());
	font.Render(buffer,-1,FTPoint(WINDOW_X*0.666,WINDOW_Y-60));
	
	//End of game text.
	
	if(Plr->dead) //Defeat
	{
		font.FaceSize(72);
		font.Render("YOU LOSE!",-1,stringseed("YOU LOSE!",Vertex(WINDOW_X*0.5,WINDOW_Y*0.5,0)));
	}

	if(Plr->victor) //Victory
	{
		font.FaceSize(72);
		font.Render("YOU WIN!",-1,stringseed("YOU WIN!",Vertex(WINDOW_X*0.5,WINDOW_Y*0.5,0)));
	}
}


void Physixmain()
{
	//Initialise the sea grid and load models.
	initialise();
	
	/********************************************************************************************/
	
	
	int running = GL_TRUE;

	// Initialise GLFW
	if( !glfwInit() )
	{
		exit( EXIT_FAILURE );
	}
		
	// Open an OpenGL window
	//if( !glfwOpenWindow( WINDOW_X,WINDOW_Y, 0,0,0,0,0,0, GLFW_WINDOW) ) //Windowed mode
	if( !glfwOpenWindow( WINDOW_X,WINDOW_Y, 0,0,0,0,0,0, GLFW_FULLSCREEN) ) //Fullscreen mode
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	//Load textures;
	glLoadTextures();
	
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);		
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Create the occupands of the world
	setup();	
	
	glClearColor(0,0.3,0.8,1);

	//Set time variables
	previous=glfwGetTime();	
	BoxingTime=glfwGetTime();
	
	// Main loop
	while( running )
	{

		//Current time
		now=glfwGetTime();

		//General hotkey input
		key();

		//Generate giftbox?
		reinforcements();

		//Update the player,...
		Plr->update();
		//...the giftboxes...
		for(int i=0; i<BOXES; i++) Gifts[i]->update();
		//...and the island(s).
		Isl->update();
		if(Isl->dead&&!Isl->active){
			//Killed one of the islands.
			NumberOfIsles--;
			//If it was the last,...
			if(NumberOfIsles>0) Isl->reset();
			//...you have won.
			else Plr->victor=true;
		}
		
		//Update the windspeed
		windspeed = windspeed * 0.9f + r.randomXZVector(1.0f);
		//Update the landscape
		update_landscape();

		//Check for collisions
		generateContacts();
		
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,WINDOW_X,WINDOW_Y);

		//Set up view
		glProjection(WINDOW_X,WINDOW_Y,camera,Plr->boat.body);

		//Draw world
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		scenery();
		Plr->display();
		for(int i=0; i<BOXES; i++) Gifts[i]->display();
		Isl->display();

		//Report
		report();		
		
		// Swap front and back rendering buffers
		glfwSwapBuffers();

		// Check if ESC key	was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
					glfwGetWindowParam( GLFW_OPENED );

		//Update timers
		previous=now;
	}

	// Close window and terminate GLFW
	glfwTerminate();

	//Clean up
	delete Plr;
	delete Isl;
	for(int i=0;i<BOXES;i++)delete Gifts[i];

	// Exit program
	exit( EXIT_SUCCESS );

}