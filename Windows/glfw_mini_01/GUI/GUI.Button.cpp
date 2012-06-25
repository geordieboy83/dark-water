#include "GUI.Button.h"

extern SoundSystem* GUISounds;
extern FontSystem* GUIFonts;
extern UITexturing* GUITextures;
//extern UIEvents GUIEvents;

Button::~Button()
{
	//cout << "Button " << ID << " destroyed." << endl;
}

Button::Button(
	string id,
	string Text,
	FTFont* fnt,
	GLuint fontsize,
	Pixel Origin,
	int xsize,
	int ysize,
	bool unclickable,
	bool invisible,
	//void (*callback)()
	string callback
	):
ID(id),
origin(Origin),
size_x(xsize),
size_y(ysize),
state(BTN_INACTIVE),
value(false),
font(fnt),
font_size(fontsize),
text(Text),
//fire(callback),
//callback(callback),
invisible(invisible),
unclickable(unclickable),
font_id(""),
sticky(false),
round(false),
textbox(false)
{
	
	set_callback(callback);
	displays[BTN_INACTIVE]=&button_display_inactive;
	displays[BTN_HOVERED]=&button_display_hovered;
	displays[BTN_PRESSED]=&button_display_pressed;
	displays[BTN_ACTIVE]=&button_display_active;
	displays[BTN_HOVERED_ACTIVE]=&button_display_active_hovered;
	displays[BTN_PRESSED_ACTIVE]=&button_display_active_pressed;
	text_displays[BTN_INACTIVE]=&button_text_display;
	text_displays[BTN_HOVERED]=&button_text_hovered;
	text_displays[BTN_PRESSED]=&button_text_pressed;
	text_displays[BTN_ACTIVE]=&button_text_active;
	text_displays[BTN_HOVERED_ACTIVE]=&button_text_hovered;
	text_displays[BTN_PRESSED_ACTIVE]=&button_text_pressed;

//	for(int i=0; i<BTN_STATES; i++) textures[i]=0;
	for(int i=0; i<BTN_STATES; i++) texture_ids[i]="NONE";
	
	glfwGetWindowSize(&window_width,&window_height);
	if(origin.x<0||origin.y<0)
		origin.set(window_width/2,window_height/2);
	adjust_to_text();
	if(!invisible) visibility();
	else invisibility();
};

bool Button::is_hovered()
{
	int x, y;
	glfwGetMousePos(&x, &y);
	y=window_height-y;
	if(round) {
		/*char blah[256];		
		float d=origin.distance(Vertex(x,y));
		sprintf(blah,"Origin: (%.3f,%.3f), Mouse: (%d, %d), distance: %.3f",origin.x,origin.y,x,y,d);		
		cout << blah << endl;*/
		return (origin.distance(Pixel(x,y))<=radius);
	}
	else return ((x>origin.x-0.5*size_x)&&(x<origin.x+0.5*size_x)&&(y>origin.y-0.5*size_y)&&(y<origin.y+0.5*size_y));
}

void Button::update_active(bool i_can_has_mouse){
	
	//cout << ID << " update active" << endl;
	//printf("I can has mouse? : %d\n",(int)i_can_has_mouse);
	if(!i_can_has_mouse)  { state=BTN_ACTIVE; return; }
	else{
		if(sticky) return;
		int mouse=glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT);
		if (mouse==GLFW_PRESS) {state=BTN_PRESSED; return; }
		else { 
			if(state==BTN_PRESSED) {
				state=BTN_HOVERED;
				value=false;
				printf("%s Inactive\n",text.c_str());
				if(GUISounds!=NULL) GUISounds->ambient("CLICK");
			}
			else state=BTN_HOVERED_ACTIVE;
			return;
		}
	}
}

void Button::update_inactive(bool i_can_has_mouse)
{
	//cout << ID << " update inactive" << endl;
	//printf("I can has mouse? : %d\n",(int)i_can_has_mouse);
	if(!i_can_has_mouse) { state=BTN_INACTIVE; return; }
	else{
		int mouse=glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT);
		if (mouse==GLFW_PRESS) {state=BTN_PRESSED; return; }
		else { 
			if(state==BTN_PRESSED) {
				if(GUISounds!=NULL) GUISounds->ambient("CLICK");
				if(!unclickable){
					if(fire!=NULL) fire();
					//if(callback!="NONE") GUIEvents.get(callback)();
					//state=BTN_INACTIVE;
					printf("%s Fired\n",text.c_str());					
					//reset();
					state=BTN_INACTIVE;
					value=true;
					return;
				}
				state=BTN_ACTIVE;
				value=true;
				printf("%s Active\n",text.c_str());
				
			}
			else state=BTN_HOVERED;
			return;
		}
	}
}

bool Button::update()
{	
	if(textbox) return false;
	//cout << ID << " update called" << endl;
	if(value&&!unclickable) value=false;
	bool i_can_has_mouse=is_hovered();
	//if(i_can_has_mouse) cout << ID << " hovered." << endl;
	//else cout << ID << " not hovered." << endl;
	//glfwSleep(1);
	//if(!unclickable) {
	//	//cout << ID << ": " << (int)value << endl;
	//	update_inactive(i_can_has_mouse);
	//	return i_can_has_mouse;
	//	//reset();
	//}
	if(value) update_active(i_can_has_mouse);
	else update_inactive(i_can_has_mouse);
	return i_can_has_mouse;
}

