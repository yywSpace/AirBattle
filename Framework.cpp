#include <curses.h>
#include <cstdlib>
#include <vector>
#include "Framework.h"
#include "Tool.h"

Framework::Framework()
	:user(30,40,1,1000,1000,3,2), enemy(30,40,1,1000,1000,1000,2000,20,2)
{
	totalKillCount = 0;
	initscr();
	curs_set(0);
	start_color();
	cbreak();
}

void Framework::masterMenu()
{
	int s;
	while (1) {
		erase();
		mvprintw(getBoardLenth()/2-4, getBoardWidth()/2-6, "Air Battle");
		mvprintw(getBoardLenth()/2-3, getBoardWidth()/2-6, "1.Play");
		mvprintw(getBoardLenth()/2-2, getBoardWidth()/2-6, "2.Level:%s", "Easy");
		mvprintw(getBoardLenth()/2-1, getBoardWidth()/2-6, "3.Help");
		mvprintw(getBoardLenth()/2-0, getBoardWidth()/2-6, "4.Exit");
		drawBackgrand();
		refresh();
		s = getch();
		switch(s) {
		case '1': playGame(); break;
		case '2':  break;
		case '3': help(); break;
		case '4': exit(0); break;
		}
	}
}

bool Framework::insideMenu()
{
	int s;
	mvprintw(getBoardLenth()/2-4, getBoardWidth()/2-6, "1.Restart");
	mvprintw(getBoardLenth()/2-3, getBoardWidth()/2-6, "2.Master menu");
	mvprintw(getBoardLenth()/2-2, getBoardWidth()/2-6, "3.Help");
	mvprintw(getBoardLenth()/2-1, getBoardWidth()/2-6, "4.Exit");
	mvprintw(getBoardLenth()/2-0, getBoardWidth()/2-6, " ...");
	mvprintw(getBoardLenth()/2+1, getBoardWidth()/2-6, " Press any key to countinue...");
	drawBackgrand();
	refresh();
	s = getch();
	switch(s) {
	case '1': playGame(); break;
	case '2': return 1;//masterMenu(); break;
	case '3': help(); break;
	case '4': exit(0); break;
	}
	return 0;


}

void Framework::help()
{

	init_pair(TEXT, COLOR_WHITE, COLOR_BLACK);
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
	drawBackgrand();
	refresh();
	getch();
}

int Framework::getBoardLenth()
{
	return user.getBoardLenth();
}

int Framework::getBoardWidth()
{
	return user.getBoardWidth();
}

void Framework:: drawBackgrand()
{
	init_pair(BOUNDARY, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(BOUNDARY));
	for (int i = 0; i < getBoardLenth(); ++i) {
		mvprintw(i, getBoardWidth(), "|");
	}
	for (int j = 0; j < getBoardWidth(); ++j) {
		mvprintw(getBoardLenth(), j, "^");
	}
	attroff(COLOR_PAIR(BOUNDARY));
	addch('\n');
}
void Framework::drawInterface()
{
	mvprintw(getBoardLenth()+1, 0 , "Life:%d     Kill:%d    Shrapnel:%d   (%d,%d)", user.getAttribute().life,
			 totalKillCount, user.getShrapnel(), user.getAttribute().x, user.getAttribute().y);
}

bool Framework::gameOver()
{
	if (--user.getAttribute().life != 0) {// 如果飞机被击中，或撞击，则重设位置，生命减一
		user.setAttribute(getBoardLenth()-1, getBoardWidth()/2, user.getAttribute().life);
	} else {
		//erase();
		mvprintw(getBoardLenth()/2-1, getBoardLenth()/2-1, "Game over!");
		mvprintw(getBoardLenth()/2, getBoardWidth()/2-14, "Press any key to continue...");
		getch();
		return 1;
	}
	return 0;
}

bool Framework::airCrash()
{
	for (int i = 0; i < enemy.getEnemyNumberCnt(); ++i) {
		if (enemy.getAttribute(i).x >= getBoardLenth())// 如果敌机超出边界则，重新生成
			enemy.singleEnemyGenerate(enemy.getAttribute(i));

		if ((enemy.getAttribute(i).y == user.getAttribute().y && enemy.getAttribute(i).x == user.getAttribute().x-1) ||
			(enemy.getAttribute(i).y == user.getAttribute().y-2 && enemy.getAttribute(i).x == user.getAttribute().x) ||
			(enemy.getAttribute(i).y == user.getAttribute().y-1 && enemy.getAttribute(i).x == user.getAttribute().x) ||
			(enemy.getAttribute(i).y == user.getAttribute().y-0 && enemy.getAttribute(i).x == user.getAttribute().x) ||
			(enemy.getAttribute(i).y == user.getAttribute().y+1 && enemy.getAttribute(i).x == user.getAttribute().x) ||
			(enemy.getAttribute(i).y == user.getAttribute().y+2 && enemy.getAttribute(i).x == user.getAttribute().x)) { // 判断是否与飞机任意一部位相撞
			enemy.singleEnemyGenerate(enemy.getAttribute(i));
			totalKillCount++;
			if (gameOver()) return 1;// 如果生命为零则结束游戏
		}

		for (int j = 0; j < getBoardLenth(); ++j)
			for (int k = 0; k < getBoardWidth(); ++k)
				if (user.getBullet()[j][k] == 1)
					if (enemy.getAttribute(i).x == j && enemy.getAttribute(i).y == k) { //如果敌机与子弹重合
						user.setBullet(j, k, 0);
						if (--enemy.getAttribute(i).life <= 0) { // 如果击中，敌机减血
							enemy.singleEnemyGenerate(enemy.getAttribute(i));
							totalKillCount++;// 杀敌数增加
						}
						if (totalKillCount % 100 == 99)
							user.setShrapnel(user.getShrapnel()+1); //如果杀敌数超过一百，增加霰弹枪数量
					}
	}
	return 0;

}

void Framework::drawEverything(std::vector <Aircraft *> air, int& fire)
{
	air[0] = &enemy;
	air[1] = &user;
	erase();
	for (int i = 0; i < 2; ++i) {
		if (fire) air[1]->generateBullet();
		air[0]->generateBullet();
		air[i]->moveBullet();
		air[i]->drawBullet();
		air[i]->drawAircraft();
	}
	drawBackgrand();
	drawInterface();
	refresh();
}

void Framework::playGame()
{
	int action, fire = -1;
	std::vector <Aircraft *> aircraft(2);

	while (1) {
		if (Tool::kbhit()) {
			action = getch();
			user.moveAircraft(action);
			if (action == 'p') if(insideMenu()) return;
			if (action == ' ') fire = ~fire;
			if (action == 'u' && user.getShrapnel()> 0) {
				user.singleBulletGenerate(user.getAttribute(), -1, 10);
				user.setShrapnel(user.getShrapnel()-1);
			}
		}
		enemy.generateAircraft();
		enemy.moveAircraft();
		drawEverything(aircraft, fire);
		if(airCrash()) return;
	}
	endwin();
}

