#include "GUI.Layout.h"

extern FontSystem *GUIFonts;
extern UITexturing* GUITextures;
extern UIScreens* GUIScreens;
extern UIEvents* GUIEvents;
extern SoundSystem* GUISounds;

void LayoutSwitch::switch_layout()
{
	source->set_active(false);
	target->set_active(true);
	Button* b=source->get_button(trigger_id);
	if(b->fire) b->fire();
	b->reset();
	GUIScreens->current=target;
}

void LayoutSwitch::update()
{
}


void Layout::play_bgm()
{
	if(!GUISounds) return;
	if(!bgm_playing){
		BGM=GUISounds->ambientloop(BGM_ID);
		bgm_playing=true;
	}
}

void Layout::stop_bgm()
{
	if(!GUISounds) return;
	GUISounds->stop(BGM);
	bgm_playing=false;
}

bool Layout::update()
{
	if(has_bgm&&!bgm_playing) 
		play_bgm();	
	bool flag=update_internals();
	compile_report();
	return flag;
}

void Layout::compile_report()
{
	booleans.clear();
	floats.clear();
	strings.clear();
	ints.clear();

	for(map<string,Layout>::iterator i=tabbed_layouts.begin(); i!=tabbed_layouts.end(); i++) {

		i->second.compile_report();

		map<string,bool>* tab_bools=i->second.get_bools();
		booleans.insert(tab_bools->begin(),tab_bools->end());

		map<string,float>* tab_floats=i->second.get_floats();
		floats.insert(tab_floats->begin(),tab_floats->end());

		map<string,string>* tab_strings=i->second.get_strings();
		strings.insert(tab_strings->begin(),tab_strings->end());

		map<string,int>* tab_ints=i->second.get_ints();
		ints.insert(tab_ints->begin(),tab_ints->end());
	}
		
	for(int i=0; i<sliders.size(); i++){
			floats.insert(floats.begin(),pair<string,float>(sliders[i].get_ID(),sliders[i].get_value()));
			ints.insert(ints.begin(),pair<string,int>(sliders[i].get_ID(),sliders[i].get_int()));
		
	}

	for(int i=0; i<buttonarrays.size(); i++){
		strings.insert(strings.begin(),pair<string,string>(buttonarrays[i].get_ID(),buttonarrays[i].get_active()));
	}
	
	for(int i=0; i<buttons.size(); i++){
		booleans.insert(booleans.begin(),pair<string,bool>(buttons[i].get_ID(),buttons[i].get_value()));
	}
		
	for(int i=0; i<menus_static.size(); i++){
		List* l = dynamic_cast<List*>(menus_static[i]);
		if(l==NULL) {
			map<string,bool>* flags=menus_static[i]->get_flags();
		}
		else {
			strings.insert(strings.begin(),pair<string,string>(l->get_ID(),l->get_selection()));
		}
	}

	for(int i=0; i<menus_floating.size(); i++){
		List* l = dynamic_cast<List*>(menus_floating[i]);
		if(l==NULL) {
			map<string,bool>* flags=menus_floating[i]->get_flags();
		}
		else {
			strings.insert(strings.begin(),pair<string,string>(l->get_ID(),l->get_selection()));
		}
	}

	for(int i=0; i<consoles.size(); i++){
		strings.insert(strings.begin(),pair<string,string>(consoles[i].get_ID(),consoles[i].get_content()));
	}
}



bool Layout::update_internals()
{
	if(!active) return false;

	bool flag=false, flag2=false;
	for(int i=0; i<menus_floating.size(); i++){		
		flag2=menus_floating[i]->update();
		flag=flag||flag2;
	}
	if(flag) return true;

	for(int i=0; i<consoles.size(); i++){		
		flag2=consoles[i].update();
		flag=flag||flag2;
	}
	if(flag) return true;

	for(int i=0; i<menus_static.size(); i++){		
		flag2=menus_static[i]->update();
		flag=flag||flag2;
	}
	if(flag) return true;
	
	for(int i=0; i<sliders.size(); i++){
		flag2=sliders[i].update();
		flag=flag||flag2;		
	}
	if(flag) return true;

	flag2=tabs.update();
	flag=flag||flag2;
	map<string,Layout>::iterator i;
	if(flag){
		for(i=tabbed_layouts.begin(); i!=tabbed_layouts.end(); i++){
			i->second.set_active(tabs.get_active()==i->second.ID);
		}
		return true;
	}

	if(tabs.number_of_buttons()!=NULL&&tabs.get_active()!=""){ 
		flag2=tabbed_layouts[tabs.get_active()].update();
		flag=flag||flag2;
	}
	if(flag) return true;
	
	for(int i=0; i<buttonarrays.size(); i++){
		flag2=buttonarrays[i].update();
		flag=flag||flag2;		
	}
	if(flag) return true;
	
	for(int i=0; i<buttons.size(); i++){
		flag2=buttons[i].update();
		flag=flag||flag2;
	}
	
	for(int i=0; i<switches.size(); i++){
		Button* btn=get_button(switches[i].trigger_id);
		if(btn->get_value())
			switches[i].switch_layout();
	}
	if(flag) return true;

	return false;
}

