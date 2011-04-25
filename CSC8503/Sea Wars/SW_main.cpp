using namespace std;

//#include <GL/glew.h>
//#include <GL\glfw.h>
//#include "SW_Universe.h"
//#include "SW_UI.h"
#include "SW_main.h"

extern GLuint wtrshdr;
GLuint wtrshdrhandle;
extern float minimap_colours[SW_MINIMAP_COLOURS][4];
extern Entity* Entities[SW_IDS-2];
extern FTGLPixmapFont font;
extern GLPolygon models[];
extern float pos[];
//extern bool singleplayer;
extern bool endgame;
extern state//report
	reports[];
extern int NumberofIsles;
extern int SW_WINDOW_X, SW_WINDOW_Y;



int SW_main(void)
{
	int running = GL_TRUE;

	// Initialise GLFW
	if( !glfwInit() )
	{
		exit( EXIT_FAILURE );
	}
	
	
	

	// Open an OpenGL window
	if( !glfwOpenWindow( SW_WINDOW_X,SW_WINDOW_Y, 0,0,0,0,0,0, GLFW_WINDOW) )
	//if( !glfwOpenWindow( WINDOW_X,WINDOW_Y, 0,0,0,0,0,0, GLFW_FULLSCREEN) )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	srand(time(NULL));
	
	
		

	glfwSetWindowTitle( "Dark Water");
	glfwSwapInterval(1);
		



	NumberofIsles=1;
	sw_glLoadTextures();
	loadingscreen();
	sw_initialise();
	sw_glInitialise();	
		
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
		
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	bool saving=false;
	bool loading=false;
	
	// Main loop
	while( running )
	{
		
		if(glfwGetKey(GLFW_KEY_F1))
		//HEALTH
		Entities[SW_PLAYER1]->wound(-25);
		
		if(glfwGetKey(GLFW_KEY_F2))			
		//POISON
		Entities[SW_PLAYER1]->wound(25);

		if(glfwGetKey(GLFW_KEY_F3))
		//TRANSFORMATION
		((SeaWarsPlayer*)Entities[SW_PLAYER1])->transform();

		if(glfwGetKey(GLFW_KEY_F4))
		//BLUE SCREEN OF DEATH
		sw_BSOD();

		if(glfwGetKey(GLFW_KEY_F5)){
		//ULTIMATE ARTIFACT
		((SeaWarsPlayer*)Entities[SW_PLAYER1])->ultimateartifact=true;
		((SeaWarsPlayer*)Entities[SW_PLAYER1])->updatedependencies();}
				
		if(glfwGetKey(GLFW_KEY_F6)){
		//DOUBLE DAMAGE
		((SeaWarsPlayer*)Entities[SW_PLAYER1])->doubledamage=true;
				((SeaWarsPlayer*)Entities[SW_PLAYER1])->ddstart=glfwGetTime();
				((SeaWarsPlayer*)Entities[SW_PLAYER1])->updatedependencies();}

		if(glfwGetKey(GLFW_KEY_F7)){
		//RAPID FIRE
		 ((SeaWarsPlayer*)Entities[SW_PLAYER1])->rapidfire=true;
				((SeaWarsPlayer*)Entities[SW_PLAYER1])->rfstart=glfwGetTime();
				((SeaWarsPlayer*)Entities[SW_PLAYER1])->updatedependencies();}
				


		if(glfwGetKey(GLFW_KEY_F8))			
		//PLAGUE
		Entities[SW_PLAYER1]->wound(50);

		

		if(glfwGetKey(GLFW_KEY_F9)&&!saving){
			saving=true;
			save();
			saving=false;
		}
		
		if(glfwGetKey(GLFW_KEY_F10)&&!loading){
			loading=true;
			load();
			loading=false;
		}
		
		glClear(GL_COLOR_BUFFER_BIT);
		if(!reports[SW_PLAYER1].alive||!reports[SW_PLAYER2].alive) endgame=true;
		if(!endgame) update_world();
		sw_update_landscape();

		glViewport(0,0,SW_WINDOW_X,SW_WINDOW_Y);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	
		
		//((Player*)Entities[PLAYER1])->glProjection(0,0,WINDOW_X*0.5,WINDOW_Y);
		((SeaWarsPlayer*)Entities[SW_PLAYER1])->glProjection(SW_WINDOW_X*0.5,0,SW_WINDOW_X*0.5,SW_WINDOW_Y);
		
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		sw_scenery();
		display_world();
		lasers();

		//((Player*)Entities[PLAYER2])->glProjection(WINDOW_X*0.5,0,WINDOW_X*0.5,WINDOW_Y);
		((SeaWarsPlayer*)Entities[SW_PLAYER2])->glProjection(0,0,SW_WINDOW_X*0.5,SW_WINDOW_Y);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		sw_scenery();
		display_world();
		lasers();


		minimap((int)(0.5*SW_WINDOW_X*0.875),0,SW_WINDOW_X*0.125,SW_WINDOW_X*0.125);

		summarise(SW_PLAYER1);
		summarise(SW_PLAYER2);
		summariseisles();


		if(endgame) gameover();
	

		// Swap front and back rendering buffers
		glfwSwapBuffers();

		// Check if ESC key	was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
					glfwGetWindowParam( GLFW_OPENED );
	}

	// Close window and terminate GLFW
	glfwTerminate();

	for(int i=0; i<SW_IDS-2; i++) if(Entities[i]!=NULL) delete Entities[i];


	// Exit program
	exit( EXIT_SUCCESS );
}
