#ifndef AIRBATTLE_H
#define AIRBATTLE_H

struct Aircraft {
	int v;
	int h;
	int model[3][6] = {};
	int life;
};

class AirBattle
{
public:
	AirBattle();
	~AirBattle();
	void initColor();
	void initGame();
	void initBoard();
	void initEnemy();
	void initBullet();
	void initEnemyBullet();
	void initAircraftBullet();
	void initAircraft();
	void masterMenu();
	bool insideMenu();
	void help();
	bool gameOver();
	void enemyMove();
	void enemyGenerate();
	void singleEnemyGenerate(Aircraft &);

	void singleBulletGenerate(int speed, int **bullet, Aircraft location, int direc);
	void bulletGenerate(int speed, int **bullet, Aircraft location, int direc);
	void aircraftBulletMove();
	void enemyBulletMove();
	void bulletMove();
	void enemyBulletGenerate();


	void aircraftMove(int direction);
	bool airCrash();
	void bulletDraw(int **, const int);
	void aircraftDraw();
	void backgrandDraw();
	void drawEverything();
	void playGame();
private:
	const int AIR_BUTTLE = 1;
	const int ENEMY_BUTTLE = 2;
	const int AIRCRAFT = 3;
	const int ENEMY = 4;
	const int BOUNDARY = 5;
	const int TEXT = 6;
	const int BULLET_UP = -1;
	const int BULLET_DOWN= 1;
	int totalKillCount;
	int boardLenth;
	int boardWidth;
	int **aircraftBullet;
	int shrapnelReady;
	int aircraftBulletForce;
	int aircraftBulletForceCnt;
	int aircraftBulletGenerateSpeed;
	int aircraftBulletGenerateSpeedCnt;
	int aircraftBulletMoveSpeed;
	int aircraftBulletMoveSpeedCnt;

	int enemyBulletGenerateSpeed;
	int enemyBulletGenerateSpeedCnt;
	int enemyBulletMoveSpeed;
	int enemyBulletMoveSpeedCnt;
	int **enemyBullet;

	int enemyLife;
	int enemyMoveSpeed;
	int enemyMoveSpeedCnt;
	int enemyGenerateSpeed;
	int enemyGenerateSpeedCnt;
	int enemyNumber;
	int enemyNumberCnt;
	Aircraft aircraft, *enemy;
};

#endif
