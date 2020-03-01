// labyrinth.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "commons.h"
#include "myGraph.h"

#include <iostream>
#include <graphics.h>
#include<malloc.h>
#include<queue>

#include <conio.h>//在控制台输入输出文件

using namespace std;

void GameMenu();
void MainMenu();
void init();

int flag1 = 0;


//设置迷宫的边界
void init() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXM; j++)
			mg[i][j] = 0;
	for (int i = 0; i < MAXN; i++) mg[i][MAXM - 1] = 1;
	for (int i = 0; i < MAXN; i++) mg[i][0] = 1;
	for (int i = 0; i < MAXM; i++) mg[MAXN - 1][i] = 1;
	for (int i = 0; i < MAXM; i++) mg[0][i] = 1;
}




vector<Node> findPathByBFS(int sx, int sy, int ex, int ey) {
	queue<Node> qu;
	vector<Node> vt;
	qu.push(Node(ex, ey, -1, 0));


	int cnt = 1;
	while (!qu.empty()) {
		Node node = qu.front();		qu.pop();
		vt.push_back(node);
		if (node.x == sx && node.y == sy) {
			//cout << "yes" << endl;
			return vt;
		}

		for (int i = 0; i < 4; i++) {
			int tx = node.x + dx[i];
			int ty = node.y + dy[i];

			if (tx < 0 || tx >= MAXN || ty < 0 || ty >= MAXM || mg[tx][ty] == 1) { continue; }
			mg[tx][ty] = 1;
			qu.push(Node(tx, ty, node.index, cnt)); cnt++;
		}
	}
	vt.clear();
	return vt;
}
vector<Node> getBFSVector(vector<Node> vt) {
	vector<Node> res;
	if (vt.size() == 0) {
		return res;
	}
	Node tp = vt[vt.size() - 1];
	while (tp.pre != 0) {
		Node index = vt[tp.pre];
		res.push_back(index);
		//cout << index.x << " " << index.y << endl;
		tp = index;
	}
	return res;
}

bool fillColorByVector(vector<Node> vt)
{
	sx = sy = ex = ey = -1;

	
	if (vt.size() != 0) {

		for (auto box : vt)
		{
			setfillcolor(GREEN);

			solidrectangle((box.y - 1) * 50, (box.x - 1) * 50, (box.y - 1) * 50 + 50, (box.x - 1) * 50 + 50);

			//暂停0.1s钟以便于观察路径过程
			Sleep(1000);
		}
		return true;
	}
	else {
		return false;
	}
	
}
void dfs(vector<Node> &vt, int x, int y, int ex, int ey, bool &op) {
	if (op) { return; }

	for (int i = 0; i < 4; i++) {
		int tx = x + dx[i];
		int ty = y + dy[i];

		if (tx == ex && ty == ey) {
			op = true;
			return;
		}
		if (tx < 0 || tx >= MAXN || ty <= 0 || ty >= MAXM || mg[tx][ty] == 1) { continue; }

		vt.push_back(Node(tx, ty, 0));
		mg[tx][ty] = 1;
		dfs(vt, tx, ty, ex, ey, op);
		if (op) { return; }
		vt.pop_back();
		mg[tx][ty] = 0;
	}
}
vector<Node> findPathByDFS(int sx, int sy, int ex, int ey) {
	vector<Node> vt;
	bool op = false;
	mg[sx][sy] = 1;
	dfs(vt, sx, sy, ex, ey, op);
	return vt;
}

