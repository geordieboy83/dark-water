#include "GLPolygon.h"

// Default. Null polygon.
GLPolygon::GLPolygon():
	Polygon(),
	minx(0), maxx(0),
	miny(0), maxy(0),
	minz(0), maxz(0),
	centre(),
	creator(-1),
	list(0),
	num_textures(0),
	num_normals(0),
	geometry_textures(NULL),
	next(NULL)
	{}

// Unload before destroying.
GLPolygon::~GLPolygon()
{
	if (is_loaded()){
		unload();
	}
}

void GLPolygon::bounding()
{
	maxx=-INF;
	maxy=maxx;
	maxz=maxx;
	minx=INF;
	miny=minx;
	minz=minx;
	for(int i=0; i<get_vertices(); i++){
		if(geometry_vertices[i].getx()<minx) minx=geometry_vertices[i].getx();
		if(geometry_vertices[i].getx()>maxx) maxx=geometry_vertices[i].getx();
		if(geometry_vertices[i].gety()<miny) miny=geometry_vertices[i].gety();
		if(geometry_vertices[i].gety()>maxy) maxy=geometry_vertices[i].gety();
		if(geometry_vertices[i].getz()<minz) minz=geometry_vertices[i].getz();
		if(geometry_vertices[i].getz()>maxz) maxz=geometry_vertices[i].getz();
	}
	return;
}

void GLPolygon::get_boundaries(float *minmax)
{
	minmax[0]=minx;
	minmax[1]=maxx;
	minmax[2]=miny;
	minmax[3]=maxy;
	minmax[4]=minz;
	minmax[5]=maxz;
}

Vertex GLPolygon::get_origin() { return centre; }

void GLPolygon::origin()
{
	centre.set_coords(
		minx+(float)(maxx-minx)/(float)2,
		miny+(float)(maxy-miny)/(float)2,
		minz+(float)(maxz-minz)/(float)2);
	return;
}

void GLPolygon::movetocentre()
{
	Vector v=centre;
	v.negate();
	translate(v);
	return;
}

bool GLPolygon::load(string name)
{
	if(Polygon::load(name)){
		TYPE="PHIL";
		bounding();
		origin();
		movetocentre();
		bounding();
		origin();
		return true;
	}
	else return false;
}

void GLPolygon::set_creator(int crtr) { creator=crtr;	return; }

int GLPolygon::get_creator() { return creator; }

void GLPolygon::display(float shift)
{
	for(int i=0;i<get_faces();i++){
		glBegin(GL_POLYGON);
		for(int j=1;j<=geometry_faces[i*get_max()];j++){
			glVertex3f(
				geometry_vertices[geometry_faces[i*get_max()+j]].getx()+geometry_normals[i].getx()*shift,
				geometry_vertices[geometry_faces[i*get_max()+j]].gety()+geometry_normals[i].gety()*shift,
				geometry_vertices[geometry_faces[i*get_max()+j]].getz()+geometry_normals[i].getz()*shift);
		}
		glEnd();
	}
}

GLuint GLPolygon::get_list() { return list; }

// Parse geometry file. Under normal circumstances an open file with its pointer at the beginning will be passed to this function.
bool GLPolygon::objparse(fstream& file)
{
	string s;
	
	//Must be triangular faces
	max_cells_per_face=10;
	
	// Read file
	while (getline(file,s)){

		while(s.c_str()[0]=='v'&s.c_str()[1]==' '){
			num_vertices++;
			getline(file,s);
		}
			
		while(s.c_str()[0]=='v'&s.c_str()[1]=='n'&s.c_str()[2]==' '){
			num_normals++;
			getline(file,s);
		}
		
		while(s.c_str()[0]=='v'&s.c_str()[1]=='t'&s.c_str()[2]==' '){
			num_textures++;
			getline(file,s);
		}

		while(s.c_str()[0]=='f'&s.c_str()[1]==' '){
			num_faces++;
			getline(file,s);
			if(s.c_str()[0]=='s'&s.c_str()[1]==' ') getline(file,s);
		}


	}

	cout << num_vertices << " vertices found." << endl;
	cout << num_normals << " normals found." << endl;
	cout << num_textures << " texture coordinates found." << endl;
	cout << num_faces << " faces found." << endl;
	
	return true;
}

