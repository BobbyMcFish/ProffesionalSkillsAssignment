#include "Runner.h"


class DShooterEnemy : public CEnemy
{
private:
	float scale;
	float bulletSpeed;
	int numOfEnemies;
	IModel* playerModel;
	IModel* shooter;
	IMesh* bulletMesh;
	vector <IModel*> shooters;
	IModel* bullet;
	int spawnDistance;
	float bulletLife;
	float MinX;
	float MaxX;
	float MinY;
	float MaxY;
	float pMaxX;
	float pMinX;
	float pMaxY;
	float pMinY;
	float shootY;
	int numOfBullets;
	bool bulletBool;
	bool playerHit;
public:
	DShooterEnemy(IModel* ground, IModel* player);
	void Creation(IModel* ground, float updateTime);
	void Moving(float updateTime);
	void minMax();
	bool PlayerHit();
	bool PlayerCollisionDetection();
	bool BulletCollisionDetection(IModel* bullet);
	bool ReturnBulletCollision();
};