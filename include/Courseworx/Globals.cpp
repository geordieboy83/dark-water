#include "Globals.h"

FTGLPixmapFont font("..\\Resources\\TT1141M.ttf");

int WINDOW_X=800, WINDOW_Y=600;

float watergrid_x[WATERQUADS+1], watergrid_z[WATERQUADS+1];

material materials[]={
	WATERMATERIALS,
	MERCURYMATERIALS,
	PARAFFINMATERIALS,
	ISLEMATERIALS,	
	BOXMATERIALS,
	PLAYER1MATERIALS
};

GLuint textures[TEXTURES];

GLPolygon models[MODELS];

float pos[]={WORLD_TO,0,WORLD_TO};
float ambient0[]={1,1,1,1};
float texx=0, texz=0;
float lightangle=0;

extern string SEA_TYPE="WATER";

float deg2rad(float angle_in_degrees)
{
	return (float)(angle_in_degrees*PI)/(float)180;
}

void materialise(unsigned int what){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials[what].Ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials[what].Kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,materials[what].Ks);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materials[what].Ns);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materials[what].Ke);
}

void texturise(unsigned int what){
	glBindTexture(GL_TEXTURE_2D, textures[what]);
}

FTPoint stringseed(const char* string, Vertex origin)
{
	FTBBox box=font.BBox(string);
	Vertex low(box.Lower().Xf(),box.Lower().Yf(),box.Lower().Zf());
	Vertex hi(box.Upper().Xf(),box.Upper().Yf(),box.Upper().Zf());
	return FTPoint::FTPoint(
		origin.getx()-(hi.getx()-low.getx())*0.5,
		origin.gety()-(hi.gety()-low.gety())*0.5,
		origin.getz()-(hi.getz()-low.getz())*0.5);
}


void BSOD()
{
	//glfwSetWindowSize( 640, 480 );
	
	glDisable(GL_LIGHTING);

	
	//glViewport(0,0,640,480);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,1,0,1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	
	glBindTexture(GL_TEXTURE_2D, textures[BSODTX]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBegin(GL_QUADS);
		glTexCoord2i(0,0);
		glVertex2i(0,0);
		glTexCoord2i(1,0);
		glVertex2i(1,0);
		glTexCoord2i(1,1);
		glVertex2i(1,1);
		glTexCoord2i(0,1);
		glVertex2i(0,1);
	glEnd();
	glDisable(GL_TEXTURE_2D);		
	glfwSwapBuffers();
	glfwSleep(10);
		
	//glfwSetWindowSize( WINDOW_X, WINDOW_Y );	
	glEnable(GL_LIGHTING);
	
}

void sea(float y, string type)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glEnable(GL_TEXTURE_2D);
	if(type=="WATER") { materialise(WTRMTL); texturise(WTRTX);  }
	else if(type=="MERCURY") { materialise(MRCMTL); texturise(MRCTX); }
	else if(type=="PARAFFIN") { materialise(PRFMTL); texturise(PRFTX); }
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	int i,j;
	glBegin(GL_QUADS);
		for(i=0; i< WATERQUADS; i++){
			for(j=0; j< WATERQUADS; j++){
				glTexCoord2f(0+texx,0+texz);
				glNormal3f(0,1,0);
				glVertex3f(watergrid_x[i],y,watergrid_z[j]);

				glTexCoord2f(0+texx,1+texz);
				glNormal3f(0,1,0);
				glVertex3f(watergrid_x[i],y, watergrid_z[j+1]);

				glTexCoord2f(1+texx,1+texz);
				glNormal3f(0,1,0);
				glVertex3f(watergrid_x[i+1],y, watergrid_z[j+1]);

				glTexCoord2f(1+texx,0+texz);
				glNormal3f(0,1,0);
				glVertex3f(watergrid_x[i+1],y, watergrid_z[j]);				
							
			}
		}
	glEnd();	
	glDisable(GL_TEXTURE_2D);
	
	return;
}


void update_landscape()
{
	texx+=0.001;
	texz-=0.001;

	lightangle+=0.1;	
}

void scenery()
{
	glPushMatrix();
	glRotatef(lightangle,-1,0,1);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glPopMatrix();

	sea(0,SEA_TYPE);
}


