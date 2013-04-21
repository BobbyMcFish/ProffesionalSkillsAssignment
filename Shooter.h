#include "Runner.h"


class DShooterEnemy : public CEnemy
{
private:
	float scale;
	int numOfEnemies;
	IModel* playerModel;
	IModel* shooter;
	IMesh* bulletMesh;
	vector <IModel*> shooters;
	IModel* bullet;
	float bulletSpeed;
	int spawnDistance;
	float minX;
	float maxX;
	float minY;
	float maxY;
	int numOfBullets;
	bool bulletBool;
public:
	DShooterEnemy(IModel* ground, IModel* player);
	void Creation(IModel* ground, float updateTime);
	void Moving(float updateTime);
	void minMax(IModel* shootEnemy, int i);
	bool PlayerCollisionDetection(int i);
	bool BulletCollisionDetection(int i);
};