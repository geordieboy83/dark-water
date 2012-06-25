#include "GUI.Slider.h"

extern UITexturing* GUITextures;

Slider::Slider():
value(0.5),
	bar_height_factor(0.25),
	bartexture("NONE"),
	states(1)
{
	int w,h;
	glfwGetWindowSize(&w,&h);
	from.set(0,h*0.9);
	to.set(w,h*0.9);
	control.set_origin(Pixel(w/2,h/2));
	control.set_non_unclickable();
	for(int i=BTN_INACTIVE;i<BTN_STATES;i++){
		control.set_texture(i,"NONE");
	}
	

}


Slider::~Slider()
{
}

Slider::Slider(string id, Pixel from, Pixel to, float value, unsigned int states, int size_x, int size_y, float barheightfactor):
	from(from),to(to),value(value),bar_height_factor(barheightfactor), bartexture("NONE"), states(states)
{
	control.set_origin(Pixel(from.x+(to.x-from.x)*value,from.y+(to.y-from.y)*value));
	control.set_non_unclickable();
	control.set_size(size_x,size_y);
	if(states==0) states=1;
	set_ID(id);
	for(int i=BTN_INACTIVE;i<BTN_STATES;i++){
		control.set_texture(i,"NONE");
	}
}

bool Slider::update()
{
	int x, y,w,h;
		glfwGetMousePos(&x,&y);
		glfwGetWindowSize(&w,&h);
		y=h-y;
	if(control.get_state()==BTN_PRESSED &&glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)){
		Pixel v=control.get_origin();			
			if(x>to.x) v.x=to.x;
			else if(x<from.x) v.x=from.x;
			else v.x=x;
			value=from.distance(v)/from.distance(to);			
			if(states>1){
				value=floor(value*(states-1))/(float)(states-1);
				v.x=from.x+value*(to.x-from.x);
			}
			control.set_origin(v);
			cout<<value; if(states>1) cout << " " << get_int(); cout << endl;
			return true;
	}

	bool flag=control.update();
	if(flag==false)	return flag;
	else{
		
		if(control.get_state()==BTN_PRESSED){
			Pixel v=control.get_origin();			
			if(x>to.x) v.x=to.x;
			else if(x<from.x) v.x=from.x;
			else v.x=x;
			value=from.distance(v)/from.distance(to);
			if(states>1){
				value=floor(value*(states-1))/(float)(states-1);
				v.x=from.x+value*(to.x-from.x);
			}
			control.set_origin(v);
			
			cout<<value << endl;
		}
	}
}

void Slider::display()
{
	int x, y;
	control.get_size(x,y);
	
	if(bartexture=="NONE") {
		
		glBindTexture(GL_TEXTURE_2D,0);
	}
	else{
		glBindTexture(GL_TEXTURE_2D,GUITextures->get(bartexture));
	}
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
	
	glColor4f(0,0,1,0.5);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_QUADS);

		glTexCoord2i(0,0);
		glVertex2f(from.x, from.y-0.5*bar_height_factor*y);
		glTexCoord2i(1,0);
		glVertex2f(to.x, to.y-0.5*bar_height_factor*y);
		glTexCoord2i(1,1);
		glVertex2f(to.x, to.y+0.5*bar_height_factor*y);
		glTexCoord2i(0,1);
		glVertex2f(from.x, from.y+0.5*bar_height_factor*y);

	glEnd();
	glFlush();
	control.display();

}

