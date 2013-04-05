#include "Enemy.h"

Enemy::Enemy()
{
	maxEnemies = 6;
	maxEnemyBullets = 3;
}
Enemy::~Enemy()
{

}

int Enemy::MaxEnemiesGet()
{
	return maxEnemies;
}
void Enemy::RunningCreation(IModel* ground, float updateTime, IModel* player)
{

}


RunningEnemy::RunningEnemy() : Enemy()
{
	speed = 0.05f;
	scale = 5.0f;
	numOfEnemies = 0;
	runnerMesh = myEngine->LoadMesh("sopwith-camel.x");
}


void RunningEnemy::RunningCreation(IModel* ground, float updateTime, IModel* player)
{
	int maxNumber = MaxEnemiesGet();
	const int maxSpawn = 3;
	IModel* runner[maxSpawn];
	for(numOfEnemies; numOfEnemies < maxSpawn; numOfEnemies++)
	{
		runner[numOfEnemies] = runnerMesh->CreateModel(player->GetX()+400, player->GetY(), player->GetZ()); 
		runner[numOfEnemies]->Scale(scale);
		runner[numOfEnemies]->AttachToParent(ground);
		runner[numOfEnemies]->SetLocalPosition(-1000.0f, 20.0f, 0.0f);
		runner[numOfEnemies]->RotateLocalY(-90.0f);
	}
	for(int i = 0; i < numOfEnemies; i++)
	{
		runner[i]->LookAt(player); 
		runner[i]->MoveX(-speed * updateTime);
		if(runner[i]->GetX() < -200)
		{
			runnerMesh->RemoveModel(runner[i]);
			numOfEnemies--;
		}
	}
}


/*void EnemyBulletMovement()
{
	for(int i = 0; i < maxEnemyBullets; i++)
	{
		enemyBullets[i].model->Move( -bulletSpeed * updateTime, 0, 0);

		enemyBullets[i].life -= updateTime;

		if (enemyBullets[i].life <= 0)
		{
			// Destroy bullet
			bulletMesh->RemoveModel( enemyBullets[i].model );

			// Copy last bullet into this dead slot to keep all live bullets in one block
			enemyBullets[i].model = enemyBullets[numEnemyBullets-1].model;
			enemyBullets[i].xVel = enemyBullets[numEnemyBullets-1].xVel;
			enemyBullets[i].yVel = enemyBullets[numEnemyBullets-1].yVel;
			enemyBullets[i].life = enemyBullets[numEnemyBullets-1].life;

			// Decrease number of bullets
			numEnemyBullets--;
		}
	}
	if(enemy->GetX() < 300 && numEnemyBullets < maxEnemyBullets)
	{
		enemyBullets[numEnemyBullets].model = bulletMesh->CreateModel( enemy->GetX(), enemy->GetY(), enemy->GetZ());

		// Length of bullet's life measured in seconds
		enemyBullets[numEnemyBullets].life = 1.5f;
		numEnemyBullets++;
	}
	
}*/