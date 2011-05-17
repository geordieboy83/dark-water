#include "GUI.Console.h"

extern FontSystem* GUIFonts;
Console *current;

struct {
	string consolestring;
	unsigned int length;
} consoletext;

void GLFWCALL consolespecial(int key,int action)
{
	if(action==GLFW_RELEASE) return;
	if(key==GLFW_KEY_BACKSPACE){
		if(!consoletext.consolestring.empty())consoletext.consolestring.erase(consoletext.consolestring.end()-1);		
	}

	if(key==GLFW_KEY_ENTER){	
		stringstream ss(consoletext.consolestring);
		string s;
		string content="";
		while(ss>>s){
			if(s!=""){
				if(content!="") content=content+" "+s;
				else content=s;
			}
		}
		if(content!="") current->set_content(content);
		current->get_text()->set_text(current->get_content());
		current->set_inactive();		
	}
	if(key==GLFW_KEY_ESC){
		current->get_text()->set_text(current->get_content());
		current->set_inactive();
	}
}

void GLFWCALL console( int key, int action )
{
	if(key=='_'){
		if(consoletext.consolestring.length()<consoletext.length)
		consoletext.consolestring+=' ';
		return;
	}
	
	if(consoletext.consolestring.length()<consoletext.length)
		consoletext.consolestring+=char(key);
}

void Console::set_active() {
	active=true;
	current=this;
	text.force_active();
	glfwSetKeyCallback(consolespecial);
	glfwSetCharCallback(console);
	glfwEnable(GLFW_KEY_REPEAT);
	consoletext.length=length;
	consoletext.consolestring="";
}
void Console::set_inactive() {
	active=false;
	glfwSetKeyCallback(NULL);	
	glfwSetCharCallback(NULL);
	glfwDisable(GLFW_KEY_REPEAT);
	text.reset();
}

Console::Console(string id,int length, string font_id, unsigned int font_size, Pixel lowerleft):
ID(id),length(length),font_id(font_id),font_size(font_size),origin(lowerleft),active(false)
{
	if(font_id!="") font=GUIFonts->get_font(font_id,font_size);
	string test="";
	for(int i=1;i<=length+1;i++) test+="W";
	text.set_textbox(true);
	text.set_font(font_id,font_size);
	text.set_text(test);
	text.adjust_to_text();
	text.set_text("");
	int x,y;
	text.get_size(x,y);
	text.set_display(BTN_INACTIVE,NULL);
	text.reset();
	
	enter.set_size(min(x,y),min(x,y));	
	enter.set_round();
	enter.set_non_unclickable();
	enter.set_texture(BTN_INACTIVE,"CON_YES");
	enter.set_texture(BTN_HOVERED,"CON_SEL_YES");
	enter.set_texture(BTN_PRESSED,"CON_SEL_YES");
	enter.set_texture(BTN_ACTIVE,"CON_SEL_YES");

	cancel.set_size(min(x,y),min(x,y));
	cancel.set_round();
	cancel.set_non_unclickable();
	cancel.set_texture(BTN_INACTIVE,"CON_NO");
	cancel.set_texture(BTN_HOVERED,"CON_SEL_NO");
	cancel.set_texture(BTN_PRESSED,"CON_SEL_NO");
	cancel.set_texture(BTN_ACTIVE,"CON_SEL_NO");


	cancel.lower_left(origin);
	text.lower_left(Pixel(origin.x+min(x,y),origin.y));
	enter.lower_left(Pixel(origin.x+min(x,y)+x,origin.y));

	size_y=y;
	Pixel v=enter.get_origin();
	size_x=v.x+0.5*min(x,y)-origin.x;

}

 bool Console::update()
{
	bool flag;
	if(active) flag=update_active();
	else flag=update_inactive();	
	return flag;
}

bool Console::update_active()
{
	enter.update();
	cancel.update();

	if(cancel.get_value()){
		set_inactive();
		text.set_text(content);
		return true;
	}
	if(enter.get_value()){
		stringstream ss(consoletext.consolestring);
		string s,temp;
		temp="";
		while(ss>>s){
			if(s!=""){
				if(temp!="") temp=temp+" "+s;
				else temp=s;
			}
		}
		if(temp!="") content=temp;
		text.set_text(content);
		set_inactive();
		return true;
	}


	text.set_text(consoletext.consolestring+'_');	
	return true;
}

bool Console::update_inactive()
{
	trigger.update();
	if(trigger.get_value()){
		trigger.reset();
		set_active();
		return true;
	}
	
	return false;
	
}

void Console::display()
{
	if(!active){
		trigger.display();
	}
	if(active){
		enter.display();
		cancel.display();
	}
	text.display();

}

void Console::centre(float x, float y)
{
	int textx, texty;
	text.get_size(textx, texty);
	text.set_origin(Pixel(x,y));
	
	float newx; 
	newx=0.5*textx+0.5*min(textx,texty);
	
	cancel.set_origin(Pixel(x-newx,y));
	enter.set_origin(Pixel(x+newx,y));
}