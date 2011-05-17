using namespace std;
#pragma once

#include "Boulder.h"

extern Entity* Entities[];
extern SoundSystem* Audio;

Boulder::Boulder(unsigned int id,unsigned int owner,bool active) : Projectile(id,owner,active), horizontalvelocity(), g(9.8)/*,  u0z(0,0,40), gravity(0,0,g)*/
{
	rangeinsec=4;
	timetolive=rangeinsec;
	damage=35;
}

void Boulder::fire()
{

	if(!alive){
		alive=true;
		fired=true;
		off_edge=false;
		rotationangle=0;
		quad(current,geometry->get_origin(),currentquad);
		when=glfwGetTime();
		FiredAt=current;
		horizontalvelocity=subtract(TravelsTill, FiredAt);
		horizontalvelocity.set_coords(horizontalvelocity.getx(), horizontalvelocity.gety(),0);
		horizontalvelocity.unit();
		horizontalvelocity.scale(30*ISLEPROJECTILESPEED);
		g=2*abs(FiredAt.getz()-TravelsTill.getz())/(rangeinsec*rangeinsec);
		if(Audio) Audio->ambient("BLDR_FIRE");//,FX_VOLUME);
	}
}


void Boulder::update()
{
	if(!alive) return;
	float elapsed=glfwGetTime()-when;
	if(elapsed >= rangeinsec)
	{
		fired=false;
		alive=false;
		//if(Audio) Audio->ambient("BLDR_SINK");
		unmark(currentquad);
		return;
	}
	if(fired){

		 rotationangle+=ANGLEFACTOR;
		
		attempted.set_coords(
			FiredAt.getx()+horizontalvelocity.getx()*elapsed,
			FiredAt.gety()+horizontalvelocity.gety()*elapsed,
			FiredAt.getz()-0.5*elapsed*elapsed*g
			);

		if(	attempted.getx()<WORLD_FROM||
		attempted.getx()>WORLD_TO||
		attempted.gety()<WORLD_FROM||
		attempted.gety()>WORLD_TO)
			off_edge=true;
			
		if(off_edge){
			unmark(currentquad);
			//if(current.gety()>=0&&attempted.gety()<0&&Audio){
			//	cout << "Boulder sinx" << endl;
			//	Audio->ambient("BLDR_SINK");//,FX_VOLUME);
			//}
			current=attempted;
			return;
		}

		quad(attempted,geometry->get_origin(),attemptedquad);
		if(can_move()){
			//if(current.gety()>=0&&attempted.gety()<0&&Audio) {
			//	cout << "Boulder sinx" << endl;
			//	Audio->ambient("BLDR_SINK");//,FX_VOLUME);
			//}

			unmark(currentquad);
			current=attempted;
			quad(current,geometry->get_origin(),currentquad);
			mark(currentquad);
			if(Entities[whose]->alive)Entities[whose]->mark(Entities[whose]->currentquad);
		}
		else{
			bool flag=(collisions[EDGE]>0);
			if (flag)for(int i=0; i<=IDS-2; i++)if(collisions[i]>0&&i!=ID&&i!=whose){flag=false; break;}
			if(flag) {off_edge=true; unmark(currentquad); current=attempted; return;}

			for(int i=FIRST_PLAYER; i<=LAST_PLAYER; i++)
				if(collisions[i]>0){ 
					Entities[i]->wound(damage);
					if(Audio) Audio->ambient("IMPACT",FX_VOLUME);
				}
			for(int i=FIRST_BOX; i<=LAST_BOX; i++)
				if(collisions[i]>0&&
					Entities[i]->geometry_bounds[5]>=current.getz()+geometry_bounds[4]){
						Entities[i]->wound(damage);
						if(Audio) Audio->ambient("IMPACT",FX_VOLUME);
				}
			for(int i=FIRST_ISLE; i<=LAST_ISLE; i++)
				if(i!=whose&&collisions[i]>0) fired=false;
			fired=false;
			alive=false;
			TimeOfDeath=glfwGetTime();
			unmark(currentquad);

		}

	

		
	}

}

void Boulder::display()
{
	if(!alive) return;

	glPushMatrix();
	
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glTranslatef(current.getx(),current.gety(),current.getz());		
	if(rotationangle!=0) 
		glRotatef(rotationangle,1,0,0);
		
	//if(alive)
	{ glCallList(list); }
	/*else{
		glPushAttrib(GL_POLYGON_BIT);
		glCallList(list);
		glPopAttrib();

		if((glfwGetTime()-TimeOfDeath)<=TimeToDie){
			GLPolygon *plgn=geometry;
			int currentmaterial=0;
			while(plgn!=NULL){
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, stuff[currentmaterial].Ka);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, stuff[currentmaterial].Kd);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, stuff[currentmaterial].Ks);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, stuff[currentmaterial].Ns);
				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, stuff[currentmaterial].Ke);
				plgn->objdisplay(AshesScatter);
				plgn=plgn->next;
				currentmaterial++;
			}
		}
	}*/

	glPopMatrix();
}

bool Boulder::can_move()
{
	int i;
	collides();
	//if(collisions[EDGE]>0) return false;
	for(i=FIRST_PLAYER; i<=LAST_PLAYER; i++) if(collisions[i]>0) return false;
	for(i=FIRST_ISLE; i<=LAST_ISLE; i++) if(i!=whose&&collisions[i]>0) return false;
	for(i=FIRST_BOX; i<=LAST_BOX; i++) if(collisions[i]>0) return false;
	for(i=FIRST_PROJECTILE; i<=LAST_PROJECTILE; i++)
		if(i!=ID&&collisions[i]>0)
			if(((Projectile*)Entities[i])->current.getz()<=attempted.getz())
				return false;
	return true;
}