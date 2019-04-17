#include <cstdio>

#define	SIZE	4000001
#define	P		1000000007

using namespace std;

typedef long long ll;
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

	if (n == 0 || k == 0 || n == k)
	{
		puts("1");
		return 0;
	}

	ll nParent = n;
	int nChildIndex = (n - k < k) ? n - k : k;
	ll nChild = nChildIndex;

	for (int i = 1; i < nChildIndex; ++i)
	{
		nParent = ((nParent % P) * (n - i)) % P;
		nChild = ((nChild % P) * (nChildIndex - i)) % P;
	}

	ll lastParent = pow(nChild, P - 2) % P;
	printf("%lld\n", (nParent * lastParent) % P);

	return 0;
}
