#pragma once
#include "Player.h"

extern Entity* Entities[];
extern report reports[];

/*=================================================================================*/

Player::Player(unsigned int id, int* keys, bool active):
	sniper(false),
	MovingEntity(id,active),
	loser(false),
	sniperview(),
	transforming(false),
	TransformationDuration(5),
	alternate(NULL),
	transformed(false),
	TransformationRemaining(EffectDuration),
	is_original(true),
	ultimateartifact(false),	
	rapidfire(false),
	doubledamage(false)
{
	for(int i=0; i<PLAYER_CONTROLS; i++) controls[i]=keys[i];
	HP=maxPlayerHP;
}

void Player::update(){
	reports[ID].HP=HP;
	reports[ID].rf=rapidfire;
	reports[ID].alive=alive;
	reports[ID].dd=doubledamage;
	reports[ID].ua=ultimateartifact;
	reports[ID].present=present;
	reports[ID].tf=!is_original;
	reports[ID].shot=!((Projectile*)Entities[prj_of_player(ID,"prj")])->alive;
	reports[ID].snipe=!((Projectile*)Entities[prj_of_player(ID,"sprj")])->alive;
	reports[ID].sniperviewpt=sniper;
	if(!alive||!present)
	
	if(rapidfire&&(glfwGetTime()-rfstart)>=EffectDuration){
			rapidfire=false;
			((Projectile*)Entities[prj_of_player(ID,"prj")])->rapidfire=false;
	}
	if(doubledamage&&(glfwGetTime()-ddstart)>=EffectDuration){
			doubledamage=false;
			((Projectile*)Entities[prj_of_player(ID,"prj")])->doubledamage=false;
	}
	
	if(transforming){
		if(glfwGetTime()-TransformationStart>TransformationDuration){
			transforming=false;
			if(!is_original){
				transformed=true;
				TransformationRemaining=EffectDuration;
			}
			else{
				transformed=false;
				TransformationRemaining=0;
			}
		}
		return;
	}

	if(transformed&&!is_original){
		TransformationRemaining=EffectDuration-(glfwGetTime()-(TransformationStart+TransformationDuration));
		
		if(TransformationRemaining<=0){
			transformed=!transformed;
			transform();
		}

	}
	
	float radang;
	
	if(glfwGetKey(controls[SN_ON])){
			sniper=true;

			if(glfwGetKey(controls[SN_UP])
				&&sniperview.getz()<20){
					sniperview.set_coords(
						sniperview.getx(),
						sniperview.gety(),
						sniperview.getz()+SNIPERFACTOR);
			}
			if(glfwGetKey(controls[SN_DN])
				&&sniperview.getz()>-20){
					sniperview.set_coords(
						sniperview.getx(),
						sniperview.gety(),
						sniperview.getz()-SNIPERFACTOR);			
			}
			if(glfwGetKey(controls[SN_LFT])
				&&sniperangle<rotationangle+20){					
				sniperangle+=(float)ANGLEFACTOR;
				radang=deg2rad(sniperangle);
				sniperview.set_coords(
					geometry_bounds[1]*cos(radang)+current.getx(),
					geometry_bounds[1]*sin(radang)+current.gety(),
					sniperview.getz());
			}
			if(glfwGetKey(controls[SN_RT])
					&&sniperangle>rotationangle-20){
						sniperangle-=(float)ANGLEFACTOR;
						radang=deg2rad(sniperangle);
						sniperview.set_coords(
							geometry_bounds[1]*cos(radang)+current.getx(),
							geometry_bounds[1]*sin(radang)+current.gety(),					
							sniperview.getz());
			}
			if(glfwGetKey(controls[FIRE])){
				fire();
			}			
	}
	else{
		sniper=false;

		mark(currentquad);
		sniperview=orientation;
		sniperangle=rotationangle;
		if(glfwGetKey(controls[FWD])){
			radang=deg2rad(rotationangle);
			attempted.set_coords(
				current.getx()+(float)(2*MOVEMENTFACTOR*cos(radang)),
				current.gety()+(float)(2*MOVEMENTFACTOR*sin(radang)),
				current.getz());
			move();
		}
		if(glfwGetKey(controls[RT])){
			rotationangle-=(float)ANGLEFACTOR;
			radang=deg2rad(rotationangle);
			attempted.set_coords(
				current.getx()+(float)(MOVEMENTFACTOR*cos(radang)),
				current.gety()+(float)(MOVEMENTFACTOR*sin(radang)),
				current.getz());
			move();
		}
		if(glfwGetKey(controls[LFT])){
			rotationangle+=(float)ANGLEFACTOR;
			radang=deg2rad(rotationangle);
			attempted.set_coords(
				current.getx()+(float)(MOVEMENTFACTOR*cos(radang)),
				current.gety()+(float)(MOVEMENTFACTOR*sin(radang)),
				current.getz());
			move();
		}
		if(glfwGetKey(controls[FIRE])) fire();
		
	}
}

