#include<bits/stdc++.h>

using namespace std;

const int N=1e6;

int a[N+2],node[4*N+2];

void Build(int nodeNum,int l,int r)
{
    if(l == r)
    {
        node[nodeNum]=a[l];
        return;
    }

    int mid=(l+r) >> 1;
    Build(2*nodeNum,l,mid);
    Build(2*nodeNum+1,mid+1,r);
    node[nodeNum]=min(node[2*nodeNum],node[2*nodeNum+1]);
}

void Update(int nodeNum,int start,int end,int pos,int x)
{
    if(start == end)
    {
        node[nodeNum]=x;
        return;
    }
    int mid=(start+end) >> 1;
    if(pos <= mid)Update(2*nodeNum,start,mid,pos,x);
    else Update(2*nodeNum+1,mid+1,end,pos,x);
    node[nodeNum]=min(node[2*nodeNum],node[2*nodeNum+1]);
}

int Query(int nodeNum,int start,int end,int l,int r)
{
    if(l == start  &&  r == end)return node[nodeNum];
    int mid=(start+end) >> 1;
    if(r <= mid)return Query(nodeNum*2,start,mid,l,r);
    if(mid < l)return Query(nodeNum*2+1,mid+1,end,l,r);
    return min(Query(nodeNum*2,start,mid,l,mid),Query(nodeNum*2+1,mid+1,end,mid+1,r));
}

int main()
{
    int i,n;
    printf("Please enter the number of elements : ");
    scanf("%d",&n);
    printf("Enter the elements : \n");
    for(i=1; i<=n; i++)
    {
        scanf("%d",&a[i]);
    }

    Build(1,1,n);

    int t,l,r,c,x;
    printf("Please enter the number of queries : ");
    scanf("%d",&t);
    while(t--)
    {
        printf("Please enter the number of changes : ");
        scanf("%d",&c);
        while(c--)
        {
            printf("Enter the  index number and new value : ");
            scanf("%d %d",&i,&x);

            Update(1,1,n,i,x);
        }

        printf("Please enter the left and right index number : ");
        scanf("%d %d",&l,&r);
        int min_ans=Query(1,1,n,l,r);
        printf("%d\n",min_ans);
    }
    return 0;
}

