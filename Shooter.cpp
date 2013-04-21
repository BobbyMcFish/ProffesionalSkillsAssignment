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
}

void DShooterEnemy::Moving(float updateTime)
{
	int maxBullets = 3;
	int x = 0;
	for(numOfBullets; numOfBullets < maxBullets; numOfBullets++)
	{
		x =+ 10;
		IModel* tmp;
		tmp = bulletMesh->CreateModel((shooter->GetX() + x), shooter->GetY(), shooter->GetZ());
		tmp->AttachToParent(shooter);
		tmp->SetPosition((shooter->GetX() + x), shooter->GetY(), shooter->GetZ());
		tmp->Scale(1.0f);
		tmp->SetSkin("venus.jpg");
		bullets.push_back(tmp);
	}
	for(int i = 0; i < numOfBullets; i++)
	{
		bullets.at(i)->MoveZ(5.0f * updateTime);
		if(bullets.at(i)->GetX() < playerModel->GetX())
		{
			bullets.pop_front();
			numOfBullets--;
		}
	}
}

void DShooterEnemy::minMax(IModel* shootEnemy, int i)
{

}

bool DShooterEnemy::PlayerCollisionDetection(int i)
{
	return false;
}

bool DShooterEnemy::BulletCollisionDetection(int i)
{
	return false;
}