air : Aircraft.h Aircraft.cpp main.cpp Aircraft_User.h Aircraft_User.cpp Aircraft_Enemy.h\
		Aircraft_Enemy.cpp Framework.h Framework.cpp
	g++ -g -lcurses Aircraft.h Aircraft.cpp main.cpp Aircraft_User.h Aircraft_User.cpp \
		Aircraft_Enemy.cpp Aircraft_Enemy.h Framework.h Framework.cpp