void Layout::display()
{	
	if(!active) return;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for(int i=0; i<quads.size(); i++){
		display_quad(i);
	}

	tabs.display();
	map<string,Layout>::iterator i=tabbed_layouts.begin();
	
	for(int i=0; i<sliders.size(); i++){
		sliders[i].display();
	}

	for(int i=0; i<buttonarrays.size(); i++){
		buttonarrays[i].display();
	}
	
	for(int i=0; i<buttons.size(); i++){
		buttons[i].display();
	}
		
	for(int i=0; i<menus_static.size(); i++){
		menus_static[i]->display();
	}

	if(tabs.number_of_buttons()!=NULL&&tabs.get_active()!="") tabbed_layouts[tabs.get_active()].display();

	for(int i=0; i<texts.size(); i++){
		texts[i].display();
	}

	for(int i=0; i<consoles.size(); i++){
		consoles[i].display();
	}

	for(int i=0; i<menus_floating.size(); i++){
		menus_floating[i]->display();
	}

	glDisable(GL_BLEND);
}

Layout::~Layout()
{
	for(int i=0; i<menus_static.size(); i++) delete menus_static[i];
	for(int i=0; i<menus_floating.size(); i++) delete menus_floating[i];
}

void Layout::display_quad(int index)
{
	if(quads[index].texture_id!="NONE") {
		glBindTexture(GL_TEXTURE_2D,GUITextures->get(quads[index].texture_id));
	}
	else glBindTexture(GL_TEXTURE_2D,0);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	glColor3f(0,0,1);
	glBegin(GL_QUADS);
		glTexCoord2i(0,0);
		glVertex2f(quads[index].lower_left.x,quads[index].lower_left.y);
		glTexCoord2i(1,0);
		glVertex2i(quads[index].upper_right.x,quads[index].lower_left.y);
		glTexCoord2i(1,1);
		glVertex2i(quads[index].upper_right.x,quads[index].upper_right.y);
		glTexCoord2i(0,1);
		glVertex2i(quads[index].lower_left.x,quads[index].upper_right.y);
	glEnd();
}

void Layout::add_tab(string id, Layout& tab)
{
	tabs.add_button(Button(id));
	tab.set_ID(id);
	tabbed_layouts.insert(tabbed_layouts.begin(),pair<string,Layout>(id, tab));
	if(tabbed_layouts.size()==1) activate_tab(id);
	else {
		tabs.get_button(id)->reset();
		tabbed_layouts[id].set_active(false);
	}
}

void Layout::add_tab(Button& head, Layout& tab)
{
	string id=head.get_ID();
	tabs.add_button(head);
	tab.set_ID(id);
	tabbed_layouts.insert(tabbed_layouts.begin(),pair<string,Layout>(id, tab));
	if(tabbed_layouts.size()==1) activate_tab(id);
	else {
		tabs.get_button(id)->reset();
		tabbed_layouts[id].set_active(false);
	}
}


void Layout::activate_tab(string ID) 
{ 
	if(ID=="") return;
	tabs.get_button(ID)->force_active();
	tabbed_layouts[ID].set_active(true);
	tabs.set_active(ID); 
}

bool Layout::save_configuration(string filename)
{
	
	
	ofstream out(filename);
	if(!out) return false;
	
	save(out);	

	out.close();

	return true;
}

