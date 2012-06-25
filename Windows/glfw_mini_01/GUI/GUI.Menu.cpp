#include "GUI.Menu.h"

extern SoundSystem* GUISounds;
extern FontSystem* GUIFonts;

Menu::Menu():
Entries(NULL),
Submenus(NULL),
active(false),
font(NULL),
font_size(10),
L2R(true),
font_id(""),
ID(""),
menumap("")
{
	int window_width, window_height;
	glfwGetWindowSize(&window_width,&window_height);

	displays[BTN_INACTIVE]=&button_display_inactive;
	displays[BTN_HOVERED]=&button_display_hovered;
	displays[BTN_PRESSED]=&button_display_pressed;
	displays[BTN_ACTIVE]=&button_display_active;
	displays[BTN_HOVERED_ACTIVE]=&button_display_active_hovered;
	displays[BTN_PRESSED_ACTIVE]=&button_display_active_pressed;

	for(int i=0; i<BTN_STATES; i++) texture_ids[i]="NONE";

	origin.set(0,window_height);
	CalculateInternals();
}

void Menu::make_entries(unsigned int entries)
{
	for(int i=0; i< entries; i++){
		Entries.push_back(Button());
		Submenus.push_back(NULL);
	}
}

void Menu::set_font(string font_id, unsigned int font_size)
{
	if(Entries.size()==0)return;
	Menu::font_id=font_id;
	for(int i=0; i<Entries.size(); i++){
		Entries[i].set_font(font_id,font_size);
		Entries[i].adjust_to_text();
	}
	if(Submenus.size()!=0)
		for(int i=0; i<Entries.size(); i++)
			if(Submenus[i]!=NULL)
				Submenus[i]->set_font(font_id, font_size);
	CalculateInternals();
}

Menu::~Menu()
{
	for(int i=0; i<Entries.size(); i++) if(Submenus[i]!=NULL) delete Submenus[i];
}

void Menu::adjust_origin()
{
	int x=origin.x, y=origin.y, w, h;
	glfwGetWindowSize(&w,&h);
	if(L2R){
		if((x+size_x<=w)&&(y+size_y>=0)) return;
		else{
			int newx=x, newy=y;
			if(x+size_x>w){
				newx=x-size_x;
				if(newx<0) newx=w-size_x;
			}
			if(y+size_y<0){
				if(PATH==0){
					newy=y-size_y;
				}
				else{
					newy=y-size_y*(float)(Entries.size()-1)/(float)Entries.size();
				}
				if(newy>h) newy=-size_y;			
			}
			origin.set(newx,newy);
		}
	}
	else{
		if(y+size_y>=0) return;
		else{
			if(y+size_y<0){
				int newy=y-size_y*(float)(Entries.size()-1)/Entries.size();
				if(newy>h) newy=-size_y;
				origin.y=newy;
			}
		}
	}
	CalculateInternals();
}


void Menu::set_origin(Pixel upper_left)
{
	if(Entries.size()==NULL) return;
	origin=upper_left;
	CalculateInternals();
	adjust_origin();
}

void Menu::set_origin()
{
	if(Entries.size()==NULL) return;
	int x, y, w, h;
	glfwGetMousePos(&x,&y);
	glfwGetWindowSize(&w,&h);
	y=h-y;
	origin.set(x,y);
	CalculateInternals();
	adjust_origin();
}

void Menu::CalculateInternals()
{
	if(Entries.size()==NULL)return;
	unsigned int min_font=1000, max_xsize=0, max_ysize=0;
	int tempfont, tempx, tempy;
	for(int i=0; i<Entries.size(); i++){
		if(Entries[i].get_text()!=""){
			tempfont=Entries[i].get_font_size();
			Entries[i].get_size(tempx,tempy);
			if(tempfont<min_font) min_font=tempfont;
			if(tempx>max_xsize) { max_xsize=tempx; max_ysize=tempy; }
		}
	}
	for(int i=0; i<Entries.size(); i++){
		Entries[i].set_font(font_id,min_font);
		Entries[i].set_size(max_xsize,max_ysize);
		Entries[i].set_origin(
			Pixel(
				origin.x+0.5*max_xsize,
				origin.y-(0.5+i)*max_ysize
				)
			);
	}
	font_size=min_font;
	size_x=max_xsize;
	size_y=-max_ysize*Entries.size();
	if(Submenus.size()!=NULL)
		for(int i=0; i<Entries.size(); i++)
			if(Submenus[i]!=NULL)
				Submenus[i]->CalculateInternals();
		

}

