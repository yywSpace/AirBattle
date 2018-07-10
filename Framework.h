#ifndef FRAMEWORK_H
#define FRAMEWORK_H
#include <vector>
#include "Aircraft.h"
#include "Aircraft_User.h"
#include "Aircraft_Enemy.h"

class Framework
{
public:
	Framework();
	void playGame();
	void masterMenu();
	bool insideMenu();
	void help();
	bool gameOver();
	bool airCrash();

	void drawEverything(std::vector <Aircraft *> air, int& fire);
	void drawBackgrand();
	void drawInterface();
	int getBoardLenth();
	int getBoardWidth();

private:
	const int TEXT = 5;
	const int BOUNDARY = 6;
	int totalKillCount;
	Aircraft_User user;
	Aircraft_Enemy enemy;
};

#endif
