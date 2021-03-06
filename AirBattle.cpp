#include <curses.h>
#include <cstdlib>
#include <ctime>
#include "AirBattle.h"
#include "Tool.h"

AirBattle::AirBattle()
{
	srand(time(0));
	initscr();
	initGame();
	initColor();
	noecho();
	curs_set(0);
	cbreak();
	keypad(stdscr, true);
}

AirBattle::~AirBattle()
{
	noecho();
	nocbreak();
	for (int i = 0; i < boardLenth; ++i) {
		delete [] aircraftBullet[i];
		delete [] enemyBullet[i];
	}
	delete [] aircraftBullet;
	delete [] enemyBullet;
	delete [] enemy;
	aircraftBullet = NULL;
	enemyBullet = NULL;
	enemy = NULL;
	endwin();
}

void AirBattle::initColor()
{
	start_color();
	init_pair(AIR_BUTTLE, COLOR_WHITE, COLOR_BLACK);
	init_pair(ENEMY_BUTTLE, COLOR_RED, COLOR_BLACK);
	init_pair(ENEMY, COLOR_RED, COLOR_BLACK);
	init_pair(AIRCRAFT, COLOR_CYAN, COLOR_BLACK);
	init_pair(BOUNDARY, COLOR_WHITE, COLOR_BLACK);
	init_pair(TEXT, COLOR_WHITE, COLOR_BLACK);
}

void AirBattle::initGame()
{
	initBoard();
	initEnemy();
	initBullet();
	initAircraft();
}

void AirBattle::initBoard()
{
	boardLenth = 30;
	boardWidth = 40;
}

void AirBattle::initAircraft()
 {
	// aircraft.model[1][3] = 1;
	// for (int i = 1; i < 6; ++i)
	// 	aircraft.model[2][i] = 1;
	aircraft.life = 3;
	totalKillCount = 0;
	aircraft.h = boardLenth-1;
	aircraft.v = boardWidth/2;

	aircraftBullet = new int* [boardLenth]();
	for (int i = 0; i < boardLenth; ++i)
		aircraftBullet[i] = new int [boardWidth]();

}

void AirBattle::initBullet()
{
	initAircraftBullet();
	initEnemyBullet();
}

void AirBattle::initEnemyBullet()
{
	enemyBulletMoveSpeed = enemyMoveSpeed-700;
	enemyBulletMoveSpeedCnt = 0;
	enemyBulletGenerateSpeed = enemyMoveSpeed-500;
	enemyBulletGenerateSpeedCnt = 0;
}
void AirBattle::initAircraftBullet()
{
	shrapnelReady = 2;
	aircraftBulletForce = 10;
	aircraftBulletForceCnt = 0;
	aircraftBulletGenerateSpeed= 1000;
	aircraftBulletGenerateSpeedCnt = 0;
	aircraftBulletMoveSpeed = 1000;
	aircraftBulletMoveSpeedCnt = 0;
}

void AirBattle::initEnemy()
{
	enemyLife = 3;
	enemyNumber = 20;
	enemyNumberCnt = 0;
	enemy = new Aircraft [enemyNumber];
	for (int i = 0; i < enemyNumber; ++i)
		enemy[i].h = enemy[i].v = 0;
	enemyMoveSpeed = 3000;
	enemyGenerateSpeed = 6000;
	enemyMoveSpeedCnt = 0;
	enemyGenerateSpeedCnt = 0;

	enemyBullet = new int* [boardLenth]();
	for (int i = 0; i < boardLenth; ++i)
		enemyBullet[i] = new int [boardWidth]();
}

void AirBattle::singleEnemyGenerate(Aircraft &enemy)
{
	enemy.v = rand() % boardWidth;
	enemy.h = 0;
	enemy.life = enemyLife;
	enemyGenerateSpeedCnt = 0;
}

void AirBattle::enemyGenerate()
{
	if (enemyGenerateSpeedCnt++ == enemyGenerateSpeed) {
		if (enemyNumberCnt < enemyNumber)
			singleEnemyGenerate(enemy[enemyNumberCnt++]);
	}
}

void AirBattle::enemyMove()
{
	 if (enemyMoveSpeedCnt++ == enemyMoveSpeed) {
		 for (int i = 0; i < enemyNumber; ++i) {
			 enemy[i].h++;
		 }
		 enemyMoveSpeedCnt = 0;
	 }
}

void AirBattle::singleBulletGenerate(int force, int **bullet, Aircraft location, int direc)
{
	for (int i = 0; i < force; ++i) {
		bullet[location.h+direc][location.v+i] = 1;
		bullet[location.h+direc][location.v] = 1;
		bullet[location.h+direc][location.v-i] = 1;
	}
}

