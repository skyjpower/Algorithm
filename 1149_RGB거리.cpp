#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

using namespace std;
const int SIZE = 1010;
const int R = 0, G = 1, B = 2;

int Min(int a, int b) { return (a < b ? a : b); }

int n;
int cost[SIZE][3] = { 0 };
int dp[SIZE][3] = { 0 };

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) for (int j = 0; j < 3; ++j) scanf("%d", &cost[i][j]);
	dp[0][R] = cost[0][R];
	dp[0][G] = cost[0][G];
	dp[0][B] = cost[0][B];
	for (int i = 1; i < n; ++i)
	{
		dp[i][R] = cost[i][R] + Min(dp[i - 1][G], dp[i - 1][B]);
		dp[i][G] = cost[i][G] + Min(dp[i - 1][R], dp[i - 1][B]);
		dp[i][B] = cost[i][B] + Min(dp[i - 1][R], dp[i - 1][G]);
	}
	int nResult = Min(dp[n - 1][R], dp[n - 1][G]);
	printf("%d\n", Min(nResult, dp[n - 1][B]));

	return 0;
}