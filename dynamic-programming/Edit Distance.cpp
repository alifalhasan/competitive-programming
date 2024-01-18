#include<bits/stdc++.h>

using namespace std;

const int N=5002;
int dp[N][N];
char a[N],b[N];

void PathPrint(const int& la,const int& lb)
{
    int i=la,j=lb,cnt=0;
    while(i > 0  ||  j > 0)
    {
        if(a[i] == b[j])i--,j--;
        else if(j  &&  dp[i][j] == dp[i][j-1]+1)
        {
            printf("%d ",++cnt);
            printf("Insert %d,%c\n",i+1,b[j]);
            j--;
        }
        else if(i  &&  j  &&  dp[i][j] == dp[i-1][j-1]+1)
        {
            printf("%d ",++cnt);
            printf("Replace %d,%c\n",i,b[j]);
            i--,j--;
        }
        else if(i  &&  dp[i][j] == dp[i-1][j]+1)
        {
            printf("%d ",++cnt);
            printf("Delete %d\n",i);
            i--;
        }
    }
}

int main()
{
    int i,j,la,lb;
    while(scanf("%s %s",a+1,b+1) == 2)
    {
        la=strlen(a+1);
        lb=strlen(b+1);
        for(i=1;i<=la;i++)dp[i][0]=i;
        for(i=1;i<=lb;i++)dp[0][i]=i;
        for(i=1;i<=la;i++)
            {
            for(j=1;j<=lb;j++)
            {
                if(a[i] == b[j])dp[i][j]=dp[i-1][j-1];
                else
                {
                    dp[i][j]=dp[i-1][j-1];
                    dp[i][j]=min(dp[i][j],dp[i-1][j]);
                    dp[i][j]=min(dp[i][j],dp[i][j-1]);
                    ++dp[i][j];
                }
            }
        }
        printf("%d\n",dp[la][lb]);
        PathPrint(la,lb);
    }
    return 0;
}
