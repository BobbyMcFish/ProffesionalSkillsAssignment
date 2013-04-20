// Game play.cpp: A program using the TL-Engine
#include "GlobalVars.h"
#include "Main Controls.h"

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
	player = new Player();
	enemies.push_back(new DRunningEnemy(ground[0], player->GetModel()));
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
	camera = myEngine->CreateCamera(kFPS,0.0f,50.0f,-60.0f);
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


	enemies[0]->Creation(ground[0], updateTime);

	enemies[0]->Moving(updateTime);

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

	bulletMovement(bulletSpeed, maxBullets, playerY, playerX);
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
