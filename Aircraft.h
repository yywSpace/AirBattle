#ifndef AIRCRAFT_H
#define AIRCRAFT_H

struct Aircraft_Attr {
	int x;
	int y;
	int model[3][6] = {};
	int life;
};

class Aircraft
{
public:
	Aircraft(int lenth, int width, int force, int generateSpeed, int moveSpeed);
	~Aircraft();
	void initBoard(int lenth, int width);
	void initBullet(int force, int generateSpeed, int moveSpeed);
	void singleBulletGenerate(Aircraft_Attr position, int direc, int force);
	void bulletGenerate(Aircraft_Attr aircraft_pst, int dirc);
	int getBulletGenerateSpeed() const;
	void setBulletGenerateSpeed(int generateSpeed);
	int getBulletGenerateSpeedCnt() const;
	void setBulletGenerateSpeedCnt(int state);
	int getBulletMoveSpeed() const;
	void setBulletMoveSpeed(int moveSpeed);
	int getBulletMoveSpeedCnt() const;
	void setBulletMoveSpeedCnt(int state);
	int getBulletForce() const;
	void setBulletForce(int force);
	int ** getBullet() const;
	void setBullet(int x, int y, int state);
	int getBoardLenth() const;
	int getBoardWidth() const;

	virtual void generateBullet() = 0;
	virtual void moveBullet() = 0;
	virtual void drawAircraft() = 0;
	virtual void drawBullet() = 0;

public:
	const int BULLTE_UP = -1;
	const int BULLTE_DOWN = 1;

private:
	int boardLenth;
	int boardWidth;
	int **bullet;
	int shrapnelReady;
	int bulletForce;
	int bulletForceCnt;
	int bulletGenerateSpeed;
	int bulletGenerateSpeedCnt;
	int bulletMoveSpeed;
	int bulletMoveSpeedCnt;
};

#endif
