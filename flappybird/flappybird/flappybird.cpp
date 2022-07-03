#include<stdio.h>

#include<stdlib.h>

#include <conio.h>

#include<time.h>

#include<graphics.h>

IMAGE background;//背景图

IMAGE myBird[2];//鸟图 

IMAGE up[2];//朝上的柱子图

IMAGE down[2];//朝下的柱子图

IMAGE end[2];//游戏结束的动画图

IMAGE background2;

IMAGE digit[10];


//初始化柱子


struct pillar
{
	int x=288;
	
	//贴柱子的起使坐标

	int y=0;
	
	//贴柱子的起使坐标


	int height;
	
	//柱子的高度
};


//初始化小鸟



struct bird
{
	int x;

	//小鸟起始横坐标

	int y;

	//小鸟起始纵坐标


	int speed;
	
	//小鸟下坠速度

}flybird = { 120,300,50 };


//加载资源

//加载图片和掩码图


void loadResource()
{

	//加载图片资源


//背景图、小鸟图、游戏结束图、柱子图（上半部分和下半部分）


//图片有背景，显示不美观


//需要加载掩码图遮盖

//
	loadimage(myBird, "bird.bmp", 48, 48);

	loadimage(myBird + 1, "birdy.bmp", 48, 48);

	//将小鸟图和小鸟掩码图放置于同一个数组


	loadimage(digit, "0.png", 0, 0);

	loadimage(digit + 1, "1.png", 0, 0);

	loadimage(digit + 2, "2.png", 0, 0);

	loadimage(digit + 3, "3.png", 0, 0);

	loadimage(digit + 4, "4.png", 0, 0);

	loadimage(digit + 5, "5.png", 0, 0);

	loadimage(digit + 6, "6.png", 0, 0);

	loadimage(digit + 7, "7.png", 0, 0);

	loadimage(digit + 8, "8.png", 0, 0);

	loadimage(digit + 9, "9.png", 0, 0);

	//以下end图 up down 图同理

	loadimage(&background2, "background2.bmp");

	loadimage(&background, "background.bmp");

	loadimage(end, "end.bmp");


	loadimage(end + 1, "endy.bmp");

	loadimage(down, "down.bmp");


	loadimage(down + 1, "downy.bmp");

	loadimage(up, "up.bmp");


	loadimage(up + 1, "upy.bmp");

}



//绘制柱子


void drawPillar(struct pillar mypillar)
	{


	//截取 512-（320-mypillar.height）



	//图片除去底部泥土像素为512、柱子长度像素为320




		putimage(mypillar.x, 0,/*柱子贴的位置*/ 52/*柱子宽52*/, mypillar.height/*柱子的高*/, down + 1/*贴的是哪个图片*/, 0, 320 - mypillar.height/*从图片的哪个位置开始截取*/, SRCAND);


		//第一对是贴柱子的位置（即柱子左上角的坐标）


		//第二对是截取图片的尺寸，mypillar.height之后会随机生成


		//第三个是选择的图片


		//第四对是截取图片的部分


		putimage(mypillar.x, 0, 52, mypillar.height, down, 0, 320 - mypillar.height, SRCPAINT);
		putimage(mypillar.x, 192 + mypillar.height, 52, 320 - mypillar.height, up + 1, 0, 0, SRCAND);
		putimage(mypillar.x, 192 + mypillar.height, 52, 320 -mypillar.height, up, 0, 0, SRCPAINT);

	}


//绘制小鸟

void drawBird(int x, int y)
{
	putimage(x, y, myBird + 1, SRCAND);
	putimage(x, y, myBird, SRCPAINT);
}



//设置读取用户键盘输入的函数



void KeyDown()
{
	char userkey = _getch();//不可见字符键盘输入
	switch (userkey)
	{
	case 32:
		flybird.y -= flybird.speed;
		break;
	default:
		break;
	}
}


//游戏开始动画


int gameBeginAction()
{
	int x = 50, y = 608;
	putimage(0, 0, &background2);
	char userkey = _getch();//不可见字符键盘输入
	switch (userkey)
	{
	case 32:
		return 1;
		break;
	default:
			return 0;
		break;
	}
}


//游戏结束动画


void gameOverAction()
{
	int x = 50, y = 240;
	    putimage(0, 0, &background);
		putimage(x, y, end + 1, SRCAND);
		putimage(x, y, end, SRCPAINT);
}



//初始化柱子


void initPillar(struct pillar arrayPillar[],int i)
{
	arrayPillar[i].height = rand() % 100 + 50;
	arrayPillar[i].x = 288;
	arrayPillar[i].y = 0;
}


//判定撞到地板（可增加撞到天花板）



