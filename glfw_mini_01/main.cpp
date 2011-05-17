using namespace std;

#include <GL\glfw.h>
#include "Universe.h"
#include "UI.h"

extern GLuint wtrshdr;
GLuint wtrshdrhandle;
extern float minimap_colours[MINIMAP_COLOURS][4];
extern Entity* Entities[IDS-2];
extern FTGLPixmapFont* font;
extern GLPolygon models[];
extern float pos[];
extern bool endgame;
extern report reports[];
extern int NumberofIsles;

bool has_audio;

extern SoundSystem* Audio;

bool cheats=false;
bool paused=false;
bool pausedbeforeexit=false;
int running = GL_TRUE;
ALuint bgm;

void reinforcements()
{
	for(int i=FIRST_BOX; i<=LAST_BOX; i++){
		if(!((Box*)Entities[i])->alive){
			((Box*)Entities[i])->reset(Randomise("BOX"));
			return;
		}
	}
}

void reset()
{
	for(int i=0; i<IDS-2; i++)
		if(Entities[i]!=NULL){
			Entities[i]->unmark(Entities[i]->currentquad);
			delete Entities[i];
		}
	glInitialise();
}

void GLFWCALL key(int key, int action)
{
	if(action == GLFW_RELEASE) return;
	
	if(cheats) switch(key){

		case GLFW_KEY_F1:
			//HEALTH
			if(Audio) Audio->ambient("GIFT_YES");
			Entities[PLAYER1]->wound(-25);
			break;
		
		case GLFW_KEY_F2:			
			//POISON
			if(Audio) Audio->ambient("GIFT_NO");
			Entities[PLAYER1]->wound(25);
			break;

		case GLFW_KEY_F3:
			//TRANSFORMATION
			if(Audio) Audio->ambient("GIFT_TPT");
			((Player*)Entities[PLAYER1])->transform();
			break;

		case GLFW_KEY_F4:
			//BLUE SCREEN OF DEATH
			BSOD();
			break;

		case GLFW_KEY_F5:
			//ULTIMATE ARTIFACT
			if(Audio) Audio->ambient("GIFT_ULTIMATE");
			((Player*)Entities[PLAYER1])->ultimateartifact=true;
			((Player*)Entities[PLAYER1])->updatedependencies();
			break;
				
		case GLFW_KEY_F6:
			//DOUBLE DAMAGE
			if(Audio) Audio->ambient("GIFT_ULTIMATE");
			((Player*)Entities[PLAYER1])->doubledamage=true;
			((Player*)Entities[PLAYER1])->ddstart=glfwGetTime();
			((Player*)Entities[PLAYER1])->updatedependencies();
			break;

		case GLFW_KEY_F7:
			//RAPID FIRE
			if(Audio) Audio->ambient("GIFT_ULTIMATE");
			((Player*)Entities[PLAYER1])->rapidfire=true;
			((Player*)Entities[PLAYER1])->rfstart=glfwGetTime();
			((Player*)Entities[PLAYER1])->updatedependencies();
			break;
				
		case GLFW_KEY_F8:			
			//PLAGUE
			if(Audio) Audio->ambient("GIFT_NO");
			Entities[PLAYER1]->wound(50);
			break;

		case '1':
			//HEALTH
			if(Audio) Audio->ambient("GIFT_YES");
			Entities[PLAYER2]->wound(-25);
			break;
		
		case '2':			
			//POISON
			if(Audio) Audio->ambient("GIFT_NO");
			Entities[PLAYER2]->wound(25);
			break;

		case '3':
			//TRANSFORMATION
			if(Audio) Audio->ambient("GIFT_TPT");
			((Player*)Entities[PLAYER2])->transform();
			break;

		case '4':
			//BLUE SCREEN OF DEATH
			BSOD();
			break;

		case '5':
			//ULTIMATE ARTIFACT
			if(Audio) Audio->ambient("GIFT_ULTIMATE");
			((Player*)Entities[PLAYER2])->ultimateartifact=true;
			((Player*)Entities[PLAYER2])->updatedependencies();
			break;
				
		case '6':
			//DOUBLE DAMAGE
			if(Audio) Audio->ambient("GIFT_ULTIMATE");
			((Player*)Entities[PLAYER2])->doubledamage=true;
			((Player*)Entities[PLAYER2])->ddstart=glfwGetTime();
			((Player*)Entities[PLAYER2])->updatedependencies();
			break;

		case '7':
			//RAPID FIRE
			if(Audio) Audio->ambient("GIFT_ULTIMATE");
			((Player*)Entities[PLAYER2])->rapidfire=true;
			((Player*)Entities[PLAYER2])->rfstart=glfwGetTime();
			((Player*)Entities[PLAYER2])->updatedependencies();
			break;
				
		case '8':			
			//PLAGUE
			if(Audio) Audio->ambient("GIFT_NO");
			Entities[PLAYER2]->wound(50);
			break;

		case GLFW_KEY_F12:
			for(int i=FIRST_BOX; i<=LAST_BOX; i++){
				if(!((Box*)Entities[i])->alive){
				((Box*)Entities[i])->reset(Randomise("BOX"));
				}
			}
			break;

	}

	switch(key) {

		case GLFW_KEY_F9:
			save();
			break;
		
		case GLFW_KEY_F10:
			load();
			break;
		
		case GLFW_KEY_F11:
			cheats=!cheats;
			break;
		
		case GLFW_KEY_PAUSE:
			if(pausedbeforeexit) pausedbeforeexit=false;
			else paused=!paused;
			break;

		case GLFW_KEY_ESC:
			if(paused){
				paused=false;
				break;
			}
			if(endgame||pausedbeforeexit) running=GL_FALSE;
			pausedbeforeexit=!pausedbeforeexit;
			break;
		case 'N':
			if(endgame||pausedbeforeexit){
				reset();
				if(endgame){
					endgame=false;
					if(has_audio){
						Audio->stop(bgm);
						bgm=Audio->ambientloop("BGM");
					}
				}
				if(pausedbeforeexit) pausedbeforeexit=false;
				break;
			}
	}	

}

