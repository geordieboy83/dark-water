using namespace std;
#pragma once

#include "Projectile.h"

extern Entity* Entities[];
extern unsigned int world_bounds[QUADS][QUADS];
extern SoundSystem* Audio;
//extern FTGLPixmapFont font;

Projectile::Projectile(unsigned int id, unsigned int owner, bool active) : MovingEntity(id,active),
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

void Projectile::fire()
{
	if(!alive){
		if(Audio) Audio->ambient("RCKT_FIRE");	
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

void Projectile::update()
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
		//if(Audio) Audio->ambient("RCKT_SINK");
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

void Projectile::display()
{
	if(alive&&fired)MovingEntity::display();	
}

void Projectile::move()
{
	quad(attempted,geometry->get_origin(),attemptedquad);
	if(	attempted.getx()<WORLD_FROM||
		attempted.getx()>WORLD_TO||
		attempted.gety()<WORLD_FROM||
		attempted.gety()>WORLD_TO){
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
		bool flag=(collisions[EDGE]>0);
		int i;
		if (flag)
			for(i=0; i<=IDS-2; i++)
				if(collisions[i]>0&&i!=ID&&i!=whose){
					flag=false;
					break;
				};
		if(flag) off_edge=true;
		else{
			unmark(currentquad);
			int dmg;
			if(doubledamage) dmg=2*damage; else dmg=damage;
			for(i=FIRST_PLAYER; i<=LAST_PLAYER; i++) if(i!=whose&&collisions[i]>0){
				if(Audio) Audio->ambient("IMPACT");
				Entities[i]->wound(dmg);
			}
			for(i=FIRST_ISLE; i<=LAST_ISLE; i++) if(collisions[i]>0){ 
				if(Audio) Audio->ambient("IMPACT");
				Entities[i]->wound(dmg);
			}
			for(i=FIRST_BOX; i<=LAST_BOX; i++) if(collisions[i]>0){
				if(Audio) Audio->ambient("IMPACT");
				Entities[i]->wound(dmg);
			}
			for(i=FIRST_PROJECTILE; i<=LAST_PROJECTILE; i++)
				if(i!=ID&&collisions[i]>0)
					if(((Projectile*)Entities[i])->current.getz()<=attempted.getz()){
						((Projectile*)Entities[i])->fired=false;
						((Projectile*)Entities[i])->unmark(((Projectile*)Entities[i])->currentquad);
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

bool Projectile::can_move()
{
	int i;
	collides();
	//if(collisions[EDGE]>0) return false;
	for(i=FIRST_PLAYER; i<=LAST_PLAYER; i++) if(i!=whose&&collisions[i]>0) return false;
	for(i=FIRST_ISLE; i<=LAST_ISLE; i++) if(collisions[i]>0) return false;
	for(i=FIRST_BOX; i<=LAST_BOX; i++) if(collisions[i]>0) return false;
	for(i=FIRST_PROJECTILE; i<=LAST_PROJECTILE; i++)
		if(i!=ID&&collisions[i]>0)
			if(((Projectile*)Entities[i])->current.getz()<=attempted.getz())
				return false;
	return true;
}

void Projectile::collides()
{
	int i,j;
	for(i=0; i<IDS; i++) collisions[i]=0;
	for(i=max(attemptedquad[0], 0); i<min(attemptedquad[1],QUADS); i++)
		for(j=max(attemptedquad[2],0);j<min(attemptedquad[3],QUADS);j++)
			collisions[world_bounds[i][j]]++;
	return;
}

void Projectile::wound(int damage)
{
	fired=false;
	unmark(currentquad);
}