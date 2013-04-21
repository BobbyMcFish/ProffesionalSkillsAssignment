#ifndef _GLOBAL
#define _GLOBAL
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <fstream>
#include <sstream>
#include <iostream>
#include <time.h>
#include <vector>
#include <deque>
#include <stdlib.h> // General console window includes
#include <conio.h>
#include <ctype.h>
#include "Player.h"
#include "Map.h"
#include "XboxController.h"
#include "Runner.h"
using namespace tle;

#include <al.h>      // Main OpenAL functions
#include <alc.h>     // OpenAL "context" functions (also part of main OpenAL API)
#include <AL/alut.h> // OpenAL utility library - helper functions

/*Sound Variables*/

ALuint buffer;
ALuint bufferBack;
ALuint bufferMenu;

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
float volume = 0.1f;
const float maxVolume = 2.0f;
const float minVolume = 0.0f;
//Constant Variables
const float baseHeight = -15.0f;// Height the main floor is at
const float speed = 50.0f; // speed of player and jumping

//Engine
I3DEngine* myEngine = New3DEngine( kTLX );

//Bullet variables
const float bulletSpeed = 100.0f; // Movement speed of a bullet
int numBullets = 0;
const int maxBullets = 5;


//Mesh/Model Variables
ICamera* camera = NULL;

IMesh* floorMesh = NULL;
IMesh* sphereMesh = NULL;
IMesh* bulletMesh = NULL;
IMesh* skyMesh = NULL;
IMesh* enemyMesh = NULL;

IModel* bullet = NULL;
IModel* ground[7];
IModel* sky = NULL;
IModel* enemy = NULL;

//Text Variables
int fontY = 20;
int fontX = 20;
int livesfontY = 40;
int livesfontX = 40;
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
enum EKeyCode enterKey = Key_Return;
enum EKeyCode pauseKey = Key_P;
float gravity = 2.5f;
float updateTime = 0.0f; // calculating the updatetime every frame
const float playerY = 5.0f;
const float playerX = 0.0f;

int playerHealth;
int playerLives;

bool isPaused = false;
bool isQuiting = false;
bool isBegining = false;
/************Structures/Classes****************/

/*Structures*/
struct BulletData
{
	IModel* model;
	float xVel, yVel;
	float life;
};

/*Classes*/
Player* player = NULL;
deque <BulletData*> bullets;
vector <CMap*> map;
vector <CEnemy*> enemies;
CXBOXController* Player1 = new CXBOXController(1); 

#else

#endif