bool Layout::save(ofstream& out)
{
	int w, h;
	glfwGetWindowSize(&w,&h);

	out << "LAYOUT" << endl;
	out << ID << endl;
	out << "BEGIN" << endl;
	out << w << endl << h << endl;

	out << "QUADS" << endl << quads.size() << endl;
	for(int i=0; i<quads.size(); i++){
		save_quad(out,&quads[i]);
	}

	out << "TEXTS" << endl << texts.size() << endl;
	for(int i=0; i<texts.size(); i++){
		save_text(out, &texts[i]);
	}

	out << "SLIDERS" << endl << sliders.size() << endl;
	for(int i=0; i<sliders.size(); i++){
		save_slider(out,&sliders[i]);
	}

	out << "BUTTONS" << endl << buttons.size() << endl;
	for(int i=0; i<buttons.size(); i++){
		save_button(out,&buttons[i]);
	}

	out << "BUTTONARRAYS" << endl << buttonarrays.size() << endl;
	for(int i=0; i<buttonarrays.size(); i++){
		save_buttonarray(out,&buttonarrays[i]);
	}

	out << "STATIC MENUS" << endl << menus_static.size() << endl;
	for(int i=0; i<menus_static.size(); i++) {
		List* l = dynamic_cast<List*>(menus_static[i]);
		if(l!=NULL) save_list(out, l);
		else save_menu(out, menus_static[i]);
	}

	out << "FLOATING MENUS" << endl << menus_floating.size() << endl;
	for(int i=0; i<menus_floating.size(); i++) {
		List* l = dynamic_cast<List*>(menus_floating[i]);
		if(l!=NULL) save_list(out, l);
		else save_menu(out, menus_floating[i]);
	}

	vector<string> tbs=tabs.get_button_ids();
	out << "TABS" << endl << tbs.size() << endl;
	out << "ACTIVE" << endl << tabs.get_active() << endl;
	for(int i=0; i<tbs.size(); i++){
		Tab t=get_tab(tbs[i]);
		save_tab(out,&t);		
	}
	
	out << "SWITCHES" << endl << switches.size() << endl;
	for(int i=0; i<switches.size(); i++) {
		save_switch(out, &switches[i]);
	}


	out << ID << " ENDS" << endl;
	

	return true;
}

void Layout::save_switch(ofstream& out, LayoutSwitch* lsw)
{
	out<< "SWITCH" << endl << lsw->trigger_id << endl << lsw->target->get_ID() << endl;
}


void Layout::save_text(ofstream& out, Text* t)
{
	out << "TEXT" << endl;
	out << t->text << endl
		<< t->font << endl
		<< t->font_size << endl
		<< t->origin.x << endl
		<< t->origin.y << endl;
	out << t->text_colour.r << endl
		<< t->text_colour.g << endl
		<< t->text_colour.b << endl
		<< t->text_colour.a << endl;
}

void Layout::save_slider(ofstream& out, Slider* sl)
{
	out << "SLIDER" << endl;
	int x, y;
	sl->get_control()->get_size(x,y);
	out << sl->get_ID() << endl
		<< x << endl << y << endl << sl->get_bar_height_factor() << endl
		<< sl->get_from().x << endl << sl->get_from().y << endl
		<< sl->get_to().x << endl << sl->get_to().y << endl
		<< sl->get_value() << endl
		<< sl->get_bar_texture() << endl
		<< sl->get_control_texture() << endl;
}

void Layout::save_quad(ofstream& out, Quad* q)
{
	out << "QUAD" << endl;
	out << q->lower_left.x << endl << q->lower_left.y << endl
		<< q->upper_right.x << endl << q->upper_right.y << endl
		<< q->texture_id << endl;
}

void Layout::save_button(ofstream& out, Button* b)
{
	int x, y;
	b->get_size(x,y);
	out << "BUTTON" << endl;
	out << b->get_ID() << endl
		<< b->get_font_id() << endl
		<< b->get_font_size() << endl;
	if(b->is_unclickable())	out << "UNCLICKABLE" << endl; else out << "NON_UNCLICKABLE" << endl;
	if(b->is_sticky())	out << "STICKY" << endl; else out << "NON_STICKY" << endl;
	if(b->is_round())	out << "ROUND" << endl; else out << "SQUARE" << endl;
	if(b->is_invisible())	out << "INVISIBLE" << endl; else out << "VISIBLE" << endl;
	if(b->is_textbox())	out << "TEXTBOX" << endl; else out << "REGULAR" << endl;
	out	<< b->get_text() << endl
		<< b->get_origin().x << endl << b->get_origin().y << endl
		<< x << endl << y << endl;
	for(int i=BTN_INACTIVE;i<BTN_STATES;i++){
		out << i << endl << b->get_texture(i) << endl;
		if(b->has_display(i)) out << "NOT NULL" << endl; else out << "NULL" << endl;
	}
}

