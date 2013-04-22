#include "Shooter.h"

extern struct BulletData
{
	IModel* model;
	float xVel, yVel;
	float life;
};

extern deque <BulletData*> bullets;

DShooterEnemy::DShooterEnemy(IModel* ground, IModel* player) : CEnemy('b')
{
	playerModel = player;
	scale = 5.0f;
	shooter = ReturnModel();
	numOfEnemies = 0;
	spawnDistance = 10;
	numOfBullets = 0;
	shootY = 0.0f;
	shootZ = 0.0f;
	bulletBool = false;
	MinX = 0;
	MinY = 0;
	MaxX = 0;
	MaxY = 0;
}

void DShooterEnemy::Creation(IModel* ground, float updateTime)
{
	if(numOfBullets < 1)
	{
		shooter->AttachToParent(ground);
		shooter->SetLocalPosition(-1000.0f, 25.0f, 0.0f);
		shooter->LookAt(playerModel);
		shooter->Scale(1.0f);
		bulletSpeed = 200.0f;
		numOfBullets++;
	}
}

void DShooterEnemy::Moving(float updateTime)
{
	if (bulletBool == false)
	{
		float shooterX = shooter->GetX();
		float shooterY = shooter->GetY();
		float shooterZ = shooter->GetZ();
		bulletMesh = myEngine->LoadMesh("Bullet.x");
		bulletBool = true;
		bullet = bulletMesh->CreateModel();
		bullet->AttachToParent(shooter);
		shooter->LookAt(playerModel);
		bullet->SetPosition(shooterX, shooterY, shooterZ);
		bullet->Scale(1.0f);
		bulletLife = 3.0f;
		bullet->SetSkin("venus.jpg");
	}
	 
	bullet->MoveZ(bulletSpeed * updateTime);
	bulletLife -= updateTime;
	minMax();
	bool playerHit = PlayerCollisionDetection();
	if(playerModel->GetX()-50 > shooter->GetX())
	{
		shootY += 25;
		shootZ -= 30;
		shooter->SetX(playerModel->GetX()+100);
		shooter->SetY( 0.0f + shootY);
	}
	if(bulletBool == true)
	{
		if(bulletLife <= 0.0f )
		{
			bulletMesh->RemoveModel(bullet);
			bulletBool = false;
		}
	}
	if(shootY >= 50)
	{
		shootY = 0.0f;
	}
}

void DShooterEnemy::minMax()
{
	MinX = shooter->GetX() - 10.0f;
	MaxX = shooter->GetX() + 10.0f;
	MinY = shooter->GetY() - 10.0f;
	MaxY = shooter->GetY() + 10.0f;

	pMinX = playerModel->GetX() - 10.0f;
	pMaxX = playerModel->GetX() + 10.0f;
	pMinY = playerModel->GetY() - 10.0f;
	pMaxY = playerModel->GetY() + 10.0f;
}

bool DShooterEnemy::PlayerCollisionDetection()
{
	float playerX = playerModel->GetX();
	float playerY = playerModel->GetY();
	if(playerX > MinX && playerX < MaxX && playerY > MinY && playerY < MaxY)
	{
		if((MaxY - playerY)  > playerY)
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

bool DShooterEnemy::BulletCollisionDetection(IModel* bullet)
{
	return false;
}