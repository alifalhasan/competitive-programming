// Returns minimum x for which a ^ x % m = b % m.

#include<bits/stdc++.h>

using namespace std;

int DiscreteLog(int a,int b,int m)
{
    a%=m,b%=m;
    int g,k=1,add=0;
    while((g=__gcd(a,m)) > 1)
    {
        if(b == k)return add;
        if(b%g)return -1;
        b/=g,m/=g,++add;
        k=(1ll*k*(a/g))%m;
    }
    int an=1,n=sqrt(m)+1;
    for(int i=0;i<n;i++)an=(1ll*a*an)%m;
    unordered_map<int,int>vals;
    for(int q=0,cur=b;q<=n;q++)
    {
        vals[cur]=q;
        cur=(1ll*a*cur)%m;
    }
    for(int p=1,cur=k;p<=n;p++)
    {
        cur=(1ll*an*cur)%m;
        if(vals.count(cur))return (n*p-vals[cur]+add);
    }
    return -1;
}

int main()
{
    return 0;
}
