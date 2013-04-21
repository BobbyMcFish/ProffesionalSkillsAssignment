#include "Shooter.h"

DShooterEnemy::DShooterEnemy(IModel* ground, IModel* player) : CEnemy('b')
{
	playerModel = player;
	scale = 5.0f;
	shooter = ReturnModel();
	numOfEnemies = 0;
	spawnDistance = 10;
	numOfBullets = 0;
	bulletMesh = myEngine->LoadMesh("Bullet.x");
}

void DShooterEnemy::Creation(IModel* ground, float updateTime)
{
	shooter = ReturnModel();
	shooter->AttachToParent(ground);
	shooter->SetLocalPosition((-1000.0f), 20.0f, 0.0f);
	shooter->LookAt(playerModel);
	shooter->Scale(1.0f);
	bullet = bulletMesh->CreateModel((shooter->GetX()), shooter->GetY(), shooter->GetZ());
	bullet->AttachToParent(shooter);
	bullet->SetPosition((shooter->GetX()), shooter->GetY(), shooter->GetZ());
	bullet->Scale(1.0f);
	bullet->SetSkin("venus.jpg");
	
}

void DShooterEnemy::Moving(float updateTime)
{
	bullet->MoveZ(10.0f * updateTime);
	bool playerHit = PlayerCollisionDetection(0);
	if(playerHit != false);
	{
		shooter->SetX(playerModel->GetX()+500);	
	}
	if(bullet->GetX() < playerModel->GetX())
	{
		bullet->SetPosition((shooter->GetX()), shooter->GetY(), shooter->GetZ());
	}
}

void DShooterEnemy::minMax(IModel* shootEnemy, int i)
{
	minX = shooter->GetX() - 10.0f;
	maxX = shooter->GetX() + 10.0f;
	minY = shooter->GetY() - 10.0f;
	maxY = shooter->GetY() + 10.0f;
}

bool DShooterEnemy::PlayerCollisionDetection(int i)
{
	if(playerModel->GetX() > minX && playerModel->GetX() < maxX && playerModel->GetY() > minY && playerModel->GetY() < maxY)
	{
		if(maxY - playerModel->GetY()  > playerModel->GetY())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool DShooterEnemy::BulletCollisionDetection(int i)
{
	return false;
}