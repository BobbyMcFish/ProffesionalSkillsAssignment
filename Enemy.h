#ifndef _ENEMY
#define _ENEMY
#include <TL-Engine.h>
using namespace tle;
extern I3DEngine* myEngine;


class Enemy
{
private:
	int maxEnemies;
	int maxEnemyBullets;
public:
	Enemy();
	~Enemy();
	int MaxEnemiesGet();
	virtual void RunningCreation(IModel* ground, float updateTime, IModel* player);
};

class RunningEnemy : public Enemy
{
private:
	float speed;
	float scale;
	int maxRunners;
	int numOfEnemies;
	IMesh* runnerMesh;
public:
	RunningEnemy();
	void RunningCreation(IModel* ground, float updateTime, IModel* player);
};
#else

#endif