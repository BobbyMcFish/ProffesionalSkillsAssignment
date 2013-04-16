#include "Enemy.h"


class DShooterEnemy : public CEnemy
{
private:
	float scale;
	int numOfEnemies;
	IModel* shooter;
	vector <IModel*> shooters;
	int spawnDistance;
	float minX[3];
	float maxX[3];
	float minY[3];
	float maxY[3];
public:
	DShooterEnemy(IModel* ground, IModel* player);
	void Creation(IModel* ground, float updateTime);
	void Moving(float updateTime);
	void minMax(IModel* shootEnemy, int i);
	bool PlayerCollisionDetection(int i);
	bool BulletCollisionDetection(int i);
};