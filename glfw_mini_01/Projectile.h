using namespace std;
#pragma once
#include "MovingEntity.h"

class Projectile : public MovingEntity
{
	public:
		Projectile(unsigned int id,unsigned int owner, bool active);
		//void sniper();
		bool fired;
		float when;
		float timetolive;
		float rangeinsec;
		int damage;
		Vector FiredAt;
		Vector TravelsTill;
		string TYPE;
		unsigned int whose;
		virtual void update();
		//void crash();
		virtual void fire();
		void display();
		virtual void move();
		virtual bool can_move();
		bool off_edge;
		void collides();
		void wound(int dmg);
		bool doubledamage;
		bool rapidfire;


	private:
		static const int default_damage=20;
		static const int default_range_in_sec=5;
};