#include<bits/stdc++.h>

using namespace std;

void EGCD(long long A,long long B,long long *X,long long *Y)
{
    int q,r,r1,r2,x,x1,x2,y,y1,y2;
    x1=y2=0;
    x2=y1=1;
    for(r2=A,r1=B;r1 != 0;r2=r1,r1=r,x2=x1,x1=x,y2=y1,y1=y)
    {
        q=r2/r1;
        r=r2%r1;
        x=x2-(q*x1);
        y=y2-(q*y1);
    }
    *X=x2,*Y=y2;
}

long long CRT(vector<long long>& A,vector<long long>& M)
{
    int i,l=A.size();
    long long a1=A[0],a2,g,m1=M[0],m2,p,q,x,mod;
    a1%=m1;
    for(i=1;i<l;i++)
    {
        a2=A[i],m2=M[i];
        g=__gcd(m1,m2);
        if(a1%g != a2%g)return -1;
        EGCD(m1/g,m2/g,&p,&q);
        mod=(m1/g)*m2;
        x=(((__int128)a1*(m2/g)%mod)*q%mod + ((__int128)a2*(m1/g)%mod)*p%mod) % mod;
        a1=x;
        if(a1 < 0)a1+=mod;
        m1=mod;
    }
    return a1;
}

int main()
{
    return 0;
}
