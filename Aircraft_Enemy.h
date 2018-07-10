#ifndef AIRCRAFT_ENEMY_H
#define AIRCRAFT_ENEMY_H

#include "Aircraft.h"

class Aircraft_Enemy :public Aircraft
{
public:
	Aircraft_Enemy(int lenth, int width, int force, int bGenerateSpeed,
				   int bMoveSpeed, int eGenerateSpeed, int eMoveSpeed, int enemyNum, int life);
	~Aircraft_Enemy();
	int getEnemyNumber();
	int getEnemyNumberCnt();
	void singleEnemyGenerate(Aircraft_Attr &);
	void generateAircraft();
	void moveAircraft();
	void setAttribute(int n, int x, int y, int life);
	Aircraft_Attr& getAttribute(int n);
	void initAircraft();
	virtual void generateBullet();
	virtual void moveBullet();
	virtual void drawAircraft();
	virtual void drawBullet();

private:
	const int ENEMY = 3;
	const int ENEMY_BULLTE = 4;

	int enemyLife;
	int enemyGenerateSpeed;
	int enemyGenerateSpeedCnt;
	int enemyMoveSpeed;
	int enemyMoveSpeedCnt;
	int enemyNumber;
	int enemyNumberCnt;
	Aircraft_Attr *enemy;
};

#endif