void Layout::save_buttonarray(ofstream& out, ButtonArray* ba)
{
	vector<string> btns=ba->get_button_ids();
	out << "BUTTONARRAY" << endl
		<< ba->get_ID() << endl
		<< btns.size() << endl
		<< ba->get_active() << endl;
	for(int i=0;i<btns.size(); i++){
		save_button(out, ba->get_button(btns[i]));
	}
}

void Layout::save_menu(ofstream& out, Menu* m)
{
	out << "MENU" << endl;
	out << m->get_ID() << endl
		<< m->get_origin().x << endl << m->get_origin().y << endl
		<< m->get_font() << endl << m->get_font_size() << endl
		<< m->get_menumap() << endl;
	for(int i=BTN_INACTIVE;i<BTN_STATES;i++){
		out << i << endl;
		out << m->get_texture(i) << endl;
		if(m->has_display(i)) out << "NOT NULL" << endl; else out << "NULL" << endl;
	}
}

void Layout::save_list(ofstream& out, List* l)
{
	out << "LIST" << endl;
	out << l->get_ID() << endl 
		<< l->get_origin().x << endl << l->get_origin().y << endl 
		<< l->get_font() << endl << l->get_font_size() << endl
		<< l->get_menumap() << endl;
	out << "CHOICE" << endl << l->get_selection() << endl;
	for(int i=BTN_INACTIVE;i<BTN_STATES;i++){
		out << i << endl;
		out << l->get_texture(i) << endl;
		if(l->has_display(i)) out << "NOT NULL" << endl; else out << "NULL" << endl;
	}
}

void Layout::save_tab(ofstream& out, Tab* t)
{
	out<< "TAB" << endl << t->tab_header->get_ID() << endl;
	out<<"TAB HEADER"<< endl;
	save_button(out,t->tab_header);
	out<<"TAB BODY" << endl;
	t->tab_layout->save(out);
}

bool Layout::load_configuration(string filename)
{	
	ifstream in(filename);
	if(!in) return false;
	
	reset();

	load(in);	

	in.close();

	compile_report();

	return true;
}

bool Layout::load_configuration(ifstream& filename)
{	
	
	reset();

	load(filename);	

	compile_report();

	return true;
}

bool Layout::load(ifstream& in)
{
	int w, h;
	glfwGetWindowSize(&w,&h);

	string s;
	getline(in, s);
	if(s!="LAYOUT") return false;
	getline(in,ID);
	getline(in,s);
	if(s!="BEGIN") return fail();	

	int layout_x, layout_y;
	float xfactor, yfactor;

	getline(in,s);
	layout_x=atoi(s.c_str());
	getline(in,s);
	layout_y=atoi(s.c_str());

	xfactor=(float)w/(float)layout_x;
	yfactor=(float)w/(float)layout_x;
		
	getline(in,s);
	if(s!="QUADS") return fail();

	getline(in,s);
	int multitude=atoi(s.c_str());

	for(int i=0; i<multitude; i++){
		Quad q=load_quad(in, xfactor, yfactor);
		add_quad(q.lower_left.x,q.lower_left.y,q.upper_right.x-q.lower_left.x,q.upper_right.y-q.lower_left.y,q.texture_id);
	}

	getline(in,s);
	if(s!="TEXTS") return fail();

	getline(in,s);
	multitude=atoi(s.c_str());

	for(int i=0; i<multitude; i++){
		add_text(load_text(in, xfactor, yfactor));
	}
	
	getline(in,s);
	if(s!="SLIDERS") return fail();

	getline(in,s);
	multitude=atoi(s.c_str());

	for(int i=0; i<multitude; i++){
		add_slider(load_slider(in, xfactor, yfactor));
	}

	getline(in,s);
	if(s!="BUTTONS") return fail();

	getline(in,s);
	multitude=atoi(s.c_str());

	for(int i=0; i<multitude; i++){
		add_button(load_button(in, xfactor, yfactor));
	}	

	getline(in,s);
	if(s!="BUTTONARRAYS") return fail();

	getline(in,s);
	multitude=atoi(s.c_str());

	for(int i=0; i<multitude; i++){
		add_buttonarray(load_buttonarray(in, xfactor, yfactor));
	}
	
	getline(in,s);
	if(s!="STATIC MENUS") return fail();

	getline(in,s);
	multitude=atoi(s.c_str());

	for(int i=0; i<multitude; i++){
		add_static_menu(load_menu(in, xfactor, yfactor));
	}

	getline(in,s);
	if(s!="FLOATING MENUS") return fail();

	getline(in,s);
	multitude=atoi(s.c_str());

	for(int i=0; i<multitude; i++){
		add_floating_menu(load_menu(in, xfactor, yfactor));
	}

	
	getline(in,s);
	if(s!="TABS") return fail();

	getline(in,s);
	multitude=atoi(s.c_str());
	getline(in,s);
	if(s!="ACTIVE") return fail();
	getline(in,s);
	for(int i=0; i<multitude; i++){
		load_tab(in, xfactor, yfactor);
	}
	activate_tab(s);
	

	getline(in,s);
	if(s!="SWITCHES") return fail();	
	getline(in,s);
	multitude=atoi(s.c_str());
	for(int i=0; i<multitude; i++) {
		load_switch(in);		
	}

	

	getline(in,s);
	string s2=ID+" ENDS";
	if(s!=s2) return fail();	

	return true;
}

