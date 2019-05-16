#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>

using namespace std;

int n;

void Solution(char * str, int len)
{
	if (str[len - 1] == 'a')
		str[len] = 's';
	else if (str[len - 1] == 'i' || str[len - 1] == 'y')
	{
		// ios
		str[len - 1] = '\0';
		strcat(str, "ios");
	}
	else if (str[len - 1] == 'l')
		strcat(str, "es");
	else if (str[len - 1] == 'n')
	{
		str[len - 1] = '\0';
		strcat(str, "anes");
	}
	else if (str[len - 1] == 'e')
	{
		if (len - 2 >= 0 && str[len - 2] == 'n')
		{
			str[len - 1] = str[len - 2] = '\0';
			strcat(str, "anes");
		}
		else
			strcat(str, "us");
	}
	else if (str[len - 1] == 'o')
		strcat(str, "s");
	else if (str[len - 1] == 'r')
		strcat(str, "es");
	else if (str[len - 1] == 't')
		strcat(str, "as");
	else if (str[len - 1] == 'v')
		strcat(str, "es");
	else if (str[len - 1] == 'w')
		strcat(str, "as");
	else if (str[len - 1] == 'u')
		strcat(str, "s");
	else
		strcat(str, "us");
}

int main()
{
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
	{
		char cInput[32] = { 0 };
		scanf(" %s", cInput);
		int len = strlen(cInput);
		Solution(cInput, len);
		
		printf("%s\n", cInput);
	}

	return 0;
}