double cos2x(double cosx) { return cos(2*acos(cosx)); }
double sin2x(double sinx) { return sin(2*asin(sinx)); }

void glLoadModels()
{
	Vector v;
	float bounds[6];
	string names[]={"..\\Resources\\ship.obj","..\\Resources\\mast.obj","..\\Resources\\sail.obj"};
	
	cout << "LOADING PLAYER MODEL..." << endl;
	models[PLMDL].chainload(3,names, false);	
	cout <<"PLAYER MODEL LOADED." << endl << endl;	

	cout << "LOADING ISLE MODEL..." << endl;
	models[ISLEMDL].objload("..\\Resources\\volcano.obj",true);
	models[ISLEMDL].scale(2);
	models[ISLEMDL].bounding();
	models[ISLEMDL].get_boundaries(bounds);
	v.set_coords(0,-bounds[2]-1,0);
	models[ISLEMDL].translate(v);
	models[ISLEMDL].bounding();
	models[ISLEMDL].origin();
	cout <<"ISLE MODEL LOADED." << endl << endl;
	
	cout << "LOADING ISLE PROJECTILE MODEL..." << endl << endl;
	models[ISLPRJMDL].objload("..\\Resources\\boulder.obj",true);
	models[ISLPRJMDL].scale(0.5);
	models[ISLPRJMDL].bounding();
	models[ISLPRJMDL].origin();
	cout <<"ISLE PROJECTILE MODEL LOADED." << endl;
	
	cout << "LOADING GIFTBOX MODEL..." << endl << endl;
	names[0]="..\\Resources\\giftbox.obj"; names[1]="..\\Resources\\giftwrap.obj";
	models[BOXMDL].chainload(2,names,true);
	cout << "GIFTBOX MODEL LOADED." << endl << endl;
	
}

