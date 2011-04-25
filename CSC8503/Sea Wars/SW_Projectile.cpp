using namespace std;
#pragma once

#include "SW_Projectile.h"

extern Entity* Entities[];
extern unsigned int world_bounds[SW_QUADS][SW_QUADS];
extern FTGLPixmapFont font;

SeaWarsProjectile::SeaWarsProjectile(unsigned int id, unsigned int owner, bool active) : MovingEntity(id,active),
	damage(default_damage),
	fired(false),
	timetolive(10),
	TravelsTill(),
	rangeinsec(default_range_in_sec),
	whose(owner),
	off_edge(true),
	rapidfire(false),
	doubledamage(false),
	when(glfwGetTime()-300)
{
	HP=1;
	alive=false;
}

/*void Projectile::crash()
{
}*/

void SeaWarsProjectile::fire()
{
	if(!alive){
		
		alive=true;
		fired=true;
		off_edge=false;
		orient();
		quad(current,geometry->get_origin(),currentquad);
		mark(currentquad);
		when=glfwGetTime();
		FiredAt=current;
		TravelsTill=subtract(orientation,current);
		TravelsTill.unit();
		TravelsTill.scale(rangeinsec*30*projectilefactor(ID));
		TravelsTill.magn();
		TravelsTill.set_coords(
			TravelsTill.getx()+current.getx(),
			TravelsTill.gety()+current.gety(),
			-(geometry_bounds[5]-2));		
	}
}

void SeaWarsProjectile::update()
{
	//Inactive projectile
	if(!alive) return;

//	float radang;
	float elapsedtime=glfwGetTime()-when;

	/*char s[256];
	sprintf(s, "Can shoot again in %f s.",timetolive-elapsedtime);
	font.Render(s);*/
		
	//Expired
	if(elapsedtime>=rangeinsec)
	{
		fired=false;
		if(rapidfire) alive=false;
		unmark(currentquad);
		if(elapsedtime>timetolive) alive=false;
		return;
	}
		
	//Active and firing
	if(fired){		

		Vector v=subtract(orientation,current);
		v.unit();
		v.scale(elapsedtime*30*projectilefactor(ID));
		v.set_coords(
			v.getx()+FiredAt.getx(),
			v.gety()+FiredAt.gety(),
			(float)elapsedtime*(TravelsTill.getz()-FiredAt.getz())/(float)rangeinsec);
		attempted=(Vertex)v;
		
		if(off_edge){
			current=attempted;
			orient();
		}
		else{
			move();
		}




		return;
	}

}

void SeaWarsProjectile::display()
{
	if(alive&&fired)MovingEntity::display();	
}

void SeaWarsProjectile::move()
{
	quad(attempted,geometry->get_origin(),attemptedquad);
	if(	attempted.getx()<SW_WORLD_FROM||
		attempted.getx()>SW_WORLD_TO||
		attempted.gety()<SW_WORLD_FROM||
		attempted.gety()>SW_WORLD_TO){
			off_edge=true;
			return;
	}
	if(can_move()){
		unmark(currentquad);
		current=attempted;
		//quad(current,currentquad);
		quad(current,geometry->get_origin(),currentquad);
		mark(currentquad);
		orient();
	}
	else{
		bool flag=(collisions[SW_EDGE]>0);
		int i;
		if (flag)
			for(i=0; i<=SW_IDS-2; i++)
				if(collisions[i]>0&&i!=ID&&i!=whose){
					flag=false;
					break;
				};
		if(flag) off_edge=true;
		else{
			unmark(currentquad);
			int dmg;
			if(doubledamage) dmg=2*damage; else dmg=damage;
			for(i=SW_FIRST_PLAYER; i<=SW_LAST_PLAYER; i++) if(i!=whose&&collisions[i]>0) Entities[i]->wound(dmg);
			for(i=SW_FIRST_ISLE; i<=SW_LAST_ISLE; i++) if(collisions[i]>0) Entities[i]->wound(dmg);
			for(i=SW_FIRST_BOX; i<=SW_LAST_BOX; i++) if(collisions[i]>0) Entities[i]->wound(dmg);
			for(i=SW_FIRST_PROJECTILE; i<=SW_LAST_PROJECTILE; i++)
				if(i!=ID&&collisions[i]>0)
					if(((SeaWarsProjectile*)Entities[i])->current.getz()<=attempted.getz()){
						((SeaWarsProjectile*)Entities[i])->fired=false;
						((SeaWarsProjectile*)Entities[i])->unmark(((SeaWarsProjectile*)Entities[i])->currentquad);
					}
			/*for(i=FIRST_PLAYER; i<=LAST_BOX; i++){
				if(Entities[i]!=NULL&&
					i!=whose&&
					collisions[i]>0)					
					Entities[i]->wound(damage);
			}
			for(i=FIRST_PROJECTILE; i<=LAST_PROJECTILE; i++)
				if(i!=ID&&collisions[i]>0)
					if(((Projectile*)Entities[i])->current.getz()<=attempted.getz())
						((Projectile*)Entities[i])->wound(damage);*/
			fired=false;
			if(rapidfire)alive=false;
			unmark(currentquad);
		}
	}
	

}

bool SeaWarsProjectile::can_move()
{
	int i;
	collides();
	//if(collisions[EDGE]>0) return false;
	for(i=SW_FIRST_PLAYER; i<=SW_LAST_PLAYER; i++) if(i!=whose&&collisions[i]>0) return false;
	for(i=SW_FIRST_ISLE; i<=SW_LAST_ISLE; i++) if(collisions[i]>0) return false;
	for(i=SW_FIRST_BOX; i<=SW_LAST_BOX; i++) if(collisions[i]>0) return false;
	for(i=SW_FIRST_PROJECTILE; i<=SW_LAST_PROJECTILE; i++)
		if(i!=ID&&collisions[i]>0)
			if(((SeaWarsProjectile*)Entities[i])->current.getz()<=attempted.getz())
				return false;
	return true;
}

void SeaWarsProjectile::collides()
{
	int i,j;
	for(i=0; i<SW_IDS; i++) collisions[i]=0;
	for(i=max(attemptedquad[0], 0); i<min(attemptedquad[1],SW_QUADS); i++)
		for(j=max(attemptedquad[2],0);j<min(attemptedquad[3],SW_QUADS);j++)
			collisions[world_bounds[i][j]]++;
	return;
}

void SeaWarsProjectile::wound(int damage)
{
	fired=false;
	unmark(currentquad);
}