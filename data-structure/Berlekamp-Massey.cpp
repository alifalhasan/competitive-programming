//0 - indexed
//Complexity = m^2log(M)
//m = length of recurrence

#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int mod=1e9+7;

int m,a[N],h[N],s[N],t[N],t_[N];

long long BigMod(long long val,long long pow)
{
    long long res = 1;
    val = val % mod;
    while(pow > 0)
    {
        if(pow & 1)res = (res*val) % mod;
        pow = pow >> 1;
        val = (val*val) % mod;
    }
    return res;
}

vector<long long>BerlekampMassey(vector<long long>v)
{
    int i,j,l;
    long long k,ld,lf,t;
    vector<long long>cur,ls;
    l=(int)v.size();
    for(i=0; i<l; i++)
    {
        t=0;
        for(j=0; j<(int)cur.size(); j++)t=(t+cur[j]*v[i-j-1])%mod;
        if((t-v[i])%mod == 0)continue;
        if(!cur.size())
        {
            cur.resize(i+1);
            ld=(t-v[i])%mod,lf=i;
            continue;
        }
        k=(-(v[i]-t)*BigMod(ld,mod-2))%mod;
        vector<long long>c(i-lf-1);
        c.emplace_back(k);
        for(j=0; j<(int)ls.size(); j++)c.emplace_back((-ls[j]*k)%mod);

        if((int)c.size() < (int)cur.size())c.resize((int)cur.size());
        for(j=0; j<(int)cur.size(); j++)c[j]=(c[j]+cur[j])%mod;
        if(i-lf+(int)ls.size() >= (int)cur.size())ld=(t-v[i])%mod,lf=i,ls=cur;
        cur=c;
    }
    for(i=0; i<(int)cur.size(); i++)cur[i]=(cur[i]%mod+mod)%mod;
    return cur;
}

void Mul(int*p,int*q)
{
    int i,j;
    for(i=0; i<m+m; i++)t_[i]=0;
    for(i=0; i<m; i++)
    {
        if(p[i])
        {
            for(j=0; j<m; ++j)t_[i+j]=(t_[i+j]+1LL*p[i]*q[j])%mod;
        }
    }

    for(i=m+m-1; i>=m; i--)
    {
        if(t_[i])
        {
            for(j=m-1; ~j; j--)t_[i-j-1]=(t_[i-j-1]+t_[i]*h[j])%mod;
        }
    }
    for(i=0; i<m; ++i)p[i]=t_[i];
}

int Cal(int k)
{
    int i;
    for(i=m; ~i; --i)s[i]=t[i]=0;
    s[0]=1;
    if(m!=1)t[1]=1;
    else t[0]=h[0];
    while(k)
    {
        if(k&1)Mul(s,t);
        Mul(t,t);
        k >>= 1;
    }
    int su=0;
    for(i=0; i<m; i++)su=(su+s[i]*a[i])%mod;
    return (su%mod+mod)%mod;
}

void Work(vector<long long>x)//first element should be non zero
{
    vector<long long>v=BerlekampMassey(x);
    m=(int)v.size();
    for(int i=0; i<m; i++)h[i]=v[i],a[i]=x[i];
}

int main()
{
    return 0;
}