void GameMenu()
{
	initgraph(1300, 600);
	setbkcolor(WHITE);
	cleardevice();

	PrintLine();
	//FillColor();
	settextcolor(GREEN);//字体颜色
	setMenuText();
	initGameMenu();
	LPCTSTR tp[3];
	while (true) {
		MOUSEMSG Mou = GetMouseMsg();
		BeginBatchDraw();
		switch (Mou.uMsg) {
		case WM_MOUSEMOVE:
			EndBatchDraw();
			if ((Mou.x >= 1050 && Mou.x <= 1250) && (Mou.y >= 100 && Mou.y <= 150)) {
				tp[0] = _T("设置起点");
				tp[1] = _T("设置终点");
				tp[2] = _T("随机障碍");
				tp[3] = _T("开始寻路");
				tp[4] = _T("退出迷宫");
				int point[][4] = { {1050, 100, 1250, 150},
									{1050, 150, 1250, 200},
									{1050, 200, 1250, 250},
									{1050, 250, 1250, 300},
									{1050, 300, 1250, 350}
				};
				paintMainMenu(YELLOW, GREEN, tp, point);
			}
			else if (Mou.x >= 1050 && Mou.x <= 1250 && Mou.y >= 150 && Mou.y <= 200) {

				tp[0] = _T("设置终点");
				tp[1] = _T("设置起点");
				tp[2] = _T("随机障碍");
				tp[3] = _T("开始寻路");
				tp[4] = _T("退出迷宫");
				int point[][4] = { {1050, 150, 1250, 200},
									{1050, 100, 1250, 150},
									{1050, 200, 1250, 250},
									{1050, 250, 1250, 300},
									{1050, 300, 1250, 350}
				};
				paintMainMenu(YELLOW, GREEN, tp, point);
			}
			else if (Mou.x >= 1050 && Mou.x <= 1250 && Mou.y >= 200 && Mou.y <= 250) {
				tp[0] = _T("随机障碍");
				tp[1] = _T("设置起点");
				tp[2] = _T("设置终点");
				tp[3] = _T("开始寻路");
				tp[4] = _T("退出迷宫");
				int point[][4] = { {1050, 200, 1250, 250},
									{1050, 100, 1250, 150},
									{1050, 150, 1250, 200},
									{1050, 250, 1250, 300},
									{1050, 300, 1250, 350}
				};
				paintMainMenu(YELLOW, GREEN, tp, point);
			}
			else if (Mou.x >= 1050 && Mou.x <= 1250 && Mou.y <= 300 && Mou.y >= 250) {

				tp[0] = _T("开始寻路");
				tp[1] = _T("设置起点");
				tp[2] = _T("设置终点");
				tp[3] = _T("随机障碍");
				tp[4] = _T("退出迷宫");
				int point[][4] = { {1050, 250, 1250, 300},
									{1050, 100, 1250, 150},
									{1050, 150, 1250, 200},
									{1050, 200, 1250, 250},
									{1050, 300, 1250, 350}
				};
				paintMainMenu(YELLOW, GREEN, tp, point);
			}
			else if (Mou.x >= 1050 && Mou.x <= 1250 && Mou.y >= 300 && Mou.y <= 350) {
				tp[0] = _T("退出迷宫");
				tp[1] = _T("设置起点");
				tp[2] = _T("设置终点");
				tp[3] = _T("随机障碍");
				tp[4] = _T("开始寻路");
				int point[][4] = { {1050, 300, 1250, 350},
									{1050, 100, 1250, 150},
									{1050, 150, 1250, 200},
									{1050, 200, 1250, 250},
									{1050, 250, 1250, 300}
				};
				paintMainMenu(YELLOW, GREEN, tp, point);
			}
			else {
				initGameMenu();
			}
			break;
		case WM_LBUTTONDOWN:
			EndBatchDraw();
			if (Mou.x >= 1050 && Mou.x <= 1250 && Mou.y >= 100 && Mou.y <= 150) {

				bool flag = true;
				while (flag) {
					//FlushMouseMsgBuffer();
					Mou = GetMouseMsg();
					BeginBatchDraw();
					switch (Mou.uMsg) {
					case WM_LBUTTONDOWN:
						EndBatchDraw();
						sy = Mou.x / 50;
						sx = Mou.y / 50;
						if (mg[sy + 1][sx + 1] != 1) {
							setfillcolor(BLUE);
							fillrectangle(Mou.x / 50 * 50, Mou.y / 50 * 50, Mou.x / 50 * 50 + 50, Mou.y / 50 * 50 + 50);
							flag = false;
						}
						sy += 1;
						sx += 1;
						mg[sx][sy] = 0;
						break;
					}
				}
			}
			else if (Mou.x >= 1050 && Mou.x <= 1250 && Mou.y >= 150 && Mou.y <= 200) {
				bool flag = true;
				while (flag) {
					//FlushMouseMsgBuffer();
					Mou = GetMouseMsg();
					BeginBatchDraw();
					switch (Mou.uMsg) {
					case WM_LBUTTONDOWN:
						EndBatchDraw();
						ey = Mou.x / 50;
						ex = Mou.y / 50;
						if (mg[ey + 1][ex + 1] != 1) {
							setfillcolor(YELLOW);
							fillrectangle(Mou.x / 50 * 50, Mou.y / 50 * 50, Mou.x / 50 * 50 + 50, Mou.y / 50 * 50 + 50);
							flag = false;
						}
						ey += 1;
						ex += 1;
						mg[ex][ey] = 0;
						break;
					}
				}
			}
			else if (Mou.x >= 1050 && Mou.x <= 1250 && Mou.y >= 200 && Mou.y <= 250) {
				init();
				cleardevice();
				PrintLine();
				FillColor();
			}
			else if (Mou.x >= 1050 && Mou.x <= 1250 && Mou.y <= 300 && Mou.y >= 250) {
				if (sx == -1 || sy == -1 || ex == -1 || ey == -1) {
					msg(_T("请设置起点或终点"));
					continue;
				}
				bool judgeWork = false;
				if (flag1 == 1) {
					vector<Node> vt = findPathByDFS(sx, sy, ex, ey);
					judgeWork = fillColorByVector(vt);

				}
				else if (flag1 == 2) {
					vector<Node> vt = findPathByBFS(sx, sy, ex, ey);
					vt = getBFSVector(vt);
					judgeWork = fillColorByVector(vt);
				}
				if (!judgeWork) {
					msg(_T("该迷宫无解"));
				}
			}
			else if (Mou.x >= 1050 && Mou.x <= 1250 && Mou.y >= 300 && Mou.y <= 350) {
				closegraph();
				flag1 = 0;
				init();
				MainMenu();
			}
		}
	}
}

