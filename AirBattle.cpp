#include <curses.h>
#include <cstdlib>
#include <ctime>
#include "AirBattle.h"
#include "../Tool/Tool.h"

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
	delete [] enemy;
	enemy = NULL;
	endwin();
}

void AirBattle::initColor()
{
	start_color();
	init_pair(AIR_BUTTLE, COLOR_WHITE, COLOR_BLACK);
	init_pair(AIR_ENEMY, COLOR_RED, COLOR_BLACK);
	init_pair(AIRCRAFT, COLOR_CYAN, COLOR_BLACK);
	init_pair(BOUNDARY, COLOR_WHITE, COLOR_BLACK);
	init_pair(TEXT, COLOR_GREEN, COLOR_BLACK);
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
	board = new int* [boardLenth]();
	for (int i = 0; i < boardLenth; ++i)
		board[i] = new int [boardWidth]();
}

void AirBattle::initAircraft()
{
	aircraft.life = 3;
	totalKillCount = 0;
	aircraft.h = boardLenth-1;
	aircraft.v = boardWidth/2;
}

void AirBattle::initBullet()
{
	shrapnelReady = 2;
	bulletForce = 10;
	bulletForceCnt = 0;
	bulletGenerateSpeed = 1000;
	bulletGenerateSpeedCnt = 0;
	bulletMoveSpeed = 1000;
	bulletMoveSpeedCnt = 0;
}

void AirBattle::initEnemy()
{
	enemyNumber = 30;
	enemyNumberCnt = 0;
	enemy = new Aircraft [enemyNumber];
	enemyMoveSpeed = 2500;
	enemyGenerateSpeed = 6000;
	enemyMoveSpeedCnt = 0;
	enemyGenerateSpeedCnt = 0;
}

void AirBattle::singleEnemyGenerate(Aircraft &enemy)
{
		enemy.v = rand() % boardWidth;
		enemy.h = 0;
		// int y = rand() % boardWidth;
		// board[0][y] = -2;
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
	// if (enemyMoveSpeedCnt++ == enemyMoveSpeed) {
	// 	for (int i = boardLenth-1; i >= 0; --i) {
	// 		for (int j = boardWidth-1; j >= 0; --j) {
	// 			if (board[i][j] == -2) {
	// 				board[i][j] = 0;
	// 				if (i+1 >= boardLenth) continue;
	// 				board[i+1][j] = -2;
	// 			}
	// 		}
	// 	}
	// 	enemyMoveSpeedCnt = 0;
	// }
}

void AirBattle::singleBulletGenerate(int force)
{
	for (int i = 0; i < force; ++i) {
		board[aircraft.h][aircraft.v+i] = 1;
		board[aircraft.h][aircraft.v] = 1;
		board[aircraft.h][aircraft.v-i] = 1;
	}

}

void AirBattle::bulletGenerate()
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
	if (bulletGenerateSpeedCnt++ == bulletGenerateSpeed) {
		singleBulletGenerate(force);
		bulletGenerateSpeedCnt = 0;
	}
}

void AirBattle::bulletMove()
{
	if (bulletMoveSpeedCnt++ == bulletMoveSpeed) {
		for (int i = 0; i < boardLenth; ++i) {
			for (int j = 0; j < boardWidth; ++j) {
				if (board[i][j] == 1) {
					board[i][j] = 0;
					if (i-1 <= 0) continue;
					board[i-1][j] = 1;
				}
			}
		}
		bulletMoveSpeedCnt = 0;
	}
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

void AirBattle:: bulletDraw()
{
	for (int i = 0; i < boardLenth; ++i) {
		for (int j = 0; j < boardWidth; ++j) {
			if (board[i][j] == 1) {
				attron(COLOR_PAIR(AIR_BUTTLE));
				mvprintw(i, j,"\"");
				attroff(COLOR_PAIR(AIR_BUTTLE));
			}
		}
	}
}

void AirBattle::drawEverything()
{
	erase();
	backgrandDraw();
	bulletDraw();
	aircraftDraw();
	refresh();
}

void AirBattle::aircraftDraw()
{
	for (int i = 0; i < enemyNumberCnt; ++i) {
		attron(COLOR_PAIR(AIR_ENEMY));
		mvprintw(enemy[i].h, enemy[i].v, "@");
		attroff(COLOR_PAIR(AIR_ENEMY));
	}

	attron(COLOR_PAIR(AIRCRAFT));
	mvprintw(aircraft.h, aircraft.v, "G(%d,%d,%d)", aircraft.life, totalKillCount, shrapnelReady);
	attron(COLOR_PAIR(AIRCRAFT));
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
	for (int i = 0; i < enemyNumber; ++i) {
		if (enemy[i].h == aircraft.h && enemy[i].v == aircraft.v) {
			singleEnemyGenerate(enemy[i]);
			totalKillCount++;
			if (gameOver()) return 1;// 如果生命为零则结束游戏
		}
		else if (enemy[i].h >= boardLenth)
			singleEnemyGenerate(enemy[i]);

		for (int j = 0; j < boardLenth; ++j)
			for (int k = 0; k < boardWidth; ++k)
				if (board[j][k] == 1)
					if (enemy[i].h == j && enemy[i].v == k) { //如果敌机与子弹重合
						board[j][k] = 0;
						singleEnemyGenerate(enemy[i]);
						totalKillCount++;// 杀敌数增加
						if (totalKillCount % 100 == 0)
							shrapnelReady++;// 如果杀敌数超过一百，增加霰弹枪数量
					}
	}
	return 0;
}

bool AirBattle::gameOver()
{
	if (--aircraft.life != 0) {
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
				singleBulletGenerate(bulletForce);
				shrapnelReady--;
			}
		}
		if (fire) bulletGenerate();
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
