#pragma once

#ifndef SSOUNDMANAGER_H
#define SSOUNDMANAGER_H

#include <alut.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

class SoundSystem {
	public:
		SoundSystem(string AudioMap, ALint NumberOfSources);
		~SoundSystem();
		void playDB();
		ALuint play(string ID, float* position = NULL, float* velocity = NULL, float gain = 1.f, float pitch = 1.f);
		ALuint loop(string ID, float* position = NULL, float* velocity = NULL, float gain = 1.f, float pitch = 1.f);
		ALuint ambient(string ID, float gain = 1.f, float pitch = 1.f);
		ALuint ambientloop(string ID, float gain = 1.f, float pitch = 1.f);
		void movesource(ALuint source, float* position, float* velocity);
		void pause(ALuint source);
		void stop(ALuint source);
		void resume(ALuint source);
		float get_master() { return master_gain; }
		void set_master(float new_master_gain) { master_gain = new_master_gain; }
	protected:
		bool load(string AudioMap);
		vector<ALuint> sources;
		map<string, ALuint> sounds;
		float master_gain;
		ALuint available();
};



#endif