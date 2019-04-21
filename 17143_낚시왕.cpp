#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#define SIZE 110

using namespace std;

typedef struct _tagShark
{
	int m_nPosX; // 위치x
	int m_nPosY; // 위치y
	int m_nSpeed; // 스피드
	int m_nDir; // 방향
	int m_nSize; // 크기

}SHARK, *PSHARK;

int R, C, M;
int aMap[SIZE][SIZE];
vector<SHARK> sharks;
int nTotal = 0;
int xarr[4] = { -1,0,1,0 };
int yarr[4] = { 0,-1,0,1 };

bool bFlag = false;

// 상어 위치 체크
void CheckShark()
{
	int vSize = sharks.size();

	for (int i = 0; i < vSize; ++i)
		aMap[sharks[i].m_nPosX][sharks[i].m_nPosY] = 1;
}

// 낚시
void AnglerTurn(int currentCol)
{
	int nTmpRow = 0;
	bool bCatch = false;

	for (int i = 0; i < R; ++i)
	{
		if (aMap[i][currentCol] == 1)
		{
			nTmpRow = i;
			bCatch = true;
			aMap[i][currentCol] = 0;
			break;
		}
	}

	if (bCatch)
	{
		int vSize = sharks.size();

		for (int i = 0; i < vSize; ++i)
		{
			// 잡은 상어 탐색
			if (sharks[i].m_nPosX == nTmpRow && sharks[i].m_nPosY == currentCol)
			{
				nTotal += sharks[i].m_nSize;
				vector<SHARK>::iterator iter = sharks.begin();
				sharks.erase(iter + i);
				break;
			}
		}
	}

	if (sharks.size() <= 0) bFlag = true;
}

// 상어 움직임
void SharkMove()
{
	int vSize = sharks.size();

	// 기존 맵에 체크한 상어의 위치 초기화
	for (int i = 0; i < vSize; ++i)
		aMap[sharks[i].m_nPosX][sharks[i].m_nPosY] = 0;

	// 상어 움직임
	for (int i = 0; i < vSize; ++i)
	{
		int moveSpeed = sharks[i].m_nSpeed;
		int moveDir = sharks[i].m_nDir;

		// 좌우
		if (moveDir % 2)
			moveSpeed %= (2 * (C - 1));
		else
			moveSpeed %= (2 * (R - 1));

		for (int j = 0; j < moveSpeed; ++j)
		{
			if (sharks[i].m_nPosX + xarr[moveDir] < 0
				|| sharks[i].m_nPosX + xarr[moveDir] >= R
				|| sharks[i].m_nPosY + yarr[moveDir] < 0
				|| sharks[i].m_nPosY + yarr[moveDir] >= C)
			{
				sharks[i].m_nDir = (sharks[i].m_nDir + 2) % 4;
				moveDir = sharks[i].m_nDir;
			}

			if (moveDir % 2)
				sharks[i].m_nPosY += yarr[moveDir];
			else
				sharks[i].m_nPosX += xarr[moveDir];
		}
	}
	// 상어끼리의 먹이싸움 체크
	vector<SHARK>::iterator iter;
	vector<SHARK>::iterator iterEnd = sharks.end();

	vector<SHARK>::iterator iter2;
	// vector<SHARK>::iterator iterEnd = sharks.end();

	for (iter = sharks.begin(); iter != (iterEnd - 1);)
	{
		// 기준 상어가 패배했는 지 확인
		bool bLose = false;

		// 기준 상어 스펙
		int tmpX = (*iter).m_nPosX;
		int tmpY = (*iter).m_nPosY;
		int tmpSize = (*iter).m_nSize;

		for (iter2 = iter + 1; iter2 != iterEnd;)
		{
			// 싸울 상어 스펙
			int tmp2X = (*iter2).m_nPosX;
			int tmp2Y = (*iter2).m_nPosY;
			int tmp2Size = (*iter2).m_nSize;

			// 위치가 같은 상어인 경우
			if (tmpX == tmp2X && tmpY == tmp2Y)
			{
				// 기준 상어가 이긴 경우
				if (tmpSize > tmp2Size)
				{
					iter2 = sharks.erase(iter2);
					iterEnd = sharks.end();
				}
				// 기준 상어가 진 경우
				else
				{
					iter = sharks.erase(iter);
					iterEnd = sharks.end();
					bLose = true;
					break;
				}
			}
			// 상관 없는 상어인 경우
			else
				++iter2;
		}

		if (!bLose) iter++;
	}
}

int main()
{
	scanf("%d %d %d", &R, &C, &M);
	if (M == 0)
	{
		puts("0");
		return 0;
	}

	for (int i = 0; i < M; ++i)
	{
		int r, c, s, d, z;
		scanf("%d %d %d %d %d", &r, &c, &s, &d, &z);

		if (d == 1) d = 0;
		else if (d == 2) d = 2;
		else if (d == 3) d = 3;
		else if (d == 4) d = 1;

		SHARK tmpS = { r - 1 , c - 1, s, d, z };
		sharks.push_back(tmpS);
	}

	for (int i = 0; i < C; ++i)
	{
		CheckShark();
		AnglerTurn(i);
		if (i == C - 1) break;
		if (bFlag) break;
		SharkMove();
	}
	printf("%d\n", nTotal);

	return 0;
}