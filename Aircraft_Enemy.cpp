#include <curses.h>
#include <cstdlib>

#include "Aircraft_Enemy.h"

Aircraft_Enemy::Aircraft_Enemy(int lenth, int width, int force, int bGenerateSpeed,
							   int bMoveSpeed, int eGenerateSpeed, int eMoveSpeed, int enemyNum, int life)

	:Aircraft(lenth, width, force, bGenerateSpeed, bMoveSpeed)
{
	initAircraft(eGenerateSpeed, eMoveSpeed, enemyNum, life);
}

Aircraft_Enemy::~Aircraft_Enemy()
{
	delete [] enemy;
	enemy = NULL;
}

void Aircraft_Enemy::initAircraft(int eGenerateSpeed, int eMoveSpeed, int enemyNum, int life)
{
	enemyGenerateSpeed = eGenerateSpeed;
	enemyMoveSpeed = eMoveSpeed;
	enemyNumber = enemyNum;
	enemyLife = life;


	enemyMoveSpeedCnt = 0;
	enemyNumberCnt= 0;
	enemyGenerateSpeedCnt = 0;

	enemy = new Aircraft_Attr[enemyNumber];
	for (int i = 0; i < enemyNumber; ++i)
		setAttribute(i, 0, 0, enemyLife);
}

void Aircraft_Enemy::generateBullet()
{
	for (int i = 0; i < getEnemyNumberCnt(); ++i) {
		if (rand() % 20 == 0 && enemy[i].x < getBoardLenth()-1) {
			bulletGenerate(enemy[i],BULLTE_DOWN);
		}
	}
}

void Aircraft_Enemy::generateAircraft()
{
	if (enemyGenerateSpeedCnt++ == enemyGenerateSpeed) {
		if (enemyNumberCnt < enemyNumber)
			singleEnemyGenerate(enemy[enemyNumberCnt++]);
	}

}

void Aircraft_Enemy::singleEnemyGenerate(Aircraft_Attr &enemy)
{
	enemy.x = 0;
	enemy.y = rand() % getBoardWidth();
	enemy.life = enemyLife;
	enemyGenerateSpeedCnt = 0;
}


void Aircraft_Enemy::moveAircraft()
{
	if (enemyMoveSpeedCnt++ == enemyMoveSpeed) {
		for (int i = 0; i < enemyNumber; ++i) {
			enemy[i].x++;
		}
		enemyMoveSpeedCnt = 0;
	}
}

void Aircraft_Enemy::moveBullet()
{
	setBulletMoveSpeedCnt(1);
	if (getBulletMoveSpeedCnt() == getBulletMoveSpeed()) {
		for (int i = getBoardLenth()-1; i >= 0; --i) {
			for (int j = getBoardWidth()-1; j >= 0; --j) {
				if (getBullet()[i][j] == 1) {
					setBullet(i, j, 0);
					if (i+1 >= getBoardLenth()) continue;
					setBullet(i+1, j, 1);
				}
			}
		}
		setBulletMoveSpeedCnt(0);
	}
}

void Aircraft_Enemy::drawAircraft()
{
	init_pair(ENEMY, COLOR_RED, COLOR_BLACK);
	for (int i = 0; i < enemyNumberCnt; ++i) {
		attron(COLOR_PAIR(ENEMY));
		mvprintw(enemy[i].x, enemy[i].y, "@");
		attroff(COLOR_PAIR(ENEMY));
	}
}

void Aircraft_Enemy::drawBullet()
{

	init_pair(ENEMY_BULLTE, COLOR_RED, COLOR_BLACK);
	for (int i = getBoardLenth()-1; i >= 0; --i) {
		for (int j = getBoardWidth()-1; j >= 0; --j) {
			if (getBullet()[i][j] == 1) {
				attron(COLOR_PAIR(ENEMY_BULLTE));
				mvprintw(i, j,"\"");
				attroff(COLOR_PAIR(ENEMY_BULLTE));
			}
		}
	}
}

int Aircraft_Enemy::getEnemyNumberCnt()
{
	return enemyNumberCnt;
}

int Aircraft_Enemy::getEnemyNumber()
{
	return enemyNumber;
}

Aircraft_Attr& Aircraft_Enemy::getAttribute(int n)
{
	return enemy[n];
}

void Aircraft_Enemy::setAttribute(int n, int x, int y, int life)
{
	getAttribute(n).x = x;
	getAttribute(n).y = y;
	getAttribute(n).life = life;
}
