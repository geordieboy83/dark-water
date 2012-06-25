#include "GUI.Screens.h"

SoundSystem* GUISounds;
FontSystem* GUIFonts;
UITexturing* GUITextures;
UIScreens* GUIScreens;
UIEvents* GUIEvents;
CreditsScreen* GUICredits;
HighScores Scores;

void load_ui_textures(UITexturing* texdb)
{
	GLuint txs[11];

	string PATH = //PhysicsWorld::getPhysicsWorld()->projectDir + 
		"assets\\UI\\";

	glGenTextures(11,txs);
	glBindTexture(GL_TEXTURE_2D, txs[0]);
	glfwLoadTexture2D((PATH+"logo.tga").c_str(),GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	texdb->add("LOGO",txs[0]);

	glBindTexture(GL_TEXTURE_2D, txs[1]);
	glfwLoadTexture2D((PATH+"background.tga").c_str(),GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	texdb->add("BKG",txs[1]);

	glBindTexture(GL_TEXTURE_2D, txs[2]);
	glfwLoadTexture2D((PATH+"options_menu.tga").c_str(),GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	texdb->add("OPTIONS_MENU",txs[2]);

	glBindTexture(GL_TEXTURE_2D, txs[3]);
	glfwLoadTexture2D((PATH+"options_sub_menu.tga").c_str(),GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	texdb->add("OPTIONS_SUBMENU",txs[3]);

	glBindTexture(GL_TEXTURE_2D, txs[4]);
	glfwLoadTexture2D((PATH+"selection_button.tga").c_str(),GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	texdb->add("SELECTION_BTN",txs[4]);

	glBindTexture(GL_TEXTURE_2D, txs[5]);
	glfwLoadTexture2D((PATH+"selection_circle.tga").c_str(),GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	texdb->add("SELECT_CIRCLE",txs[5]);

	glBindTexture(GL_TEXTURE_2D, txs[6]);
	glfwLoadTexture2D((PATH+"sub_menu_highlight.tga").c_str(),GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	texdb->add("SUBMENU_HIGHLIGHT",txs[6]);

	glBindTexture(GL_TEXTURE_2D, txs[7]);
	glfwLoadTexture2D((PATH+"console_yes.tga").c_str(),GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	texdb->add("CON_YES",txs[7]);

	glBindTexture(GL_TEXTURE_2D, txs[8]);
	glfwLoadTexture2D((PATH+"console_no.tga").c_str(),GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	texdb->add("CON_NO",txs[8]);

	glBindTexture(GL_TEXTURE_2D, txs[9]);
	glfwLoadTexture2D((PATH+"console_sel_yes.tga").c_str(),GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	texdb->add("CON_SEL_YES",txs[9]);

	glBindTexture(GL_TEXTURE_2D, txs[10]);
	glfwLoadTexture2D((PATH+"console_sel_no.tga").c_str(),GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	texdb->add("CON_SEL_NO",txs[10]);
}

void init_events(UIEvents* eventsdb)
{
	/*eventsdb->add("QUIT", &quit);
	eventsdb->add("CREDITS", &cr);
	eventsdb->add("READ", &read);
	eventsdb->add("EMIT", &emit);
	eventsdb->add("READ_USER", &readuser);
	eventsdb->add("WRITE_USER", &writeuser);
	eventsdb->add("READ_SCORES", &readscores);
	eventsdb->add("WRITE_SCORES", &writescores);*/
}

void cr(){ 
	GUIScreens->get("MAIN MENU")->stop_bgm();
	GUICredits->trigger();
}

void quit(){
	glfwTerminate();
	exit( EXIT_SUCCESS );
}

void configure_screens()
{
	int w, h;
	glfwGetWindowSize(&w,&h);
	float xfactor=w/1280.f,yfactor=h/720.f;

	FTBBox bb=GUICredits->configure_text(FTGL::ALIGN_CENTER,((FTPolygonFont*)GUIFonts->get_font("FORMAL_PL",20*yfactor)),w-h-100*xfactor);
	GUICredits->set_animation(Pixel(h+50*xfactor,0),Pixel(h+50*xfactor,h+bb.Upper().Yf()-bb.Lower().Yf()),90);

	//Layout* main_menu=GUIScreens->add("MAIN MENU");	
	//Layout* options_screen=GUIScreens->add("OPTIONS MENU",false);
	//Layout* high_scores=GUIScreens->add("HIGH SCORES", false);
	//Layout* in_game=GUIScreens->add("IN GAME", false);
	//Layout* pause=GUIScreens->add("PAUSE");
	//Layout* game_over=GUIScreens->add("GAME OVER");	


	//design_main_menu(main_menu);	
	//main_menu->get_button("CRD")->set_callback("CREDITS");
	//main_menu->set_event_on_activation(&readuser);
	//main_menu->set_event_on_deactivation(&writeuser);
	//main_menu->set_bgm_id("MAIN");
	//main_menu->get_button("NEW")->set_callback("WRITE_USER");
	//
	//design_options_screen(options_screen);
	//options_screen->set_event_on_activation(&read);
	//options_screen->get_button("OPS_OK")->set_callback(&emit);
	//	
	////design_high_scores(high_scores);
	//string PATH = PhysicsWorld::getPhysicsWorld()->projectDir + "assets\\UI\\";
	//high_scores->load_configuration(PATH+"high_scores.txt");
	////high_scores->set_event_on_activation(&writescores);
	////readscores();

	//design_in_game(in_game);

	//design_pause(pause);
	//pause->get_button("CRD")->set_callback("CREDITS");
	//pause->set_bgm_id("MAIN");

	//design_game_over(game_over);
	//game_over->get_button("CRD")->set_callback("CREDITS");
	//game_over->set_bgm_id("MAIN");

	GUIScreens->current=GUIScreens->get("MAIN MENU");
}


//void design_in_game(Layout* in_game)
//{
//	int w, h;
//	glfwGetWindowSize(&w, &h);
//	float xfactor=w/1280.f, yfactor=h/720.f;
//	string PATH = PhysicsWorld::getPhysicsWorld()->projectDir + "assets\\UI\\";
//
//	Quad* q=in_game->add_quad(2*w/6,2*h/6,2*w/6,2*h/6,"OPTIONS_MENU");
//	
//	Button* b=in_game->add_button(Button("IN_NO","Resume"));
//	b->set_font("FORMAL", 25*yfactor);
//	b->adjust_to_text();
//	int x,y;
//	b->get_size(x,y);
//	b->set_texture(BTN_INACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_texture(BTN_HOVERED,"SUBMENU_HIGHLIGHT");
//	b->set_texture(BTN_PRESSED,"SUBMENU_HIGHLIGHT");
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_non_unclickable();
//	b->set_origin(Pixel(3.5*w/6,2.5*h/6));
//	
//	b=in_game->add_button(Button("IN_YES","Quit"));
//	b->set_font("FORMAL", 25*yfactor);
//	b->set_texture(BTN_INACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_texture(BTN_HOVERED,"SUBMENU_HIGHLIGHT");
//	b->set_texture(BTN_PRESSED,"SUBMENU_HIGHLIGHT");
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_non_unclickable();
//	b->set_origin(Pixel(2.5*w/6,2.5*h/6));	
//	b->set_size(x,y);
//	
//	
//
//	Text* t=in_game->add_text(Text("GAME PAUSED","FORMAL",30*yfactor,Pixel(w/2,3.5*h/6)));
//
//	//in_game->save_configuration(PATH+IN_GAME_CONF);
//}
//
//void design_pause(Layout* main_menu)
//{
//	int w, h;
//	glfwGetWindowSize(&w, &h);
//	float xfactor=w/1280.f, yfactor=h/720.f;
//
//	Quad* qd=main_menu->add_quad(0,0,w,h,"BKG");
//	qd=main_menu->add_quad(4*w/5,0,w/5,h/5,"LOGO");
//
//	Button* btn=main_menu->add_button(Button("NEW","Resume Game"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->set_non_unclickable();
//	btn->lower_left(Pixel(815*xfactor,250*yfactor));
//	btn=main_menu->add_button(Button("HS","High Scores"));
//	
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->lower_left(Pixel(785*xfactor,180*yfactor));
//	LayoutSwitch* ls=main_menu->add_switch("HS","HIGH SCORES");
//	btn=main_menu->add_button(Button("OPS","Options"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->lower_left(Pixel(745*xfactor,115*yfactor));
//	ls=main_menu->add_switch("OPS","OPTIONS MENU");
//	btn=main_menu->add_button(Button("CRD","Credits"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->set_non_unclickable();
//	btn->lower_left(Pixel(30*xfactor,190*yfactor));
//	btn=main_menu->add_button(Button("EXIT","Quit"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->set_non_unclickable();
//	btn->lower_left(Pixel(100*xfactor,125*yfactor));
//	
//	main_menu->add_text(Text("GAME PAUSED","FORMAL",40*yfactor,Pixel(8*w/10,9*h/10)));	
//	
//	/*Console* c=main_menu->add_console(Console("USERNAME",10,"FORMAL",35*yfactor));
//	btn=c->get_trigger();
//	btn->set_text("Not you?");
//	btn->set_origin(Vertex(8.5*w/10,8*h/10));
//	btn->set_font("FORMAL",15*yfactor);
//	
//	btn->invisibility();
//	c->centre(8*w/10,8.5*h/10);	
//	int x, y;
//	c->get_size(x,y);*/
//
//	main_menu->compile_report();
//	string PATH = PhysicsWorld::getPhysicsWorld()->projectDir + "assets\\UI\\";
//	//main_menu->save_configuration(PATH+MAIN_CONF);
//}
//
//void design_game_over(Layout* main_menu)
//{
//	int w, h;
//	glfwGetWindowSize(&w, &h);
//	float xfactor=w/1280.f, yfactor=h/720.f;
//
//	Quad* qd=main_menu->add_quad(0,0,w,h,"BKG");
//	qd=main_menu->add_quad(4*w/5,0,w/5,h/5,"LOGO");
//
//	/*Button* btn=main_menu->add_button(Button("NEW","FlyThis!"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->set_non_unclickable();
//	btn->lower_left(Vertex(815*xfactor,250*yfactor));*/
//
//	Button *btn=main_menu->add_button(Button("HS","High Scores"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->lower_left(Pixel(785*xfactor,180*yfactor));
//	LayoutSwitch* ls=main_menu->add_switch("HS","HIGH SCORES");
//	btn=main_menu->add_button(Button("OPS","Options"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->lower_left(Pixel(745*xfactor,115*yfactor));
//	ls=main_menu->add_switch("OPS","OPTIONS MENU");
//	btn=main_menu->add_button(Button("CRD","Credits"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->set_non_unclickable();
//	btn->lower_left(Pixel(30*xfactor,190*yfactor));
//	btn=main_menu->add_button(Button("EXIT","Quit"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->set_non_unclickable();
//	btn->lower_left(Pixel(100*xfactor,125*yfactor));
//	
//	main_menu->add_text(Text("GAME OVER","FORMAL",40*yfactor,Pixel(8*w/10,9*h/10)));	
//	main_menu->add_text(Text("Your score is","FORMAL",25*yfactor,Pixel(8*w/10,8*h/10)));
//	Button* b=main_menu->add_button(Button("SCORE"));
//	b->set_font("FORMAL",25*yfactor);
//	b->set_textbox(true);
//	b->invisibility();//set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(8*w/10,7*h/10));
//	b->set_text("0");
//	
//	/*Console* c=main_menu->add_console(Console("USERNAME",10,"FORMAL",35*yfactor));
//	btn=c->get_trigger();
//	btn->set_text("Not you?");
//	btn->set_origin(Vertex(8.5*w/10,8*h/10));
//	btn->set_font("FORMAL",15*yfactor);
//	
//	btn->invisibility();
//	c->centre(8*w/10,8.5*h/10);	
//	int x, y;
//	c->get_size(x,y);*/
//
//	main_menu->compile_report();
//	string PATH = PhysicsWorld::getPhysicsWorld()->projectDir + "assets\\UI\\";
//	//main_menu->save_configuration(PATH+MAIN_CONF);
//}
//
//void design_main_menu(Layout* main_menu)
//{
//	int w, h;
//	glfwGetWindowSize(&w, &h);
//	float xfactor=w/1280.f, yfactor=h/720.f;
//
//	Quad* qd=main_menu->add_quad(0,0,w,h,"BKG");
//	qd=main_menu->add_quad(4*w/5,0,w/5,h/5,"LOGO");
//
//	Button* btn=main_menu->add_button(Button("NEW","FlyThis!"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->set_non_unclickable();
//	btn->lower_left(Pixel(815*xfactor,250*yfactor));
//	btn=main_menu->add_button(Button("HS","High Scores"));
//	
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->lower_left(Pixel(785*xfactor,180*yfactor));
//	LayoutSwitch* ls=main_menu->add_switch("HS","HIGH SCORES");
//	btn=main_menu->add_button(Button("OPS","Options"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->lower_left(Pixel(745*xfactor,115*yfactor));
//	ls=main_menu->add_switch("OPS","OPTIONS MENU");
//	btn=main_menu->add_button(Button("CRD","Credits"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->set_non_unclickable();
//	btn->lower_left(Pixel(30*xfactor,190*yfactor));
//	btn=main_menu->add_button(Button("EXIT","Quit"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->set_non_unclickable();
//	btn->lower_left(Pixel(100*xfactor,125*yfactor));
//	
//	main_menu->add_text(Text("Welcome,","FORMAL",25*yfactor,Pixel(8*w/10,9*h/10)));	
//	
//	Console* c=main_menu->add_console(Console("USERNAME",10,"FORMAL",35*yfactor));
//	btn=c->get_trigger();
//	btn->set_text("Not you?");
//	btn->set_origin(Pixel(8.5*w/10,8*h/10));
//	btn->set_font("FORMAL",15*yfactor);
//	
//	btn->invisibility();
//	c->centre(8*w/10,8.5*h/10);	
//	int x, y;
//	c->get_size(x,y);
//
//	main_menu->compile_report();
//	string PATH = PhysicsWorld::getPhysicsWorld()->projectDir + "assets\\UI\\";
//	//main_menu->save_configuration(PATH+MAIN_CONF);
//}
//
//void design_options_screen(Layout* options_screen)
//{
//	int w, h;
//	glfwGetWindowSize(&w, &h);
//	float xfactor=w/1280.f, yfactor=h/720.f;
//	string PATH = PhysicsWorld::getPhysicsWorld()->projectDir + "assets\\UI\\";
//
//	Quad* qd=options_screen->add_quad(0,0,w,h,"BKG");
//	qd=options_screen->add_quad(4*w/5,0,w/5,h/5,"LOGO");
//	
//
//	Text* txt=options_screen->add_text(Text("Options","FORMAL",30*yfactor,Pixel(1010*xfactor,620*yfactor)));
//	
//	options_screen->add_quad(800*xfactor,150*yfactor,420*xfactor,500*yfactor,"OPTIONS_MENU");
//	qd=options_screen->add_quad(800*xfactor,540*yfactor,420*xfactor,50*yfactor,"OPTIONS_SUBMENU");
//	
//	//ADD TABS
//
//	options_screen->add_tab("GPL",Layout());
//	options_screen->add_tab("GFX",Layout());
//	options_screen->add_tab("CTRL",Layout());
//	
//	//GAMEPLAY CONFIGURATION
//	
//	Tab t1=options_screen->get_tab("GPL");
//	t1.tab_header->set_size(xfactor*420/3,50*yfactor);
//	t1.tab_header->lower_left(Pixel(800*xfactor,540*yfactor));
//	t1.tab_header->set_text("Gameplay");
//	t1.tab_header->set_font("FORMAL",20*yfactor);
//	t1.tab_header->set_texture(BTN_HOVERED,"SUBMENU_HIGHLIGHT");
//	t1.tab_header->set_texture(BTN_PRESSED,"SUBMENU_HIGHLIGHT");
//	t1.tab_header->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	t1.tab_header->set_display(BTN_INACTIVE,NULL);
//
//	txt=t1.tab_layout->add_text(Text("Note: The game must be restarted for these settings to take effect!","FORMAL",20*yfactor,Pixel(w/2,h/20)));
//
//	ButtonArray* arr=t1.tab_layout->add_buttonarray(ButtonArray("AUTO_CTRL"));
//	qd=t1.tab_layout->add_quad(960*xfactor,440*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//	
//	Button* btn=arr->add_button(Button("AUTO_OFF","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(962*xfactor,442*yfactor));
//	
//	txt=t1.tab_layout->add_text(Text("Auto Target:","FORMAL",17*yfactor,Pixel(885*xfactor,btn->get_origin().y)));
//	txt->relative_origin();
//	
//	txt=t1.tab_layout->add_text(Text("off","FORMAL",20*yfactor,Pixel(1002*xfactor,btn->get_origin().y)));
//	txt->relative_origin();
//		
//	btn=arr->add_button(Button("AUTO_ON","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(1027*xfactor,442*yfactor));
//	txt=t1.tab_layout->add_text(Text("on","FORMAL",20*yfactor,Pixel(1070*xfactor,btn->get_origin().y)));
//	qd=t1.tab_layout->add_quad(1025*xfactor,440*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//	
//
//	arr=t1.tab_layout->add_buttonarray(ButtonArray("DIFF_CTRL"));
//	qd=t1.tab_layout->add_quad(960*xfactor,400*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//	
//	btn=arr->add_button(Button("DIFF_LOW","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(962*xfactor,402*yfactor));
//	
//	txt=t1.tab_layout->add_text(Text("Difficulty:","FORMAL",17*yfactor,Pixel(885*xfactor,btn->get_origin().y)));
//	txt->relative_origin();
//	
//	txt=t1.tab_layout->add_text(Text("low","FORMAL",20*yfactor,Pixel(1002*xfactor,btn->get_origin().y)));
//			
//	btn=arr->add_button(Button("DIFF_MED","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(1027*xfactor,402*yfactor));
//	txt=t1.tab_layout->add_text(Text("med","FORMAL",20*yfactor,Pixel(1070*xfactor,btn->get_origin().y)));
//	qd=t1.tab_layout->add_quad(1025*xfactor,400*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//
//	btn=arr->add_button(Button("DIFF_HI","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(1097*xfactor,402*yfactor));
//	txt=t1.tab_layout->add_text(Text("high","FORMAL",20*yfactor,Pixel(1140*xfactor,btn->get_origin().y)));
//	qd=t1.tab_layout->add_quad(1095*xfactor,400*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//
//	Slider* sl;
//	
//	//GRAPHICS CONFIGURATION
//
//	Tab t2=options_screen->get_tab("GFX");
//	t2.tab_header->set_size(xfactor*420/3,50*xfactor);
//	t2.tab_header->lower_left(Pixel((800+420/3)*xfactor,540*yfactor));
//	t2.tab_header->set_text("Graphics");
//	t2.tab_header->set_font("FORMAL",20*yfactor);	
//	t2.tab_header->set_texture(BTN_HOVERED,"SUBMENU_HIGHLIGHT");
//	t2.tab_header->set_texture(BTN_PRESSED,"SUBMENU_HIGHLIGHT");
//	t2.tab_header->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	t2.tab_header->set_display(BTN_INACTIVE,NULL);
//
//	txt=t2.tab_layout->add_text(Text("Note: The game must be restarted for these settings to take effect!","FORMAL",20*yfactor,Pixel(w/2,h/20)));
//
//	Menu* l=t2.tab_layout->add_floating_menu(new List("RES_LIST",PATH+"List.txt","FORMAL",20*yfactor//,3
//		));
//	btn=l->get_entry(0);
//	int x,y;
//	btn->get_size(x,y);
//	l->set_origin(Pixel(960*xfactor,500*yfactor+y));
//	
//	txt=t2.tab_layout->add_text(Text("Resolution:","FORMAL",20*yfactor,Pixel(885*xfactor,btn->get_origin().y)));
//	txt->relative_origin();
//
//	Layout* gfx=t2.tab_layout;
//
//
//
//
///******************************************************************************************/
//
//	arr=t2.tab_layout->add_buttonarray(ButtonArray("USE_GFX"));
//	btn=arr->add_button(Button("USE_QUICK","Quick"));
//	
//	btn->set_font("FORMAL",20*yfactor);
//	btn->adjust_to_text();
//	btn->lower_left(Pixel(1000*xfactor,170*yfactor));
//	btn->set_texture(BTN_HOVERED,"SUBMENU_HIGHLIGHT");
//	btn->set_texture(BTN_PRESSED,"SUBMENU_HIGHLIGHT");
//	btn->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	btn->set_display(BTN_INACTIVE,NULL);
//
//	
//	Pixel v=btn->get_origin();
//	btn->get_size(x,y);
//
//	btn=arr->add_button(Button("USE_ADV","Advanced"));
//	
//	btn->set_font("FORMAL",20*yfactor);
//	btn->adjust_to_text();
//	btn->lower_left(Pixel(v.x+0.5*x+10*xfactor,170*yfactor));
//	btn->set_texture(BTN_HOVERED,"SUBMENU_HIGHLIGHT");
//	btn->set_texture(BTN_PRESSED,"SUBMENU_HIGHLIGHT");
//	btn->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	btn->set_display(BTN_INACTIVE,NULL);
//
//	txt=t2.tab_layout->add_text(Text("Settings to use:","FORMAL",20*yfactor,Pixel(920*xfactor,btn->get_origin().y)));
//	txt->relative_origin();
//
///******************************************************************************************/	
//	
//	gfx->add_tab("GFX_QUICK");
//	gfx->add_tab("GFX_ADVANCED");
//
//	Tab qgfx=gfx->get_tab("GFX_QUICK"), agfx=gfx->get_tab("GFX_ADVANCED");
//
//	qgfx.tab_header->set_text("Quick");
//	qgfx.tab_header->set_font("FORMAL",20*yfactor);
//	qgfx.tab_header->adjust_to_text();
//	qgfx.tab_header->lower_left(Pixel(960*xfactor,450*yfactor));
//	qgfx.tab_header->get_size(x,y);
//	v=qgfx.tab_header->get_origin();
//
//	agfx.tab_header->set_text("Advanced");
//	agfx.tab_header->set_font("FORMAL",20*yfactor);
//	agfx.tab_header->adjust_to_text();
//	agfx.tab_header->lower_left(Pixel(v.x+0.5*x+10*xfactor,450*yfactor));
//
//	txt=gfx->add_text(Text("Settings:","FORMAL",20*yfactor,Pixel(885*xfactor,v.y)));
//	txt->relative_origin();
//	
//	//QUICK GRAPHICS
//
//	sl=qgfx.tab_layout->add_slider(Slider("P/Q",Pixel(970*xfactor,350*yfactor), Pixel(1100*xfactor,350*yfactor),1,10,20*xfactor,20*yfactor,0.2));
//	sl->set_control_texture("SELECTION_BTN");
//	sl->set_bar_texture("SELECTION_BTN");
//	btn=sl->get_control();
//	btn->set_round();
//	
//	txt=qgfx.tab_layout->add_text(Text("Performance","FORMAL",20*yfactor,Pixel(885*xfactor,btn->get_origin().y)));
//	txt=qgfx.tab_layout->add_text(Text("Quality","FORMAL",20*yfactor,Pixel(1150*xfactor,btn->get_origin().y)));
//
//	//ADVANCED GRAPHICS
//		
//	arr=agfx.tab_layout->add_buttonarray(ButtonArray("HDR_CTRL"));
//	qd=agfx.tab_layout->add_quad(960*xfactor,400*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//	
//	btn=arr->add_button(Button("HDR_OFF","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(962*xfactor,402*yfactor));
//
//	txt=agfx.tab_layout->add_text(Text("HDR:","FORMAL",17*yfactor,Pixel(885*xfactor,btn->get_origin().y)));
//	txt->format(FTGL::ALIGN_CENTER,150*xfactor);
//
//	txt=agfx.tab_layout->add_text(Text("off","FORMAL",20*yfactor,Pixel(1002*xfactor,btn->get_origin().y)));
//	txt->relative_origin();
//		
//	btn=arr->add_button(Button("HDR_ON","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(1027*xfactor,402*yfactor));
//	txt=agfx.tab_layout->add_text(Text("on","FORMAL",20*yfactor,Pixel(1070*xfactor,btn->get_origin().y)));
//	qd=agfx.tab_layout->add_quad(1025*xfactor,400*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//	
//	arr=agfx.tab_layout->add_buttonarray(ButtonArray("SUN_CTRL"));
//	btn=arr->add_button(Button("SUN_OFF","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(962*xfactor,362*yfactor));
//	
//	txt=agfx.tab_layout->add_text(Text("Sun Rays:","FORMAL",17*yfactor,Pixel(885*xfactor,btn->get_origin().y)));
//	txt->format(FTGL::ALIGN_CENTER,150*xfactor);
//
//	txt=agfx.tab_layout->add_text(Text("off","FORMAL",20*yfactor,Pixel(1002*xfactor,btn->get_origin().y)));
//	txt->relative_origin();
//	
//	qd=agfx.tab_layout->add_quad(960*xfactor,360*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//	btn=arr->add_button(Button("SUN_ON","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(1027*xfactor,362*yfactor));
//	txt=agfx.tab_layout->add_text(Text("on","FORMAL",20*yfactor,Pixel(1070*xfactor,btn->get_origin().y)));
//	qd=agfx.tab_layout->add_quad(1025*xfactor,360*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//
//
//	arr=agfx.tab_layout->add_buttonarray(ButtonArray("SHIP_CTRL"));
//	btn=arr->add_button(Button("SHIP_LOW","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(962*xfactor,322*yfactor));
//	
//	txt=agfx.tab_layout->add_text(Text("Ship Geometry:","FORMAL",17*yfactor,Pixel(885*xfactor,btn->get_origin().y)));
//	txt->format(FTGL::ALIGN_CENTER,150*xfactor);
//	
//	txt=agfx.tab_layout->add_text(Text("low","FORMAL",20*yfactor,Pixel(1002*xfactor,btn->get_origin().y)));
//	
//	qd=agfx.tab_layout->add_quad(960*xfactor,320*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//	btn=arr->add_button(Button("SHIP_HI","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(1027*xfactor,322*yfactor));
//	txt=agfx.tab_layout->add_text(Text("high","FORMAL",20*yfactor,Pixel(1070*xfactor,btn->get_origin().y)));
//	qd=agfx.tab_layout->add_quad(1025*xfactor,320*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//
//	arr=agfx.tab_layout->add_buttonarray(ButtonArray("ENV_CTRL"));
//	btn=arr->add_button(Button("ENV_LOW","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(962*xfactor,282*yfactor));
//	
//	txt=agfx.tab_layout->add_text(Text("Environment Geometry:","FORMAL",17*yfactor,Pixel(885*xfactor,btn->get_origin().y)));
//	txt->format(FTGL::ALIGN_CENTER,150*xfactor);
//
//	txt=agfx.tab_layout->add_text(Text("low","FORMAL",20*yfactor,Pixel(1002*xfactor,btn->get_origin().y)));
//	
//	qd=agfx.tab_layout->add_quad(960*xfactor,280*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//	btn=arr->add_button(Button("ENV_HI","",NULL,10,Pixel(-1,-1),18*xfactor,18*yfactor));
//	btn->set_round();
//	btn->set_display(BTN_INACTIVE,NULL);
//	btn->set_texture(BTN_HOVERED,"SELECTION_BTN");
//	btn->set_texture(BTN_PRESSED,"SELECTION_BTN");
//	btn->set_texture(BTN_ACTIVE,"SELECTION_BTN");
//	btn->lower_left(Pixel(1027*xfactor,282*yfactor));
//	txt=agfx.tab_layout->add_text(Text("high","FORMAL",20*yfactor,Pixel(1070*xfactor,btn->get_origin().y)));
//	qd=agfx.tab_layout->add_quad(1025*xfactor,280*yfactor,22*xfactor,22*yfactor,"SELECT_CIRCLE");
//
//	sl=agfx.tab_layout->add_slider(Slider("POST_PROC",Pixel(975*xfactor,250*yfactor), Pixel(1100*xfactor,250*yfactor),1,5,20*xfactor,20*yfactor,0.2));
//	sl->set_control_texture("SELECTION_BTN");
//	sl->set_bar_texture("SELECTION_BTN");
//	btn=sl->get_control();
//	btn->set_round();
//	txt=agfx.tab_layout->add_text(Text("Post Processing:","FORMAL",17*yfactor,Pixel(885*xfactor,btn->get_origin().y)));
//	txt->format(FTGL::ALIGN_CENTER,150*xfactor);
//
//
//	sl=agfx.tab_layout->add_slider(Slider("TRF_VOL",Pixel(975*xfactor,220*yfactor), Pixel(1100*xfactor,220*yfactor),1,5,20*xfactor,20*yfactor,0.2));
//	sl->set_control_texture("SELECTION_BTN");
//	sl->set_bar_texture("SELECTION_BTN");
//	btn=sl->get_control();
//	btn->set_round();
//	txt=agfx.tab_layout->add_text(Text("Traffic Volume:","FORMAL",17*yfactor,Pixel(885*xfactor,btn->get_origin().y)));
//	txt->format(FTGL::ALIGN_CENTER,150*xfactor);
//
//	/*======================================================================================================*/
//	
//	//CONTROLS CONFIGURATION
//		
//	Tab t3=options_screen->get_tab("CTRL");
//	t3.tab_header->set_size(xfactor*420/3,50*xfactor);
//	t3.tab_header->lower_left(Pixel((800+2*420/3)*xfactor,540*yfactor));
//	t3.tab_header->set_text("Controls");
//	t3.tab_header->set_font("FORMAL",20*yfactor);
//	t3.tab_header->set_texture(BTN_HOVERED,"SUBMENU_HIGHLIGHT");
//	t3.tab_header->set_texture(BTN_PRESSED,"SUBMENU_HIGHLIGHT");
//	t3.tab_header->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	t3.tab_header->set_display(BTN_INACTIVE,NULL);
//
//	txt=t3.tab_layout->add_text(Text("","FORMAL",17*yfactor,Pixel(//915
//		350*xfactor,360*yfactor)));
//	txt->format(FTGL::ALIGN_LEFT,190*yfactor);
//	txt->text=
//		string("Roll Left\n")+"Roll Right\n"+
//		"Pitch Up\n"+"Pitch Down\n"+
//		"Yaw Left\n"+"Yaw Right\n"+" \n"+
//		"Accelerate\n"+"Decelerate\n"+"Horn\n"+" \n"+
//		"Fire Left Torpedo\n"+"Fire Right Torpedo\n"+
//		"Beam Ragdolls\n"+"Eject Ragdolls\n"+"Docking Mode\n"+
//		"Pick Passenger\n"+"Drop Passenger\n"+" \n"+
//		//"Camera Change\n"+"Look Left\n"+"Look Right\n"+
//		//"Look Up\n"+"Look Down\n"+" \n"+
//		//"Get Screenshot\n"+
//		"Pause Game\n"+
//		"Debug Mode\n"+"AI Debug Mode\n";
//
//			/*	accelerateKey       = GLFW_KEY_LSHIFT;
//			decelerateKey       = GLFW_KEY_SPACE;
//			hornKey				= (unsigned char)int('H');
//			
//			leftTorpedoFireKey	= GLFW_MOUSE_BUTTON_1;
//			rightTorpedoFireKey	= GLFW_MOUSE_BUTTON_2;
//			beamRagdollsKey     = GLFW_KEY_CAPS_LOCK;
//			ejectRagdollsKey    = GLFW_KEY_TAB;
//			dockingModeKey		= (unsigned char)int('T');
//			pickPassengerKey	= (unsigned char)int('P');
//			dropPassengerKey	= (unsigned char)int('O');
//
//			showMiniMapKey		= (unsigned char)int('M');
//			showStatsKey		= (unsigned char)int('N');
//
//			changeCameraKey     = (unsigned char)int('C');
//			cameraLookLeftKey   = (unsigned char)int('A');
//			cameraLookRightKey	= (unsigned char)int('D');
//			cameraLookUpKey     = (unsigned char)int('S');
//			cameraLookDownKey	= (unsigned char)int('W');*/
//
//	txt=t3.tab_layout->add_text(Text("","FORMAL",17*yfactor,Pixel(//1105
//		540*xfactor,360*yfactor)));
//	txt->format(FTGL::ALIGN_RIGHT,190*yfactor);
//	txt->text=
//		string("A\n")+"D\n"+
//		"W\n"+"S\n"+
//		"Q\n"+"E\n"+" \n"+
//		"Left Shift\n"+"Space\n"+"H\n"+" \n"+
//		"Left Mouse Button\n"+"Right Mouse Button\n"+
//		"Caps Lock\n"+"Tab\n"+"T\n"+
//		"P\n"+"O\n"+" \n"+
//		//"C\n"+"A\n"+"D\n"+
//		//"S\n"+"W\n"+" \n"+
//		//"Scroll Lock\n"+
//		"Esc\n"+
//		"F3\n"+"F4\n";
//
//	qd=t3.tab_layout->add_quad(225*xfactor,20*yfactor,380*1.2*xfactor,h-40*yfactor,"OPTIONS_MENU");
//	
//
//	sl=t3.tab_layout->add_slider(Slider("VOL",Pixel(970*xfactor,440*yfactor), Pixel(1100*xfactor,440*yfactor),1,1,20*xfactor,20*yfactor,0.2));
//	sl->set_control_texture("SELECTION_BTN");
//	sl->set_bar_texture("SELECTION_BTN");
//	btn=sl->get_control();
//	btn->set_round();
//	txt=t3.tab_layout->add_text(Text("Sound Volume:","FORMAL",17*yfactor,Pixel(885*xfactor,btn->get_origin().y)));
//
//	txt=t3.tab_layout->add_text(Text("Note: This setting will not be saved once the game terminates!","FORMAL",20*yfactor,Pixel(1010*xfactor,4*h/10)));
//	txt->format(FTGL::ALIGN_CENTER,300*xfactor);
//
//	btn=options_screen->add_button(Button("OPS_OK","OK"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->lower_left(Pixel(745*xfactor,115*yfactor));
//	LayoutSwitch* ls=options_screen->add_switch("OPS_OK","MAIN MENU");
//	btn=options_screen->add_button(Button("OPS_BACK","Cancel"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->lower_left(Pixel(840*xfactor,115*yfactor));
//	ls=options_screen->add_switch("OPS_BACK","MAIN MENU");
//
//	options_screen->compile_report();
//	//options_screen->save_configuration(PATH+OPTIONS_CONF);
//}
//
//void design_high_scores(Layout* high_scores)
//{
//	int w, h;
//	glfwGetWindowSize(&w, &h);
//	float xfactor=w/1280.f, yfactor=h/720.f;
//
//	Quad* qd=high_scores->add_quad(0,0,w,h,"BKG");
//	qd=high_scores->add_quad(4*w/5,0,w/5,h/5,"LOGO");
//	qd=high_scores->add_quad(w/10,h/5,3*w/10,3*h/5,"OPTIONS_MENU");
//
//	float f1=(3*h/5)/8, f2=f1/4;
//	qd=high_scores->add_quad(w/10,h/5+f1,3*w/10,f1,"OPTIONS_SUBMENU");
//	qd=high_scores->add_quad(w/10,h/5+2*f1+f2,3*w/10,f1,"OPTIONS_SUBMENU");
//	qd=high_scores->add_quad(w/10,h/5+3*f1+2*f2,3*w/10,f1,"OPTIONS_SUBMENU");
//	qd=high_scores->add_quad(w/10,h/5+4*f1+3*f2,3*w/10,f1,"OPTIONS_SUBMENU");
//	qd=high_scores->add_quad(w/10,h/5+5*f1+4*f2,3*w/10,f1,"OPTIONS_SUBMENU");
//
//	qd=high_scores->add_quad(6*w/10,h/5,3*w/10,3*h/5,"OPTIONS_MENU");
//
//	qd=high_scores->add_quad(6*w/10,h/5+f1,3*w/10,f1,"OPTIONS_SUBMENU");
//	qd=high_scores->add_quad(6*w/10,h/5+2*f1+f2,3*w/10,f1,"OPTIONS_SUBMENU");
//	qd=high_scores->add_quad(6*w/10,h/5+3*f1+2*f2,3*w/10,f1,"OPTIONS_SUBMENU");
//	qd=high_scores->add_quad(6*w/10,h/5+4*f1+3*f2,3*w/10,f1,"OPTIONS_SUBMENU");
//	qd=high_scores->add_quad(6*w/10,h/5+5*f1+4*f2,3*w/10,f1,"OPTIONS_SUBMENU");
//
//	Text* t=high_scores->add_text(Text("High Scores","FORMAL",35*yfactor,Pixel(w/2,0.9*h)));
//	float f3=w/10+(3*w/10)/2;
//	t=high_scores->add_text(Text("1","FORMAL",35*yfactor,Pixel(f3,h/5+5*f1+4*f2+f1/2)));
//
//	Button* b=high_scores->add_button(Button("HS1_NAME"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(1.5*w/10,h/5+5*f1+4*f2+f1/2));
//	b->set_size(w/10,f1);
//	b->reduce_text_to_size();
//
//	b=high_scores->add_button(Button("HS1_SCORE"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(3.5*w/10,h/5+5*f1+4*f2+f1/2));
//	b->set_size(w/10,f1);
//
//	t=high_scores->add_text(Text("2","FORMAL",35*yfactor,Pixel(f3,h/5+4*f1+3*f2+f1/2)));
//
//	b=high_scores->add_button(Button("HS2_NAME"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(1.5*w/10,h/5+4*f1+3*f2+f1/2));
//	b->set_size(w/10,f1);
//
//	b=high_scores->add_button(Button("HS2_SCORE"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(3.5*w/10,h/5+4*f1+3*f2+f1/2));
//	b->set_size(w/10,f1);
//
//
//	t=high_scores->add_text(Text("3","FORMAL",35*yfactor,Pixel(f3,h/5+3*f1+2*f2+f1/2)));
//
//	b=high_scores->add_button(Button("HS3_NAME"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(1.5*w/10,h/5+3*f1+2*f2+f1/2));
//	b->set_size(w/10,f1);
//
//	b=high_scores->add_button(Button("HS3_SCORE"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(3.5*w/10,h/5+3*f1+2*f2+f1/2));
//	b->set_size(w/10,f1);
//
//	t=high_scores->add_text(Text("4","FORMAL",35*yfactor,Pixel(f3,h/5+2*f1+f2+f1/2)));
//	
//	b=high_scores->add_button(Button("HS4_NAME"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(1.5*w/10,h/5+2*f1+f2+f1/2));
//	b->set_size(w/10,f1);
//
//	b=high_scores->add_button(Button("HS4_SCORE"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(3.5*w/10,h/5+2*f1+f2+f1/2));
//	b->set_size(w/10,f1);
//
//	t=high_scores->add_text(Text("5","FORMAL",35*yfactor,Pixel(f3,h/5+f1+f1/2)));
//
//	b=high_scores->add_button(Button("HS5_NAME"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(1.5*w/10,h/5+f1+f1/2));
//	b->set_size(w/10,f1);
//
//	b=high_scores->add_button(Button("HS5_SCORE"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(3.5*w/10,h/5+f1+f1/2));
//	b->set_size(w/10,f1);
//	
//	
//	t=high_scores->add_text(Text("6","FORMAL",35*yfactor,Pixel(0.5*w+f3,h/5+5*f1+4*f2+f1/2)));
//
//	b=high_scores->add_button(Button("HS6_NAME"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(0.5*w+1.5*w/10,h/5+5*f1+4*f2+f1/2));
//	b->set_size(w/10,f1);
//
//	b=high_scores->add_button(Button("HS6_SCORE"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(0.5*w+3.5*w/10,h/5+5*f1+4*f2+f1/2));
//	b->set_size(w/10,f1);
//
//	t=high_scores->add_text(Text("7","FORMAL",35*yfactor,Pixel(0.5*w+f3,h/5+4*f1+3*f2+f1/2)));
//
//	b=high_scores->add_button(Button("HS7_NAME"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(0.5*w+1.5*w/10,h/5+4*f1+3*f2+f1/2));
//	b->set_size(w/10,f1);
//
//	b=high_scores->add_button(Button("HS7_SCORE"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(0.5*w+3.5*w/10,h/5+4*f1+3*f2+f1/2));
//	b->set_size(w/10,f1);
//
//	t=high_scores->add_text(Text("8","FORMAL",35*yfactor,Pixel(0.5*w+f3,h/5+3*f1+2*f2+f1/2)));
//
//	b=high_scores->add_button(Button("HS8_NAME"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(0.5*w+1.5*w/10,h/5+3*f1+2*f2+f1/2));
//	b->set_size(w/10,f1);
//
//	b=high_scores->add_button(Button("HS8_SCORE"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(0.5*w+3.5*w/10,h/5+3*f1+2*f2+f1/2));
//	b->set_size(w/10,f1);
//
//	t=high_scores->add_text(Text("9","FORMAL",35*yfactor,Pixel(0.5*w+f3,h/5+2*f1+f2+f1/2)));
//
//	b=high_scores->add_button(Button("HS9_NAME"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(0.5*w+1.5*w/10,h/5+2*f1+f2+f1/2));
//	b->set_size(w/10,f1);
//
//	b=high_scores->add_button(Button("HS9_SCORE"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(0.5*w+3.5*w/10,h/5+2*f1+f2+f1/2));
//	b->set_size(w/10,f1);
//
//	t=high_scores->add_text(Text("10","FORMAL",35*yfactor,Pixel(0.5*w+f3,h/5+f1+f1/2)));
//
//	b=high_scores->add_button(Button("HS10_NAME"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(0.5*w+1.5*w/10,h/5+f1+f1/2));
//	b->set_size(w/10,f1);
//
//	b=high_scores->add_button(Button("HS10_SCORE"));
//	b->set_font("FORMAL",20*yfactor);
//	b->set_textbox(true);
//	b->set_texture(BTN_ACTIVE,"SUBMENU_HIGHLIGHT");
//	b->set_origin(Pixel(0.5*w+3.5*w/10,h/5+f1+f1/2));
//	b->set_size(w/10,f1);
//
//	Button* btn=high_scores->add_button(Button("HS_BACK","Back"));
//	btn->set_font("FORMAL",35*yfactor);
//	btn->invisibility();
//	btn->set_origin(Pixel(w/10,h/10));
//	LayoutSwitch* ls=high_scores->add_switch("HS_BACK","MAIN MENU");
//
//	high_scores->compile_report();
//	//string PATH = PhysicsWorld::getPhysicsWorld()->projectDir + "assets\\UI\\";
//	//high_scores->save_configuration(PATH+SCORE_CONF);
//}
//
//
//void read()
//{
//	Layout* options=GUIScreens->get("OPTIONS MENU");
//	Config *cConfig = PhysicsWorld::getPhysicsWorld()->config;
//	ButtonArray* ba;
//	int k=cConfig->getResolutionWidth();
//
//	Tab gameplay=options->get_tab("GPL");
//	Tab graphics=options->get_tab("GFX");
//	Tab qgfx=graphics.tab_layout->get_tab("GFX_QUICK");
//	Tab agfx=graphics.tab_layout->get_tab("GFX_ADVANCED");
//	Tab controls=options->get_tab("CTRL");
//
//	Menu* m=graphics.tab_layout->get_menu("RES_LIST",true);
//	Button* b=m->get_entry(0);
//	
//	switch(k){
//		/*case 640:			
//			b->set_text("640 x 360");
//			break;
//		case 800:
//			b->set_text("800 x 450");
//			break;*/
//		case 1280: 
//			b->set_text("1280 x 720");
//			break;
//		/*case 1680:
//			b->set_text("1680 x 945");
//			break;*/
//		case 1920:
//			b->set_text("1920 x 1080");
//			break;
//		default: break;
//	}
//	
//	ba=gameplay.tab_layout->get_array("AUTO_CTRL");
//	if(cConfig->getAutoTargetSystemState()){
//		ba->set_active("AUTO_ON");
//	}
//	else {
//		ba->set_active("AUTO_OFF");
//	}
//	ba=gameplay.tab_layout->get_array("DIFF_CTRL");
//	k=cConfig->getDifficulty();
//	if(k==0){
//		ba->set_active("DIFF_LOW");
//	}
//	else if(k==1){
//		ba->set_active("DIFF_MED");
//	}
//	else {
//		ba->set_active("DIFF_HI");
//	}
//	
//	
//	
//
//	k=cConfig->getGraphicsSlider();
//	Slider* sl=qgfx.tab_layout->get_slider("P/Q");
//	sl->set_state(k);
//
//	
//
//
//	ba=agfx.tab_layout->get_array("HDR_CTRL");
//	if(cConfig->getHdrState()) {
//		ba->set_active("HDR_ON");
//	} else {
//		ba->set_active("HDR_OFF");
//	}
//	ba=agfx.tab_layout->get_array("SUN_CTRL");
//	if(cConfig->getSunState()) {
//		ba->set_active("SUN_ON");
//	} else {
//		ba->set_active("SUN_OFF");
//	}
//
//	ba=agfx.tab_layout->get_array("SHIP_CTRL");
//	if(cConfig->getShipState()) {
//		ba->set_active("SHIP_HI");
//	} else {
//		ba->set_active("SHIP_LOW");
//	}
//	ba=agfx.tab_layout->get_array("ENV_CTRL");
//	if(cConfig->getEnvState()) {
//		ba->set_active("ENV_HI");
//	} else {
//		ba->set_active("ENV_LOW");
//	}
//
//
//	k=cConfig->getBlurPasses();
//	sl=agfx.tab_layout->get_slider("POST_PROC");
//	sl->set_state(k);
//
//	k=cConfig->getTrafficVolume();
//	sl=agfx.tab_layout->get_slider("TRF_VOL");
//	sl->set_state(k);
//
//	ba=graphics.tab_layout->get_array("USE_GFX");
//	if(cConfig->getAdvancedGraphicsState()) {
//		ba->set_active("USE_ADV");
//	} else {
//		ba->set_active("USE_QUICK");
//	}
//	
//	
//	sl=controls.tab_layout->get_slider("VOL");
//	float gain;
//	alGetListenerf(AL_GAIN,&gain);
//	cout << "MASTER VOLUME" << gain << endl;
//	sl->set_value(gain);
//
//}
//
//void emit()
//{
//	Layout* options=GUIScreens->get("OPTIONS MENU");
//	Config *cConfig = PhysicsWorld::getPhysicsWorld()->config;
//	ButtonArray* ba;
//	int k;
//
//	cConfig->setAutoTargetSystemState(options->report_string("AUTO_CTRL")=="AUTO_ON");
//	
//	string s=options->report_string("DIFF_CTRL");
//	if(s=="DIFF_LOW"){
//		cConfig->setDifficulty(0);
//	}
//	else if(s=="DIFF_MED"){
//		cConfig->setDifficulty(1);
//	}
//	else {
//		cConfig->setDifficulty(2);
//	}
//	
//	cConfig->setGraphicsSlider(options->report_int("P/Q"));
//	cConfig->setHdrState(options->report_string("HDR_CTRL")=="HDR_ON");
//	cConfig->setSunState(options->report_string("SUN_CTRL")=="SUN_ON");
//	cConfig->setShipState(options->report_string("SHIP_CTRL")=="SHIP_HI");
//	cConfig->setEnvState(options->report_string("ENV_CTRL")=="ENV_HI");
//	cConfig->setBlurPasses(options->report_int("POST_PROC"));
//	cConfig->setTrafficVolume(options->report_int("TRF_VOL"));
//
//	s=options->report_string("RES_LIST");
//	stringstream ss(s);
//	int w,h;
//	string temp;
//	ss >> w >> temp >> h;
//	cConfig->setResolutionWidth(w);
//	cConfig->setResolutionHeight(h);
//	
//	cConfig->setAdvancedGraphicsState(options->report_string("USE_GFX")=="USE_ADV");
//
//	alListenerf(AL_GAIN,options->report_float("VOL"));
//	cConfig->save();
//}
//
//void readuser()
//{
//	Config *cConfig = PhysicsWorld::getPhysicsWorld()->config;
//	Layout* main=GUIScreens->get("MAIN MENU");
//	Console* c=main->get_console("USERNAME");
//	c->set_content(cConfig->getUserName());
//}
//
//void writeuser()
//{
//	Config *cConfig = PhysicsWorld::getPhysicsWorld()->config;
//	Layout* main=GUIScreens->get("MAIN MENU");
//	cConfig->setUserName(main->report_string("USERNAME"));
//}
//
//void readscores()
//{
//	Layout* scores=GUIScreens->get("HIGH SCORES");
//	Scores.scores.clear();
//	for(int i=1; i<=10; i++){
//		char name[10], score[11];
//		sprintf(name,"HS%d_NAME",i);
//		sprintf(score,"HS%d_SCORE",i);
//		//name="HS"+itoa(i)+"_NAME";
//		//score="HS"+itoa(i)+"_SCORE";
//		Button* nm=scores->get_button(name), *sc=scores->get_button(score);
//		if(nm->get_text()!=""&&sc->get_text()!=""){
//			Scores.add(nm->get_text(),atoi(sc->get_text().c_str()));
//		}
//
//	}
//
//}
//
//void writescores()
//{
//
//	Layout* scores=GUIScreens->get("HIGH SCORES");
//	multimap<string,int>::reverse_iterator j=Scores.scores.rbegin();
//	for(int i=1; i<=10; i++){
//		if(i>Scores.scores.size()) break;
//		char name[10], score[11];
//		sprintf(name,"HS%d_NAME",i);
//		sprintf(score,"HS%d_SCORE",i);
//		//name="HS"+itoa(i)+"_NAME";
//		//score="HS"+itoa(i)+"_SCORE";
//		Button* nm=scores->get_button(name), *sc=scores->get_button(score);
//		nm->set_text(j->first);
//		char scr[15];
//		sprintf(scr,"%d",j->second);
//		sc->set_text(scr);
//		j--;
//
//	}
//
//}