#ifndef _MAIN
#define _MAIN
void soundLoader(float volume);
void bulletMovement(float bulletSpeed, int maxBullets, float playerY, float playerX);
void soundLoader();
void bulletMovement(float bulletSpeed, int maxBullets, float playerY, float playerX, bool hit);
#endif