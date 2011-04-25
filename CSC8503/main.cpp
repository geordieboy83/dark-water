#include <GL\glfw.h>
#include <FTGL\ftgl.h>
#include "GUI\GUI.h"
#include "Sea Wars\SW_Universe.h"
#include "Sea Wars\SW_UI.h"
#include <cyclone\cyclone.h>
#include <iostream>
#include <Courseworx\Globals.h>
#include "Player.h"
#include "Present.h"
#include "Projectile.h"
#include "Isle.h"

#include "Sea Wars\SW_main.h"
#include "Psysixmain.h"

using namespace std;
using namespace cyclone;

int main(int argc, char *argv[])
{
	//if(argv[1]=="1") Physixmain();
	//else if (argv[1]=="2") SW_main();
	int which;
	cout << "Which game would you like to play?" << endl;
	cin >> which;

	if (which==1) 
		Physixmain();
	else if(which==2) 
		SW_main();
	//else return 0;
}