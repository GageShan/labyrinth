#pragma once

#include "commons.h"

#include<graphics.h>
#include<vector>

void initGameMenu() {
	settextcolor(GREEN);
	rectangle(1050, 100, 1250, 150);//设置起点
	rectangle(1050, 150, 1250, 200);//设置终点
	rectangle(1050, 200, 1250, 250);//随机障碍
	rectangle(1050, 250, 1250, 300);//开始寻路
	rectangle(1050, 300, 1250, 350);//退出迷宫
	RECT r1 = { 1050, 100, 1250, 150 };
	drawtext(_T("设置起点"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r2 = { 1050, 150, 1250, 200 };
	drawtext(_T("设置终点"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { 1050, 200, 1250, 250 };
	drawtext(_T("随机障碍"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = { 1050, 250, 1250, 300 };
	drawtext(_T("开始寻路"), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5 = { 1050, 300, 1250, 350 };
	drawtext(_T("退出迷宫"), &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void paintMainMenu(COLORREF headColor, COLORREF tailColor, LPCTSTR text[3], int point[][4]) {
	settextcolor(headColor);
	for (int i = 0; i < 3; i++) {
		if (i == 1) { settextcolor(tailColor); }
		rectangle(point[i][0], point[i][1], point[i][2], point[i][3]);
		RECT r = { point[i][0], point[i][1], point[i][2], point[i][3] };
		drawtext(text[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}


//画游戏页面
void paintGameMenu(COLORREF headColor, COLORREF tailColor, LPCTSTR text[5], int point[][4]) {
	settextcolor(headColor);
	for (int i = 0; i < 5; i++) {
		if (i == 1) { settextcolor(tailColor); }
		rectangle(point[i][0], point[i][1], point[i][2], point[i][3]);
		RECT r = { point[i][0], point[i][1], point[i][2], point[i][3] };
		drawtext(text[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}


//初始化主页面
void initMainMenu() {
	settextcolor(GREEN);
	rectangle(550, 300, 750, 400);
	rectangle(550, 400, 750, 500);
	rectangle(550, 500, 750, 600);
	RECT r1 = { 550, 300, 750, 400 };
	drawtext(_T("DFS"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r2 = { 550, 400, 750, 500 };
	drawtext(_T("BFS"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { 550,500,750,600 };
	drawtext(_T("EXIT"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//画迷宫图形
void PrintLine()
{
	setbkcolor(WHITE);
	cleardevice();
	//画迷宫图形
	setlinecolor(BLACK);
	for (int i = 0; i <= 1000; i += 50)  line(i, 0, i, 1000);
	for (int i = 0; i <= 600; i += 50)  line(0, i, 1000, i);
}

//填充颜色，随机迷宫路径
void FillColor()     
{
	srand(time(NULL)); //初始化随机数种子
	setfillcolor(RED);
	//填充颜色，以分别可走路径和不可走路径
	int flag = 1;
	for (int i = 0; i < 1000; i += 50) {

		for (int j = 0; j < 600; j += 50) {

			//随机设置位置为不可走状态
			flag = rand();

			if (flag % 2 != 0 && flag % 3 != 0) {

				solidrectangle(i, j, i + 50, j + 50);
				mg[(j + 50) / 50][(i + 50) / 50] = 1;

				Sleep(10);

			}
		}
	}
}

void setWindowsName(LPCTSTR name) {
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, name);
}

void setMenuText() {
	setbkmode(TRANSPARENT);//透明字体
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 48;                      // 设置字体高度为 48
	_tcscpy_s(f.lfFaceName, _T("宋体"));    // 设置字体为“宋体”
	//f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	setWindowsName(_T("by gageshan"));		//设置窗口句柄
}

void msg(LPCTSTR message) {
	settextcolor(GREEN);
	//rectangle(1050, 450, 1250, 500);
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 20;                      // 设置字体高度为 48
	_tcscpy_s(f.lfFaceName, _T("宋体"));    // 设置字体为“宋体”
	//f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	RECT r = { 1050, 450, 1250, 500 };
	drawtext(message, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	f.lfHeight = 48;                      // 设置字体高度为 48
	settextstyle(&f);                     // 设置字体样式
}