LayoutSwitch Layout::load_switch(ifstream &in)
{
	string s, trigger, target;
	getline(in,s);
	getline(in,trigger);
	getline(in,target);

	

	return *(add_switch(trigger, target));
}

Text Layout::load_text(ifstream& in, float xfactor, float yfactor)//, Text* t)
{
	string txt, font,s;
	int font_size;
	Pixel v;	
	getline(in,s);

	getline(in,txt);
	getline(in,font);
	getline(in,s);
	font_size=atoi(s.c_str());
	getline(in,s);
	v.x=atof(s.c_str())*xfactor;
	getline(in,s);
	v.y=atof(s.c_str())*yfactor;

	float r,g,b,a;
	getline(in,s); r=atof(s.c_str());
	getline(in,s); g=atof(s.c_str());
	getline(in,s); b=atof(s.c_str());
	getline(in,s); a=atof(s.c_str());	
	
	Text t(txt,font,font_size*yfactor,v);
	t.set_colour(r,g,b,a);
	return t;
}

Slider Layout::load_slider(ifstream& in, float xfactor, float yfactor)//, Slider* sl)
{
	Pixel from, to;
	int x, y;
	float value, barheight;
	string id,s;
	getline(in,s);

	getline(in,id);
	getline(in,s); x=atoi(s.c_str())*xfactor;
	getline(in,s); y=atoi(s.c_str())*yfactor;
	getline(in,s); barheight=atof(s.c_str());
	getline(in,s); from.x=atof(s.c_str())*xfactor;
	getline(in,s); from.y=atof(s.c_str())*yfactor;
	getline(in,s); to.x=atof(s.c_str())*xfactor;
	getline(in,s); to.y=atof(s.c_str())*yfactor;
	getline(in,s); value=atof(s.c_str());
	
	Slider sl(id,from,to,value,x,y,barheight);

	getline(in,s); sl.set_bar_texture(s);
	getline(in,s); sl.set_control_texture(s);

	return sl;
}

Quad Layout::load_quad(ifstream& in, float xfactor, float yfactor)
{
	float llx, lly, urx, ury;
	string s, tex_id;
	getline(in,s);

	getline(in,s); llx=atof(s.c_str())*xfactor;
	getline(in,s); lly=atof(s.c_str())*yfactor;
	getline(in,s); urx=atof(s.c_str())*xfactor;
	getline(in,s); ury=atof(s.c_str())*yfactor;
	getline(in,tex_id);

	return Quad(llx,lly,urx-llx,ury-lly,tex_id);
}

