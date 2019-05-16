#include <iostream>
#include <string>

using namespace std;

const int SIZE = 1010;
int n;
string dp[SIZE];

string Add(string& a, string& b)
{
	string strResult;

	int lenA = a.length();
	int lenB = b.length();
	int len = lenA > lenB ? lenA : lenB;

	int nA[SIZE] = { 0 };
	int nB[SIZE] = { 0 };
	int nResult[SIZE] = { 0 };

	for (int i = 0; i < lenA; ++i) nA[i] = a[lenA - 1 - i] - '0';
	for (int i = 0; i < lenB; ++i) nB[i] = b[lenB - 1 - i] - '0';

	for (int i = 0; i < len; ++i)
	{
		int nTmp = nA[i] + nB[i] + nB[i] + nResult[i];
		nResult[i] = nTmp % 10;
		nResult[i + 1] = nTmp / 10;
	}
	if (nResult[len] != 0) len++;

	for (int i = len - 1; i >= 0; i--)
		strResult += (nResult[i] + '0');
	
	return strResult;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	dp[0] = "1";
	dp[1] = "1";
	dp[2] = "3";

	for (int i = 3; i <= 255; ++i)
		dp[i] = Add(dp[i - 1], dp[i - 2]);

	while (true)
	{
		cin >> n;
		if (cin.fail() != false) break;

		cout << dp[n] << endl;
	}

	return 0;
}