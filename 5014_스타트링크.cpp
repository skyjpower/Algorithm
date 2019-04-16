#include <cstdio>

#define TOTAL 0
#define START 1
#define DEST 2
#define UP 3
#define DOWN 4

#define SIZE 1000010

using namespace std;

int input[5] = { 0 };

int main()
{
	scanf("%d %d %d %d %d", 
		&input[TOTAL], &input[START], &input[DEST], &input[UP], &input[DOWN]);

	int nCurFloor = input[START];

	for (int i = 0; nCurFloor > 0 && nCurFloor <= input[TOTAL] && i <= input[TOTAL]; i++)
	{
		if (nCurFloor == input[DEST])
		{
			printf("%d\n", i); return 0;
		}

		if (nCurFloor > input[DEST] || nCurFloor + input[UP] > input[TOTAL]) nCurFloor -= input[DOWN];
		else nCurFloor += input[UP];
	}
	printf("use the stairs\n");

	return 0;
}