Button Layout::load_button(ifstream& in, float xfactor, float yfactor)
{
	int x, y, fontsize;
	string ID, font_id, text, s;
	Pixel v;
	bool unclickable, round, sticky, invisible, textbox;
	getline(in,s);

	getline(in, ID);
	getline(in, font_id);
	getline(in, s); fontsize=atoi(s.c_str())*yfactor;
	getline(in, s); if(s=="UNCLICKABLE") unclickable=true; else unclickable=false;
	getline(in, s); if(s=="STICKY") sticky=true; else sticky=false;
	getline(in, s); if(s=="ROUND") round=true; else round=false;
	getline(in, s); if(s=="INVISIBLE") invisible=true; else invisible=false;
	getline(in, s); if(s=="TEXTBOX") textbox=true; else textbox=false;
	getline(in, text);
	getline(in, s); v.x=atof(s.c_str())*xfactor;
	getline(in, s); v.y=atof(s.c_str())*yfactor;
	getline(in, s); x=atoi(s.c_str())*xfactor;
	getline(in, s); y=atoi(s.c_str())*yfactor;
	
	Button b(ID,text);
	b.set_size(x,y);
	b.set_font(font_id, fontsize);	
	b.set_origin(v);
	if(round) b.set_round(); else b.set_square();
	if(unclickable) b.set_unclickable(); else b.set_non_unclickable();
	if(sticky) b.set_sticky(); else b.set_non_sticky();
	if(invisible) b.invisibility(); else b.visibility();
	b.set_textbox(textbox);

	for(int i=BTN_INACTIVE;i<BTN_STATES;i++){
		getline(in, s);
		getline(in, s); b.set_texture(i,s);
		getline(in, s); if(s=="NULL") b.set_display(i,NULL);
	}
	b.set_size(x,y);
	return b;
}

ButtonArray Layout::load_buttonarray(ifstream& in, float xfactor, float yfactor)
{
	string active, s, id;
	int buttons;
	getline(in,s);
	getline(in,id); 

	getline(in,s); buttons=atoi(s.c_str());
	getline(in, active);
	
	ButtonArray ba(id);
	
	for(int i=0; i<buttons; i++){
		ba.add_button(load_button(in, xfactor, yfactor));
	}
	ba.set_active(active);

	return ba;
}

Menu* Layout::load_menu(ifstream& in, float xfactor, float yfactor)
{
	
	string s, ID, menumap, font, header;
	Pixel v;
	int font_size;
	getline(in,header);
	
	getline(in,ID);
	getline(in, s); v.x=atof(s.c_str())*xfactor;
	getline(in, s); v.y=atof(s.c_str())*yfactor;
	getline(in, font);
	getline(in, s); font_size=atoi(s.c_str())*yfactor;
	getline(in, menumap); 

	Menu* m;
	if(header=="MENU") {
		m=new Menu(ID,menumap,font,font_size);
		m->set_origin(v);
	}

	else if(header=="LIST") {
		m=new List(ID,menumap,font,font_size);
		m->set_origin(v);
		getline(in,s);
		getline(in,s); ((List*)m)->set_selection(s);
	}

	else m=NULL;

	for(int i=BTN_INACTIVE;i<BTN_STATES;i++){
		getline(in, s);
		getline(in, s); m->set_texture(i,s);
		getline(in, s); if(s=="NULL") m->set_display(i,NULL);
	}

	return m;
}

void Layout::load_tab(ifstream& in, float xfactor, float yfactor)
{
	string s,ID;
	
	getline(in, s);
	if(s!="TAB") return;
	getline(in,ID);
	add_tab(ID,Layout(ID));
	Tab t=get_tab(ID);
	getline(in,s);
	if(s!="TAB HEADER") return;
	Button b=load_button(in,xfactor,yfactor);
	*(t.tab_header)=b;
	getline(in, s);
	if(s!="TAB BODY") return;	
	
	t.tab_layout->load_configuration(in);
}

void Layout::reset()
{
	ID="";
	quads.clear();
	buttonarrays.clear();
	buttons.clear();
	tabs.reset();
	tabbed_layouts.clear();
	switches.clear();
	texts.clear();
	for(int i=0; i<menus_floating.size(); i++) delete menus_floating[i];
	menus_floating.clear();
	for(int i=0; i<menus_static.size(); i++) delete menus_static[i];
	menus_static.clear();
}

LayoutSwitch* Layout::add_switch(string id, string target)
{
	switches.push_back(LayoutSwitch());
	LayoutSwitch* lsw=&switches.back();
	lsw->trigger_id=id;
	lsw->target=GUIScreens->get(target);
	lsw->source=this;
	get_button(id)->set_sticky();
	return lsw;
}

