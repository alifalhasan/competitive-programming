/*
    0-based indexing
*/
#include<bits/stdc++.h>

using namespace std;

const int N=1e7;

int k,n;
long long a[N+1];

/********************Sum operation********************/

long long ans[N+1][25];

void Build()
{
   int i,j;
   k=log2(n)+1;
   for(i=0;i<n;i++)ans[i][0]=a[i];
   for(j=1;j<=k;j++)
   {
       for(i=0;i+(1 << j)<=n;i++)ans[i][j]=ans[i][j-1]+ans[i+(1 << (j-1))][j-1];
   }
}

long long Query(int l,int r)
{
    int j;
    long long sum=0;
    for(j=k;j>=0;j--)
    {
        if((1 << j) <= r-l+1)
        {
            sum+=ans[l][j];
            l+=(1 << j);
        }
    }
}

/********************Sum operation********************/

/********************Maximum operation********************/

int lg[N+1];

void Build()
{
   int i,j;
   lg[1]=0;
   k=log2(n)+1;
   for(i=0;i<n;i++)ans[i][0]=a[i];
   for(i=2;i<=n;i++)lg[i]=lg[i/2]+1;
   for(j=1;j<=k;j++)
   {
       for(i=0;i+(1 << j)<=n;i++)ans[i][j]=max(ans[i][j-1],ans[i+(1 << (j-1))][j-1]);
   }
}

long long Query(int l,int r)
{
    int j=lg[r-l+1];
    return max(ans[l][j],ans[r-(1 << j)+1][j]);
}

/********************Maximum operation********************/

int main()
{
    return 0;
}
