#include <cstdio>
#define SIZE 505

using namespace std;
int n, m;

int map[SIZE][SIZE];
int dp[SIZE][SIZE];

int xarr[4] = { 1, -1, 0, 0 };
int yarr[4] = { 0, 0, 1, -1 };

int DFS(int cur_x, int cur_y)
{
	bool bFlag = false;

	if (cur_x == n - 1 && cur_y == m - 1) return 1;

	for (int i = 0; i < 4; ++i)
	{
		int next_x = cur_x + xarr[i];
		int next_y = cur_y + yarr[i];

		// 맵 밖에 벗어나는 경우
		if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= m) continue;
		// 내리막 길이 아닌 경우
		if (map[cur_x][cur_y] <= map[next_x][next_y]) continue;
		bFlag = true;
		if (dp[next_x][next_y] == -1) continue;

		// 경로가 존재하는 경우
		if (dp[next_x][next_y])
		{
			dp[cur_x][cur_y] += dp[next_x][next_y];
			continue;
		}
		// DFS 값
		int nTmp = DFS(next_x, next_y);

		// 경로가 존재하지 않는 경우
		if (nTmp <= 0)
			if (dp[cur_x][cur_y] <= 0) dp[cur_x][cur_y] = -1;
		// 경로가 존재하는 경우
		else
		{
			// 경로가 없다고 판정한 곳인 경우 0으로 초기화
			if (dp[cur_x][cur_y] == -1) dp[cur_x][cur_y] = 0;

			dp[cur_x][cur_y] += nTmp;
		}
	}
	// 아무 경로가 없다면 -1 처리
	if (!bFlag) dp[cur_x][cur_y] = -1;

	return dp[cur_x][cur_y];
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
			scanf("%d", &map[i][j]);
	}
	dp[n - 1][m - 1] = 1;

	DFS(0, 0);

	printf("%d\n", dp[0][0]);

	return 0;
}
