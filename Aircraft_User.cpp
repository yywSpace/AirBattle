#include <curses.h>
#include <cstdlib>
#include <ctime>

#include "Aircraft_User.h"

Aircraft_User::Aircraft_User(int lenth, int width, int force, int generateSpeed, int moveSpeed, int life, int shrapnel)
	:Aircraft(lenth, width, force, generateSpeed, moveSpeed)
{
	srand(time(NULL));
	setShrapnel(shrapnel);
	setAttribute(getBoardLenth()-1, getBoardWidth()/2, life);
}

void Aircraft_User::moveAircraft(int dirc)
{
	keypad(stdscr,true);
	switch(dirc) {
	case KEY_UP:
		getAttribute().x--;
		break;
	case KEY_DOWN:
		getAttribute().x++;
		break;
	case KEY_LEFT:
		getAttribute().y--;
		break;
	case KEY_RIGHT:
		getAttribute().y++;
		break;
	}
}

void Aircraft_User::moveBullet()
{
	setBulletMoveSpeedCnt(1);
	if (getBulletMoveSpeedCnt() == getBulletMoveSpeed()) {
		for (int i = 0; i < getBoardLenth(); ++i) { // 本机子弹移动
			for (int j = 0; j < getBoardWidth(); ++j) {
				if (getBullet()[i][j] == 1) {
					setBullet(i, j, 0);
					if (i-1 <= 0) continue;
					setBullet(i-1, j, 1);
				}
			}
		}
		setBulletMoveSpeedCnt(0);
	}
}

void Aircraft_User::generateBullet()
{
	Aircraft::bulletGenerate(aircraft, BULLET_UP);
}

void Aircraft_User::drawAircraft()
{
	init_pair(AIRCRAFT_COLOR, COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(AIRCRAFT_COLOR));
	mvaddch(aircraft.x-1, aircraft.y,    'A');
	mvprintw(aircraft.x, aircraft.y-2, "/WMW\\");
	attron(COLOR_PAIR(AIRCRAFT_COLOR));

}
void Aircraft_User::drawBullet()
{
	init_pair(BULLTE_COLOR, COLOR_WHITE, COLOR_BLACK);
	for (int i = 0; i < getBoardLenth(); ++i) {
		for (int j = 0; j < getBoardWidth(); ++j) {
			if (getBullet()[i][j] == 1) {
				attron(COLOR_PAIR(BULLTE_COLOR));
				mvprintw(i, j,"\"");
				attroff(COLOR_PAIR(BULLTE_COLOR));
			}
		}
	}
}

void Aircraft_User::setAttribute(int x, int y, int life)
{
	aircraft.x = x;
	aircraft.y = y;
	aircraft.life = life;
}

Aircraft_Attr& Aircraft_User::getAttribute()
{
	return aircraft;
}

int Aircraft_User::getShrapnel()
{
	return shrapnelReady;
}
void Aircraft_User::setShrapnel(int num)
{
	shrapnelReady = num;
}
