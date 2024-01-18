#include<bits/stdc++.h>

using namespace std;

unsigned long long power(__int128 a,__int128 n,__int128 p)
{
    __int128 res=1;
    a=a%p;

    while (n > 0)
    {
        if (n & 1)res = (res*a) % p;
        n = n>>1;
        a = (a*a) % p;
    }
    return res;
}

bool isPrime(unsigned long long n, int k)
{
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
    while (k>0)
    {
        unsigned long long a = 2 + rand()%(n-4);
        if (power(a, n-1, n) != 1)return false;
        k--;
    }
    return true;
}

int main()
{
    int k = 50;
    int t;
    long long x;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld",&x);
        isPrime(x, k)?  cout << "YES\n": cout << "NO\n";
    }
    return 0;
}
