#include "Player.h"

Player::Player()
{
	health = 100;
	lives = 3;
	playerMesh = myEngine->LoadMesh("Robot.x");
	model = playerMesh->CreateModel(0.0f, 5.0f, 100.0f);
	model->Scale(10);
}

Player::~Player()
{
	playerMesh->RemoveModel(model);
	myEngine->RemoveMesh(playerMesh);
}

void Player::GetHealth(int &playerHealth) const
{
	playerHealth = health;
}

void Player::GetLives( int &playerLife) const
{
	playerLife = lives;
}

IModel* Player::GetModel() const
{
	return model;
}

void Player::SetHealth( int damage)
{
	health -= damage;
}

void Player::SetLives(int life)
{
	lives -= life;
}

void Player::MoveModel()
{

}