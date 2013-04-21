#include "Player.h"

Player::Player()
{
	//Sets default values for the players variables
	health = 100;
	lives = 3;

	playerMesh = myEngine->LoadMesh("Robot.x");
	model = playerMesh->CreateModel(0.0f, 0.0f, 100.0f);
	model->Scale(3.0f);
	model->RotateY(100.0f);

	legLimit = 200;

	lCounter = 0;
	rCounter = 0;

	nextLeg =  true;
}

Player::~Player()
{
	playerMesh->RemoveModel(model);
	myEngine->RemoveMesh(playerMesh);
}

void Player::GetHealth(int &playerHealth) const
{
	playerHealth = health;
}

void Player::GetLives( int &playerLife) const
{
	playerLife = lives;
}

IModel* Player::GetModel() const
{
	return model;
}

void Player::SetHealth( int damage)
{
	health -= damage;
}

void Player::SetLives(int life)
{
	lives -= life;
}

void Player::leftLeg()
{
	// tests to see if bool is true and if the left leg limit has not been reached
	if( nextLeg && lCounter < legLimit)
		{
			//gets the nodes for the right and left leg then rotates them in oppsite directions
			model->GetNode(2)->RotateY(0.05f);
			model->GetNode(3)->RotateY(-0.05);

			//increases and decreause apporpriate counters
			lCounter++;
			rCounter--;

			//checks if the left counter has exceded the limit
			if(lCounter >= legLimit)
			{
				//if so changes to next leg and set right counter to default value
				nextLeg = !nextLeg;
				rCounter = 0;
			}
		}
	// tests to see if bool is false and if the right leg limit has not been reached
		else if( !nextLeg && rCounter < legLimit)
		{
			model->GetNode(3)->RotateY(0.05f);
			model->GetNode(2)->RotateY(-0.05);
			
			rCounter++;
			lCounter--;
			if(rCounter >= legLimit)
			{
				nextLeg = !nextLeg;
				lCounter = 0;
			}
		}
}

void Player::rightLeg()
{
	if( nextLeg && rCounter < legLimit)
		{
			model->GetNode(3)->RotateY(0.05f);
			model->GetNode(2)->RotateY(-0.05);

			rCounter++;
			lCounter--;
			if(rCounter >= legLimit)
			{
				nextLeg = !nextLeg;
				lCounter = 0;
			}
		}
		else if( !nextLeg && lCounter < legLimit)
		{
			model->GetNode(2)->RotateY(0.05f);
			model->GetNode(3)->RotateY(-0.05);
			
			lCounter++;
			rCounter--;
			if(lCounter >= legLimit)
			{
				nextLeg = !nextLeg;
				rCounter = 0;
			}
		}
}