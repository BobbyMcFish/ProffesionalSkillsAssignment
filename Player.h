#ifndef _PLAYER
#define _PLAYER
#include <TL-Engine.h>
#include <windows.h>
using namespace tle;
extern I3DEngine* myEngine;

class Player
{
private:
	int health; // players health
	int lives; // players lives
	IMesh* playerMesh; // players mesh
	IModel* model; // players model
	int legLimit; // the legs rotation limit
	int lCounter; // left leg counter
	int rCounter; // right leg counter
	bool nextLeg; // allows switching between moving leg forward and back
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