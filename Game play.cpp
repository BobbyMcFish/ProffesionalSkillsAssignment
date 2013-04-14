// Game play.cpp: A program using the TL-Engine
#include "GlobalVars.h"

void soundLoader()
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
	alListenerf ( AL_GAIN,        1.0f );  // "Master" gain / volume. Controls overall loudness of all sounds
}

void bulletMovement()
{
	if (myEngine->KeyHit( fireKey ) || Player1->IsConnected() && Player1->GetState().Gamepad.bRightTrigger & XINPUT_GAMEPAD_RIGHT_THUMB && numBullets < maxBullets)
	{
		alSourcePlay( source );
		BulletData* tmp = new BulletData;
		tmp->xVel = 0.0f;
		tmp->yVel = 0.0f;
		tmp->model = bulletMesh->CreateModel( 0.0f, 0.0f, 0.0f );
		tmp->life = 1.5f;
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

		if (bullets[i]->life <= 0)
		{
			// Destroy bullet
  			bulletMesh->RemoveModel(bullets[i]->model);
			bullets.pop_front();

			// Decrease number of bullets
			numBullets--;
		}
	}
}

void frontEndSetUp()
{	
	soundLoader();
	alSourcePlay( Menu );
	frontEndFont = myEngine->LoadFont("Poplar Std", 85);
	textBackColour = myEngine->CreateSprite("BackTextColour.png",145,100,0);
	backdrop = myEngine->CreateSprite( "lab.jpg", 0, 0, 1);
}

void frontEndUpdate()
{
	frontEndFont->Draw("Start Game",155,100);
	frontEndFont->Draw("Quit",155,200);

	if(myEngine->KeyHit(downArrowKey))
	{
		textBackColour->SetY(200);
	}
	else if(myEngine->KeyHit(upArrowKey))
	{
		textBackColour->SetY(100);
	}
}

void frontEndRemovel()
{
	myEngine->RemoveSprite(textBackColour);
	myEngine->RemoveFont(frontEndFont);
	myEngine->RemoveSprite(backdrop);
	alSourceStop( Menu );
}
	
void gameSetUp()
{
	alSourcePlay( sourceBack );
	/*Model Setup*/
	sphereMesh = myEngine->LoadMesh("Sphere.x");
	player = sphereMesh->CreateModel(0.0f, 5.0f, 100.0f);
	floorMesh = myEngine->LoadMesh("Block.x");
	bulletMesh = myEngine->LoadMesh("Bullet.x");
	enemyMesh = myEngine->LoadMesh("sopwith-camel.x");
	ground[0] = floorMesh->CreateModel(1500.0f, baseHeight, 100.0f);
	float x = 1000.0f;
	for(int i = 1;  i <= 5; i++)
	{
		ground[i] = floorMesh->CreateModel(x, 0.0f, 0.0f);
		ground[i]->AttachToParent(ground[0]);
		x += 1000.0f;
	}
	ground[6] = floorMesh->CreateModel(-1545.0f, -117.0f, 0.0f);
	ground[6]->AttachToParent(ground[0]);
	ground[6]->RotateZ(-90);
	camera = myEngine->CreateCamera(kFPS,0.0f,50.0f,-60.0f);
	enemy = enemyMesh->CreateModel(0.0f,5.0f,100.0f);
	enemy->Scale(5.0f);
	player->SetSkin("WhiteBall.jpg");
	enemy->AttachToParent(ground[0]);
	enemy->SetLocalPosition(-1000.0f, 20.0f, 0.0f);
	enemy->RotateLocalY(-90.0f);
	numOfEnemies++;
	numBullets = 0;

	/*Map Setup*/
	CMap* temp = new CMap();
	temp->MapLoading(ground[0]);

	/*UI Setup*/
	FPSDisplay = myEngine->LoadFont( "Comic Sans MS", 36 );
	backdrop = myEngine->CreateSprite( "SARF_Jungle_Background_by_MrCanavan.jpg", 0, 0, 1);
}

void gameUpdate()
{
	updateTime = myEngine->Timer();
	outText << "FPS: " << 0.25f / updateTime  ;
	FPSDisplay ->Draw( outText.str(), fontX, fontY );
	outText.str("");

	map[0]->setMinMax();
	float floorY = ground[0]->GetY();

	//used to check for collision
	const int SIZE = map.size();
	bool collision = false;

	for(int i = 0; i < SIZE; i++)
	{
		collision = map[i]->collisionDetection(player, i);
		if(collision == true)
		{
			break;
		}
	}

	//Movement Controls
	if((myEngine->KeyHeld(leftKey) ||  (Player1->IsConnected()) 
		&& Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) && ground[0]->GetX() < 1525)
	{
		ground[0]->MoveX(speed * updateTime);
	}
	if((myEngine->KeyHeld(rightKey) ||  (Player1->IsConnected())
		&& Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) //&& ground[0]->GetX() < 1510)
	{
		ground[0]->MoveX(-speed * updateTime);
	}

	//Code to make the player look like they are jumping but the platforms moves down
	if((myEngine->KeyHeld(jumpKey) || (Player1->IsConnected()) 
		&& Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A ))
	{
		//code to apply gravity and move the ground and platforms attached to it
		ground[0]->MoveY(-speed * gravity * updateTime);
		gravity -= 0.0095f;
		if(floorY > baseHeight || collision)
		{
			gravity = 3.0f;
		}
	}
	else
	{
	//checks to see if players is in the air moves ground up if so
		if(floorY < baseHeight && !collision)
		{
			gravity = -2.5f;
			ground[0]->MoveY(-speed * gravity * updateTime);
		}
	//sets gravity to start value if thier is a collision or on ground floor
		if(floorY > baseHeight || collision)
		{
			gravity = 3.0f;
		}
	}

	bulletMovement();
}

void gameRemovel()
{
	alutExit();
	sphereMesh->RemoveModel(player);
	for(int i = 0; i < 3; i++)
	{
		floorMesh->RemoveModel(ground[i]);
	}
	myEngine->RemoveMesh(floorMesh);
	myEngine->RemoveMesh(sphereMesh);
	myEngine->RemoveMesh(bulletMesh);
	myEngine->RemoveMesh(enemyMesh);
	myEngine->RemoveCamera(camera);
}

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "Media" );

	frontEndSetUp();

	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();
		frontEndUpdate();

		if(myEngine->KeyHit(quitKey) ||  (Player1->IsConnected()) && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			break;
		}
	}

	frontEndRemovel();

	gameSetUp();
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();
		
		gameUpdate();

		if(myEngine->KeyHit(quitKey)||  (Player1->IsConnected()) && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			break;
		}
	}

	gameRemovel();
	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