// Load geometry file. Under normal circumstances, an open file with its pointer to the beginning should be passed to this function.
void GLPolygon::objload(fstream& file)
{
	
	string s;
		
	int iv=0, ivn=0, ivt=0, iff=0;

	// Read file
	while (getline(file,s)){

		while(s.c_str()[0]=='v'&s.c_str()[1]==' '){
			float vx=0, vy=0, vz=0;
			sscanf(s.c_str(),"v %f %f %f",&vx,&vy,&vz);
			geometry_vertices[iv].set_coords(vx,vy,vz);			
			iv++;
			getline(file,s);
		}
			
		while(s.c_str()[0]=='v'&s.c_str()[1]=='n'&s.c_str()[2]==' '){
			float vnx=0, vny=0, vnz=0;
			sscanf(s.c_str(),"vn %f %f %f",&vnx,&vny,&vnz);
			geometry_normals[ivn].set_coords(vnx,vny,vnz);			
			ivn++;
			getline(file,s);
		}
		
		while(s.c_str()[0]=='v'&s.c_str()[1]=='t'&s.c_str()[2]==' '){
			float vtx=0, vty=0, vtz=0;
			sscanf(s.c_str(),"vt %f %f %f",&vtx,&vty,&vtz);
			geometry_textures[ivt].set_coords(vtx,vty,vtz);			
			ivt++;
			getline(file,s);
		}

		while(s.c_str()[0]=='f'&s.c_str()[1]==' '){
		
			geometry_faces[iff]=3;
			
			int test[7]={-1,-1,-1,-1,-1,-1,-1};
			sscanf(s.c_str(),"f %d/%d/%d ", &test[0], &test[1], &test[2]);
			sscanf(s.c_str(),"f %d//%d ", &test[3], &test[4]);
			sscanf(s.c_str(),"f %d/%d ", &test[5], &test[6]);

			if(test[0]!=-1&&test[1]!=-1&&test[2]!=-1){
				sscanf(s.c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",
					&geometry_faces[iff+1], &geometry_faces[iff+4], &geometry_faces[iff+7],
					&geometry_faces[iff+2], &geometry_faces[iff+5], &geometry_faces[iff+8],
					&geometry_faces[iff+3], &geometry_faces[iff+6], &geometry_faces[iff+9]
					);				
			}
			else if(test[3]!=-1&&test[4]!=-1){
				sscanf(s.c_str(),"f %d//%d %d//%d %d//%d",
					&geometry_faces[iff+1], &geometry_faces[iff+7],
					&geometry_faces[iff+2], &geometry_faces[iff+8],
					&geometry_faces[iff+3], &geometry_faces[iff+9]);
				geometry_faces[iff+4]=-1;
				geometry_faces[iff+5]=-1;
				geometry_faces[iff+6]=-1;				
			}
			else if(test[5]!=-1&&test[6]!=-1){
				sscanf(s.c_str(),"f %d/%d %d/%d %d/%d",
					&geometry_faces[iff+1], &geometry_faces[iff+4],
					&geometry_faces[iff+2], &geometry_faces[iff+5],
					&geometry_faces[iff+3], &geometry_faces[iff+6]);
				geometry_faces[iff+7]=-1;
				geometry_faces[iff+8]=-1;
				geometry_faces[iff+9]=-1;				
			}
			iff+=max_cells_per_face;
			
			getline(file,s);
			if(s.c_str()[0]=='s'&s.c_str()[1]==' ') getline(file,s);
		}				
	}
		
	for(int i=0;i<get_faces();i++){
	
		for(int j=1;j<=geometry_faces[i*get_max()];j++){
			geometry_faces[i*get_max()+j]--;
			geometry_faces[i*get_max()+j+3]--;
			geometry_faces[i*get_max()+j+6]--;
		}
		
	}

	// There is a polygon in memory now.
	loaded=true;

	if (num_normals==0) normals();
	outdated=false;
	return;
}

// The overall process of loading geometry file <name> into memory.
bool GLPolygon::objload(string name, bool centred)
{
	// Test if file can be opened.
	fstream in(name,ios::in);		
	if (in.fail()) {cout <<"Unable to open " << name << "!" << endl; return false;}

	// If there is previous geometry data in memory, reset the polygon.
	if (loaded) unload();

	// Parse the geometry file. If this fails, the process cannot continue.
	if (!objparse(in)) return false;

	if(num_vertices==0||num_faces==0) return false;

	// Allocate space for polygon data.
	geometry_vertices=new Vertex[num_vertices];
	geometry_faces=new int[num_faces*max_cells_per_face];
	if(num_normals!=0) geometry_normals=new Vector[num_normals]; else geometry_normals=new Vector[num_faces];
	if(num_normals!=0) geometry_textures=new Vertex[num_textures];

	// Reset the input file.
	in.clear();
	in.seekg(0, ios::beg);

	// Read data into memory.
	objload(in);	
	in.close();
	TYPE="OBJ";
	bounding();
	origin();
	if(centred){
		movetocentre();
		bounding();
		origin();
	}
	return true;
}

