#ifndef _PLAYER
#define _PLAYER
#include <TL-Engine.h>
using namespace tle;
extern I3DEngine* myEngine;

class Player
{
private:
	int health;
	int lives;
	IMesh* playerMesh;
	IModel* model;
public:
	Player();
	~Player();
	void SetHealth( int damage);
	void SetLives(int life);
	void GetModel( IModel* playerModel) const;
	void GetHealth( int &playerHealth) const;
	void GetLives(int & playerLife) const;
	void MoveModel();
	bool CollisionDection();
};
#endif