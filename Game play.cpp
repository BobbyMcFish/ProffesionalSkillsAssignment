// Game play.cpp: A program using the TL-Engine
#include "GlobalVars.h"
#include "Main Controls.h"

void frontEndSetUp()
{	
	soundLoader(volume);
	//CXBOXController* Player1 = new CXBOXController(1); 
	alSourcePlay( Menu );
	frontEndFont = myEngine->LoadFont("Poplar Std", 85);
	textBackColour = myEngine->CreateSprite("BackTextColour.png",145,100,0);
	backdrop = myEngine->CreateSprite( "lab.jpg", 0, 0, 1);
}

void frontEndUpdate()
{
	frontEndFont->Draw("Start Game",155,100);
	frontEndFont->Draw("Quit",155,200);

	if(myEngine->KeyHit(downKey) || (Player1->IsConnected())
	&& Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		textBackColour->SetY(200);
	}
	else if(myEngine->KeyHit(jumpKey) || (Player1->IsConnected())
	&& Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		textBackColour->SetY(100);
	}
	if((myEngine->KeyHit(enterKey) || (Player1->IsConnected())
	&& Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) && textBackColour->GetY() == 100)
	{
		isBegining = !isBegining;
	}

	if((myEngine->KeyHit(quitKey) || (Player1->IsConnected())
	&& Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B) && textBackColour->GetY() == 200)
	{
		isQuiting = !isQuiting;
	}
}

void frontEndRemovel()
{
	myEngine->RemoveSprite(textBackColour);
	myEngine->RemoveFont(frontEndFont);
	myEngine->RemoveSprite(backdrop);
	alSourceStop( Menu );
}

void gameShutDown()
{
	myEngine->Stop();
}
	
void gameSetUp()
{
	alSourcePlay( sourceBack );
	player = new Player();
	/*Model Setup*/
	sphereMesh = myEngine->LoadMesh("Sphere.x");
	floorMesh = myEngine->LoadMesh("Block.x");
	bulletMesh = myEngine->LoadMesh("Bullet.x");
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
	camera = myEngine->CreateCamera(kManual,0.0f,50.0f,-60.0f);
	numBullets = 0;

	/*Map Setup*/
	CMap* temp = new CMap();
	temp->MapLoading(ground[0]);

	/*UI Setup*/
	FPSDisplay = myEngine->LoadFont( "Comic Sans MS", 36);
	backdrop = myEngine->CreateSprite( "SARF_Jungle_Background_by_MrCanavan.jpg", 0, 0, 1);

	/*Enemy Setup*/
	runners = new DRunningEnemy(ground[0], player->GetModel(),100.0f);
	shooters = new DShooterEnemy(ground[0], player->GetModel());	
}

void gameUpdate()
{
	player->GetHealth(playerHealth);
	player->GetLives(playerLives);
	updateTime = myEngine->Timer();
	outText << "Health: " << playerHealth;
	FPSDisplay ->Draw( outText.str(), fontX, fontY, kWhite );
	outText.str("");
	outText << "Lives remaining: " << playerLives ;
	FPSDisplay ->Draw( outText.str(), livesfontX, livesfontY, kWhite );
	outText.str("");
	map[0]->setMinMax();
	float floorY = ground[0]->GetY();
	if(myEngine->KeyHit(Key_Period) || Player1->IsConnected() && Player1->GetState().Gamepad.bRightTrigger & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		if( volume > minVolume)
		{
		volume -= 0.1; 
		alListenerf ( AL_GAIN,        volume ); 
		}
	}
	else if(myEngine->KeyHit(Key_Comma)|| Player1->IsConnected() && Player1->GetState().Gamepad.bRightTrigger & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		if( volume < maxVolume)
		{
			volume += 0.1;
			alListenerf ( AL_GAIN,        volume );
		}
	}
	runners->Creation(ground[0], updateTime);
	shooters->Creation(ground[0], updateTime);

	runners->Moving(updateTime);
	shooters->Moving(updateTime);
	//used to check for collision
	const int SIZE = map.size();
	bool collision = false;
	IModel* playerModel = player->GetModel();
	for(int i = 0; i < SIZE; i++)
	{
		collision = map[i]->collisionDetection(playerModel, i);
		if(collision == true)
		{
			break;
		}
	}

	bool runnerHit = runners->ReturnPlayerCollision();
	bool shooterHit = shooters->ReturnBulletCollision();
	
	if(runnerHit == true)
	{
		player->SetHealth(50);
	}
	if(shooterHit == true)
	{
		player->SetHealth(10);
	}
	if(playerHealth <= 0)
	{
		player->SetLives(1);
		if(playerLives > 0)
		{
			ground[0]->SetX(1500.0f);
			ground[0]->SetY(baseHeight);
			player->SetHealth(-100);
		}
		else if(playerLives == 0)
		{
			gameOver = true;
		}
	}
	//Movement Controls
	if((myEngine->KeyHeld(leftKey) ||  (Player1->IsConnected()) 
	&& Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) && ground[0]->GetX() < 1525)
	{
		ground[0]->MoveX(speed * updateTime);
		player->leftLeg();
	}
	if((myEngine->KeyHeld(rightKey) ||  (Player1->IsConnected())
	&& Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) //&& ground[0]->GetX() < 1510)
	{
		ground[0]->MoveX(-speed * updateTime);
		player->rightLeg();
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
			gravity = 2.5f;
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
			gravity = 2.5f;
		}
	}
	if((myEngine->KeyHeld(downKey) ||  (Player1->IsConnected()) 
	&& Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && collision)
	{
		ground[0]->MoveY(speed * updateTime + 5.0f);
	}
	if(myEngine->KeyHit(pauseKey) || (Player1->IsConnected()) && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
	{
		isPaused = !isPaused;
	}

	bulletMovement(bulletSpeed, maxBullets, playerY, playerX, false);
}

void gameRemovel()
{
	alutExit();
	for(int i = 0; i < 3; i++)
	{
		floorMesh->RemoveModel(ground[i]);
	}
	myEngine->RemoveMesh(floorMesh);
	myEngine->RemoveMesh(sphereMesh);
	myEngine->RemoveMesh(bulletMesh);
	myEngine->RemoveCamera(camera);
}

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	myEngine->StartWindowed();
	bool win = false;

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "Media" );

	frontEndSetUp();

	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		frontEndUpdate();

		if(isBegining)
		{
			break;
		}
		if(isQuiting)
		{
			gameShutDown();
		}
	}

	frontEndRemovel();

	if(myEngine->IsRunning())
	{
		gameSetUp();
	}
	
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();
		if(!isPaused)
		{
			gameUpdate();
		}
		else 
		{

			if(myEngine->KeyHit(quitKey) || (Player1->IsConnected()) && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				isQuiting = !isQuiting;	
			}
			if(myEngine->KeyHit(pauseKey) || (Player1->IsConnected()) && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
			{
				isPaused = !isPaused;
			}
			FPSDisplay->Draw("Paused", 200, 200, kWhite);
		}
		if(gameOver == true)
		{
			gameRemovel();
			break;
		}
		if(player->GetModel()->GetX() > ground[1]->GetX())
		{
			win == true;
		}
		if(isQuiting)
		{
			gameRemovel();
			break;
		}
	}
	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
	if(gameOver == true)
	{
		cout << "I am sorry you are out of lives, game over." << endl;
		cout << "Please insert 50p to try again!" << endl;
		system ("pause");
	}
	if(win == true)
	{
		cout << "congratulations you won the game!";
		system ("pause");
	}
}
