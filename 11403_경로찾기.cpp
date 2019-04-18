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

	// ���İ����� ����
	for (int k = 0; k < n; ++k)
	{
		// ��� ����
		for (int i = 0; i < n; ++i)
		{
			if (k == i || !map[i][k]) continue;
			// ���� ����
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