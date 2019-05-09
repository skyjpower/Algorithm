#include <cstdio>

using namespace std;

int r = 0, c = 0;
int nMax = 1;
int alphabet[26] = { 0 };
int xDir[4] = { 1,-1,0,0 };
int yDir[4] = { 0,0,1,-1 };
char map[22][22] = { 0 };
bool visit[22][22] = { 0 };


void DFS(int cur_x, int cur_y, int nPath)
{
	if (nMax < nPath)
		nMax = nPath;

	for (int i = 0; i < 4; ++i)
	{
		int next_x = cur_x + xDir[i];
		int next_y = cur_y + yDir[i];

		// 맵 밖
		if (next_x < 0 || next_y < 0 || next_x >= r || next_y >= c) continue;
		// 방문한 적 있는 곳
		if (alphabet[map[next_x][next_y]]) continue;

		alphabet[map[next_x][next_y] - 'A'] = 1;
		visit[next_x][next_y] = 1;

		DFS(next_x, next_y, nPath + 1);

		alphabet[map[next_x][next_y] - 'A'] = 0;
		visit[next_x][next_y] = 0;
	}
}

int main()
{
	scanf("%d %d", &r, &c);
	for (int i = 0; i < r; ++i)
	{
		scanf(" %s", map[i]);
	}

	DFS(0, 0, 1);

	printf("%d\n", nMax);

	return 0;
}