void AirBattle::bulletGenerate(int bulletSpeed, int &bulletSpeedCnt, int **bullet, Aircraft location,int direc)
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
	if (bulletSpeedCnt++ == bulletSpeed) {
		singleBulletGenerate(force,bullet,location, direc);
		bulletSpeedCnt = 0;
	}
}

void AirBattle::enemyBulletGenerate()
{
	for (int i = 0; i < enemyNumberCnt; ++i) {
		if (rand() % 10 == 0 && enemy[i].h < boardLenth-1) {
			bulletGenerate(enemyBulletGenerateSpeed, enemyBulletGenerateSpeedCnt, enemyBullet, enemy[i], BULLET_DOWN);
		}
	}
}

void AirBattle::aircraftBulletMove()
{
	if (aircraftBulletMoveSpeedCnt++ == aircraftBulletMoveSpeed) {
		for (int i = 0; i < boardLenth; ++i) { // 本机子弹移动
			for (int j = 0; j < boardWidth; ++j) {
				if (aircraftBullet[i][j] == 1) {
					aircraftBullet[i][j] = 0;
					if (i-1 <= 0) continue;
					aircraftBullet[i-1][j] = 1;
				}
			}
		}
		aircraftBulletMoveSpeedCnt = 0;
	}
}

void AirBattle::enemyBulletMove()
{
	if (enemyBulletMoveSpeedCnt++ == enemyBulletMoveSpeed) {
		for (int i = boardLenth-1; i >= 0; --i) {
			for (int j = boardWidth-1; j >= 0; --j) {
				if (enemyBullet[i][j] == 1) {
					enemyBullet[i][j] = 0;
					if (i+1 >= boardLenth) continue;
					enemyBullet[i+1][j] = 1;
				}
			}
		}
		enemyBulletMoveSpeedCnt = 0;
	}

}

void AirBattle::bulletMove()
{
	enemyBulletMove();
	aircraftBulletMove();
}

void AirBattle::backgrandDraw()
{
	for (int i = 0; i < boardLenth; ++i) {
		attron(COLOR_PAIR(BOUNDARY));
		mvprintw(i, boardWidth, "|");
		attroff(COLOR_PAIR(BOUNDARY));
	}
	for (int j = 0; j < boardWidth; ++j) {
		attron(COLOR_PAIR(BOUNDARY));
		mvprintw(boardLenth, j, "^");
		attroff(COLOR_PAIR(BOUNDARY));
	}
	addch('\n');
}

void AirBattle:: bulletDraw(int **bullet,const int COLOR)
{
	for (int i = 0; i < boardLenth; ++i) {
		for (int j = 0; j < boardWidth; ++j) {
			if (bullet[i][j] == 1) {
				attron(COLOR_PAIR(COLOR));
				mvprintw(i, j,"\"");
				attroff(COLOR_PAIR(COLOR));
			}
		}
	}
}

void AirBattle::drawEverything()
{
	erase();
	backgrandDraw();
	bulletDraw(enemyBullet,ENEMY_BUTTLE);
	bulletDraw(aircraftBullet,AIR_BUTTLE);
	aircraftDraw();
	refresh();
}

void AirBattle::aircraftDraw()
{

	for (int i = 0; i < enemyNumberCnt; ++i) {
		attron(COLOR_PAIR(ENEMY));
		mvprintw(enemy[i].h, enemy[i].v, "@");
		attroff(COLOR_PAIR(ENEMY));
	}

	attron(COLOR_PAIR(AIRCRAFT));
	mvaddch(aircraft.h-1, aircraft.v,    'A');
	mvprintw(aircraft.h, aircraft.v-2, "/WMW\\");
	//mvprintw(aircraft.h, aircraft.v, "G");
	attron(COLOR_PAIR(AIRCRAFT));
	mvprintw(boardLenth+1, 0 , "Life:%d     Kill:%d    Shrapnel:%d   (%d,%d)", aircraft.life, totalKillCount, shrapnelReady, aircraft.h, aircraft.v);
	mvprintw(boardLenth+2, 0 , "EnemyNumber:%d ,EnemyNumberCnt:%d", enemyNumber, enemyNumberCnt);
}

void AirBattle::aircraftMove(int direction)
{
	switch(direction) {
	case KEY_UP:
		aircraft.h--;
		break;
	case KEY_DOWN:
		aircraft.h++;
		break;
	case KEY_LEFT:
		aircraft.v--;
		break;
	case KEY_RIGHT:
		aircraft.v++;
		break;
	}
}