void glLoadTextures()
{
	glGenTextures(1, &textures[WTRTX]);	
	glBindTexture(GL_TEXTURE_2D, textures[WTRTX]);
	glfwLoadTexture2D("..\\Resources\\Water.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &textures[ISLTX]);	
	glBindTexture(GL_TEXTURE_2D, textures[ISLTX]);
	glfwLoadTexture2D("..\\Resources\\Volcano.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &textures[BSODTX]);	
	glBindTexture(GL_TEXTURE_2D, textures[BSODTX]);
	glfwLoadTexture2D("..\\Resources\\BSOD.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &textures[MRCTX]);	
	glBindTexture(GL_TEXTURE_2D, textures[MRCTX]);
	glfwLoadTexture2D("..\\Resources\\mercury.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &textures[PRFTX]);	
	glBindTexture(GL_TEXTURE_2D, textures[PRFTX]);
	glfwLoadTexture2D("..\\Resources\\paraffin.tga",GLFW_BUILD_MIPMAPS_BIT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void initialise()
{
	for(int i=0; i<= WATERQUADS; i++){watergrid_x[i]=2.6*(WORLD_FROM+i*(float)(WORLD_TO-WORLD_FROM)/(float)WATERQUADS); watergrid_z[i]=watergrid_x[i];}
	glLoadModels();
}

void axes()
{
	glDisable(GL_LIGHTING);
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(0.2,0,0);
	glVertex3f(2*WORLD_FROM,0,0);
	glColor3f(1,0,0);
	glVertex3f(2*WORLD_TO,0,0);
	glColor3f(0,.2,0);
	glVertex3f(0,2*WORLD_FROM,0);
	glColor3f(0,1,0);
	glVertex3f(0,2*WORLD_TO,0);
	glColor3f(0,0,.2);
	glVertex3f(0,0,2*WORLD_FROM);
	glColor3f(0,0,1);
	glVertex3f(0,0,2*WORLD_TO);
	glEnd();
	glLineWidth(10);
	glEnable(GL_LIGHTING);
}


float dampen(Vector3 position, float original_drag)
{
	float maxx=abs(WORLD_TO-position.x),
		minx=abs(WORLD_FROM-position.x),
		maxz=abs(WORLD_FROM-position.z),
		minz=abs(WORLD_TO-position.z);
	float penalty=min(min(minx,maxx),min(minz,maxz));
	if(penalty>200) return original_drag;
	else {

		float penalise=(float)penalty/200;
		return original_drag*max(0.1f,penalise);
	}


}


void bboxdisplay(CollisionBox &bbox)
{
	Matrix4 transform = bbox.getTransform();
	GLfloat gl_transform[16];
	glPushAttrib(GL_POLYGON_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);	
    transform.fillGLArray(gl_transform);
    glPushMatrix();
    glMultMatrixf(gl_transform);
	
	float minx=-bbox.halfSize.x, maxx=bbox.halfSize.x,
		miny=-bbox.halfSize.y, maxy=bbox.halfSize.y,
		minz=-bbox.halfSize.z, maxz=bbox.halfSize.z;
	
	
	glBegin(GL_LINES);

		glVertex3f(minx,miny,minz);	glVertex3f(maxx,miny,minz);

		glVertex3f(minx,maxy,minz);	glVertex3f(maxx,maxy,minz);

		glVertex3f(minx,miny,minz);	glVertex3f(minx,maxy,minz);

		glVertex3f(maxx,miny,minz);	glVertex3f(maxx,maxy,minz);


		glVertex3f(minx,miny,maxz);	glVertex3f(maxx,miny,maxz);

		glVertex3f(minx,maxy,maxz);	glVertex3f(maxx,maxy,maxz);

		glVertex3f(minx,miny,maxz);	glVertex3f(minx,maxy,maxz);

		glVertex3f(maxx,miny,maxz);	glVertex3f(maxx,maxy,maxz);


		glVertex3f(minx,miny,minz);	glVertex3f(minx,miny,maxz);

		glVertex3f(minx,maxy,minz);	glVertex3f(minx,maxy,maxz);

		glVertex3f(maxx,miny,minz);	glVertex3f(maxx,miny,maxz);

		glVertex3f(maxx,maxy,minz);	glVertex3f(maxx,maxy,maxz);
		
	glEnd();

	glPopMatrix();

	glPopAttrib();
}

void bspheredisplay(CollisionSphere &csphere)
{
	Matrix4 transform = csphere.getTransform();
	GLfloat gl_transform[16];
	
	GLUquadricObj* sphere=gluNewQuadric();
	gluQuadricOrientation(sphere,GLU_OUTSIDE);
	
	
	glPushAttrib(GL_POLYGON_BIT);
	glLineWidth(1);
	gluQuadricDrawStyle(sphere,GLU_LINE);
    transform.fillGLArray(gl_transform);
    glPushMatrix();
    glMultMatrixf(gl_transform);
	
	gluSphere(sphere,csphere.radius,30,30);
	
	glPopMatrix();

	glPopAttrib();

	gluDeleteQuadric(sphere);

}

void glProjection(int width, int height, unsigned int style,RigidBody& body)
{
	Vector3 pos = body.getPosition();
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	switch(style){
		default:
			glOrtho(sqrt(2.0)*WORLD_FROM,sqrt(2.0)*WORLD_TO,sqrt(2.0)*WORLD_FROM,sqrt(2.0)*WORLD_TO,sqrt(2.0)*WORLD_FROM,sqrt(2.0)*WORLD_TO);
			gluLookAt(0, 100, 0,0, 0, 0, -1,0,-1);
			break;
		case 1:
			glOrtho(WORLD_FROM/2,WORLD_TO/2,height*WORLD_FROM/(2*width),height*WORLD_TO/(2*width),WORLD_FROM,WORLD_TO);	
			gluLookAt(pos.x+100, 100, pos.z+100,pos.x, 0, pos.z, 0,1,0);
			break;
		case 2:
			glOrtho(WORLD_FROM/3,WORLD_TO/3,height*WORLD_FROM/(3*width),height*WORLD_TO/(3*width),WORLD_FROM,WORLD_TO);
			gluLookAt(pos.x+100, 100, pos.z+100,pos.x, 0, pos.z, 0,1,0);
			break;
		case 3:
			glOrtho(WORLD_FROM/4,WORLD_TO/4,height*WORLD_FROM/(4*width),height*WORLD_TO/(4*width),WORLD_FROM,WORLD_TO);	
			gluLookAt(pos.x+100, 100, pos.z+100,pos.x, 0, pos.z, 0,1,0);
			break;
	}
    
}