void Button::display()
{
	float minx = origin.x-size_x*0.5;
	float maxx = origin.x+size_x*0.5;
	float miny = origin.y-size_y*0.5;
	float maxy = origin.y+size_y*0.5;
	
	
	//glDisable(GL_DEPTH_TEST);
	if(!invisible&&displays[state]!=NULL){
		if(texture_ids[state]!="NONE"){
			glBindTexture(GL_TEXTURE_2D,GUITextures->get(texture_ids[state]));
		}
		else{
			glBindTexture(GL_TEXTURE_2D,0);
		}
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
		//else glDisable(GL_TEXTURE_2D);
		displays[state](minx,maxx,miny,maxy);
		/*if(texture_ids[state]=="NONE"){
			glEnable(GL_TEXTURE_2D);
		}*/
	}
	//glDisable(GL_TEXTURE_2D);
	render_text();
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_DEPTH_TEST);
	
}

//void Button::adjust_to_text()
//{
//	if((text=="")||(font==NULL)||(font_size==0)) return;
//	font->FaceSize(font_size);
//	FTBBox box=font->BBox(text.c_str());
//	float x=(box.Upper().Xf()-box.Lower().Xf());
//	float y=(box.Upper().Yf()-box.Lower().Yf());
//	size_x=ceil(x)+20;
//	size_y=ceil(y)+20;
//}

//void Button::adjust_text_to_size()
//{
//	if((text=="")||(font==NULL)||(font_size==0)) return;
//
//	unsigned int new_font_size=font_size;
//	int x, y;
//	do{
//		font->FaceSize(new_font_size--);
//		FTBBox box=font->BBox(text.c_str());
//		x=ceil(box.Upper().Xf()-box.Lower().Xf())+20;
//		y=ceil(box.Upper().Yf()-box.Lower().Yf())+20;
//	}while(((x>size_x)||(y>size_y))&&(new_font_size>0));
//
//	font_size=new_font_size+1;
//	printf("New size: %d\n",font_size);
//}


void Button::adjust_to_text()
{
	if((text=="")||(font==NULL)||(font_size==0)) return;
	//font->FaceSize(font_size);
	FTBBox box=font->BBox(text.c_str());
	float x=(box.Upper().Xf()-box.Lower().Xf());
	float y=(box.Upper().Yf()-box.Lower().Yf());
	size_x=ceil(x)+BTN_BORDER_FACTOR*font_size;//20;
	size_y=ceil(y)+BTN_BORDER_FACTOR*font_size;//20;
}


void Button::reduce_text_to_size()
{
	if((text=="")||(font==NULL)||(font_size==0)||(font_id=="")) return;

	unsigned int new_font_size=font_size;
	int x, y;
	do{		
		font=GUIFonts->get_font(font_id,new_font_size--);//->FaceSize(new_font_size--);
		FTBBox box=font->BBox(text.c_str());
		x=ceil(box.Upper().Xf()-box.Lower().Xf())+BTN_BORDER_FACTOR*font_size;//20;
		y=ceil(box.Upper().Yf()-box.Lower().Yf())+BTN_BORDER_FACTOR*font_size;//20;
	}while(((x>size_x)||(y>size_y))&&(new_font_size>0));

	font_size=new_font_size+1;
	//printf("New size: %d\n",font_size);
}


void Button::render_text()
{
	if((text=="")||(font==NULL)||(font_size==0)) return;
	//glCallList(textlists[state]);
	
	//font->FaceSize(font_size);
	//FTPoint pt=stringseed(text.c_str(),origin,font);
	FTBBox box=font->BBox(text.c_str());
	Pixel textorigin(origin.x, origin.y-box.Lower().Yf());
	
	text_displays[state]();
	font->Render(text.c_str(),-1,stringseed(text.c_str(),textorigin,font));
	
	
	
}

bool Button::set_display(GLuint state, void (*fn)(float minx, float maxx, float miny, float maxy)) 
{ 
	if(state<=BTN_STATES){
		displays[state]=fn;
		return true;
	}
	else return false; 
}

bool Button::set_text_display(GLuint state, void (*fn)()) 
{ 
	if(state<=BTN_STATES){
		text_displays[state]=fn;
		return true;
	}
	else return false; 
}

void Button::invisibility()
{
	invisible=true;
	if((text=="")||(font==NULL)||(font_size==0)) return;
	font->FaceSize(font_size);
	FTBBox box=font->BBox(text.c_str());
	float x=(box.Upper().Xf()-box.Lower().Xf());
	float y=(box.Upper().Yf()-box.Lower().Yf());
	size_x=ceil(x);
	size_y=ceil(y);
}

void Button::visibility()
{
	invisible=false;
	adjust_to_text();
}

void Button::set_font(string font_id, unsigned int font_size)
{
	Button::font_size=font_size;
	Button::font_id=font_id;
	font=GUIFonts->get_font(font_id, font_size);
}

void Button::upper_left(Pixel upper_left)
{
	origin.set(upper_left.x+0.5*size_x,upper_left.y-0.5*size_y);

}
void Button::lower_left(Pixel lower_left)
{
	origin.set(lower_left.x+0.5*size_x,lower_left.y+0.5*size_y);
}
void Button::upper_right(Pixel upper_right)
{
	origin.set(upper_right.x-0.5*size_x,upper_right.y-0.5*size_y);
}
void Button::lower_right(Pixel lower_right)
{
	origin.set(lower_right.x-0.5*size_x,lower_right.y-0.5*size_y);
}
