#include <cstdio>
#include <queue>
#include <memory.h>

#define SIZE 22
#define INF 1234567890

using namespace std;

typedef struct _tagNode
{
	int x;
	int y;
}NODE, *PNODE;

char map[SIZE][SIZE];
int aPath[SIZE][SIZE];

int xarr[4] = { 1, -1, 0, 0 };
int yarr[4] = { 0, 0, 1, -1 };

int w, h;
int nIndex = 1;
int nMin = INF;

NODE tDirty[11];

void Input()
{
	for (int i = 0; i < h; ++i)
	{
		scanf(" %s", map[i]);
		for (int j = 0; j < w; ++j)
		{
			// 더러운 곳
			if (map[i][j] == '*')
			{
				tDirty[nIndex].x = i;
				tDirty[nIndex++].y = j;
			}
			// 로봇 청소기
			else if (map[i][j] == 'o')
			{
				tDirty[0].x = i;
				tDirty[0].y = j;
			}
		}
	}
	memset(aPath, -1, sizeof(aPath));
}

void BFS(int start_x, int start_y, int dirty, int nSelf)
{
	queue<NODE> q;
	bool visit[SIZE][SIZE] = { 0 };
	
	q.push({ start_x, start_y });
	visit[start_x][start_y] = true;
	int nPath = 0;
	int remaining = dirty;
	bool bFlag = false;

	while (!q.empty())
	{
		bFlag = false;
		int qSize = q.size();

		for (int i = 0; i < qSize; ++i)
		{
			int cur_x = q.front().x;
			int cur_y = q.front().y;
			q.pop();
			
			// 더러운 곳을 발견했고 자기자신이 아니라면
			if (map[cur_x][cur_y] == '*' && (cur_x != tDirty[nSelf].x || cur_y != tDirty[nSelf].y))
			{
				--remaining;
				// 몇 번째인지 확인
				for (int i = 1; i <= dirty + 1; i++)
				{
					if (cur_x == tDirty[i].x && cur_y == tDirty[i].y)
					{
						aPath[nSelf][i] = nPath;
						break;
					}
				}

				// 더러운 곳을 모두 발견했다면 리턴
				if (!remaining) return;
			}

			for (int j = 0; j < 4; ++j)
			{
				int next_x = cur_x + xarr[j];
				int next_y = cur_y + yarr[j];

				// 맵 내에 존재
				if (next_x < 0 || next_y < 0 || next_x >= h || next_y >= w) continue;
				// 방문 여부
				if (visit[next_x][next_y]) continue;
				// 벽인 경우
				if (map[next_x][next_y] == 'x') continue;

				// queue에 넣어주기
				visit[next_x][next_y] = true;
				q.push({ next_x, next_y });
				bFlag = true;
			}
		}
		if (bFlag) nPath++;
	}
}

void DFS(int current, int nTotal, int remaining, bool v[])
{
	// 최소 경로가아닌 경우
	if (nMin <= nTotal) return;

	if (remaining == 0)
	{
		nMin = nTotal;
		return;
	}

	for (int i = 1; i < nIndex; ++i)
	{
		int cur_x = tDirty[current].x;
		int cur_y = tDirty[current].y;

		// 자기 자신인 경우 검사 x
		if (i == current) continue;
		// 방문한 곳인 경우 return
		if (v[i]) continue;
		// 최단 거리를 계산할 필요가 없는 경우
		if (nTotal + aPath[current][i] >= nMin) continue;

		v[i] = true;
		DFS(i, nTotal + aPath[current][i], remaining - 1, v);
		v[i] = false;
	}
}

int main()
{
	while (1)
	{
		scanf("%d %d", &w, &h);
		if (w == 0 && h == 0) break;

		// 입력
		Input();
		bool cantFlag = false;

		// Solution
		BFS(tDirty[0].x, tDirty[0].y, nIndex - 1, 0); // 플레이어와 각 점들의 거리 구해주기

		// 모든 점에 접근 가능한 지 확인
		for (int i = 1; i < nIndex; ++i)
		{
			if (aPath[0][i] == -1)
			{
				// 종료 시키기
				nMin = INF;
				nIndex = 1;
				cantFlag = true;
				break;
			}
		}

		if (cantFlag)
		{
			puts("-1");
			continue;
		}
		

		// 각 점끼리의 최단 거리 계산
		for (int i = 1; i <= nIndex; ++i)
			BFS(tDirty[i].x, tDirty[i].y, nIndex - 2, i);

		// 경로 탐색하여 최단 거리 찾기
		bool v[11] = { 0 };
		v[0] = true;
		DFS(0, 0, nIndex - 1, v);

		// 출력
		printf("%d\n", nMin);

		// 리셋
		nMin = INF;
		nIndex = 1;
	}

	return 0;
}
