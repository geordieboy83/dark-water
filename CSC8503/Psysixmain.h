//using namespace std;

#include <GL\glfw.h>
#include <FTGL\ftgl.h>
#include <cyclone\cyclone.h>
#include <iostream>
#include <Courseworx\Globals.h>
#include "Player.h"
#include "Present.h"
#include "Projectile.h"
#include "Isle.h"

using namespace cyclone;

//Creating the occupants of the world
void setup();

//General hotkeys
void key();

//Collision detection and resolution
void generateContacts();

//The giftbox mechanism
void reinforcements();

//Displays text on the screen.
void report();

void Physixmain();