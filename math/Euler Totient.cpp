/*
    number of all numbers i where 1<=i<=N and GCD(i,N)<=X.
*/
#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
int lp;
bool mark[N];
long long sum[N];
vector<int>primes;

void Sieve()
{
    int i,j,rt=1e3;
    primes.emplace_back(2);
    for(i=3;i<N;i+=2)
    {
        if(!mark[i])
        {
            primes.emplace_back(i);
            if(i < rt)
            {
                for(j=i*i;j<N;j+=2*i)mark[j]=1;
            }
        }
    }
    lp=primes.size();
}

void FindDivisors(long long const& n,vector<long long>&v)
{
    int i,rt=sqrt(n);
    for(i=1;i<rt;i++)
    {
        if(n%i == 0)
        {
            v.emplace_back(i);
            v.emplace_back(n/i);
        }
    }
    if(n%rt == 0)
    {
        v.emplace_back(rt);
        if(n/rt != rt)v.emplace_back(n/rt);
    }
    sort(v.begin(),v.end());
}

long long Phi(long long n)
{
    int i,x,rt=sqrt(n);
    long long ans=n;
    for(i=0;i<lp  &&  primes[i]<=rt;i++)
    {
        x=primes[i];
        if(n%x == 0)
        {
            while(n%x == 0)n/=x;
            rt=sqrt(n);
            ans/=x;
            ans*=(x-1);
        }
    }
    if(n > 1)
    {
        ans/=n;
        ans*=(n-1);
    }
    return ans;
}

int main()
{
    int i,j,l,t,q;
    long long n,x;
    Sieve();
    scanf("%d",&t);
    for(i=1;i<=t;i++)
    {
        scanf("%lld %d",&n,&q);
        printf("Case %d\n",i);
        vector<long long>divisors;
        FindDivisors(n,divisors);
        l=divisors.size();
        for(j=0;j<l;j++)sum[j+1]=sum[j]+Phi(n/divisors[j]);
        while(q--)
        {
            scanf("%lld",&x);
            auto it=upper_bound(divisors.begin(),divisors.end(),x)-divisors.begin();
            printf("%lld\n",sum[it]);
        }
    }
    return 0;
}
