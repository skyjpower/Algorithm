#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#define SIZE 101

using namespace std;

int n;
int map[SIZE][SIZE];

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			scanf("%d", &map[i][j]);
		}
	}

	// 거쳐가지는 지점
	for (int k = 0; k < n; ++k)
	{
		// 출발 지점
		for (int i = 0; i < n; ++i)
		{
			if (k == i || !map[i][k]) continue;
			// 도착 지점
			for (int j = 0; j < n; ++j)
			{
				if (map[i][k] && map[k][j]) map[i][j] = 1;
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			printf("%d ", map[i][j]);
		putchar('\n');
	}

	return 0;
}