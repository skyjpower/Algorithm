#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

#define SIZE	1010
#define INF		1000000007

using namespace std;

typedef struct _tagNODE
{
	int x;
	int y;
	bool isCrash;
	int nCount;
}NODE, *PNODE;

int n, m;
int map[SIZE][SIZE];
int visit[SIZE][SIZE];
int nMin = INF;
int xarr[4] = { 1, -1, 0, 0 };
int yarr[4] = { 0, 0, 1, -1 };

queue<NODE> q;

void BFS()
{
	visit[0][0] = 1;
	q.push({ 0, 0, false, 1 });

	while (!q.empty())
	{
		int qSize = q.size();

		for (int i = 0; i < qSize; ++i)
		{
			int cur_x = q.front().x;
			int cur_y = q.front().y;
			bool cur_Crash = q.front().isCrash;
			int cur_Count = q.front().nCount;
			q.pop();

			// 종료 시점
			if (map[cur_x][cur_y] != 1 && cur_x == n - 1 && cur_y == m - 1)
			{
				nMin = cur_Count;
				return;
			}

			for (int i = 0; i < 4; ++i)
			{
				int next_x = cur_x + xarr[i];
				int next_y = cur_y + yarr[i];

				// 맵 밖에 벗어나는 경우
				if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= m) continue;

				// 방문되어져 있는 경우
				if (visit[next_x][next_y] == 1) continue;

				// 벽이면서, 부쉬고 들어간 적이 있는 경우
				if (visit[next_x][next_y] == 2 && cur_Crash) continue;

				// 가려는 곳이 벽인 경우
				if (map[next_x][next_y] == 1)
				{
					// 이미 벽을 뚫고 온 경우
					if (cur_Crash) continue;

					// 벽을 뚫지 않은 경우
					visit[next_x][next_y] = 2;
					q.push({ next_x, next_y, true, cur_Count + 1 });
				}
				// 일반 도로인 경우
				else
				{
					visit[next_x][next_y] = cur_Crash == true ? 2 : 1;
					q.push({ next_x, next_y, cur_Crash, cur_Count + 1 });
				}
			}
		}
	}
}

int main()
{
	// 입력
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
			scanf("%1d", &map[i][j]);
	}

	BFS();

	printf("%d\n", nMin == INF ? -1 : nMin);

	return 0;
}