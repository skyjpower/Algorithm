#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <memory.h>
#include <algorithm>

#define SIZE 110

using namespace std;

int aMap[SIZE][SIZE] = { 0 };
int r, c, k;
int rSize = 3, cSize = 3;

class CNODE
{
public:
	int m_nNum;
	int m_nCount;

public:
	CNODE(){}
	~CNODE(){}

public:
	bool operator < (const CNODE &cNode)	const
	{
		if (m_nCount < cNode.m_nCount) return true;
		else if (m_nCount == cNode.m_nCount) return m_nNum < cNode.m_nNum;
		else return false;
	}
};

void RowOperation(int nRow)
{
	bool check[SIZE] = { 0 };
	vector<CNODE> v;

	//v.resize(rSize);
	for (int i = 0; i < rSize; ++i)
	{
		if (check[i] || aMap[nRow][i] == 0) continue;
		CNODE tmpNode;
		tmpNode.m_nNum = aMap[nRow][i];
		tmpNode.m_nCount = 1;
		for (int j = i + 1; j < rSize; ++j)
		{
			if (aMap[nRow][i] == aMap[nRow][j])
			{
				tmpNode.m_nCount++;
				check[j] = true;
			}
		}
		v.push_back(tmpNode);
	}
	sort(v.begin(), v.end());
	int vSize = v.size();
	if (vSize * 2 >= rSize)
	{
		if (vSize > 50) vSize = 50;
		rSize = vSize * 2;

		int nTmp = 0;
		for (int i = 0; i < vSize; ++i)
		{
			aMap[nRow][nTmp++] = v[i].m_nNum;		
			aMap[nRow][nTmp++] = v[i].m_nCount;
		}
	}
	else
	{
		int nIndex = vSize * 2;
		int nTmp = 0;
		for (int i = 0; i < vSize; ++i)
		{
			aMap[nRow][nTmp++] = v[i].m_nNum;
			aMap[nRow][nTmp++] = v[i].m_nCount;
		}
		for (int i = nIndex; i < rSize; ++i) aMap[nRow][i] = 0;
	}		
}

void ColOperation(int nCol)
{
	bool check[SIZE] = { 0 };
	vector<CNODE> v;

	//v.resize(cSize);
	for (int i = 0; i < cSize; ++i)
	{
		if (check[i] || aMap[i][nCol] == 0) continue;
		CNODE tmpNode;
		tmpNode.m_nNum = aMap[i][nCol];
		tmpNode.m_nCount = 1;
		for (int j = i + 1; j < cSize; ++j)
		{
			if (aMap[i][nCol] == aMap[j][nCol])
			{
				tmpNode.m_nCount++;
				check[j] = true;
			}
		}
		v.push_back(tmpNode);
	}
	sort(v.begin(), v.end());
	int vSize = v.size();
	if (vSize * 2 >= cSize)
	{
		if (vSize > 50) vSize = 50;
		cSize = vSize * 2;

		int nTmp = 0;
		for (int i = 0; i < vSize; ++i)
		{
			aMap[nTmp++][nCol] = v[i].m_nNum;
			aMap[nTmp++][nCol] = v[i].m_nCount;
		}
	}
	else
	{
		int nIndex = vSize * 2;

		int nTmp = 0;
		for (int i = 0; i < vSize; ++i)
		{
			aMap[nTmp++][nCol] = v[i].m_nNum;
			aMap[nTmp++][nCol] = v[i].m_nCount;
		}
		for (int i = nIndex; i < cSize; ++i) aMap[i][nCol] = 0;
	}
}

int main()
{
	int nTotal = 0;
	scanf("%d %d %d", &r, &c, &k);
	for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) scanf("%d", &aMap[i][j]);

	while(1)
	{
		if (aMap[r - 1][c - 1] == k)
			break;

		if (rSize <= cSize)
		{
			for (int i = 0; i < cSize; ++i)
				RowOperation(i);
		}
		else
		{
			for (int i = 0; i < rSize; ++i)
				ColOperation(i);
		}

		if (++nTotal >= 100)
			break;
	}
	
	if (aMap[r - 1][c - 1] != k)
		puts("-1");
	else
		printf("%d\n", nTotal);

	return 0;
}