using namespace std;
#pragma once

#include "SW_Snipershot.h"

class SeaWarsPlayer : public MovingEntity
{
	public:
		SeaWarsPlayer(unsigned int id, int* keys, bool active);
		unsigned int projectile;
		bool loser;
		bool sniper;
		int controls[SW_PLAYER_CONTROLS];
		float range;
		unsigned int fires;
		void glProjection(int x, int y, int width, int height);
		void snipermode();
		void fire();
		void wound(int damage);
		void update();
		//void collides();
		void die();
		Vector sniperview;
		float sniperangle;
		GLPolygon* alternate;
		bool transformed;
		void transform();
		bool transforming;
		float TransformationStart;
		float TransformationDuration;		
		static const int EffectDuration=30;
		float TransformationRemaining;
		bool is_original;
		void display();
		bool ultimateartifact;
		bool doubledamage;
		float ddstart;

		bool rapidfire;
		float rfstart;
		
		int max_HP();

		void updatedependencies();
		void move();

	private:
		static const int maxPlayerHP=200;
};

