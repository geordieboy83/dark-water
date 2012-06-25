#include "GUI.h"

extern SoundSystem* GUISounds;
extern FontSystem* GUIFonts;
extern UITexturing* GUITextures;
extern UIScreens* GUIScreens;
extern UIEvents* GUIEvents;
extern CreditsScreen* GUICredits;

GUI::GUI():
PATH(//PhysicsWorld::getPhysicsWorld()->projectDir + 
	"assets\\UI\\")
{
	Sounds=new SoundSystem(PATH+SOUND_FILE,0);
	Fonts=new FontSystem(PATH+FONT_FILE);
	Credits=new CreditsScreen(//PATH+CREDITS_VIDEO,
		PATH+CREDITS_TEXT);

	GUISounds=Sounds;
	GUITextures=&Textures;
	GUIScreens=&Screens;
	GUIEvents=&Events;
	GUICredits=Credits;
	GUIFonts=Fonts;

	load_ui_textures(&Textures);
	init_events(&Events);
	
	configure_screens();
}

GUI::~GUI()
{
	delete Sounds;
	delete Credits;
	delete Fonts;		
}

bool GUI::get_button(string button_id, string layout_id)
{
	if(Screens.current==NULL||Screens.current->get_ID()!=layout_id) return false;
	return Screens.current->report_boolean(button_id);
}

bool GUI::off_game()
{
	Screens.activate("MAIN MENU");
	int w,h;
	glfwGetWindowSize(&w,&h);
	glViewport(0,0,w,h);
	do{
		Screens.update();
		Screens.display();
		glfwSwapBuffers();		
	}while (glfwGetWindowParam( GLFW_OPENED ) && !get_button("NEW","MAIN MENU") && !get_button("EXIT","MAIN MENU"));
	//writeuser();
	Screens.current->stop_bgm();
	if(get_button("NEW","MAIN MENU")) return true;
	else return false;
}

bool GUI::pause_game()
{
	Screens.activate("PAUSE");
	int w,h;
	glfwGetWindowSize(&w,&h);
	glViewport(0,0,w,h);
	do{
		if(Screens.current->get_ID()=="MAIN MENU") Screens.activate("PAUSE");
		Screens.update();
		Screens.display();
		glfwSwapBuffers();		
	}while (glfwGetWindowParam( GLFW_OPENED ) && !get_button("NEW","PAUSE") && !get_button("EXIT","PAUSE"));
	//writeuser();
	Screens.current->stop_bgm();
	if(get_button("NEW","PAUSE")) return true;
	else return false;
}

bool GUI::game_over()
{
	Screens.activate("GAME OVER");
	int w,h;
	glfwGetWindowSize(&w,&h);
	glViewport(0,0,w,h);
	do{
		if(Screens.current->get_ID()=="MAIN MENU") Screens.activate("GAME OVER");
		Screens.update();
		Screens.display();
		glfwSwapBuffers();
	}while (glfwGetWindowParam( GLFW_OPENED )// && !get_button("NEW","MAIN MENU")
		&& !get_button("EXIT","GAME OVER"));
	//writeuser();
	Screens.current->stop_bgm();
	//if(get_button("NEW","MAIN MENU")) return true;
	//else
	return false;
}



bool GUI::in_game()
{
	Screens.activate("IN GAME");
	int w,h;
	glfwGetWindowSize(&w,&h);
	glViewport(0,0,w,h);
	do{
		Screens.update();
		Screens.display();
		glfwSwapBuffers();		
	}while (glfwGetWindowParam( GLFW_OPENED ) && !get_button("IN_YES","IN GAME") && !get_button("IN_NO","IN GAME"));
	if(get_button("IN_YES","IN GAME")) return true;
	else return false;
}