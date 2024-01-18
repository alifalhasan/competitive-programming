/*
    1-based indexing
    https://cp-algorithms.com/data_structures/treap.html
    https://tanujkhattar.wordpress.com/2016/01/10/treaps-one-tree-to-rule-em-all-part-1/
*/
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

/********************Treap********************/

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct Node
{
    int leftTree,rightTree,val,size,prior;
    void NewNode(int _val)
    {
        val=_val;
        size=1,prior=rnd();
        leftTree=rightTree=0;
    }
}treap[N];

int L,R,mid,root,availNode;

inline void Update(int node)
{
    if(node)
    {
        Node &cur=treap[node];
        Node &lt=treap[cur.leftTree];
        Node &rt=treap[cur.rightTree];

        cur.size=1+lt.size+rt.size;
    }
}

void SplitByValue(int node,int _val,int &l,int &r)
{
    if(!node)
    {
        l=r=0;
        return;
    }
    int &lt=treap[node].leftTree;
    int &rt=treap[node].rightTree;
    if(treap[node].val <= _val)
    {
        l=node;
        SplitByValue(rt,_val,rt,r);
    }
    else
    {
        r=node;
        SplitByValue(lt,_val,l,lt);
    }
    Update(node);
}

void SplitBySize(int node,int _size,int &l,int &r)
{
    if(!node)
    {
        l=r=0;
        return;
    }
    if(!_size)
    {
        l=0,r=node;
        return;
    }
    if(_size >= treap[node].size)
    {
        l=node,r=0;
        return;
    }
    int &lt=treap[node].leftTree;
    int &rt=treap[node].rightTree;
    if(treap[lt].size >= _size)
    {
        r=node;
        SplitBySize(lt,_size,l,lt);
    }
    else
    {
        l=node;
        SplitBySize(rt,_size-treap[lt].size-1,rt,r);
    }
    Update(node);
}

int Join(int &l,int &r)
{
    if(!l  ||  !r)return l ? l : r;
    Node &lt=treap[l];
    Node &rt=treap[r];
    if(lt.prior > rt.prior)
    {
        lt.rightTree=Join(lt.rightTree,r);
        Update(l);
        return l;
    }
    else
    {
        rt.leftTree=Join(l,rt.leftTree);
        Update(r);
        return r;
    }
}

void Inorder(int node)
{
    if(!node)return;
    Inorder(treap[node].leftTree);
    printf("%d ",treap[node].val);
    Inorder(treap[node].rightTree);
}

void Insert(int val)
{
    SplitByValue(root,val,L,R);
    treap[++availNode].NewNode(val);
    root=Join(L,availNode);
    root=Join(root,R);
}

void Delete(int val)
{
    SplitByValue(root,val,mid,R);
    SplitByValue(mid,val-1,L,mid);
    root=Join(L,R);
}

/********************Treap********************/

int main()
{
    return 0;
}
