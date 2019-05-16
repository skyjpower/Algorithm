#include <cstdio>
#define MOD 10007

using namespace std;

const int SIZE = 1010;
int n;
int dp[SIZE] = { 0 };
int main()
{
	scanf("%d", &n);
	dp[0] = 1;
	dp[1] = 2;

	for (int i = 2; i < n; ++i)
		dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;

	printf("%d\n", dp[n - 1]);
	return 0;
}