bool AirBattle::airCrash()
{
	for (int i = 0; i < enemyNumberCnt; ++i) {
		if (enemy[i].h >= boardLenth)// 如果敌机超出边界则，重新生成
			singleEnemyGenerate(enemy[i]);

		if ((enemy[i].v == aircraft.v && enemy[i].h == aircraft.h-1) ||
			(enemy[i].v == aircraft.v-2 && enemy[i].h == aircraft.h) ||
			(enemy[i].v == aircraft.v-1 && enemy[i].h == aircraft.h) ||
			(enemy[i].v == aircraft.v-0 && enemy[i].h == aircraft.h) ||
			(enemy[i].v == aircraft.v+1 && enemy[i].h == aircraft.h) ||
			(enemy[i].v == aircraft.v+2 && enemy[i].h == aircraft.h)) { // 判断是否与飞机任意一部位相撞
			singleEnemyGenerate(enemy[i]);
			totalKillCount++;
			if (gameOver()) return 1;// 如果生命为零则结束游戏
		}

		for (int j = 0; j < boardLenth; ++j)
			for (int k = 0; k < boardWidth; ++k)
				if (aircraftBullet[j][k] == 1)
					if (enemy[i].h == j && enemy[i].v == k) { //如果敌机与子弹重合
						aircraftBullet[j][k] = 0;
						if (--enemy[i].life <= 0) { // 如果击中，敌机减血
							singleEnemyGenerate(enemy[i]);
							totalKillCount++;// 杀敌数增加
						}
						if (totalKillCount % 100 == 99)
							shrapnelReady++;// 如果杀敌数超过一百，增加霰弹枪数量
					}
	}
	return 0;
}

bool AirBattle::gameOver()
{
	if (--aircraft.life != 0) {// 如果飞机被击中，或撞击，则重设位置，生命减一
		aircraft.h = boardLenth-1;
		aircraft.v = boardWidth/2;
	} else {
		//erase();
		mvprintw(boardLenth/2-1, boardWidth/2-6, "Game over!");
		mvprintw(boardLenth/2, boardWidth/2-14, "Press any key to continue...");
		getch();
		return 1;
	}
	return 0;
}

void AirBattle::playGame()
{
	int action, fire = -1;
	while (1) {
		enemyGenerate();
		enemyMove();

		if (Tool::kbhit()) {
			action = getch();
			aircraftMove(action);
			if (action == 'p') if(insideMenu()) return;
			if (action == ' ') fire = ~fire;
			if (action == 'u' && shrapnelReady > 0) {
				singleBulletGenerate(aircraftBulletForce,aircraftBullet,aircraft,BULLET_UP);
				shrapnelReady--;
			}
		}
		if (fire) bulletGenerate(aircraftBulletMoveSpeed,aircraftBulletMoveSpeedCnt,aircraftBullet,aircraft,BULLET_UP);

		enemyBulletGenerate();
		bulletMove();
		if (airCrash()) return;
		drawEverything();
	}
}

void AirBattle::masterMenu()
{
	int s;
	while (1) {
		erase();
		mvprintw(boardLenth/2-4, boardWidth/2-6, "Air Battle");
		mvprintw(boardLenth/2-3, boardWidth/2-6, "1.Play");
		mvprintw(boardLenth/2-2, boardWidth/2-6, "2.Level:%s", "Easy");
		mvprintw(boardLenth/2-1, boardWidth/2-6, "3.Help");
		mvprintw(boardLenth/2-0, boardWidth/2-6, "4.Exit");
		backgrandDraw();
		refresh();
		s = getch();
		switch(s) {
		case '1': initGame(); playGame(); break;
		case '2':  break;
		case '3': help(); break;
		case '4': exit(0); break;
		}
	}

}

bool AirBattle::insideMenu()
{
	int s;
	mvprintw(boardLenth/2-4, boardWidth/2-6, "1.Restart");
	mvprintw(boardLenth/2-3, boardWidth/2-6, "2.Continue");
	mvprintw(boardLenth/2-2, boardWidth/2-6, "3.Master menu");
	mvprintw(boardLenth/2-1, boardWidth/2-6, "4.Help");
	mvprintw(boardLenth/2-0, boardWidth/2-6, "5.Exit");
	backgrandDraw();
	refresh();
	s = getch();
	switch(s) {
	case '1': initGame(); playGame(); break;
	case '2': playGame(); break;
	case '3': return 1;//masterMenu(); break;
	case '4': help(); break;
	case '5': exit(0); break;
	}
	return 0;
}

void AirBattle::help()
{
	erase();
	attron(COLOR_PAIR(TEXT));
	printw(
		"Operations Guide:\n"
		"  Keyboard control,\n"
		"  Direction key control movement,\n"
		"  Blank key control shooting,\n"
		"  Press p to suspend game and get into\n"
		"  memu.\n"
		"  Press u to use shrapnel.\n"
		"  If you killing more than 100 enemies \n"
		"  your shrapnel will add one.\n"
		"  ...\n"
		"  Press any key to countinue...\n");
	attroff(COLOR_PAIR(TEXT));
	backgrandDraw();
	refresh();
	getch();
}