bool Menu::is_hovered()
{
	int x, y, w, h;
	glfwGetMousePos(&x, &y);
	glfwGetWindowSize(&w, &h);
	y=h-y;
	return ((x>origin.x)&&(x<origin.x+size_x)&&(y<origin.y)&&(y>origin.y+size_y));
}

//DFS
bool Menu::update_internals()
{
	if((!active)||(Entries.size()==NULL))
		return false;
	
	bool flag=false, flag2=is_hovered();

	if(Submenus.size()!=NULL)
		for(int i=0; i<Entries.size(); i++)
			if(Submenus[i]!=NULL){
				flag=flag||Submenus[i]->update();
			}
	
	//The mouse is on a submenu of mine
	if(flag) return true;

	//The mouse is neither on a submenu of mine nor on me
	if(!flag&&!flag2) return false;
	
	//I can has mouse
	for(int i=0; i<Entries.size(); i++){
		if(Entries[i].get_state()==BTN_ACTIVE) Entries[i].reset();
		if((Submenus.size()!=NULL)&&(Submenus[i]!=NULL)) Submenus[i]->deactivate();		
		if((Entries[i].update())&&(Submenus.size()!=NULL)&&(Submenus[i]!=NULL)){
			Submenus[i]->activate();
			int newx, newy;
			Pixel new_origin;
			int subx, suby;
			Submenus[i]->get_size(subx, suby);
			Submenus[i]->set_order(L2R);
			int w,h;
			glfwGetWindowSize(&w,&h);
			if(L2R){
				if(origin.x+size_x+subx>w) {
					Submenus[i]->set_order(!L2R);
					newx=origin.x-subx;					
				}
				else{
					newx=origin.x+size_x;
				}
				newy=origin.y+i*size_y/(int)Entries.size();
			}
			else{
				if(origin.x-subx<0) {
					Submenus[i]->set_order(!L2R);
					newx=origin.x+size_x;
				}
				else{
					newx=origin.x-subx;
				}
				newy=origin.y+i*size_y/(int)Entries.size();
			}
			new_origin.set(newx,newy);
			Submenus[i]->set_origin(new_origin);	
		}		
	}
	return true;
}

void Menu::make_report()
{
	flags.clear();
	for(map<string,Button*>::iterator i=Commands.begin(); i!=Commands.end(); i++)
		flags.insert(flags.begin(),pair<string,bool>(i->first,i->second->get_value()));

}

void Menu::execute()
{
	for(map<string, Button*>::iterator i=Commands.begin(); i!=Commands.end(); i++){
		if (i->second->get_value()){
			cout << "Active is " << i->second->get_ID() << ". " << PATH << " reporting." << endl;
			if(i->second->fire) i->second->fire();
			i->second->reset();
		}
	}
}


bool Menu::update()
{
	bool flag=update_internals();
	make_report();
	if(flag) execute();
	return flag;
}

//BFS
void Menu::display()
{
	if((!active)||(Entries.size()==NULL))return;
	for(int i=0; i<Entries.size(); i++){
		Entries[i].display();
	}
	if(Submenus.size()!=NULL)
		for(int i=0; i<Entries.size(); i++)
			if(Submenus[i]!=NULL)
				Submenus[i]->display();	
}

void Menu::add_entry_text(unsigned int entry, string Text)
{
	if((Entries.size()==NULL)||(entry < 1)||(entry>Entries.size()))return;
	Entries[entry-1].set_text(Text);
	Entries[entry-1].adjust_to_text();
	CalculateInternals();
}

Menu* Menu::get_submenu(unsigned int which)
{
	if((which>Entries.size())||(Submenus.size()==NULL)||(Submenus[which-1]==NULL))
		return NULL;
	else
		return Submenus[which-1]; 
}

void Menu::deactivate()
{
	if(!active||Entries.size()==NULL) return;
	if(Submenus.size()!=NULL)
		for(int i=0; i<Entries.size(); i++)
			if(Submenus[i]!=NULL)
				Submenus[i]->deactivate();
	active=false;
	for(int i=0; i<Entries.size(); i++)
		Entries[i].reset();
}

