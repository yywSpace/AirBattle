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
	void initAircraft();
	void masterMenu();
	bool insideMenu();
	void help();
	bool gameOver();
	void singleEnemyGenerate(Aircraft &);
	void enemyGenerate();
	void enemyMove();
	void bulletGenerate();
	void singleBulletGenerate(int);
	void bulletMove();
	void aircraftMove(int direction);
	bool airCrash();
	void bulletDraw();
	void aircraftDraw();
	void backgrandDraw();
	void drawEverything();
	void playGame();
private:
	const int AIR_BUTTLE = 1;
	const int AIR_ENEMY = 2;
	const int AIRCRAFT = 3;
	const int BOUNDARY = 4;
	const int TEXT = 5;
	int totalKillCount;
	int boardLenth;
	int boardWidth;
	int **board;
	int shrapnelReady;
	int bulletForce;
	int bulletForceCnt;
	int bulletGenerateSpeed;
	int bulletGenerateSpeedCnt;
	int bulletMoveSpeed;
	int bulletMoveSpeedCnt;
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
