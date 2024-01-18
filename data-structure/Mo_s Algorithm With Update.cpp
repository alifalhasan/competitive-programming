/*
    Editorial: https://codeforces.com/blog/entry/72690
*/

#include<bits/stdc++.h>

using namespace std;

const int M=3e5+5;

///Mo's part

const int magic = 2143;

int lastVal[M];
bool visited[M];

struct Query
{
    int id,l,r,updateCnt;
    Query() {}
    Query(int _l,int _r,int _id,int _updateCnt)
    {
        l=_l, r=_r, id=_id, updateCnt=_updateCnt;
    }
    bool operator < (const Query& q)
    {
        if(l/magic == q.l/magic)
        {
            if(r/magic == q.r/magic)return ((r/magic) & 1) ? (updateCnt > q.updateCnt) : (updateCnt < q.updateCnt);
            return r/magic < q.r/magic;
        }
        return l/magic < q.l/magic;
    }
} queries[M];

struct Update
{
    int id,prevVal,val;
    Update() {}
    Update(int _id,int _prevVal,int _val)
    {
        id=_id, prevVal=_prevVal, val=_val;
    }
} updates[M];

///Mo's part


int a[M],ans[M],curAns,freq[M];

void Increment(int x)
{
    ++freq[x];
    if(freq[x] == 1)++curAns;
}

void Decrement(int x)
{
    --freq[x];
    if(!freq[x])--curAns;
}

void Upd(int x)
{
    int y = a[x];
    if(!visited[x])Increment(y);
    else Decrement(y);
    visited[x] = 1-visited[x];
}

void Add(int i)
{
    int id=updates[i].id, x=updates[i].val;
    if(visited[id])Decrement(a[id]);
    a[id] = x;
    if(visited[id])Increment(a[id]);
}

void Delete(int i)
{
    int id=updates[i].id, x=updates[i].prevVal;
    if(visited[id])Decrement(a[id]);
    a[id] = x;
    if(visited[id])Increment(a[id]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i], lastVal[i]=a[i];
    int queryCnt=0, updateCnt=0;
    while(q--)
    {
        int t;cin >> t;
        if(t == 1)
        {
            int l,r;cin >> l >> r;
            ++queryCnt;
            queries[queryCnt] = Query(l, r, queryCnt, updateCnt);
        }
        else
        {
            int i,x; cin >> i >> x;
            updates[++updateCnt] = Update(i, lastVal[i], x);
            lastVal[i] = x;
        }
    }
    sort(queries+1, queries+queryCnt+1);

    int l=1, r=1, updatesProcessed=0;

    for(int i=1;i<=queryCnt;i++)
    {
        while(queries[i].updateCnt < updatesProcessed)Delete(updatesProcessed--);
        while(queries[i].updateCnt > updatesProcessed)Add(++updatesProcessed);
        while(queries[i].l < l)Upd(--l);
        while(queries[i].r >= r)Upd(r++);
        while(queries[i].l > l)Upd(l++);
        while(queries[i].r+1 < r)Upd(--r);

        ans[queries[i].id] = curAns;
    }

    for(int i=1;i<=queryCnt;i++)cout << ans[i] << '\n';
    return 0;
}
