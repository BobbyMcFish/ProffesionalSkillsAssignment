#include "Enemy.h"


class DRunningEnemy : public CEnemy
{
private:
	float scale;
	float speed[3];
	int numOfEnemies;
	IModel* runner;
	vector <IModel*> runners;
	int spawnDistance;
	float minX[3];
	float maxX[3];
	float minY[3];
	float maxY[3];
	bool playerCollision;
public:
	DRunningEnemy(IModel* ground, IModel* player);
	void Creation(IModel* Ground, float updateTime);
	void Moving(float updateTime);
	void minMax(IModel* runEnemy, int i);
	bool PlayerCollisionDetection(int i);
	bool BulletCollisionDetection(int i);
	bool ReturnPlayerCollision();
};