#ifndef _ENEMY
#define _ENEMY
#include <TL-Engine.h>
#include <vector>
using namespace tle;
extern I3DEngine* myEngine;


class CEnemy
{
private:
	IMesh* enemy;
	IModel* enemyModel;
	int maxEnemies;
public:
	CEnemy(char enemyType);
	~CEnemy();
	void enemyRemoval(IModel* enemyModel);
	int MaxEnemiesGet();
	IModel* ReturnModel();
	virtual void Creation(IModel* Ground, float updateTime);
	virtual void Moving(float updateTime);
};

#else

#endif