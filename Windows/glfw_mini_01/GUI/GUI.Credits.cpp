#include "GUI.Credits.h"

extern SoundSystem* GUISounds;
extern FontSystem* GUIFonts;

//CreditsScreen::CreditsScreen(string videofile, string creditsfile):
//credits(creditsfile),total(""),individual(), avi(videofile),//video(videofile),
//	effect(CREDITS_ROLL),
//	font(NULL)
//{
//	read_text();
//}

CreditsScreen::CreditsScreen(string creditsfile):
credits(creditsfile),total(""),individual(),
	effect(CREDITS_ROLL),
	font(NULL)
{
	read_text();
}

void CreditsScreen::read_text()
{
	if(credits=="") return;
	ifstream in(credits);	
	string s;
	while(getline(in,s)){
		total=total+s+"\n";
		individual.push_back(s+"\n");
	}
	in.close();
}

void CreditsScreen::trigger()
{
	if(font==NULL||total=="") return;	

	saveGL();

	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	animation_start=glfwGetTime();

	glPushMatrix();
	
	ALuint sth;

	//AviVideo aviPlayer(avi);
	//
	////refresh timer after every 0.5 secs...
	//FpsTimer fpsTimer(0.5);
	//fpsTimer.Start();

	Pixel diff(to.x-from.x,to.y-from.y);
	
	int w,h;
	glfwGetWindowSize(&w,&h);

	float yfactor=h/720.f;
	
	Button back;
	back.set_text("Back");
	back.set_font("FORMAL_PL",35*yfactor);
	back.invisibility();
	back.lower_left(Pixel(0.025*w,0.025*h));
	back.set_non_unclickable();

	if(GUISounds!=NULL) sth=GUISounds->ambient("CREDITS");
	
	bool running=true;
		
	glClearColor(0,0,0,0);
	do{
		float now=min(1.f,(float)((glfwGetTime()-animation_start)/animation_duration));

		if(now>=1)
			back.update();
		
		////update the timer
		//fpsTimer.Update();

		////update the player
		//aviPlayer.Update (fpsTimer.lastFrameDuration*1000);		
				
		// OpenGL rendering goes here ...
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
		//draw a scene on a quad		
		//if(aviPlayer.pgf) aviPlayer.DrawAvi();
		
		glDisable(GL_TEXTURE_2D);
				
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,w,0,h,-5,5);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		if(now>=1) 		
			back.display();		
		
		glColor3f(1,1,1);
		glTranslatef(from.x+diff.x*now,from.y+diff.y*now,0);
		text.Render(total.c_str());
		
		glEnable(GL_TEXTURE_2D);
		
		glfwSwapBuffers();
		
		running = (!back.get_value()&&
			!(glfwGetKey( GLFW_KEY_SPACE ))&&
			glfwGetWindowParam( GLFW_OPENED ));


	} while(running);
	if(GUISounds!=NULL) GUISounds->stop(sth);

	//aviPlayer.CloseAVI();
	glPopMatrix();
	GUIFonts->reset();

	restoreGL();
}