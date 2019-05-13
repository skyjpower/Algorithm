#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

using namespace std;
const int SIZE = 45;
int n, nInput;
int dp[2][SIZE] = { 0 };

int main()
{
	scanf("%d", &n);
	dp[0][0] = 1;
	dp[1][1] = 1;

	for (int i = 2; i <= 40; ++i)
	{
		dp[0][i] = dp[0][i - 1] + dp[0][i - 2];
		dp[1][i] = dp[1][i - 1] + dp[1][i - 2];
	}
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &nInput);
		printf("%d %d\n", dp[0][nInput], dp[1][nInput]);
	}

	return 0;
}