#include<bits/stdc++.h>

using namespace std;

/*
to insert one more string make sam.last=0 before every string insertion.
if(aut[aut[i].link].len<aut[i].len)then state i is unique.
sort the suffix with their dfs timing order in prefix tree
number of substring ending at state i = (len of i - len of i.link)*occur[i]
*/

const int N = 1e5+5;

struct SuffixAutomata
{
    vector<int>tree[N+N];
    int sz,last,occur[N+N],ent[N+N];
    int sp[N+N][20],tim,lev[N];
    long long pathCnt[N+N];//numbers of path starting from state i
    struct node
    {
        int len,link,next[26];
    } aut[N+N]; //2*insert function call
    void Clean(int n=N)//must call before insert
    {
        for(int i=0; i<=n+n; i++)
        {
            tree[i].clear();
            tim=pathCnt[i]=0;
            memset(aut[i].next,0,sizeof(aut[i].next));
        }
        sz=last=0,aut[0].link=-1;
    }
    int Con(char c)//check for word size
    {
        return c-'a';
    }
    void Insert(int c)
    {
        int now=++sz;
        aut[now].len=aut[last].len+1;
        occur[now]=1;
        int p,q,cl;
        for(p=last; p!=-1&&!aut[p].next[c]; p=aut[p].link)aut[p].next[c]=now;
        if(p==-1)aut[now].link=0;
        else
        {
            q=aut[p].next[c];
            if(aut[p].len+1==aut[q].len)aut[now].link=q;
            else
            {
                cl=++sz;
                aut[cl].len=aut[p].len+1;
                aut[cl].link=aut[q].link;
                memcpy(aut[cl].next,aut[q].next,sizeof(aut[cl].next));//for array
                //aut[cl].next=aut[q].next;//for map
                for( ; p!=-1&&aut[p].next[c]==q; p=aut[p].link)aut[p].next[c]=cl;
                aut[now].link=aut[q].link=cl;
            }
        }
        last=now;
    }
    void Insert(string s)
    {
        for(auto x:s)Insert(Con(x));
    }
    void DFS(int nd,int lv)
    {
        ent[nd]=++tim;
        lev[nd]=lv;
        for(auto x:tree[nd])DFS(x,lv+1);
    }
    void MakeTree()
    {
        for(int i=1; i<=sz; i++)
        {
            tree[aut[i].link].emplace_back(i);
            sp[i][0]=aut[i].link;
        }
        for(int j=1; j<=17; j++)
        {
            for(int i=1; i<=sz; i++)sp[i][j]=sp[sp[i][j-1]][j-1];
        }
        DFS(0,0);
    }
    int LCP(int u,int v)
    {
        //u v are automata state. to get lcp of two suffix store the state number
        if(lev[u]<lev[v])swap(u,v);
        for(int i=17; i>=0; i--)
        {
            if(lev[u]-(1<<i)>=lev[v])u=sp[u][i];
        }
        if(u==v)return aut[u].len;
        for(int i=17; i>=0; i--)
        {
            if(sp[u][i]==-1||sp[v][i]==-1)continue;
            if(sp[u][i]==sp[v][i])continue;
            u=sp[u][i],v=sp[v][i];
        }
        return aut[aut[u].link].len;
    }
    //number of occurrences for every state;
    void Occurences(int n)//n=string size;
    {
        vector<vector<int> >vLen(n+2);
        for(int i=1; i<=sz; i++)vLen[aut[i].len].emplace_back(i);
        for(int i=n; i>=1; i--)
            for(auto x:vLen[i])occur[aut[x].link]+=occur[x];
    }
    long long CountPath(int now)
    {
        if(pathCnt[now])return pathCnt[now];
        pathCnt[now]=(bool)now;
        for(int i=0; i<26; i++) //word size
            if(aut[now].next[i])pathCnt[now]+=CountPath(aut[now].next[i]);
        return pathCnt[now];
    }
    string Kth(long long k)
    {
        string ans;
        int now=0;
        if(k > pathCnt[0])return ans;
        while(k)
        {
            for(int i=0; i<26; i++)
            {
                if(!aut[now].next[i])continue;
                int nx=aut[now].next[i];
                if(pathCnt[nx]>=k)
                {
                    ans+=((char)(i+'a'));
                    k--,now=nx;
                    break;
                }
                else k-=pathCnt[nx];
            }
        }
        return ans;
    }
    int LongestCommonSubstring(string s)
    {
        int now=0,len=0,mx=0;
        for(char x:s)
        {
            int c=Con(x),p;
            if(aut[now].next[c])len++,now=aut[now].next[c];
            else
            {
                for(p=now; p!=-1&&!aut[p].next[c]; p=aut[p].link);
                if(p==-1)now=0,len=0;
                else len=aut[p].len+1,now=aut[p].next[c];
            }
            if(len>mx)mx=len;
        }
        return mx;
    }
};

int main()
{
    return 0;
}
