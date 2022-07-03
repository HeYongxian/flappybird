#include<stdio.h>

#include<stdlib.h>

#include <conio.h>

#include<time.h>

#include<graphics.h>

IMAGE background;//����ͼ

IMAGE myBird[2];//��ͼ 

IMAGE up[2];//���ϵ�����ͼ

IMAGE down[2];//���µ�����ͼ

IMAGE end[2];//��Ϸ�����Ķ���ͼ

IMAGE background2;

IMAGE digit[10];


//��ʼ������


struct pillar
{
	int x=288;
	
	//�����ӵ���ʹ����

	int y=0;
	
	//�����ӵ���ʹ����


	int height;
	
	//���ӵĸ߶�
};


//��ʼ��С��



struct bird
{
	int x;

	//С����ʼ������

	int y;

	//С����ʼ������


	int speed;
	
	//С����׹�ٶ�

}flybird = { 120,300,50 };


//������Դ

//����ͼƬ������ͼ


void loadResource()
{

	//����ͼƬ��Դ


//����ͼ��С��ͼ����Ϸ����ͼ������ͼ���ϰ벿�ֺ��°벿�֣�


//ͼƬ�б�������ʾ������


//��Ҫ��������ͼ�ڸ�

//
	loadimage(myBird, "bird.bmp", 48, 48);

	loadimage(myBird + 1, "birdy.bmp", 48, 48);

	//��С��ͼ��С������ͼ������ͬһ������


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

	//����endͼ up down ͼͬ��

	loadimage(&background2, "background2.bmp");

	loadimage(&background, "background.bmp");

	loadimage(end, "end.bmp");


	loadimage(end + 1, "endy.bmp");

	loadimage(down, "down.bmp");


	loadimage(down + 1, "downy.bmp");

	loadimage(up, "up.bmp");


	loadimage(up + 1, "upy.bmp");

}



//��������


void drawPillar(struct pillar mypillar)
	{


	//��ȡ 512-��320-mypillar.height��



	//ͼƬ��ȥ�ײ���������Ϊ512�����ӳ�������Ϊ320




		putimage(mypillar.x, 0,/*��������λ��*/ 52/*���ӿ�52*/, mypillar.height/*���ӵĸ�*/, down + 1/*�������ĸ�ͼƬ*/, 0, 320 - mypillar.height/*��ͼƬ���ĸ�λ�ÿ�ʼ��ȡ*/, SRCAND);


		//��һ���������ӵ�λ�ã����������Ͻǵ����꣩


		//�ڶ����ǽ�ȡͼƬ�ĳߴ磬mypillar.height֮����������


		//��������ѡ���ͼƬ


		//���Ķ��ǽ�ȡͼƬ�Ĳ���


		putimage(mypillar.x, 0, 52, mypillar.height, down, 0, 320 - mypillar.height, SRCPAINT);
		putimage(mypillar.x, 192 + mypillar.height, 52, 320 - mypillar.height, up + 1, 0, 0, SRCAND);
		putimage(mypillar.x, 192 + mypillar.height, 52, 320 -mypillar.height, up, 0, 0, SRCPAINT);

	}


//����С��

void drawBird(int x, int y)
{
	putimage(x, y, myBird + 1, SRCAND);
	putimage(x, y, myBird, SRCPAINT);
}



//���ö�ȡ�û���������ĺ���



void KeyDown()
{
	char userkey = _getch();//���ɼ��ַ���������
	switch (userkey)
	{
	case 32:
		flybird.y -= flybird.speed;
		break;
	default:
		break;
	}
}


//��Ϸ��ʼ����


int gameBeginAction()
{
	int x = 50, y = 608;
	putimage(0, 0, &background2);
	char userkey = _getch();//���ɼ��ַ���������
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


//��Ϸ��������


void gameOverAction()
{
	int x = 50, y = 240;
	    putimage(0, 0, &background);
		putimage(x, y, end + 1, SRCAND);
		putimage(x, y, end, SRCPAINT);
}



//��ʼ������


void initPillar(struct pillar arrayPillar[],int i)
{
	arrayPillar[i].height = rand() % 100 + 50;
	arrayPillar[i].x = 288;
	arrayPillar[i].y = 0;
}


//�ж�ײ���ذ壨������ײ���컨�壩



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


//�ж�ײ������

//���Ĵ���


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


//����ϵͳ


int score = 0;



//�Ʒ���
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


//��Ϸ����ʱ��ʾ����


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

	//����һ��288*608���صĶԻ���


	initgraph(288, 608);

	//����һ������Ϊ���Ľṹ����


	struct pillar arrayPillar[3]; 



	//��ʼ����������


	for (int i = 0; i < 3; i++)
	{
		initPillar(arrayPillar, i);
		arrayPillar[i].x = 288 + i * (rand() % 200);
	}


	//��Ϸ��������

	
		if (gameBeginAction())
		{

			while (1)//  while(1)������ѭ��ѭ����
			{
				
			

				starttime = clock();

				//���ر���ͼƬ

				putimage(0, 0, &background);

				//����

				drawBird(flybird.x, flybird.y);
	

				//С��Ĭ���½����ٶ�


				flybird.y += 5;


				for (int i = 0; i < 3; i++)
				{

					arrayPillar[i].x -= 0.2;

					//�ж������Ƿ�Խ���߽� ���Խ�������µ�һ������


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
			
				//��ȡ�û���������

				//�ո������


				if (_kbhit())
				{
					KeyDown();
				}

				//�ж�С���Ƿ�ײ�� 
			
				if (hitFloor() || hitPillar(arrayPillar))
				{

					gameOverAction();

					endtime = clock();

					showscore();

					goto sss;

				}


				//��ʾ����


				Score(arrayPillar);


				Sleep(20);

			

			}

		

		}
	getchar();
	closegraph();
	return 0;
}


