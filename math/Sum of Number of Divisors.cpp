/*
    Gives sum of number of divisors from (1 - n)
*/
#include<bits/stdc++.h>

using namespace std;

long long SNOD(long long n)
{
    long long ans=0;
    int i,rt=sqrt(n);
    for(i=1;i<=rt;i++)ans+=(n/i)-i;
    ans*=2LL;
    ans+=rt;
    return ans;
}

int main()
{
    long long n;
    cin >> n;
    cout << SNOD(n);
}
