
#include "Player.h"
using namespace cyclone;

extern GLPolygon models[];
extern Vector3 windspeed;
extern FTGLPixmapFont font;
extern float now, previous;
extern float liquid_density;
extern bool grids1, grids2;

void Player::key()
{
	if(dead) return;

	if(glfwGetKey(controls[FWD])){

		Vector3 offset(ENGINE, 0, 0);
		offset = boat.body.getTransform().transformDirection(offset);
		boat.body.addForce(offset);

	}
	
	if(glfwGetKey(controls[RT])){		
		boat.body.addTorque(Vector3(0,-TORQUE,0));
	}
	

	if(glfwGetKey( controls[LFT])){		
		boat.body.addTorque(Vector3(0,TORQUE,0));		
	}

	if(glfwGetKey(controls[FIRE])) fire();

}


//Based on Millington's code
void Player::update()
{
	for(int i=0; i<AMMO; i++) if(ammo[i].used) ammo[i].update();

	if(dead||victor)return;

	// Find the duration of the last frame in seconds
    float duration = now-previous;
    if (duration <= 0.0f) return;

  	// Start with no forces or acceleration.
    boat.body.clearAccumulators();

	key();
	
	// Add the forces acting on the boat.
    boat.registry->updateForces(duration);

    // Update the boat's physics.
    boat.body.integrate(duration);

	real original_drag=boat.body.getLinearDamping();

	real damp=real_pow((float)(dampen(boat.body.getPosition(),original_drag)/original_drag),duration);
	Vector3 dampvector(damp,1,damp);
	Vector3 vel=boat.body.getVelocity();
	vel.componentProductUpdate(dampvector);
	boat.body.setVelocity(vel);
	
	Vector3 pos=boat.body.getPosition();
	

	if(pos.x>WORLD_TO) { boat.body.setInverseMass(0); }
	if(pos.x<WORLD_FROM){ boat.body.setInverseMass(0); }
	if(pos.z>WORLD_TO) { boat.body.setInverseMass(0); }
	if(pos.z<WORLD_FROM){ boat.body.setInverseMass(0); }
	float bounds[6];
	models[PLMDL].next->get_boundaries(bounds);
	if(pos.y<-bounds[3]) dead=true;

	hull.calculateInternals();
	mast.calculateInternals();
	sail.calculateInternals();
	csphere.calculateInternals();

	

}

void Player::set()
{
	Vertex vtx=models[PLMDL].next->next->get_origin();
	boat.reset_aero(Matrix3(0,0,0, 0,0,0, 0,0,-0.25f), Vector3(vtx.getx(), 0, 0), &windspeed);

	vtx=models[PLMDL].get_origin();
	
	boat.reset_buoyancy(Vector3(0, vtx.gety()*0.25,0), -2.0f, 35.0f, 2.0f,liquid_density);

	boat.body.setPosition(0,0, 0);
    boat.body.setOrientation(1,0,0,0);

    boat.body.setVelocity(0,0,0);
    boat.body.setRotation(0,0,0);

   	boat.body.setMass(MASS);
    Matrix3 it;
    it.setBlockInertiaTensor(Vector3(2,1,1), 0.5*MASS);
    boat.body.setInertiaTensor(it);

    boat.body.setDamping(0.8f, 0.8f);

    boat.body.setAcceleration(Vector3::GRAVITY);
    boat.body.calculateDerivedData();

    boat.body.setAwake();
    boat.body.setCanSleep(false);

	boat.reset_registry();

	float hullbounds[6], mastbounds[6],sailbounds[6];
	models[PLMDL].get_boundaries(hullbounds);
	models[PLMDL].next->get_boundaries(mastbounds);
	models[PLMDL].next->next->get_boundaries(sailbounds);

	csphere.body=&boat.body;
	float minx=min(min(hullbounds[0],mastbounds[0]),sailbounds[0]),
		maxx=max(max(hullbounds[1],mastbounds[1]),sailbounds[1]),
		miny=min(min(hullbounds[2],mastbounds[2]),sailbounds[2]),
		maxy=max(max(hullbounds[3],mastbounds[3]),sailbounds[3]),
		minz=min(min(hullbounds[4],mastbounds[4]),sailbounds[4]),
		maxz=max(max(hullbounds[5],mastbounds[5]),sailbounds[5]);

	Vertex hullorigin=models[PLMDL].get_origin(),
		mastorigin=models[PLMDL].next->get_origin(),
		sailorigin=models[PLMDL].next->next->get_origin();

	csphere.radius=0.5*max(abs(maxx-minx),max(abs(maxy-miny),abs(maxz-minz)));
	csphere.offset.data[3]=hullorigin.getx();
	csphere.offset.data[7]=hullorigin.gety();
	csphere.offset.data[11]=hullorigin.getz();
	csphere.calculateInternals();
	
	hull.body=&boat.body;
	hull.halfSize=Vector3(
		0.5*(hullbounds[1]-hullbounds[0]),
		0.5*(hullbounds[3]-hullbounds[2]),
		0.5*(hullbounds[5]-hullbounds[4]));
	hull.offset.data[3]=hullorigin.getx();
	hull.offset.data[7]=hullorigin.gety();
	hull.offset.data[11]=hullorigin.getz();
	hull.calculateInternals();

	mast.body=&boat.body;
	mast.halfSize=Vector3(
		0.5*(mastbounds[1]-mastbounds[0]),
		0.5*(mastbounds[3]-mastbounds[2]),
		0.5*(mastbounds[5]-mastbounds[4]));
	mast.offset.data[3]=mastorigin.getx();
	mast.offset.data[7]=mastorigin.gety();
	mast.offset.data[11]=mastorigin.getz();
	mast.calculateInternals();

	sail.body=&boat.body;
	sail.halfSize=Vector3(
		0.5*(sailbounds[1]-sailbounds[0]),
		0.5*(sailbounds[3]-sailbounds[2]),
		0.5*(sailbounds[5]-sailbounds[4]));
	sail.offset.data[3]=sailorigin.getx();
	sail.offset.data[7]=sailorigin.gety();
	sail.offset.data[11]=sailorigin.getz();
	sail.calculateInternals();
	
}

