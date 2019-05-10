#include <cstdio>
#include <queue>

using namespace std;

const int SIZE = 55;

int waterDist[SIZE][SIZE] = { 0 };
int xDir[4] = { 1,-1,0,0 };
int yDir[4] = { 0,0,1,-1 };
int r, c;
int ans = -1;

char map[SIZE][SIZE] = { 0 };
bool visit[SIZE][SIZE] = { 0 };

pair<int, int> startPos;
pair<int, int> endPos;

queue< pair<int, int> > q_water;
bool bWater = false;

void Water_BFS()
{
	int _qSize = q_water.size();
	for (int i = 0; i < _qSize; ++i)
		waterDist[q_water.front().first][q_water.front().second] = 1;

	int nPath = 1;

	while (!q_water.empty())
	{
		int qSize = q_water.size();

		for (int i = 0; i < qSize; ++i)
		{
			int cur_x = q_water.front().first;
			int cur_y = q_water.front().second;
			q_water.pop();

			for (int j = 0; j < 4; ++j)
			{
				int next_x = cur_x + xDir[j];
				int next_y = cur_y + yDir[j];

				// �� ��
				if (next_x < 0 || next_y < 0 || next_x >=r || next_y >= c) continue;
				// �̹� üũ�� ���
				if (waterDist[next_x][next_y]) continue;
				// �� �� ����� �ұ�
				if (map[next_x][next_y] == 'X') continue;
				if (map[next_x][next_y] == 'D') continue;

				q_water.push({ next_x, next_y });
				waterDist[next_x][next_y] = nPath;
			}
		}
		++nPath;
	}
}

void Hedgehog_BFS()
{
	queue< pair<int, int> > q;
	q.push({ startPos.first, startPos.second });
	visit[startPos.first][startPos.second] = true;
	int nPath = 0;

	while (!q.empty())
	{
		int qSize = q.size();
		for (int i = 0; i < qSize; ++i)
		{
			int cur_x = q.front().first;
			int cur_y = q.front().second;
			q.pop();

			if (cur_x == endPos.first && cur_y == endPos.second)
			{
				ans = nPath;
				return;
			}

			for (int j = 0; j < 4; ++j)
			{
				int next_x = cur_x + xDir[j];
				int next_y = cur_y + yDir[j];

				if (next_x < 0 || next_y < 0 || next_x >= r || next_y >= c) continue;
				if (visit[next_x][next_y]) continue;
				if (map[next_x][next_y] == 'X') continue;
				if (waterDist[next_x][next_y] != 0 &&
					waterDist[next_x][next_y] - (nPath + 1) <= 0)
					continue;

				q.push({ next_x, next_y });
				visit[next_x][next_y] = true;
			}
		}
		++nPath;
	}
}

void Solution()
{
	// ���� ���� ��ĥ �ð��� Ÿ�� ���� ���
	Water_BFS();
	Hedgehog_BFS();
}

int main()
{
	scanf("%d %d", &r, &c);
	for (int i = 0; i < r; ++i)
	{
		scanf(" %s", map[i]);
		for (int j = 0; j < c; ++j)
		{
			// ����ġ
			if (map[i][j] == 'S')
			{
				startPos.first = i;
				startPos.second = j;
			}

			// ����� ��
			else if (map[i][j] == 'D')
			{
				endPos.first = i;
				endPos.second = j;
			}

			// ���� ������
			else if (map[i][j] == '*')
				q_water.push({ i, j });
		}
	}

	Solution();
	if (ans == -1) printf("KAKTUS\n");
	else printf("%d\n", ans);
	
	return 0;
}