#include <cstdio>
#define SIZE 1010

using namespace std;

int dp[SIZE][SIZE] = { 0 };
int n, k;

int main()
{
	scanf("%d %d", &n, &k);

	for (int i = 0; i <= n + 1; ++i)
	{
		dp[i][0] = 1;
		dp[0][i] = 1;
	}

	for (int i = 1; i <= n + 1; ++i)
	{
		for (int j = 1; j <= n + 1; ++j)
			dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % 10007;
	}
	
	printf("%d\n", dp[n - k][k] % 10007);

	return 0;
}
