# 一个关于空战的小游戏
参考知乎上[一篇文章](https://zhuanlan.zhihu.com/p/24798125)，在linux下编写而成，主要应用了curses.h和c++面向对象的基本知识  
角色为A,敌机为@，子弹为.  
~~wasd~~上下左右控制方向  
' '控制是否发射子弹  
p为暂停，及菜单  
u为发射霰弹  
## 实现的功能
1.控制移动  
2.发射子弹   
3.敌人随机出现  
4.敌人随机射击  
4.难易程度的控制(目前还未实现，主要是要大量测试，找到合适的点)  
5.敌人，子弹，产生以及移动速度的控制(目前需要在代码中更改)  
6.游戏主体为一个无限循环,为了实现在控制air飞行时子弹及敌机的移动，定义了一系列的speed和speedCnt变量  
当speedCnt自增达到speed时，子弹发射，产生，或者移动。  
7.还未实现敌人的子弹对自己造成伤害，不合理的敌人和子弹移动速度  
## 注意！！
**用更多的面向对象的知识重写了此游戏，两个版本都在此仓库中
下面的关有函数的介绍还未修改**
## 游戏主体
### 类
```c++
class Tool
class AirBattle
struct Aircraft { };
```
#### Aircraft
结构体，储存了飞机的坐标及血量
#### Tool
```c++
static bool kbhit();//linux 上没有像window上一样的kbhit函数
//找了很多替代函数发现只有这个比较好用
template<typename T> static void delay(T timer);
//自己写了一个简单的延时函数，主要通过clock()和while()实现
```
#### AirBattle
##### 关于buttle的函数
```c++
void initBullet();//初始化子弹，包括force,各种speed等
void bulletMove();//子弹的移动
void singleBulletGenerate(int);//单个子弹的产生，可以控制宽度及buttleForce
void bulletGenerate();//有间隔的产生子弹,从而控制子弹产生速度
void bulletDraw();//打印子弹，总子弹存放在一个二维数组中

```
##### 关于enemy的函数
与buttle定义非常相似，就不多说了
```c++
void initEnemy();
void singleEnemyGenerate(Aircraft &);
void enemyGenerate();
void enemyMove();
void aircraftDraw();// 打印玩家及敌机
```
##### 关于aircraft的函数
```c++
bool airCrash();
void aircraftMove(int direction);//移动
```
##### 其他函数
```c++
void masterMenu();//菜单
bool insideMenu();
void help();
bool gameOver();//内含统计杀敌数，及霰弹数
void backgrandDraw();//打印背景
void drawEverything();//整合打印函数
void playGame();//整合一些函数
```

