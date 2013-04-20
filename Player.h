#ifndef _PLAYER
#define _PLAYER
#include <TL-Engine.h>
#include <windows.h>
using namespace tle;
extern I3DEngine* myEngine;

class Player
{
private:
	int health;
	int lives;
	IMesh* playerMesh;
	IModel* model;
	int legLimit;
	int lCounter;
	int rCounter;
	bool nextLeg;
public:
	Player();
	~Player();
	void SetHealth( int damage);
	void SetLives(int life);
	IModel* GetModel() const;
	void GetHealth( int &playerHealth) const;
	void GetLives(int & playerLife) const;
	void leftLeg();
	void rightLeg();
	bool CollisionDection();
};
#endif