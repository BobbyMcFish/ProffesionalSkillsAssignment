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
	deque <IModel*> bullets;
	float bulletSpeed;
	int spawnDistance;
	float minX[3];
	float maxX[3];
	float minY[3];
	float maxY[3];
	int numOfBullets;
public:
	DShooterEnemy(IModel* ground, IModel* player);
	void Creation(IModel* ground, float updateTime);
	void Moving(float updateTime);
	void minMax(IModel* shootEnemy, int i);
	bool PlayerCollisionDetection(int i);
	bool BulletCollisionDetection(int i);
};