//Based on Millington's code
void Player::display()
{
	Matrix4 transform = boat.body.getTransform();
    GLfloat gl_transform[16];
    transform.fillGLArray(gl_transform);
    glPushMatrix();
    glMultMatrixf(gl_transform);
    draw_self();
    glPopMatrix();
	
	if(grids1) bspheredisplay(csphere);
	if(grids2){
		glLineWidth(1);
		bboxdisplay(hull);
		bboxdisplay(mast);
		bboxdisplay(sail);
	}
	

	for(int i=0; i<AMMO; i++) if(ammo[i].used) ammo[i].display(material_index);
}

void Player::draw_self()
{
	if(!dead) glCallList(living); else glCallList(carcass);
}

Player::Player(int* keys) : 
	boat(),
	dead(false),
	HP(maxHP),
	LastFired(-1),
	material_index(0),
	victor(false)
{
	for(int i=0; i<PLAYER_CONTROLS;i++) controls[i]=keys[i];
}

void Player::fire()
{
	float now=glfwGetTime();
	if(now-LastFired<2) return;
	int i;
	for (i=0; i<AMMO; i++)
    {
		if (!ammo[i].used) break;
    }

    // If we didn't find a round, then exit - we can't fire.
    if (i >= AMMO) return;

	ammo[i].fire(hull);
	LastFired=now;
}

void Player::reliquidate(string s)
{
	Vertex vtx=models[PLMDL].get_origin();

	if(s=="WATER"){
		boat.reset_buoyancy(Vector3(0, vtx.gety()*0.25,0), -2.0f, 35.0f, 2.0f,1025);
		boat.body.setDamping(0.8f, 0.8f);}
	if(s=="MERCURY"){
		boat.reset_buoyancy(Vector3(0, vtx.gety()*0.25,0), -2.0f, 35.0f, 2.0f,13590);
		boat.body.setDamping(0.2f, 0.2f);}
	if(s=="PARAFFIN"){
		boat.reset_buoyancy(Vector3(0, vtx.gety()*0.25,0), -2.0f, 35.0f, 2.0f,800);
		boat.body.setDamping(0.9f, 0.9f);}

	boat.reset_registry();


}

void Player::wound(int damage)
{
	HP-=damage;
	if(HP <= 0) dead=true;
}

void Player::affect(unsigned int effect)
{
	switch(effect){
		//HEALTH
		case 1: wound(-25); break;
		
		//POISON
		case 2: wound(25); break;

		//BLUE SCREEN OF DEATH
		case 3: BSOD(); previous=now=glfwGetTime();  break;
					
		default: break;
	}
}