#include "GUI.List.h"

extern FontSystem* GUIFonts;

List::List(string list_id, string listmap,string font_id, unsigned int font_size, unsigned int default_option)
{
	menumap=listmap;
	ID=list_id;
	Sublists.push_back(new List());	
	Submenus.push_back(Sublists.back());
	Sublists.back()->load_menu(listmap);
	Entries.push_back(Button());
	Button* btn=Sublists[0]->get_entry(default_option-1);
	
	active=true;
	
	int x,y;
	btn->get_size(x,y);
	size_x=x;
	size_y=-y;
	Entries[0].set_size(x,y);
	Entries[0].set_text(btn->get_text());
	origin.set(Entries[0].get_origin().x-0.5*x, Entries[0].get_origin().y+0.5*y);

	set_font(font_id,font_size);
	btn->get_size(x,y);
	size_x=x;
	size_y=-y;
	Entries[0].set_size(x,y);
	
	build_map();
}

//DFS
bool List::update_internals()
{
	if((!active)||(Entries.size()==NULL))
		return false;
	
	bool flag=false, flag2=is_hovered();

	if(Sublists.size()!=NULL)
		for(int i=0; i<Entries.size(); i++)
			if(Sublists[i]!=NULL){
				flag=flag||Sublists[i]->update();
			}
	
	//The mouse is on a submenu of mine
	if(flag) return true;

	//The mouse is neither on a submenu of mine nor on me
	if(!flag&&!flag2){
		for(int i=0; i<Entries.size(); i++){
			if(!Entries[i].get_value()){
			
				Entries[i].reset();
			}
			else if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)){
				Submenus[i]->deactivate();
				Entries[i].reset();
			}
		}
		return false;
	}
	
	//I can has mouse
	for(int i=0; i<Entries.size(); i++){
		if((Sublists.size()!=NULL)&&(Sublists[i]!=NULL)) Sublists[i]->deactivate();		
		if((Entries[i].update())&&(Sublists.size()!=NULL)&&(Sublists[i]!=NULL)&&Entries[i].get_value()){
			Sublists[i]->activate();
			int newx, newy;
			Pixel new_origin;
			int subx, suby;
			Sublists[i]->get_size(subx, suby);
			Sublists[i]->set_order(L2R);
			int w,h;
			glfwGetWindowSize(&w,&h);
			if(L2R){
				if(origin.x+size_x+subx>w) {
					Sublists[i]->set_order(!L2R);
					newx=origin.x-subx;					
				}
				else{
					newx=origin.x+size_x;
				}
				newy=origin.y+i*size_y/(int)Entries.size();
			}
			else{
				if(origin.x-subx<0) {
					Sublists[i]->set_order(!L2R);
					newx=origin.x+size_x;
				}
				else{
					newx=origin.x-subx;
				}
				newy=origin.y+i*size_y/(int)Entries.size();
			}
			new_origin.set(newx,newy);
			Sublists[i]->set_origin(new_origin);	
		}		
	}
	return true;
}

void List::execute()
{
	for(map<string, Button*>::iterator i=Commands.begin(); i!=Commands.end(); i++){
		if (i->second->get_value()){
			cout << "Active is " << i->second->get_ID() << ". ";
			Entries[0].set_text(i->second->get_text());
			Sublists[0]->deactivate();
			i->second->reset();
			Entries[0].reset();
		}

	}
}

void List::set_selection(string id)
{
	Entries[0].set_text(id);
	Sublists[0]->deactivate();
}