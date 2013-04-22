#include "Runner.h"
//extern Player player;
extern struct BulletData
{
	IModel* model;
	float xVel, yVel;
	float life;
};

extern deque <BulletData*> bullets;
extern int numBullets;
//extern const float playerX;
//extern const float playerY;


DRunningEnemy::DRunningEnemy(IModel* ground, IModel* player, float sentSpeed) : CEnemy('a')
{
	playerModel = player;
	scale = 3.0f;
	speed = sentSpeed;
	minX = 0;
	minY = 0;
	maxX = 0;
	maxY = 0;
	runY = 0;
	numOfEnemies = 0;
}


void DRunningEnemy::Creation(IModel* ground, float updateTime)
{
	if(numOfEnemies < 1)
	{
		runnerMesh = myEngine->LoadMesh("sopwith-camel.x");
		runner = runnerMesh->CreateModel();
		runner->AttachToParent(ground);
		runner->SetLocalPosition((-1000.0f), 20.0f, 0.0f);
		runner->LookAt(playerModel);
		runner->Scale(scale);
		numOfEnemies++;
	}
}

void DRunningEnemy::Moving(float updateTime)
{
	float playerX = playerModel->GetX();
	runner->MoveX(-speed * updateTime);
	minMax();
	playerCollision = PlayerCollisionDetection();
	for(int j = 0; j < bullets.size(); j++)
	{
		bulletCollision = BulletCollisionDetection(bullets.at(j)->model);
	}
	if(runner->GetX() < playerX-200)
	{
		float runnerX = runner->GetX();
		runnerX = playerModel->GetX()+300;
		runner->SetX(playerModel->GetX()+300);
		runner->SetY(0.0f + runY);
		runY += 25;
	}
	else if(playerCollision == true || bulletCollision == true )
	{
		runner->SetX(playerX+300);
		runner->SetY(0.0f + runY);
		runY += 10;
	}
	if(runY > 50)
	{
		runY = 0.0f;
	}
	
}

void DRunningEnemy::minMax()
{
	minX = runner->GetX() - 10.0f;
	maxX = runner->GetX() + 10.0f;
	minY = runner->GetY() - 10.0f;
	maxY = runner->GetY() + 10.0f;
	playerMinX = playerModel->GetX() - 5.0f;
	playerMaxX = playerModel->GetX() + 5.0f;
	playerMinY = playerModel->GetY() - 10.0f;
	playerMaxY = playerModel->GetY() + 10.0f;
}

bool DRunningEnemy::PlayerCollisionDetection()
{
	float radius = 13.0f;
	if(playerMaxX > minX && playerMinX < maxX && playerMaxY > minY && playerMinY < maxY)
	{
		if(maxY - playerMaxY  > playerMinY)
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

bool DRunningEnemy::BulletCollisionDetection(IModel* bullet)
{
	float bulletX;
	float bulletY;
	bulletX = bullet->GetX();
	bulletY = bullet->GetY() + 15;
	if(bulletX > minX && bulletY > minY && bulletY < maxY)
	{
		return true;
	}
	
	return false;
}

bool DRunningEnemy::ReturnPlayerCollision()
{
	return playerCollision;
}

bool DRunningEnemy::ReturnBulletCollision()
{
	return bulletCollision;
};