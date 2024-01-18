#include<bits/stdc++.h>

using namespace std;

int capacity,num_of_objects,weight[2005],value[2005],ans[2005][2005];

void KnapSack()
{
    int i,j;
    for(i=0;i<=num_of_objects;i++)
    {
        for(j=0;j<=capacity;j++)
        {
            if(i == 0  ||  j == 0)ans[i][j]=0;
            else if(weight[i] <= j)ans[i][j]=max(value[i] + ans[i-1][j-weight[i]],ans[i-1][j]);
            else ans[i][j]=ans[i-1][j];
        }
    }
}

int main()
{
    int i;
    scanf("%d %d",&capacity,&num_of_objects);
    for(i=1;i<=num_of_objects;i++)scanf("%d %d",&weight[i],&value[i]);
    KnapSack();
    printf("%d",ans[num_of_objects][capacity]);
    return 0;
}
