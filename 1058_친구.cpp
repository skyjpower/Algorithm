#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#define SIZE 55

using namespace std;

char map[SIZE][SIZE];
bool v[SIZE][SIZE];
int friends[SIZE];
int n;
int nMax = 0;


int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf(" %s", map[i]);
		for (int j = 0; j < n; ++j)
		{
			if (map[i][j] == 'Y')
			{
				v[i][j] = true;
				friends[i]++;
			}
		}
	}
		

	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			if (k == i) continue;
			for (int j = 0; j < n; ++j)
			{
				if (i == j || k == j) continue;
				if (map[i][k] == 'Y' && map[k][j] == 'Y' && !v[i][j])
				{
					friends[i]++;
					v[i][j] = true;
				}
			}
		}
	}
	
	for (int i = 0; i < n; ++i)
		if (friends[i] > nMax)
			nMax = friends[i];

	printf("%d\n", nMax);

	return 0;
}