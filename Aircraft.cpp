#include <cstdlib>
#include "Aircraft.h"

Aircraft::Aircraft(int lenth, int width, int force, int generateSpeed, int moveSpeed)
{
	initBoard(lenth, width);
	initBullet(force, generateSpeed, moveSpeed);
}

Aircraft::~Aircraft()
{
	for (int i = 0; i < boardLenth; ++i) {
		delete [] bullet[i];
	}
	delete [] bullet;
	bullet = NULL;
}
void Aircraft::initBoard(int lenth, int width)
{
	boardLenth =lenth;
	boardWidth = width;
	bullet = new int* [boardLenth]();
	for (int i = 0; i < boardLenth; ++i)
		bullet[i] = new int [boardWidth]();
}
void Aircraft::initBullet(int force, int generateSpeed, int moveSpeed)
{
	setBulletForce(force);
	setBulletGenerateSpeed(generateSpeed);
	setBulletGenerateSpeedCnt(0);
	setBulletMoveSpeed(moveSpeed);
	setBulletMoveSpeedCnt(0);

}

void Aircraft::singleBulletGenerate(Aircraft_Attr position, int direc, int force)
{
	for (int i = 0; i < force; ++i) {
		bullet[position.x+direc][position.y+i] = 1;
		bullet[position.x+direc][position.y] = 1;
		bullet[position.x+direc][position.y-i] = 1;
	}
}

void Aircraft::bulletGenerate(Aircraft_Attr aircraft_pst, int dirc)
{
	int force = 1;
	int random = rand() % 20;
	if (random == 0) {
		force = 2;
		goto aa;
	}
	random = rand() % 60;
	if (random == 0) {
		force = 3;
		goto aa;
	}
	random = rand() % 80;
	if (random == 0) {
		force = 4;
		goto aa;
	}
	random = rand() % 100;
	if (random == 0) {
		force = 5;
		goto aa;
	}

aa:
	setBulletGenerateSpeedCnt(1);
	if (getBulletGenerateSpeedCnt() == getBulletGenerateSpeed()) {
		singleBulletGenerate(aircraft_pst, dirc, force);
		setBulletGenerateSpeedCnt(0);
	}
}

int Aircraft::getBulletGenerateSpeed() const
{
	return bulletGenerateSpeed;
}

void Aircraft::setBulletGenerateSpeed(int generateSpeed)
{
	bulletGenerateSpeed = generateSpeed;
}

int Aircraft::getBulletGenerateSpeedCnt() const
{
	return bulletGenerateSpeedCnt;
}

void Aircraft::setBulletGenerateSpeedCnt(int state)
{
	if (state)
		bulletGenerateSpeedCnt++;
	else
		bulletGenerateSpeedCnt = 0;
}

int Aircraft::getBulletMoveSpeed() const
{
	return bulletMoveSpeed;
}


void Aircraft::setBulletMoveSpeed(int moveSpeed)
{
	bulletMoveSpeed = moveSpeed;
}

int Aircraft::getBulletMoveSpeedCnt() const
{
	return bulletMoveSpeedCnt;
}

void Aircraft::setBulletMoveSpeedCnt(int state)
{
	if (state)
		bulletMoveSpeedCnt++;
	else
		bulletMoveSpeedCnt = 0;
}

void Aircraft::setBulletForce(int force)
{
	bulletForce = force;
}

int Aircraft::getBulletForce() const
{
	return bulletForce;
}

int** Aircraft::getBullet() const
{
	return bullet;
}
void Aircraft::setBullet(int x, int y, int state)
{
	bullet[x][y] = state;
}

int Aircraft::getBoardLenth() const
{
	return boardLenth;
}
int Aircraft::getBoardWidth() const
{
	return boardWidth;
}
