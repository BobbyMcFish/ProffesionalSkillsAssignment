#include "Player.h"

Player::Player()
{
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
	if( nextLeg && lCounter < legLimit)
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