int main(void)
{
	

	has_audio=alutInit(NULL,NULL);
	

	// Initialise GLFW
	if( !glfwInit() )
	{
		exit( EXIT_FAILURE );
	}
	
		

	// Open an OpenGL window
	//if( !glfwOpenWindow( WINDOW_X,WINDOW_Y, 0,0,0,0,0,0, GLFW_WINDOW) )
	if( !glfwOpenWindow( WINDOW_X,WINDOW_Y, 0,0,0,0,0,0, GLFW_FULLSCREEN) )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	srand(time(NULL));
	
	if(has_audio) {
		Audio = new SoundSystem("../Resources/Audio.txt",0);
	}

	glfwSetWindowTitle( "Dark Water");
	glfwSwapInterval(1);
		
	FTGLPixmapFont GameFont("..\\Resources\\TT1141M.ttf");
	font=&GameFont;


	NumberofIsles=1;
	glLoadTextures();
	loadingscreen("");
	initialise();
	glInitialise();
		
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
		
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//bool saving=false;
	//bool loading=false;
	
	glfwSetKeyCallback(key);
	
	//ALuint bgm;
	if(has_audio) {
		bgm=Audio->ambientloop("BGM");
		Audio->ambientloop("OCEAN",FX_VOLUME);
	}

	// Main loop
	while( running )
	{
		
		glClear(GL_COLOR_BUFFER_BIT);
		/*if(!endgame&&(!reports[PLAYER1].alive||!reports[PLAYER2].alive)){ 
			endgame=true;
			if(has_audio){
				Audio->stop(bgm);
				bgm=Audio->ambient("END");
			}
		}*/
		if(!endgame&&!paused&&!pausedbeforeexit){

			update_world();

			if(//!endgame&&(
				!reports[PLAYER1].alive||!reports[PLAYER2].alive//)
				){ 
			endgame=true;
			if(has_audio){
				Audio->stop(bgm);
				bgm=Audio->ambient("END");
			}
		}


		}
		update_landscape();

		glViewport(0,0,WINDOW_X,WINDOW_Y);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	
		((Player*)Entities[PLAYER1])->glProjection(WINDOW_X*0.5,0,WINDOW_X*0.5,WINDOW_Y);
		
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		scenery();
		display_world();
		lasers();

		((Player*)Entities[PLAYER2])->glProjection(0,0,WINDOW_X*0.5,WINDOW_Y);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		scenery();
		display_world();
		lasers();


		minimap((int)(0.5*WINDOW_X*0.875),0,WINDOW_X*0.125,WINDOW_X*0.125);

		summarise();
		
		// Swap front and back rendering buffers
		glfwSwapBuffers();

		// Check if ESC key	was pressed or window was closed
		if(running) running = //!glfwGetKey( GLFW_KEY_ESC ) &&
						glfwGetWindowParam( GLFW_OPENED );
	}

	// Close window and terminate GLFW
	glfwTerminate();

	for(int i=0; i<IDS-2; i++) if(Entities[i]!=NULL) delete Entities[i];
	if(Audio) delete Audio;

	// Exit program
	exit( EXIT_SUCCESS );
}
