#include "SoundManager.h"
//#include "PhysicsWorld.h"

#include <string>
#include <map>
using namespace std;
SoundSystem::SoundSystem(string AudioMap, ALint NumberOfSources): master_gain(1.f)
{
	load(AudioMap);
	if(NumberOfSources<0)NumberOfSources=sounds.size();
	ALuint* srces = new ALuint[NumberOfSources];
	alGenSources(NumberOfSources, srces);
	for(int i=0; i<NumberOfSources; i++) sources.push_back(srces[i]);	
	delete[] srces;	
}

SoundSystem::~SoundSystem()
{
	for(map<string,ALuint>::iterator i=sounds.begin(); i!=sounds.end(); i++) alDeleteBuffers(1,&i->second);
	for(unsigned int j=0; j<sources.size(); j++) alDeleteSources(1,&sources[j]);
}

bool SoundSystem::load(string AudioMap){
	// Test if file can be opened.
	fstream in(AudioMap,ios::in);		
	if (in.fail()) {cout <<"Unable to open " << AudioMap << "!" << endl; return false;}

	vector<string> sidentifiers;
	vector<string> sfilenames;
	// Read data into memory.
	string id,fName;

	do{
		in >> id >> fName;
		if(in.fail()) 
			break;
		sidentifiers.push_back(id);
		sfilenames.push_back(fName);
	}while(!in.eof());

	in.close();

	int bufferSize = sidentifiers.size();
	ALuint* buffers = new ALuint[bufferSize];
	//string soundsPath = PhysicsWorld::getPhysicsWorld()->projectDir + "Sound\\";
	for(int i=0; i<sidentifiers.size(); i++){
		buffers[i]=alutCreateBufferFromFile(sfilenames[i].c_str());//(soundsPath + sfilenames[i]).c_str());
		if (buffers[i] == AL_NONE){
			ALint error = alutGetError ();
			printf( "Error loading file: '%s'\n",
               alutGetErrorString (error));
		}

		sounds.insert(sounds.begin(), pair<string,ALuint>(sidentifiers[i],buffers[i]));
	}

	delete[] buffers;

	return true;
}

ALuint SoundSystem::available()
{
	ALuint i=0;
	for(i ; i < sources.size(); i++){
		ALint state;
		alGetSourcei (sources[i], AL_SOURCE_STATE, &state);
		if((state!=AL_PLAYING)&&(state!=AL_PAUSED)) return sources[i];
	}
	ALuint new_source;
	alGenSources(1,&new_source);
	sources.push_back(new_source);
	return new_source;
}

void SoundSystem::playDB()
{
	ALuint source=available();
	map<string,ALuint>::iterator i=sounds.begin();
	int j=1;
	for(i; i!=sounds.end(); i++){
		cout << "Playing "<<i->first<<" (sound " <<j<<" of "<<sounds.size()<<")"<<endl;
		alSourcei(source,AL_BUFFER,i->second);
		alSourcei(source,AL_SOURCE_RELATIVE,AL_TRUE);
		alSourcePlay(source);
		ALint status;
		do{
			alutSleep (1.f);
			alGetSourcei (source, AL_SOURCE_STATE, &status);
	    } while (status == AL_PLAYING);
		j++;
	}
}

ALuint SoundSystem::play(string ID, float* position, float* velocity, float gain, float pitch)
{
	ALuint source=available();
	alSourcei(source,AL_BUFFER,sounds[ID]);
	alSourcei(source,AL_LOOPING,AL_FALSE);
	alSourcei(source,AL_SOURCE_RELATIVE,AL_FALSE);
	alSourcef(source,AL_PITCH,pitch);
	alSourcef(source,AL_GAIN,gain*master_gain);
	if(position==NULL) alSource3f(source,AL_POSITION,0.f,0.f,0.f); else alSourcefv(source,AL_POSITION,position);
	if(velocity==NULL) alSource3f(source,AL_VELOCITY,0.f,0.f,0.f); else alSourcefv(source,AL_VELOCITY,velocity);
	alSourcePlay(source);
	return source;	
}

ALuint SoundSystem::loop(string ID, float* position, float* velocity, float gain, float pitch)
{
	ALuint source=available();
	alSourcei(source,AL_BUFFER,sounds[ID]);
	alSourcei(source,AL_SOURCE_RELATIVE,AL_FALSE);
	alSourcei(source,AL_LOOPING,AL_TRUE);
	alSourcef(source,AL_PITCH,pitch);
	alSourcef(source,AL_GAIN,gain*master_gain);
	if(position==NULL) alSource3f(source,AL_POSITION,0.f,0.f,0.f); else alSourcefv(source,AL_POSITION,position);
	if(velocity==NULL) alSource3f(source,AL_VELOCITY,0.f,0.f,0.f); else alSourcefv(source,AL_VELOCITY,velocity);
	alSourcePlay(source);
	return source;
}

ALuint SoundSystem::ambient(string ID, float gain, float pitch)
{
	ALuint source=available();
	alSourcei(source,AL_BUFFER,sounds[ID]);
	alSourcei(source,AL_SOURCE_RELATIVE,AL_TRUE);
	alSourcei(source,AL_LOOPING,AL_FALSE);
	alSourcef(source,AL_PITCH,pitch);
	alSourcef(source,AL_GAIN,gain*master_gain);
	alSourcePlay(source);
	return source;
}

ALuint SoundSystem::ambientloop(string ID, float gain, float pitch)
{
	ALuint source=available();
	alSourcei(source,AL_BUFFER,sounds[ID]);
	alSourcei(source,AL_SOURCE_RELATIVE,AL_TRUE);
	alSourcei(source,AL_LOOPING,AL_TRUE);
	alSourcef(source,AL_PITCH,pitch);
	alSourcef(source,AL_GAIN,gain*master_gain);	
	alSourcePlay(source);
	return source;
}

void SoundSystem::movesource(ALuint source, float* position, float* velocity)
{
	if(position!=NULL) alSourcefv(source,AL_POSITION,position);
	if(velocity!=NULL) alSourcefv(source,AL_VELOCITY,velocity);
}

void SoundSystem::pause(ALuint source)
{
	alSourcePause(source);
}

void SoundSystem::stop(ALuint source)
{
	alSourceStop(source);
}

void SoundSystem::resume(ALuint source)
{
	alSourcePlay(source);
}