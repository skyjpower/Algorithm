/*
	<페르마 소정리>
	a^p 에서 p가 소수이면서 a가 p의 배수가 아니라면,
	a^(p - 1) % p = 1
	
	* 거듭 제곱은 분할 정복으로
*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define SIZE 4000001
#define P 1000000007LL

using namespace std;
typedef long long ll;

ll factorial[SIZE] = { 0 };
ll inverse[SIZE] = { 0 };
ll n, k;

ll pow(ll a, ll b)
{
	ll ret = 1;

	while (b > 0)
	{
		if (b % 2)
		{
			ret *= a;
			ret %= P;
		}
		a *= a;
		a %= P;
		b /= 2;
	}

	return ret;
}

int main()
{
	scanf("%lld %lld", &n, &k);

	// factorial
	factorial[0] = 1;
	for (int i = 1; i < SIZE; ++i)
		factorial[i] = (factorial[i - 1] * i) % P;

	// inverse
	inverse[SIZE - 1] = pow(factorial[SIZE - 1], P - 2);
	for (int i = SIZE - 2; i >= 0; --i)
		inverse[i] = (inverse[i + 1] * (i + 1)) % P;

	ll result = (factorial[n] * inverse[k]) % P;
	result = (result * inverse[n - k]) % P;

	printf("%lld\n", result);

	return 0;
}