bool GLPolygon::unload()
{
	Polygon::unload();
	num_textures=0;
	num_normals=0;
	if(geometry_textures!=NULL) delete[] geometry_textures;
	if(next!=NULL) delete next;
	if(glIsList(list)) glDeleteLists(list,1);
	return true;
}

void GLPolygon::objdisplay(float shift)
{
	Vector n;
	for(int i=0;i<get_faces();i++){
		glBegin(GL_TRIANGLES);
		for(int j=1;j<=geometry_faces[i*get_max()];j++){
			if(geometry_faces[i*get_max()+j+3]!=-1&&geometry_textures!=NULL){
				glTexCoord2f(				
					geometry_textures[geometry_faces[i*get_max()+j+3]].getx(),
					geometry_textures[geometry_faces[i*get_max()+j+3]].gety());
			}			
			
			if(geometry_faces[i*get_max()+j+6]!=-1){
				if(TYPE=="OBJ"){
				n.set_coords(
					geometry_normals[geometry_faces[i*get_max()+j+6]].getx(),
					geometry_normals[geometry_faces[i*get_max()+j+6]].gety(),
					geometry_normals[geometry_faces[i*get_max()+j+6]].getz());}
				else if (TYPE=="PHIL"){
					n.set_coords(
					geometry_normals[i].getx(),
					geometry_normals[i].gety(),
					geometry_normals[i].getz());
				}
				glNormal3f(n.getx(),n.gety(),n.getz());
			}

			glVertex3f(				
				geometry_vertices[geometry_faces[i*get_max()+j]].getx()+n.getx()*shift,
				geometry_vertices[geometry_faces[i*get_max()+j]].gety()+n.gety()*shift,
				geometry_vertices[geometry_faces[i*get_max()+j]].getz()+n.getz()*shift);
		}
		glEnd();
	}
}

bool GLPolygon::chainload(int how_many, const string* filenames, bool centred)
{
	GLPolygon *current=this;
	for(int i=0; i<how_many; i++){
		current->objload(filenames[i],centred);
		if(i<how_many-1){
			current->next=new GLPolygon();
			current=current->next;
		}
	}
	return true;
}

void GLPolygon::chaindesign(float shift)
{
	GLPolygon *current=this;
	list=glGenLists(1);
	glNewList(list,GL_COMPILE);
		while(current!=NULL){
			current->objdisplay(shift);
			current=current->next;
		}
	glEndList();
}

void GLPolygon::chaindisplay()
{
	glCallList(list);
}

void GLPolygon::chainprint()
{
	GLPolygon *current=this;
	while(current!=NULL){
		current->print();
		current=current->next;
	}
}

void GLPolygon::chaindesign(float shift, float* colours)
{
	GLPolygon *current=this;
	int currentcolour=0;
	list=glGenLists(1);
	glNewList(list,GL_COMPILE);
		while(current!=NULL){
			glColor3fv(&colours[currentcolour]);
			current->objdisplay(shift);
			current=current->next;
			currentcolour+=3;			
		}
	glEndList();
}

void GLPolygon::chaindesign(float shift, material* matter)
{
	GLPolygon *current=this;
	int currentmaterial=0;
	list=glGenLists(1);
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

void GLPolygon::chaindesign(float shift, GLuint *textures)
{
	GLPolygon *current=this;
	int currenttexture=0;
	list=glGenLists(1);
	glNewList(list,GL_COMPILE);
		while(current!=NULL){
			glBindTexture(GL_TEXTURE_2D,textures[currenttexture]);
			current->objdisplay(shift);
			current=current->next;
			currenttexture++;
		}
	glEndList();
}


void GLPolygon::chainscale(float scalar)
{
	GLPolygon *current=this;
	while(current!=NULL){
			current->scale(scalar);
			current=current->next;
	}
}

void GLPolygon::chaintranslate(Vector v)
{
	GLPolygon *current=this;
	while(current!=NULL){
			current->translate(v);
			current=current->next;
	}
}

void GLPolygon::chaincentre()
{
	Vector v=centre;
	v.negate();
	chaintranslate(v);
}

