#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#define SIZE 110

using namespace std;

typedef struct _tagShark
{
	int m_nPosX; // ��ġx
	int m_nPosY; // ��ġy
	int m_nSpeed; // ���ǵ�
	int m_nDir; // ����
	int m_nSize; // ũ��

}SHARK, *PSHARK;

int R, C, M;
int aMap[SIZE][SIZE];
vector<SHARK> sharks;
int nTotal = 0;
int xarr[4] = { -1,0,1,0 };
int yarr[4] = { 0,-1,0,1 };

bool bFlag = false;

// ��� ��ġ üũ
void CheckShark()
{
	int vSize = sharks.size();

	for (int i = 0; i < vSize; ++i)
		aMap[sharks[i].m_nPosX][sharks[i].m_nPosY] = 1;
}

// ����
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
			// ���� ��� Ž��
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

// ��� ������
void SharkMove()
{
	int vSize = sharks.size();

	// ���� �ʿ� üũ�� ����� ��ġ �ʱ�ȭ
	for (int i = 0; i < vSize; ++i)
		aMap[sharks[i].m_nPosX][sharks[i].m_nPosY] = 0;

	// ��� ������
	for (int i = 0; i < vSize; ++i)
	{
		int moveSpeed = sharks[i].m_nSpeed;
		int moveDir = sharks[i].m_nDir;

		// �¿�
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
	// ������ ���̽ο� üũ
	vector<SHARK>::iterator iter;
	vector<SHARK>::iterator iterEnd = sharks.end();

	vector<SHARK>::iterator iter2;
	// vector<SHARK>::iterator iterEnd = sharks.end();

	for (iter = sharks.begin(); iter != (iterEnd - 1);)
	{
		// ���� �� �й��ߴ� �� Ȯ��
		bool bLose = false;

		// ���� ��� ����
		int tmpX = (*iter).m_nPosX;
		int tmpY = (*iter).m_nPosY;
		int tmpSize = (*iter).m_nSize;

		for (iter2 = iter + 1; iter2 != iterEnd;)
		{
			// �ο� ��� ����
			int tmp2X = (*iter2).m_nPosX;
			int tmp2Y = (*iter2).m_nPosY;
			int tmp2Size = (*iter2).m_nSize;

			// ��ġ�� ���� ����� ���
			if (tmpX == tmp2X && tmpY == tmp2Y)
			{
				// ���� �� �̱� ���
				if (tmpSize > tmp2Size)
				{
					iter2 = sharks.erase(iter2);
					iterEnd = sharks.end();
				}
				// ���� �� �� ���
				else
				{
					iter = sharks.erase(iter);
					iterEnd = sharks.end();
					bLose = true;
					break;
				}
			}
			// ��� ���� ����� ���
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