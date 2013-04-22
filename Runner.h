#include "Enemy.h"
#include "Player.h"

class DRunningEnemy : public CEnemy
{
private:
	float scale;
	float speed;
	float playerX;
	float playerY;
	IMesh* runnerMesh;
	IModel* runner;
	vector <IModel*> runners;
	int numOfEnemies;
	IModel* playerModel;
	float minX;
	float maxX;
	float minY;
	float maxY;
	float shooterY;
	bool playerCollision;
	bool bulletCollision;

public:
	DRunningEnemy(IModel* ground, IModel* player, float sentSpeed);
	void Creation(IModel* Ground, float updateTime);
	void Moving(float updateTime);
	void minMax();
	bool PlayerCollisionDetection();
	bool BulletCollisionDetection(IModel* bullet);
	bool ReturnPlayerCollision();
	bool ReturnBulletCollision();
};