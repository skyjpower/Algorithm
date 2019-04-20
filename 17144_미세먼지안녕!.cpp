#include <cstdio>
#include <vector>

#define SIZE 55

using namespace std;

int r, c, t;
int map[SIZE][SIZE];

int xarr[4] = { 1, -1, 0, 0 };
int yarr[4] = { 0, 0, 1, -1 };

vector< pair<int, int> > vPath[2];

void CreatePath(int nRow, int nFlag, int nPathNum)
{
	int nCol = 0;
	int nTmpRow = nRow;

	// Right
	for ( ; nCol < c; ++nCol)
		vPath[nPathNum].push_back({ nTmpRow, nCol });
	nCol = c - 1;
	nTmpRow += nFlag;

	// Up or Down
	for (; nTmpRow >= 0 && nTmpRow < r; nTmpRow += nFlag)
		vPath[nPathNum].push_back({ nTmpRow, nCol });
	nTmpRow -= nFlag;
	nCol -= 1;

	// Left
	for (; nCol >= 0; --nCol)
		vPath[nPathNum].push_back({ nTmpRow, nCol });
	nCol = 0;
	nTmpRow -= nFlag;

	if (nFlag == -1)
	{
		// Down
		for ( ; nTmpRow < nRow; ++nTmpRow)
			vPath[nPathNum].push_back({ nTmpRow, nCol });
	}
	else
	{
		// Up
		for (; nTmpRow > nRow; --nTmpRow)
			vPath[nPathNum].push_back({ nTmpRow, nCol });
	}
}

void DiffusionCheck()
{
	int save[SIZE][SIZE] = { 0 };

	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			// 미세먼지인 경우
			if (map[i][j] != -1 && map[i][j] != 0)
			{
				// 확산된 방향
				int nCount = 0;
				// 한 타일에 확산될 양
				int nAmount = map[i][j] / 5;
				
				// 확산
				for (int k = 0; k < 4; ++k)
				{
					int next_x = i + xarr[k];
					int next_y = j + yarr[k];

					if (next_x < 0 || next_x >= r || next_y < 0 || next_y >= c) continue;
					if (map[next_x][next_y] == -1) continue;
					nCount++;
					save[next_x][next_y] += nAmount;
				}

				// 본래 자리 감소
				map[i][j] -= (nAmount * nCount);
			}
		}
	}

	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
			map[i][j] += save[i][j];
	}
}

void AirCleaner()
{
	int nIndex1 = vPath[0].size();
	int nIndex2 = vPath[1].size();

	for (int i = 0; i < nIndex1 - 1; ++i)
		map[vPath[0][nIndex1 - 1 - i].first][vPath[0][nIndex1 - 1 - i].second] = map[vPath[0][nIndex1 - 2 - i].first][vPath[0][nIndex1 - 2 - i].second];
	map[vPath[0][1].first][vPath[0][1].second] = 0;
	for (int i = 0; i < nIndex2 - 1; ++i)
		map[vPath[1][nIndex2 - 1 - i].first][vPath[1][nIndex2 - 1 - i].second] = map[vPath[1][nIndex2 - 2 - i].first][vPath[1][nIndex2 - 2 - i].second];
	map[vPath[1][1].first][vPath[1][1].second] = 0;
}

int main()
{
	int nCount = 0;
	
	scanf("%d %d %d", &r, &c, &t);
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == -1)
			{
				if (!nCount)
					CreatePath(i, -1, nCount);
				else
					CreatePath(i, 1, nCount);
				nCount++;
			}
		}
	}
	for (int i = 0; i < t; ++i)
	{
		DiffusionCheck();
		AirCleaner();
	}
	
	int nSum = 0;

	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if (map[i][j] != -1)
				nSum += map[i][j];
		}
	}

	printf("%d\n", nSum);

	return 0;
}
