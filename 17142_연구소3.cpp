#include <cstdio>
#include <queue>
#include <vector>
#include <memory.h>

#define SIZE 55
#define INF 2000000005

using namespace std;

typedef struct _tagVirus
{
	int x, y;
}VIRUS, *PVIRUS;

int aMap[SIZE][SIZE] = { 0 };
int aDist[11][SIZE][SIZE] = { 0 };
int xarr[4] = { 1,-1,0,0 };
int yarr[4] = { 0,0,1,-1 };
int vSize;
int n, m;
int nMin = INF;

vector<VIRUS> virus;

void CheckVirus(int x, int y, queue<VIRUS> &q, bool(*visit)[SIZE],
	int curVirus, int nCount)
{
	queue<VIRUS> tmpQ;

	tmpQ.push({ x, y });
	aDist[curVirus][x][y] = nCount;

	for (int i = 0; i < 4; ++i)
	{
		int next_x = x + xarr[i];
		int next_y = y + yarr[i];

		if (next_x < 0 || next_y < 0 || next_x >= n || next_y >= n) continue;
		if (aMap[next_x][next_y] == 1) continue;
		if (visit[next_x][next_y]) continue;

		q.push({ next_x, next_y });
		visit[next_x][next_y] = true;
	}
}

void BFS(int curV)
{
	bool visit[SIZE][SIZE] = { 0 };

	queue<VIRUS> q;
	q.push(virus[curV]);
	visit[virus[curV].x][virus[curV].y] = true;

	int nCount = 0;

	while (!q.empty())
	{
		int qSize = q.size();

		for (int i = 0; i < qSize; ++i)
		{
			int cur_x = q.front().x;
			int cur_y = q.front().y;
			q.pop();

			if (aMap[cur_x][cur_y] == 0)
				aDist[curV][cur_x][cur_y] = nCount;
			else if (aMap[cur_x][cur_y] == 2)
				CheckVirus(cur_x, cur_y, q, visit, curV, nCount);

			for (int j = 0; j < 4; ++j)
			{
				int next_x = cur_x + xarr[j];
				int next_y = cur_y + yarr[j];

				if (next_x < 0 || next_y < 0 || next_x >= n || next_y >= n) continue;
				if (aMap[next_x][next_y] == 1) continue;
				if (visit[next_x][next_y]) continue;

				q.push({ next_x, next_y });
				visit[next_x][next_y] = true;
			}
		}
		nCount++;
	}
}

void DFS(bool check[])
{
	int aTime[SIZE][SIZE] = { 0 };
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			aTime[i][j] = INF;
	int t = -1;

	for (int i = 0; i < vSize; ++i)
	{
		if (check[i])
		{
			for (int j = 0; j < n; ++j)
			{
				for (int k = 0; k < n; ++k)
				{
					if (j == virus[i].x && k == virus[i].y)
						aTime[j][k] = 0;
					else if (aDist[i][j][k] != -1 && aTime[j][k] > aDist[i][j][k])
						aTime[j][k] = aDist[i][j][k];
				}
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (aMap[i][j] == 1)
				continue;
			if (aMap[i][j] == 2 && aTime[i][j] != 0)
				continue;
			if (aTime[i][j] == INF) 
				return;
			if (t < aTime[i][j]) 
				t = aTime[i][j];
		}
	}

	if (nMin > t)
		nMin = t;
}

// 선택한 바이러스, 선택된 바이러스 개수, 
void DFS_Before(int curV, int selectNum, bool check[])
{
	if (vSize - curV < m - selectNum) return;

	// 바이러스 선택 완료
	if (selectNum == m)
	{
		DFS(check);
		return;
	}
		
	for (int i = curV; i < vSize; ++i)
	{
		check[i] = true;
		DFS_Before(i + 1, selectNum + 1, check);
		check[i] = false;
	}
}

int main()
{
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; ++j)
		{
			scanf("%d", &aMap[i][j]);

			if (aMap[i][j] == 2)
				virus.push_back({ i, j });
		}
	}
	vSize = virus.size();

	memset(aDist, -1, sizeof(aDist));
	for(int i = 0; i < vSize; ++i)
		BFS(i);
	
	bool v[11] = { 0 };
	DFS_Before(0, 0, v);

	printf("%d\n", nMin == INF ? -1 : nMin);

	return 0;
}