#include <al.h>      // Main OpenAL functions
#include <alc.h>     // OpenAL "context" functions (also part of main OpenAL API)
#include <AL/alut.h> // OpenAL utility library - helper functions
#include <TL-Engine.h>
#include <deque>
#include "XboxController.h"
using namespace tle;

#ifndef _EXTERNS
#define _EXTERNS
extern enum EKeyCode fireKey;
extern float updateTime;
extern I3DEngine* myEngine;
extern CXBOXController* Player1;
extern struct BulletData
{
	IModel* model;
	float xVel, yVel;
	float life;
};
extern deque <BulletData*> bullets;
extern int numBullets;
extern IModel* ground[7];
extern IMesh* bulletMesh;

// A buffer holds sound data, but the creation of a buffer on its own doesn't play a sound. It is the
// equivalent of a mesh in the TL-Engine
extern ALuint buffer;
extern ALuint bufferBack;
extern ALuint bufferMenu;
// A source is an actual sound in the world. A sound must be associated with a buffer to indicate
// which sound data to play. Sources are equivalent to models in the TL-Engine
extern ALuint source;
extern ALuint sourceBack;
extern ALuint Menu;

// Each source has several properties, see the code for examples. Here we store position and velocity of
// the sound source above (x, y & z)
extern ALfloat sourcePos[3];
extern ALfloat sourceVel[3];
extern ALfloat sourceMusicPos[3];
extern ALfloat sourceMusicVel[3];
// There is always assumed to be a listener in an OpenAL application. We don't need a specific listener
// variable. However, listeners also have properties (examples in code). Here we store the position and
// velocity of the listener
extern ALfloat listenerPos[3];
extern ALfloat listenerVel[3];

// The listener may be at an angle (which may affect the perception of sound). Here we store the 
// orientation of the listener. The first three values are the facing direction (x, y, z) of the
// listener - called "at" in the documentation. The next three values are the upward direction
// of the listener, called "up". These vectors can be extracted from a world or view matrix
// NOTE: OpenAL (like OpenGL) uses a right-handed system for 3D coordinates. To convert from the
// left-handed system  we have used, we must negate all Z values (facing direction has -ve Z below)
extern ALfloat listenerOri[6];
#endif

void soundLoader(float volume)
{
	// Initialise ALUT and hence OpenAL. If not using ALUT, we can initialise using core OpenAL functions.
	// However then we would need to consider what sound devices are available, with what features, and
	// select from those. ALUT just selects the default output device
	alutInit( 0, 0 );

	buffer = alutCreateBufferFromFile( "Media\\shoot.wav" );
	bufferBack = alutCreateBufferFromFile( "Media\\BackGround.wav" );
	bufferMenu = alutCreateBufferFromFile( "Media\\Menu.wav" );
	
	// Create sound source
	alGenSources( 1, &source );
	alGenSources( 2, &sourceBack);
	alGenSources( 1, &Menu);

	// Set the properties of the source. The full list of available properties can be found in the documentation
	// The last characters of each function name indicate the type of the second parameter (int, float, float vector etc.)
	alSourcei ( source, AL_BUFFER,   buffer ); // Attach a buffer to the source (identify which sound to play)
	alSourcef ( source, AL_PITCH,    1.0f );   // Pitch multiplier, doubling the pitch shifts the sound up 1 octave, halving
	                                           // the pitch shifts it down 1 octave. Will also shorten/lengthen the sound
    alSourcef ( source, AL_GAIN,     1.0f );   // Effectively the volume of the sound - 0.0 = silent, 1.0 = as recorded. May
	                                           // be able to increase volume over 1, but depends on sound
    alSourcefv( source, AL_POSITION, sourcePos ); // Position of sound relative to listener affects how it is reproduced through speakers
    alSourcefv( source, AL_VELOCITY, sourceVel ); // Velocity of sound relative to listener can cause Doppler effect
	alSourcei ( source, AL_LOOPING,  AL_FALSE );  // Whether to loop the sound or just stop when it finishes

	alSourcei ( sourceBack, AL_BUFFER,   bufferBack ); 
	alSourcef ( sourceBack, AL_PITCH,    1.0f );   
    alSourcef ( sourceBack, AL_GAIN,     2.0f );
    alSourcefv( sourceBack, AL_POSITION, sourceMusicPos ); 
    alSourcefv( sourceBack, AL_VELOCITY,  sourceMusicVel ); 
	alSourcei ( sourceBack, AL_LOOPING,  AL_TRUE );

	alSourcei ( Menu, AL_BUFFER,   bufferMenu ); 
	alSourcef ( Menu, AL_PITCH,    1.0f );   
    alSourcef ( Menu, AL_GAIN,     1.0f );
    alSourcefv( Menu, AL_POSITION, sourcePos ); 
    alSourcefv( Menu, AL_VELOCITY,  sourceVel ); 
	alSourcei ( Menu, AL_LOOPING,  AL_TRUE );  


	// Set the properties of the listener. These are all the available listener properties
	alListenerfv( AL_POSITION,    listenerPos ); // Position, velocity and orientation of listener affect sound...
	alListenerfv( AL_VELOCITY,    listenerVel ); // ...reproduction as noted above
	alListenerfv( AL_ORIENTATION, listenerOri ); 
	alListenerf ( AL_GAIN,        volume );  // "Master" gain / volume. Controls overall loudness of all sounds
}

void bulletMovement(float bulletSpeed, int maxBullets, float playerY, float playerX, bool hit)
{
	if (myEngine->KeyHit( fireKey ) || Player1->IsConnected() && Player1->GetState().Gamepad.bRightTrigger & XINPUT_GAMEPAD_RIGHT_THUMB && numBullets < maxBullets)
	{
		alSourcePlay( source );
		BulletData* tmp = new BulletData;
		tmp->xVel = 0.0f;
		tmp->yVel = 0.0f;
		tmp->model = bulletMesh->CreateModel( 0.0f, 0.0f, 0.0f );
		tmp->life = 2.0f;
		tmp->model->Scale(1.0f);
        bullets.push_back( tmp );

		
		bullets[numBullets]->model->AttachToParent(ground[0]);
		bullets[numBullets]->model->SetLocalPosition(playerX - ground[0]->GetX(),  (-ground[0]->GetY()) - 20.0f  + playerY , 100.0f );
		numBullets++;
	}
	for (int i = 0; i < numBullets; i++)
	{
		// Move bullet
		bullets[i]->model->Move( bulletSpeed * updateTime, 0, 0);
		
		// Decrease life and see if bullet is dead
		bullets[i]->life -= updateTime;

		if (bullets[i]->life <= 0 || hit == true)
		{
			// Destroy bullet
  			bulletMesh->RemoveModel(bullets[i]->model);
			bullets.pop_front();

			// Decrease number of bullets
			numBullets--;
		}
	}
}
