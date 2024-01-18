/*
    Transcending property: Given two functions f(x),g(x) of that type,
                           if f(t) is greater than/smaller than g(t) for some x=t,
                           then f(x) will be greater than/smaller than g(x) for x>t.
                           In other words, once f(x) “win/lose” g(x),
                           f(x) will continue to “win/lose” g(x).
*/
#include<bits/stdc++.h>

using namespace std;

struct LiChaoTree
{
    const static int MAX = 1e5 + 5;
    struct Poly
    {
        long long a,b,c,d=1e9; ///Change values accordingly for min/max;
        long long Get(long long x)
        {
            return a*x*x*x + b*x*x + c*x + d;
        }
    } segTree[4*MAX];

    void Build(int l, int r, int nodeNum = 0)
    {
        segTree[nodeNum] = Poly();
        if(l+1 == r)return;
        int m=(l+r) >> 1;
        Build(l,m,2*nodeNum+1), Build(m,r,2*nodeNum+2);
    }

    void Insert(int l,int r,Poly poly,int nodeNum = 0)
    {
        if(l+1 == r)
        {
            if(poly.Get(l) < segTree[nodeNum].Get(l))segTree[nodeNum] = poly;
            return;
        }
        int mid = (l+r) >> 1;
        bool b1 = (poly.Get(mid) < segTree[nodeNum].Get(mid));
        bool b2 = (poly.Get(l) < segTree[nodeNum].Get(l));

        if(b1)swap(poly, segTree[nodeNum]);

        if(b1 != b2)Insert(l, mid, poly, 2*nodeNum+1);
        else Insert(mid, r, poly, 2*nodeNum+2);
    }

    long long Query(int l, int r, int x, int nodeNum = 0)
    {
        if(l+1 == r)return segTree[nodeNum].Get(x);
        int mid = (l+r) >> 1;
        if(x < mid)return min(segTree[nodeNum].Get(x), Query(l, mid, x, 2*nodeNum+1));
        else return min(segTree[nodeNum].Get(x), Query(mid, r, x, 2*nodeNum+2));
    }
} lcTree;

int main()
{
    return 0;
}
