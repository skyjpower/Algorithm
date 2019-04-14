#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <memory.h>


#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define SIZE 30

using namespace std;

int r, c, nDir = 4, nTotal = 1;
int dir[4][2] =
{
   { -1, 0 },
   { 1, 0 },
   { 0, -1 },
   { 0, 1 }
};

pair<int, int> startPos;
pair<int, int> emptyPos;

char cResult = 0;
char map[SIZE][SIZE] = { 0 };
char tileList[4][6] =
{
   { '|', '+', '1', '4', 'Z' }, // Up
   { '|', '+', '2', '3', 'Z' }, // Down
   { '-', '+', '1', '2', 'Z' }, // Left
   { '-', '+', '3', '4', 'Z' }, // Right
};

bool clearFlag = false;

bool IsInMap(int x, int y)
{
	return (0 <= x && x < r && 0 <= y && y < c);
}

void DFS(int curX, int curY, int iDir, bool flag, bool visit[][SIZE], int iTotal)
{
	if (!visit[curX][curY])
	{
		visit[curX][curY] = true;
		iTotal++;
	}

	if (map[curX][curY] == '1') iDir = (iDir + 3) % 4;
	else if (map[curX][curY] == '2' || map[curX][curY] == '4') iDir = (iDir + 2) % 4;
	else if (map[curX][curY] == '3') iDir = (iDir + 1) % 4;
	else if (map[curX][curY] == 'Z' && iTotal == nTotal)
	{
		clearFlag = true;
		return;
	}

	int nX = curX + dir[iDir][0];
	int nY = curY + dir[iDir][1];

	if (!IsInMap(nX, nY)) return;

	if (map[nX][nY] != '.')
	{
		bool bTmp = false;

		for (int i = 0; i < 5; ++i)
		{
			if (tileList[iDir][i] == map[nX][nY])
			{
				bTmp = true;
				break;
			}
		}

		if (!bTmp) return;
	}

	// ºóÄ­
	if (map[nX][nY] == '.' && !flag)
	{
		for (int i = 0; i < 4; ++i)
		{
			// ºóÄ­¿¡ ´ëÀÔ
			map[nX][nY] = tileList[iDir][i];
			// DFS
			DFS(nX, nY, iDir, true, visit, iTotal);
			// Å¬¸®¾îÇßÀ» ½Ã
			if (clearFlag == true)
			{
				emptyPos.first = nX;
				emptyPos.second = nY;
				cResult = tileList[iDir][i];
				return;
			}
			visit[nX][nY] = false;
			map[nX][nY] = '.';
		}
	}
	else if (map[nX][nY] != '.')
	{
		DFS(nX, nY, iDir, flag, visit, iTotal);
		visit[nX][nY] = false;
	}
		
}

int main()
{
	// ÀÔ·Â
	scanf("%d %d", &r, &c);
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			char ch = 0;
			scanf(" %c", &ch);

			map[i][j] = ch;
			if (ch != '.') nTotal++;

			if (ch == 'M')
			{
				startPos.first = i;
				startPos.second = j;
			}
		}
	}

	bool visit[SIZE][SIZE] = { 0 };

	for (int i = 0; i < 4; ++i)
	{
		DFS(startPos.first, startPos.second, i, false, visit, 0);
		if (clearFlag) break;
		memset(visit, 0, sizeof(visit));
	}

	printf("%d %d %c\n", emptyPos.first + 1, emptyPos.second + 1 ,cResult);

	return 0;
}
