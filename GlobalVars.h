#ifndef _GLOBAL
#define _GLOBAL
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <fstream>
#include <sstream>
#include <iostream>
#include <time.h>
#include <vector>
#include <stdlib.h> // General console window includes
#include <conio.h>
#include <ctype.h>
#include "Map.h"
#include "Runner.h"
#include "Shooter.h"
#include "XboxController.h"
using namespace tle;

#include <al.h>      // Main OpenAL functions
#include <alc.h>     // OpenAL "context" functions (also part of main OpenAL API)
#include <AL/alut.h> // OpenAL utility library - helper functions

/*Sound Variables*/

// A buffer holds sound data, but the creation of a buffer on its own doesn't play a sound. It is the
// equivalent of a mesh in the TL-Engine
ALuint buffer;
ALuint bufferBack;
ALuint bufferMenu;
// A source is an actual sound in the world. A sound must be associated with a buffer to indicate
// which sound data to play. Sources are equivalent to models in the TL-Engine
ALuint source;
ALuint sourceBack;
ALuint Menu;

// Each source has several properties, see the code for examples. Here we store position and velocity of
// the sound source above (x, y & z)
ALfloat sourcePos[3] = { 0.0, 5.0, 100.0 };
ALfloat sourceVel[3] = { 0.0, 0.0, 0.0 };
ALfloat sourceMusicPos[3] = { 0.0, 0.0, 0.0 };
ALfloat sourceMusicVel[3] = { 0.0, 0.0, 0.0 };
// There is always assumed to be a listener in an OpenAL application. We don't need a specific listener
// variable. However, listeners also have properties (examples in code). Here we store the position and
// velocity of the listener
ALfloat listenerPos[3] = { 0.0, 5.0, 100.0 };
ALfloat listenerVel[3] = { 0.0, 0.0, 0.0 };

// The listener may be at an angle (which may affect the perception of sound). Here we store the 
// orientation of the listener. The first three values are the facing direction (x, y, z) of the
// listener - called "at" in the documentation. The next three values are the upward direction
// of the listener, called "up". These vectors can be extracted from a world or view matrix
// NOTE: OpenAL (like OpenGL) uses a right-handed system for 3D coordinates. To convert from the
// left-handed system  we have used, we must negate all Z values (facing direction has -ve Z below)
ALfloat listenerOri[6] = { 0.0, 0.0, -1.0,
                           0.0, 1.0, 0.0 };

//Constant Variables
const float baseHeight = -15.0f;// Height the main floor is at
const float speed = 50.0f; // speed of player and jumping


//Engine
I3DEngine* myEngine = New3DEngine( kTLX );

//Bullet variables
const float bulletSpeed = 70.0f; // Movement speed of a bullet
int numBullets = 0;
int maxBullets = 5;

//Enemy Variables

//Mesh/Model Variables
ICamera* camera = NULL;

IMesh* floorMesh = NULL;
IMesh* sphereMesh = NULL;
IMesh* bulletMesh = NULL;
IMesh* skyMesh = NULL;

IModel* player = NULL;
IModel* bullet = NULL;
IModel* ground = NULL;
IModel* sky = NULL;

//Text Variables
int fontY = 20;
int fontX = 20;
IFont* FPSDisplay = NULL;
stringstream outText;
ISprite* backdrop = NULL;
IFont* frontEndFont = NULL; // the font for the front end.
ISprite* textBackColour = NULL; //background square for front end.

//Control Variables
enum EKeyCode quitKey = Key_Escape;
enum EKeyCode jumpKey = Key_W;
enum EKeyCode leftKey = Key_A;
enum EKeyCode rightKey = Key_D;
enum EKeyCode downKey = Key_S;
enum EKeyCode fireKey = Key_Space;
enum EKeyCode upArrowKey = Key_Up;
enum EKeyCode downArrowKey = Key_Down;
enum EKeyCode enterKey = Key_Return;
float gravity = 3.0f;
float updateTime = 1/60.0f; // calculating the updatetime every frame
float playerY = 5.0f;
float playerX = 0.0f;


/************Structures/Classes****************/

/*Structures*/
struct BulletData
{
	IModel* model;
	float xVel, yVel;
	float life;
};

vector <BulletData*> bullets;
vector <IModel*> runners;

/*Classes*/
vector <CMap*> map;
vector <CEnemy*> enemies;

CXBOXController* Player1 = new CXBOXController(1); 

#else

#endif