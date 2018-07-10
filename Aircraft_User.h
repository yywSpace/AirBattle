#ifndef AIRCRAFT_USER_H
#define AIRCRAFT_USER_H

#include "Aircraft.h"

class Aircraft_User :public Aircraft
{
public:

	Aircraft_User(int lenth, int width, int force, int generateSpeed, int moveSpeed, int life, int shrapnel);
	void moveAircraft(int drc);
	Aircraft_Attr& getAttribute();
	void setAttribute(int x, int y, int life);
	int getShrapnel();
	void setShrapnel(int num);
	virtual void generateBullet();
	virtual void moveBullet();
	virtual void drawAircraft();
	virtual void drawBullet();
private:
	const int BULLTE_COLOR = 1;
	const int AIRCRAFT_COLOR = 2;
	const int BULLET_UP = -1;
	int aircraftLife;
	int shrapnelReady;
	Aircraft_Attr aircraft;
};

#endif
