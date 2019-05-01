#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory.h>

#define SIZE 1010

int dp[SIZE] = { 0 };
int arr[SIZE] = { 0 };

int main()
{
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &arr[i]);
		dp[i] = 1;
	}
		
	for (int i = n - 1; i >= 0; --i)
		for (int j = i + 1; j < n; ++j)
			if (arr[i] > arr[j])
				dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;

	int nMax = 0;
	for (int i = 0; i < n; ++i)
		if (dp[i] > nMax) nMax = dp[i];

	printf("%d\n", nMax);

	return 0;
}