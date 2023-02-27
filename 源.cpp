#include<stdio.h>
#include<easyx.h>	//需要安装...
#include<time.h>	//时间头文件
#include<conio.h>
#include<mmsystem.h>				//头文件
#pragma comment(lib,"winmm.lib")	//库文件
IMAGE img_meteor[2];
//小星星，需要绘制，需要移动（速度），需要颜色 100
struct Star
{
	int x;
	int y;
	int speed;
};
//初始化
void star_init(Star* star, int x, int y, int speed)
{
	star->x = x;
	star->y = y;
	star->speed = speed;
}
//绘制
void star_draw(Star* star)
{
	setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
	solidcircle(star->x, star->y, 1);
}
void star_moveby(Star* star, int dx, int dy)
{
	star->x += dx;
	star->y += dy;
}
//流星
typedef  Star Meteor;
void meteor_init(Meteor* me, int x, int y, int speed)
{
	star_init(me, x, y, speed);
}
void meteor_draw(Meteor* me)
{
	putimage(me->x, me->y, img_meteor + rand() % 2, SRCPAINT);
}
void meteor_moveby(Meteor* star, int dx, int dy)
{
	star_moveby(star, dx, dy);
}

//定义变量，初始化，绘制
#define STAR_NUM 500	//小星星数量
#define METEOR_NUM 100
Star stars[STAR_NUM];
Meteor mes[METEOR_NUM];
void init()
{
	for (int i = 0; i < STAR_NUM; i++)
	{
		int x = rand() % getwidth();
		int y = rand() % getheight();
		int speed = rand() % 5 + 1;	//[1,5]
		star_init(stars + i, x, y, speed);
	}

	for (int i = 0; i < METEOR_NUM; i++)
	{
		int x = rand() % getwidth();
		int y = rand() % getheight();
		int speed = rand() % 5 + 1;	//[1,5]
		meteor_init(mes + i, x, y, speed);
	}
}
void draw()
{
	for (int i = 0; i < STAR_NUM; i++)
	{
		star_draw(stars + i);
	}
	for (int i = 0; i < METEOR_NUM; i++)
	{
		meteor_draw(mes + i);
	}
}
void move()
{
	for (int i = 0; i < STAR_NUM; i++)
	{
		star_moveby(stars + i, stars[i].speed, 0);
		//判断是否超过了窗口的边界
		if (stars[i].x > getwidth())
		{
			stars[i].x = 0;
		}
	}
	for (int i = 0; i < METEOR_NUM; i++)
	{
		meteor_moveby(mes + i, mes[i].speed, mes[i].speed);
		if (mes[i].x > getwidth())
		{
			mes[i].x = -img_meteor->getwidth();
		}
		else if (mes[i].y > getheight())
		{
			mes[i].y = -img_meteor->getheight();
		}
	}
}
int main()
{
	//窗口
	initgraph(1200, 800, 1);
	//设置随机数种子(随机数才能随机)
	srand(time(NULL));

	init();

	//播放音乐
	mciSendString(L"open ./images/浪漫空气.mp3 alias bgm", NULL, 0, NULL);
	mciSendString(L"play bgm repeat", NULL, 0, NULL);

	//绘制背景图
	IMAGE img_bk[2];
	loadimage(img_bk + 0, L"./images/03.png", getwidth(), getheight());
	loadimage(img_bk + 1, L"./images/bk.png", getwidth(), getheight());
	loadimage(img_meteor + 0, L"./images/1.jpg", 50, 50);
	loadimage(img_meteor + 1, L"./images/2.jpg", 50, 50);
	//输出图片
	//putimage(0, 0, img_bk + 0);
	//putimage(0, 0, img_bk + 1);

	//设置文字的样式
	settextstyle(40, 0, L"微软雅黑");
	//设置背景模式
	setbkmode(TRANSPARENT);
	//如果没有按键按下，就一直循环，如果有按键按下，就退出循环
	while (1)
	{
		putimage(0, 0, img_bk + 0);
		//设置文字的颜色
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		outtextxy(500, 20, L"小朋友");
		outtextxy(200, 100, L"浮生若梦，慕尔如星");
		outtextxy(200, 150, L"与你同行，不介意路远");
		outtextxy(200, 200, L"平稳而不平淡，快乐而长久");
		outtextxy(200, 250, L"世间五味俱全，谢谢你给我的甜(´▽`ʃ♡ƪ)");
		outtextxy(200, 300, L"嘿嘿嘿");
		outtextxy(200, 350, L"南风过境，十里春风不如你");
		outtextxy(200, 400, L"要永远快乐鸭");
		outtextxy(200, 450, L"嘻嘻嘻");
		outtextxy(200, 500, L"--------------------------------------你的XXX");

		//绘制爱心
		for (int i = 0; i < 10; i++)
		{
			settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
			outtextxy(rand() % getwidth(), rand() % getheight(), rand() % 2 ? L"❤" : L"♥");
		}

		Sleep(300);
		if (_kbhit()) {
			printf("hahahahh\n");
			break;
		}
		printf("-----------------------\n");
	}
	while (true)
	{
		BeginBatchDraw();
		putimage(0, 0, img_bk + 1);
		draw();
		EndBatchDraw();
		move();

		Sleep(10);
	}
	_getch();
	_getch();
	_getch();
	return 0;
}