#include<bits/stdc++.h>

using namespace std;

const int N=2e3+5;

int m,n;
char s[N][N];

int ZeroSubmatrix()
{
    int i,j,ans=0;
    stack<int>stk;
    vector<int>d(m,-1),d1(m),d2(m);
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(s[i][j] == '1')d[j]=i;
        }
        while(!stk.empty())stk.pop();
        for(j=0;j<m;j++)
        {
            while(!stk.empty()  &&  d[stk.top()] <= d[j])stk.pop();
            if(stk.empty())d1[j]=-1;
            else d1[j]=stk.top();
            stk.emplace(j);
        }
        while(!stk.empty())stk.pop();
        for(j=m-1;j>=0;j--)
        {
            while(!stk.empty()  &&  d[stk.top()] <= d[j])stk.pop();
            if(stk.empty())d2[j]=m;
            else d2[j]=stk.top();
            stk.emplace(j);
        }
        for(j=0;j<m;j++)ans=max(ans,(i-d[j])*(d2[j]-d1[j]-1));
    }
    return ans;
}

int main()
{
    int i,t,tc;
    scanf("%d",&t);
    for(tc=1;tc<=t;tc++)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)scanf("%s",s[i]);
        printf("Case %d: %d\n",tc,ZeroSubmatrix());
    }
    return 0;
}