void MainMenu()
{
	initgraph(750, 600);
	setbkcolor(0x555555);
	cleardevice();
	setlinecolor(0x1000036);
	settextcolor(GREEN);//字体颜色
	setMenuText();
	BeginBatchDraw();

	LPCTSTR tp[3];
	while (true) {

		MOUSEMSG Mou = GetMouseMsg();
		switch (Mou.uMsg) {
		case WM_MOUSEMOVE:
			EndBatchDraw();
			if ((Mou.y >= 300 && Mou.y <= 400) && (Mou.x <= 750 && Mou.x >= 550)) {
				tp[0] = _T("DFS");
				tp[1] = _T("BFS");
				tp[2] = _T("EXIT");
				int point[][4] = { {550,300,750,400},{550,400,750,500},{550,750,500,600} };
				paintMainMenu(YELLOW, GREEN, tp, point);
			}
			else if (Mou.y >= 400 && Mou.y <= 500 && Mou.x <= 750 && Mou.x >= 550) {
				tp[0] = _T("BFS");
				tp[1] = _T("DFS");
				tp[2] = _T("EXIT");
				int point[][4] = { {550,400,750,500},{550,300,750,400},{550,750,500,600} };
				paintMainMenu(YELLOW, GREEN, tp, point);
			}
			else if (Mou.x >= 550 && Mou.x <= 750 && Mou.y >= 500 && Mou.y <= 600) {
				tp[0] = _T("EXIT");
				tp[1] = _T("DFS");
				tp[2] = _T("BFS");
				int point[][4] = { {550,500,750,600},{550,300,750,400},{550,400,750,500} };
				paintMainMenu(YELLOW, GREEN, tp, point);
			}
			else {
				initMainMenu();
			}
			break;
		case WM_LBUTTONDOWN:
			EndBatchDraw();
			if (Mou.x >= 550 && Mou.x <= 750 && Mou.y <= 400 && Mou.y >= 300) {
				flag1 = 1;
				closegraph();
				GameMenu();
			}
			else if (Mou.x >= 550 && Mou.x <= 750 && Mou.y >= 400 && Mou.y <= 500) {
				flag1 = 2;
				closegraph();
				GameMenu();
			}
			else if (Mou.x >= 550 && Mou.x <= 750 && Mou.y >= 500 && Mou.y <= 600) {
				closegraph();
				exit(1);
			}
			break;
		}
	}
}


void run() {
	MainMenu();
}
int main()
{
	run();
	//debug();
	return 0;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