Menu::Menu(string menu_id, string menumap, string font_id, unsigned int font_size):
Entries(NULL),
Submenus(NULL),
active(false),
font_id(font_id),
font(NULL),
menumap(menumap),
ID(menu_id),
L2R(true)
{
	int window_width, window_height;
	glfwGetWindowSize(&window_width,&window_height);
	origin.set(0,window_height);
	load_menu(menumap);

	displays[BTN_INACTIVE]=&button_display_inactive;
	displays[BTN_HOVERED]=&button_display_hovered;
	displays[BTN_PRESSED]=&button_display_pressed;
	displays[BTN_ACTIVE]=&button_display_active;
	displays[BTN_HOVERED_ACTIVE]=&button_display_active_hovered;
	displays[BTN_PRESSED_ACTIVE]=&button_display_active_pressed;

	for(int i=0; i<BTN_STATES; i++) texture_ids[i]="NONE";

	set_font(font_id,font_size);
	build_map();
}

bool Menu::load_menu(string file)
{
	ifstream in(file);
	read_menu(in);
	string s;
	while(!in.eof())
	{
		Menu* ptr=new Menu();
		if(ptr->read_menu(in)){
			add(ptr,ptr->get_path());
		}		
	}
	in.close();
	return true;
}

Menu* Menu::read_menu(ifstream& file)
{
	string s;
	if(!getline(file,s)||(s!="BEGIN")){
		if(this!=NULL) {
			delete this;
			return NULL;
		}
	}
	if(!getline(file,s)||(s=="END")){
		if(this!=NULL) {
			delete this;
			return NULL;
		}
	}
	PATH=atoi(s.c_str());
	while(getline(file,s)&&s!="END"){
		string ID=s;
		getline(file,s);
		Entries.push_back(Button(ID,s,font,font_size));
		Submenus.push_back(NULL);
	}
	return this;
}

bool Menu::add(Menu* submenu, unsigned int pathcode)
{
	if(this==NULL||pathcode==0) return false;
	if(pathcode<MENU_MAX_ENTRIES){
		if(pathcode>Entries.size()||Submenus[pathcode-1]!=NULL) return false;
		Submenus[pathcode-1]=submenu;
		return true;
	}
	unsigned int a=pathcode/(int)MENU_MAX_ENTRIES, b=pathcode%(int)MENU_MAX_ENTRIES;
	if(b>Entries.size()) return false;
	if(Submenus[b-1]==NULL) Submenus[b-1]=new Menu;
	return Submenus[b-1]->add(submenu,a);
	
}

void Menu::build_map()
{
	if(Commands.size()!=0) Commands.clear();
	
	Commands=finals();

	map<string,Button*>::iterator i=Commands.begin();
	for(i; i!=Commands.end(); i++) cout << i->first << endl;
}

map<string, Button*> Menu::finals()
{
	map<string, Button*> result;
	for(int i=0; i<Entries.size(); i++){
		if(Submenus[i]==NULL){
			result.insert(pair<string,Button*>(Entries[i].get_ID(),&Entries[i]));
		}
	}
	for(int i=0; i<Submenus.size(); i++){
		if(Submenus[i]!=NULL){
			map<string, Button*> temp=Submenus[i]->finals();
			result.insert(temp.begin(),temp.end());
		}
	}
	return result;
}

vector<string> Menu::get_commands()
{
	vector<string> result;
	map<string,Button*>::iterator i=Commands.begin();
	for(i; i!=Commands.end(); i++)
		result.push_back(i->first);
	return result;
}

void Menu::set_texture(GLuint state, string texture_id)
{ 
	if(Entries.size()==0) return;
	texture_ids[state]=texture_id;
	for(int i=0;i<Entries.size();i++) {
		Entries[i].set_texture(state,texture_id);
		if(Submenus[i]!=NULL) Submenus[i]->set_texture(state, texture_id);
	} 
}

void Menu::set_display(GLuint state, void (*fn)(float minx, float maxx, float miny, float maxy))
{
	if(Entries.size()==0) return;
	displays[state]=fn;
	for(int i=0;i<Entries.size();i++) {
		Entries[i].set_display(state,fn);
		if(Submenus[i]!=NULL) Submenus[i]->set_display(state, fn);
	} 
}