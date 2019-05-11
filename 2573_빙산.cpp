#include <cstdio>
#include <vector>
#include <queue>
#include <list>

using namespace std;

typedef struct _tagNode
{
	int x;
	int y;
	bool bMelt;

}NODE, *PNODE;

const int SIZE = 310;
int r, c, vSize;
int map[SIZE][SIZE] = { 0 };
int aMinus[SIZE][SIZE] = { 0 };
int xDir[4] = { 1,-1,0,0 };
int yDir[4] = { 0,0,1,-1 };

int nIceberg = 0;
bool bClear = false;

vector<NODE> v;

void CheckDivision()
{
	bool visit[SIZE][SIZE] = { 0 };
	int nNum = 0;

	queue<NODE> q;
	for (int i = 0; i < vSize; ++i)
	{
		if (!v[i].bMelt)
		{
			q.push({ v[i].x, v[i].y });
			visit[v[i].x][v[i].y] = true;
			break;
		}
	}
	
	while (!q.empty())
	{
		int qSize = q.size();
		for (int i = 0; i < qSize; ++i)
		{
			int cur_x = q.front().x;
			int cur_y = q.front().y;
			q.pop();
			nNum++;

			for (int j = 0; j < 4; ++j)
			{
				int next_x = cur_x + xDir[j];
				int next_y = cur_y + yDir[j];
				
				if (next_x < 0 || next_y < 0 ||
					next_x >= r || next_y >= c)
					continue;
				if (map[next_x][next_y] == 0)
				{
					aMinus[cur_x][cur_y]++;
				}
			}

			for (int j = 0; j < 4; ++j)
			{
				int next_x = cur_x + xDir[j];
				int next_y = cur_y + yDir[j];

				if (next_x < 0 || next_y < 0 ||
					next_x >= r || next_y >= c)
					continue;
				if (visit[next_x][next_y]) continue;
				if (map[next_x][next_y] == 0) continue;

				q.push({ next_x, next_y });
				visit[next_x][next_y] = true;
			}
		}
	}

	if (nNum != nIceberg) bClear = true;

	return;
}

void MeltIceberg()
{
	for (int i = 0; i < vSize; ++i)
	{
		if (!v[i].bMelt)
		{
			if (map[v[i].x][v[i].y] - aMinus[v[i].x][v[i].y] <= 0)
			{
				nIceberg--;
				map[v[i].x][v[i].y] = 0;
				v[i].bMelt = true;
			}
			else
				map[v[i].x][v[i].y] -= aMinus[v[i].x][v[i].y];

			aMinus[v[i].x][v[i].y] = 0;
		}
	}
}

int main()
{
	scanf("%d %d", &r, &c);
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j])
			{
				v.push_back({ i, j, false });
				++nIceberg;                                       
			}
		}
	}
	vSize = v.size();
	int nDay = 0;

	while (!bClear)
	{
		// ´ë·ú Ã¼Å©
		CheckDivision();
		if (bClear) break;
		nDay++;

		// ¾óÀ½ ³ì±â
		MeltIceberg();
		if (nIceberg <= 0)
		{
			puts("0");
			return 0;
		}
	}
	printf("%d\n", nDay);

	return 0;
}