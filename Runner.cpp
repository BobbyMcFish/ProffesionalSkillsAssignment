#include "Runner.h"
extern IModel* player;
extern struct BulletData;
extern vector <BulletData*> bullets;
extern int numBullets;


DRunningEnemy::DRunningEnemy(IModel* ground, IModel* player) : CEnemy('a')
{
	scale = 5.0f;
	runner = ReturnModel();
	speed[0] = 5.0f;
	speed[1] = 50.0f;
	speed[2] = 100.0f;
	numOfEnemies = 0;
	spawnDistance = 10;
}


void DRunningEnemy::Creation(IModel* ground, float updateTime)
{
	int maxNumber = 3;
	const int maxSpawn = 3;
	float x = 0.0f;
	for(numOfEnemies; numOfEnemies < maxSpawn; numOfEnemies++)
	{
		runner->AttachToParent(ground);
		runner->SetLocalPosition((-1000.0f + x), 20.0f, 0.0f);
		runner->RotateLocalY(-90.0f);
		runner->LookAt(player);
		runner->Scale(scale);
		runners.push_back(runner);
		runner = ReturnModel();
		x += 10.0f;
	}
}

void DRunningEnemy::Moving(float updateTime)
{
	for(int i = 0; i < numOfEnemies; i++)
	{
		runners.at(i)->MoveX(-speed[i] * updateTime);
		minMax(runners[i], i);
		playerCollision = PlayerCollisionDetection(i);
		if(runners.at(i)->GetX() < player->GetX()-200)
		{
			runners.at(i)->SetX(player->GetX()+400);
		}
		else if(playerCollision == true)
		{
			runners.at(i)->SetX(player->GetX()+400);
		}
	}
}

void DRunningEnemy::minMax(IModel* RunEnemy, int i)
{
	minX[i] = RunEnemy->GetX() - 10.0f;
	maxX[i] = RunEnemy->GetX() + 10.0f;
	minY[i] = RunEnemy->GetY() - 10.0f;
	maxY[i] = RunEnemy->GetY() + 10.0f;
}

bool DRunningEnemy::PlayerCollisionDetection(int i)
{
	float radius = 13.0f;
	float playerY = player->GetY();
	float playerX = player->GetX();

	if(playerX > minX[i] && playerX < maxX[i] && playerY > minY[i] && playerY < maxY[i])
	{
		if(maxY[i] - playerY  > playerY)
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

bool DRunningEnemy::BulletCollisionDetection(int i)
{
	float bulletX[5];
	for(int i = 0; i < numBullets; i++)
	{
		bulletX[i] = bullets.at(i)->Model->getX();
	}
}

bool DRunningEnemy::ReturnPlayerCollision()
{
	return playerCollision;
};