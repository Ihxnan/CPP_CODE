
#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib, "Winmm.lib")

int flags[4] = { 0,1,2,3 };
int count = 0;


void init()
{
	srand(time(0));
	for (int i = 0; i < 4; i++)
	{
		flags[i] = rand() % 4;
	}
}

void draw()
{
	cleardevice();
	setlinestyle(PS_SOLID, 2);
	setcolor(BLACK);
	for (int i = 0; i < 5; i++)
	{
		line(0, 100 + 150 * i, 400, 100 + 150 * i);
		line(100 * i, 100, 100 * i, 700);
	}
	settextcolor(BLACK);
	settextstyle(38, 0, "Arial");
	setfillcolor(BLACK);
	for (int i = 0; i < 4; i++)
	{
		int x = flags[i] * 100;
		int y = 100 + i * 150;
		fillrectangle(x, y, x + 100, y + 150);
	}
	count++;
	settextcolor(GREEN);
	settextstyle(40, 0, "Arial");
	char score[30] = { 0 };
	sprintf_s(score, "Score: %d,   object: 10000", count);
	outtextxy(10, 20, score);
}
 

int main()
{
	
	initgraph(400, 700);
	outtextxy(70, 100, "点击最后一行黑块得分， 点击其他失败");
	outtextxy(120, 200, "点击其他地方无效");
	outtextxy(150, 300, "3秒后开始");
	Sleep(3000);
	mciSendString("play 2.75.mp3 repeat", 0, 0, 0);
	setbkcolor(WHITE);

	cleardevice();
	 init();
	 draw();
	

	 while (1)
	 {
		 ExMessage msg;
		 if (peekmessage(&msg))
		 {
			 switch (msg.message)
			 {
			 case WM_KEYDOWN:
				 if (msg.vkcode == VK_ESCAPE)
				 {
					 printf("quit");
					 exit(1);
				 }
			 case WM_LBUTTONDOWN:
				 if (msg.y > 550)
				 {
					 if (flags[3] == msg.x / 100)
					 {
						 for (int i = 3; i > 0; i--)
						 {
							 flags[i] = flags[i - 1];
						 }
						 flags[0] = rand() % 4;
						
					 }
					 else
					 {
						 settextcolor(RED);
						 settextstyle(100, 0, "Arial");
						 outtextxy(getwidth() / 2 - 100, getheight() / 2, "你输了");
						 mciSendString("pause 2.75.mp3", 0, 0, 0);
						 mciSendString("play lose.mp3 repeat", 0, 0, 0);
						 Sleep(5000);
						 exit(0);
					 }
				 }
				 draw();
				 break;
			 default:
				 break;
			 }
		 }

	 }
	system("pause");
	return 0;
}