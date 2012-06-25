#pragma once
#include "Entity.h"

extern unsigned int world_bounds[QUADS][QUADS];
extern float minimap_colours[][4];

Entity::Entity(unsigned int id, bool active) :
	ID(id),
	geometry(NULL),
	alive(true),
	current(),
	HP(default_hps),
	stuff(NULL),
	list(0),
	triggered_by(-1),
	//colour(minimap_colour(id)),
	rotationangle(0),
	present(active)
	{}

Entity::~Entity(){
	if(glIsList(list)) glDeleteLists(list,1);	
}

void Entity::load(string s, string type, bool centered){
	if(geometry==NULL) { geometry=new GLPolygon();	geometry->set_creator(ID); }
	if(type=="PHIL")geometry->load(s);
	else if (type=="OBJ") geometry->objload(s,centered);
	else return;
	geometry->get_boundaries(geometry_bounds);
}

void Entity::quad(Vertex position, Vertex origin, int* quad_idxs)
{
	float minx=position.getx()+min(geometry_bounds[0]-origin.getx(), geometry_bounds[2]-origin.gety()),
		  miny=position.gety()+min(geometry_bounds[0]-origin.getx(), geometry_bounds[2]-origin.gety()),
		  maxx=position.getx()+max(geometry_bounds[1]-origin.getx(), geometry_bounds[3]-origin.gety()),
		  maxy=position.gety()+max(geometry_bounds[1]-origin.getx(), geometry_bounds[3]-origin.gety()),
		  quadstep=(float)(WORLD_TO-WORLD_FROM)/(float)QUADS;
	quad_idxs[0]=(int)floor((float)(minx-WORLD_FROM)/quadstep);
	quad_idxs[1]=(int)ceil((float)(maxx-WORLD_FROM)/quadstep);
	quad_idxs[2]=(int)floor((float)(miny-WORLD_FROM)/quadstep);
	quad_idxs[3]=(int)ceil((float)(maxy-WORLD_FROM)/quadstep);	
	return;
}

void Entity::mark(int* quad_idxs){
	for(int i=quad_idxs[0]; i<quad_idxs[1]; i++)
		for(int j=quad_idxs[2];j<quad_idxs[3];j++)
			world_bounds[i][j]=ID;
	return;
}

void Entity::unmark(int* quad)
{
	for(int i=quad[0]; i<quad[1]; i++)
		for(int j=quad[2];j<quad[3];j++)
			world_bounds[i][j]=FREE;
	return;
}

void Entity::die()
{
	alive=false;
	TimeOfDeath=glfwGetTime();
	unmark(currentquad);
	GLPolygon *current=geometry;
	if(!glIsList(list)) list=glGenLists(1);
	else glDeleteLists(list,1);	
	glNewList(list,GL_COMPILE);
	int i=0;
	glPushAttrib(GL_POLYGON_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		while(current!=NULL){
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, stuff[i].Ka);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, stuff[i].Kd);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, stuff[i].Ks);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, stuff[i].Ns);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, stuff[i].Ke);
			current->objdisplay(0);
			current=current->next;
			i++;			
		}
		glPopAttrib();
	glEndList();
}

void Entity::update(){
	if(!alive) return;
	mark(currentquad);
}

void Entity::wound(int damage)
{
	if(!alive) return;
	HP-=damage;
	if(HP<=0)die();
	else{
		chaindesign((float)(max(default_hps-HP,0))*DEATHFACTOR/(float) default_hps,stuff);		
	}
}

void Entity::design(float shift)
{
	if(!glIsList(list)) list=glGenLists(1);
	else glDeleteLists(list,1);
	if(geometry->TYPE=="PHIL"){
		glNewList(list,GL_COMPILE);
		glColor3fv(minimap_colours[ID]);
		geometry->display(shift);		
		glEndList();
		return;
	}
	if(geometry->TYPE=="OBJ"){
		glNewList(list,GL_COMPILE);
		glColor3fv(minimap_colours[ID]);
		geometry->objdisplay(shift);		
		glEndList();
		return;
	}
}

void Entity::display()
{
	glPushMatrix();
	
	glPolygonMode(GL_FRONT,GL_FILL);
	glTranslatef(current.getx(),current.gety(),current.getz());		
	if(rotationangle!=0) glRotatef(rotationangle,0,0,1);
		
	//if(alive) { glCallList(list); }
	//else{
	//	//glPushAttrib(GL_POLYGON_BIT);
	//	glCallList(list);
	//	//glPopAttrib();
	//}
	glCallList(list);
	glPopMatrix();
}

void Entity::chaindesign(float shift, float* colours)
{
	
	GLPolygon *current=geometry;
	int currentcolour=0;
	if(!glIsList(list)) list=glGenLists(1);
	else glDeleteLists(list,1);
	glNewList(list,GL_COMPILE);
		while(current!=NULL){
			glColor3fv(&colours[currentcolour]);
			current->objdisplay(shift);
			current=current->next;
			currentcolour+=3;			
		}
	glEndList();
}

void Entity::chaindesign(float shift, material* matter)
{
	GLPolygon *current=geometry;
	int currentmaterial=0;
	if(!glIsList(list)) list=glGenLists(1);
	else glDeleteLists(list,1);

	glNewList(list,GL_COMPILE);
		while(current!=NULL){			
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matter[currentmaterial].Ka);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matter[currentmaterial].Kd);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matter[currentmaterial].Ks);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matter[currentmaterial].Ns);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matter[currentmaterial].Ke);
			current->objdisplay(shift);
			current=current->next;
			currentmaterial++;			
		}
	glEndList();
}

void Entity::chaindesign(float shift, GLuint *textures)
{
	GLPolygon *current=geometry;
	int currenttexture=0;
	if(!glIsList(list)) list=glGenLists(1);
	else glDeleteLists(list,1);
	glNewList(list,GL_COMPILE);
		while(current!=NULL){
			glBindTexture(GL_TEXTURE_2D,textures[currenttexture]);
			current->objdisplay(shift);
			current=current->next;
			currenttexture++;
		}
	glEndList();
}

void Entity::chaindesign(float shift)
{
	GLPolygon *current=geometry;
	if(!glIsList(list)) list=glGenLists(1);
	else glDeleteLists(list,1);
	glNewList(list,GL_COMPILE);
	glColor3fv(minimap_colours[ID]);
		while(current!=NULL){
			current->objdisplay(shift);
			current=current->next;
		}
	glEndList();
}

bool Entity::chainload(int how_many, const string* filenames, bool centred){
	if(geometry==NULL) { geometry=new GLPolygon();	geometry->set_creator(ID); }
	geometry->chainload(how_many,filenames,centred);
	geometry->get_boundaries(geometry_bounds);
	return true;
}

int Entity::max_HP() { return default_hps; }

void Entity::set_HP(int hp)
{
	if(!alive) return;
	HP=hp;
	if(HP<=0)die();
	else{
		chaindesign((float)(max(default_hps-HP,0))*DEATHFACTOR/(float) default_hps,stuff);		
	}
}