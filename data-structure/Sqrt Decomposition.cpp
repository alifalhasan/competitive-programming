/*
    0-indexing
    Always take a big block size
    https://assets.hkoi.org/training2019/sqrt.pdf
*/

#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int blockSize=4096;

int numOfBlocks,a[N],block[N/blockSize+2];

void PreProcess(const int& n)
{
    int i,blockIndex=-1;
    for(i=0;i<n;i++)
    {
        if(i%blockSize == 0)++blockIndex;
        block[blockIndex]+=a[i];
    }
    numOfBlocks=blockIndex;
}

void Update(int idx,int val)
{
    int blockNumber=idx/blockSize;
    block[blockNumber]+=val-a[idx];
    a[idx]=val;
}

int Query(int l,int r)
{
    int i,sum=0,blockL=l/blockSize,blockR=r/blockSize;
    if(blockL == blockR)
    {
        for(i=l;i<=r;i++)sum+=a[i];
    }
    else
    {
        for(i=l,l=(blockL+1)*blockSize-1;i<=l;i++)sum+=a[i];
        for(i=blockL+1;i<blockR;i++)sum+=block[i];
        for(i=blockR*blockSize;i<=r;i++)sum+=a[i];
    }
    return sum;
}

int main()
{
    int i,n;
    cin >> n;
    for(i=0;i<n;i++)cin >> a[i];
    PreProcess(n);
    cout << Query(3,8) << endl;
    cout << Query(1,6) << endl;
    Update(8,0);
    cout << Query(8,8) << endl;
    return 0;
}