int hitFloor()
{
	if (flybird.y >= 464)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


//判定撞到柱子

//核心代码


int hitPillar(struct pillar arrayPillar[])
{
	for (int i = 0; i < 3; i++)
	{
		if ((flybird.x>=arrayPillar[i].x)&&(flybird.y<=arrayPillar[i].height))
		{
			return 1;
		}
		if ((flybird.x >= arrayPillar[i].x) && (flybird.y+20 >= 192+arrayPillar[i].height))
		{
			return 1;
		}
	}
	return 0;
}


//积分系统


int score = 0;



//计分器
void Score(struct pillar arrayPillar[])
{
	int x1 = 145, y1 = 3;
	int x2 = 100, y2 = 3;
	int x3 = 50, y3 = 3;
	for (int i = 0; i < 3; i++)
	{
		if ((flybird.x >=arrayPillar[i].x)&& (flybird.x <= arrayPillar[i].x+52))
		{
			score += 1;
		}
		{
			score += 1;
		}
	}
}


//游戏结束时显示分数


void showscore( )
{

	int x1 = 145, y1 = 200;


	int x2 = 100, y2 = 200;


	int x3 = 50, y3 = 200;

	switch (score % 10)
	{
	case 0:
		putimage(x1, y1, digit, SRCPAINT);
		break;

	case 1:
		putimage(x1, y1, digit + 1, SRCPAINT);
		break;

	case 2:
		putimage(x1, y1, digit + 2, SRCPAINT);
		break;

	case 3:
		putimage(x1, y1, digit + 3, SRCPAINT);
		break;

	case 4:
		putimage(x1, y1, digit + 4, SRCPAINT);
		break;

	case 5:
		putimage(x1, y1, digit + 5, SRCPAINT);
		break;

	case 6:
		putimage(x1, y1, digit + 6, SRCPAINT);
		break;

	case 7:
		putimage(x1, y1, digit + 7, SRCPAINT);
		break;

	case 8:
		putimage(x1, y1, digit + 8, SRCPAINT);
		break;


	case 9:
		putimage(x1, y1, digit + 9, SRCPAINT);
		break;

	}


	switch (score % 100)
	{
	case 0:
		putimage(x1, y1, digit, SRCPAINT);
		break;

	case 1:
		putimage(x1, y1, digit + 1, SRCPAINT);
		break;

	case 2:
		putimage(x1, y1, digit + 2, SRCPAINT);
		break;

	case 3:
		putimage(x1, y1, digit + 3, SRCPAINT);
		break;

	case 4:
		putimage(x1, y1, digit + 4, SRCPAINT);
		break;

	case 5:
		putimage(x1, y1, digit + 5, SRCPAINT);
		break;

	case 6:
		putimage(x1, y1, digit + 6, SRCPAINT);
		break;

	case 7:
		putimage(x1, y1, digit + 7, SRCPAINT);
		break;

	case 8:
		putimage(x1, y1, digit + 8, SRCPAINT);
		break;

	case 9:
		putimage(x1, y1, digit + 9, SRCPAINT);
		break;
	}


	Sleep(3000);


}


int main()
{


sss:
	
	clock_t  starttime, endtime;


	loadResource();

	//绘制一个288*608像素的对话框


	initgraph(288, 608);

	//声明一个长度为三的结构数组


	struct pillar arrayPillar[3]; 



	//初始化柱子数组


	for (int i = 0; i < 3; i++)
	{
		initPillar(arrayPillar, i);
		arrayPillar[i].x = 288 + i * (rand() % 200);
	}


	//游戏主体内容

	
		if (gameBeginAction())
		{

			while (1)//  while(1)：不断循环循环体
			{
				
			

				starttime = clock();

				//加载背景图片

				putimage(0, 0, &background);

				//画鸟

				drawBird(flybird.x, flybird.y);
	

				//小鸟默认下降的速度


				flybird.y += 5;


				for (int i = 0; i < 3; i++)
				{

					arrayPillar[i].x -= 0.2;

					//判定柱子是否越出边界 如果越出生成新的一组柱子


					if (arrayPillar[i].x < -25)
						
					
					{

						initPillar(arrayPillar, i);

					}
				}


				for (int i = 0; i < 3; i++)
				{
					drawPillar(arrayPillar[i]);
					arrayPillar[i].x -= 5;
				}
			
				//读取用户键盘输入

				//空格键操作


				if (_kbhit())
				{
					KeyDown();
				}

				//判定小鸟是否撞击 
			
				if (hitFloor() || hitPillar(arrayPillar))
				{

					gameOverAction();

					endtime = clock();

					showscore();

					goto sss;

				}


				//显示分数


				Score(arrayPillar);


				Sleep(20);

			

			}

		

		}
	getchar();
	closegraph();
	return 0;
}