void Player::fire()
{
	if(!sniper){
		if(!((Projectile*)Entities[prj_of_player(ID,"prj")])->alive){
			((Projectile*)Entities[prj_of_player(ID,"prj")])->current=orientation;
			((Projectile*)Entities[prj_of_player(ID,"prj")])->rotationangle=rotationangle;
			((Projectile*)Entities[prj_of_player(ID,"prj")])->fire();
		}
	}
	else{


		if(!((Projectile*)Entities[prj_of_player(ID,"sprj")])->alive){
			((Projectile*)Entities[prj_of_player(ID,"sprj")])->current.set_coords(
							current.getx(),current.gety(),current.getz()+geometry_bounds[5]);
			((Projectile*)Entities[prj_of_player(ID,"sprj")])->rotationangle=rotationangle;
			
			((Snipershot*)Entities[prj_of_player(ID,"sprj")])->sniperview.set_coords(
				sniperview.getx(),sniperview.gety(),sniperview.getz()+geometry_bounds[5]);
			((Projectile*)Entities[prj_of_player(ID,"sprj")])->fire();
			if(ultimateartifact) ultimateartifact=false;
		}

	}
}

void Player::die()
{
	Entity::die();
	loser=true;
}

void Player::glProjection(int x, int y, int width, int height)
{
	glViewport(x,y,width,height);

	float aspect=(float)(width-x)/(float)(height-y);

	glClear(GL_DEPTH_BUFFER_BIT);		
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(!sniper){
		glOrtho(WORLD_FROM/4,WORLD_TO/4,WORLD_FROM/4,WORLD_TO/4,2*WORLD_FROM,2*WORLD_TO);
		gluLookAt(current.getx()-100,	current.gety()-100, current.getz()+100,	current.getx(), current.gety(),	current.getz(), 1,1,0);
	}
	else{
		gluPerspective(45,16/9,0.1,3*WORLD_TO);
		Vector to=subtract(sniperview,current);
				to.scale(100);
				to=add(to,current);	
		
		gluLookAt(orientation.getx(), orientation.gety(), geometry_bounds[5],to.getx(),to.gety(),to.getz()+geometry_bounds[5],0,0,1);
	}
}

void Player::wound(int damage){
	if(transforming) return;
	if(!alive) return;
	HP-=damage;
	if(HP<=0)die();
	else{
		chaindesign((float)(max(maxPlayerHP-HP,0))*DEATHFACTOR/(float) maxPlayerHP,stuff);		
	}
}

void Player::display()
{
	if(!present) return;
	glDisable(GL_CULL_FACE);
	if(!transforming) Entity::display();
	else{

		glPushMatrix();
		
		glPolygonMode(GL_FRONT,GL_FILL);
		glTranslatef(current.getx(), current.gety(),0);		
		glRotatef(rotationangle,0,0,1);
		
		float where_from=(glfwGetTime()-TransformationStart)*TRANSFORMFACTOR*30;
		float where_to=(TransformationDuration-(glfwGetTime()-TransformationStart))*TRANSFORMFACTOR*30;
		GLPolygon *current=alternate;
		int currentmaterial=0;
		while(current!=NULL){			
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, stuff[currentmaterial].Ka);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, stuff[currentmaterial].Kd);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, stuff[currentmaterial].Ks);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, stuff[currentmaterial].Ns);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, stuff[currentmaterial].Ke);
			current->objdisplay(where_from);
			current=current->next;
			currentmaterial++;			
		}
		currentmaterial=0;
		current=geometry;
		while(current!=NULL){			
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, stuff[currentmaterial].Ka);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, stuff[currentmaterial].Kd);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, stuff[currentmaterial].Ks);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, stuff[currentmaterial].Ns);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, stuff[currentmaterial].Ke);
			current->objdisplay(where_to);
			current=current->next;
			currentmaterial++;			
		}

	}
	glPopMatrix();
	glEnable(GL_CULL_FACE);

}

void Player::transform()
{	
	if(transformed){
		TransformationRemaining+=EffectDuration;
		return;
	}
	if(!transforming){
		transforming=true;
		is_original=!is_original;
		transformed=false;
		TransformationStart=glfwGetTime();
		unmark(currentquad);
		GLPolygon* temp=geometry;
		geometry=alternate;
		alternate=temp;
		unmark(currentquad);
		geometry->bounding();
		geometry->origin();
		geometry->get_boundaries(geometry_bounds);
		quad(current,geometry->get_origin(),currentquad);
		mark(currentquad);
		orient();
		chaindesign((float)(max(max_HP()-HP,0))*DEATHFACTOR/(float) max_HP(),stuff);
		return;
	}
}

void Player::updatedependencies()
{
	if(ultimateartifact)((Snipershot*)Entities[prj_of_player(ID,"sprj")])->ultimateartifact=true;
	if(rapidfire)((Projectile*)Entities[prj_of_player(ID,"prj")])->rapidfire=true;
	if(doubledamage)((Projectile*)Entities[prj_of_player(ID,"prj")])->doubledamage=true;	
}

void Player::move()
{
	MovingEntity::move();
	for(int i=FIRST_BOX; i<=LAST_BOX; i++) if(collisions[i]>0) Entities[i]->triggered_by=ID;
}

int Player::max_HP() { return maxPlayerHP; }

void Player::set_HP(int hp)
{
	if(transforming) return;
	if(!alive) return;
	HP=hp;
	if(HP<=0)die();
	else{
		chaindesign((float)(max(maxPlayerHP-HP,0))*DEATHFACTOR/(float) maxPlayerHP,stuff);		
	}
}