/*
    Query->k-th smallest element,elements less than equal k and their sum.
    Complexity->O((n+q)log(maxVal))
*/

#include<bits/stdc++.h>

using namespace std;

const int N=1e6;

long long ans,sum[22][N+2];
int n,a[N+2],sorted[N+2],tree[22][N+2],link[22][N+2];

void Build(int l,int r,int lvl)
{
    if(l == r)return;
    int i,equalCnt=0,lessCnt=0,mid=(l+r) >> 1,lChild=l,rChild=mid+1;
    for(i=l;i<=r;i++)
    {
        if(tree[lvl][i] < sorted[mid])++lessCnt;
    }
    for(i=l;i<=r;i++)
    {
        if((tree[lvl][i] < sorted[mid])  ||  (tree[lvl][i] == sorted[mid]  &&  equalCnt < (mid-l-lessCnt+1)))
        {
            tree[lvl+1][lChild++]=tree[lvl][i];
            sum[lvl][i]=sum[lvl][i-1]+tree[lvl][i];
            if(tree[lvl][i] == sorted[mid])++equalCnt;
        }
        else
        {
            tree[lvl+1][rChild++]=tree[lvl][i];
            sum[lvl][i]=sum[lvl][i-1];
        }
        link[lvl][i]=link[lvl][l-1]+lChild-l;
    }
    Build(l,mid,lvl+1);
    Build(mid+1,r,lvl+1);
}

void BuildWaveletTree()
{
    for(int i=1;i<=n;i++)tree[0][i]=sorted[i]=a[i];
    sort(sorted+1,sorted+n+1);
    Build(1,n,0);
}

//ans stores the sum of  first k smallest elements
int kth(int start,int end,int curLvl,int l,int r,int k)
{
    if(start == end)
    {
        ans+=tree[curLvl][start];
        return tree[curLvl][start];
    }
    int cnt=link[curLvl][r]-link[curLvl][l-1],mid=(start+end) >> 1;
    if(cnt >= k)
    {
        int newL=link[curLvl][l-1]-link[curLvl][start-1];
        int newR=link[curLvl][r]-link[curLvl][start-1];
        return kth(start,mid,curLvl+1,start+newL,start+newR-1,k);
    }
    else
    {
        int newL=l-start-(link[curLvl][l-1]-link[curLvl][start-1]);
        int newR=r-start+1-(link[curLvl][r]-link[curLvl][start-1]);
        ans+=sum[curLvl][r]-sum[curLvl][l-1];
        return kth(mid+1,end,curLvl+1,mid+1+newL,mid+newR,k-cnt);
    }
}

//ans stores the sum of elements less equal k
int LessEqualK(int start,int end,int curLvl,int l,int r,int k)
{
    if(start == end)
    {
        if(start > r  ||  end < l)return 0;
        ans+=tree[curLvl][start]*(tree[curLvl][start] <= k);
        return tree[curLvl][start] <= k;
    }
    int cnt=link[curLvl][r]-link[curLvl][l-1],mid=(start+end) >> 1;
    if(sorted[mid] <= k)
    {
        ans+=sum[curLvl][r]-sum[curLvl][l-1];
        int newL=l-start-(link[curLvl][l-1]-link[curLvl][start-1]);
        int newR=r-start+1-(link[curLvl][r]-link[curLvl][start-1]);
        return cnt+LessEqualK(mid+1,end,curLvl+1,mid+1+newL,mid+newR,k);
    }
    else
    {
        int newL=link[curLvl][l-1]-link[curLvl][start-1];
        int newR=link[curLvl][r]-link[curLvl][start-1];
        return LessEqualK(start,mid,curLvl+1,start+newL,start+newR-1,k);
    }
}

int main()
{
    return 0;
}
