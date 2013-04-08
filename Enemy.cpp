//////test
#include "Enemy.h"
extern IModel* player;
CEnemy::CEnemy(char enemyType)
{
	enemy = NULL;
	if(enemyType == 'a')
	{
		enemy = myEngine->LoadMesh("sopwith-camel.x");
		enemyModel = enemy->CreateModel();
	}
}
CEnemy::~CEnemy()
{

}

void CEnemy::enemyRemoval(IModel* enemyModel)
{
	enemy->RemoveModel(enemyModel);
}

int CEnemy::MaxEnemiesGet()
{
	return maxEnemies;
}

IModel* CEnemy::ReturnModel()
{
	return enemyModel;
}
void CEnemy::RunningCreation(IModel* Ground, float updateTime)
{

}
void CEnemy::Moving(float updateTime)
{

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