// Complexity : |Text| + Sum of all |Pattern| + O(number of Occurrences)
// if occurrence positions needed, Worst Case Complexity : (SumLen) Root (SumLen)

#include<bits/stdc++.h>

using namespace std;

const int MAXT = 1000005;      // Length of Text
const int MAXQ = 1000005;      // Number of Patterns
const int MAXP = 1000005;      // Sun of all |Pattern|

map<char,int>Next[MAXP];
int Link[MAXP];                // failure links
int Len[MAXQ];                 // Len[i] = length of i-th pattern
vector<int>End[MAXP];          // End[i] = indices of patterns those end in node i
vector<int> edgeLink[MAXP];
vector<int> perNodeText[MAXP];
int Time,Root,numberOfNodes,euler[MAXT],in[MAXQ],out[MAXQ];

void Clear(int node)
{
    End[node].clear();
    Next[node].clear();
    edgeLink[node].clear();
    perNodeText[node].clear();
}

void Init()
{
    Time = 0;
    Root = numberOfNodes = 0;
    Clear(Root);
}

void InsertWord(string s,int idx)
{
    int now = Root;
    int len = Len[idx] = s.size();
    for(int i=0; i<len; i++)
    {
        if(!Next[now][s[i]])
        {
            Next[now][s[i]] = ++numberOfNodes;
            Clear(numberOfNodes);
        }
        now = Next[now][s[i]];
    }
    End[now].emplace_back(idx);
}

void PushLinks()
{
    char ch;
    int j,u,v;
    queue<int> q;
    Link[0] = -1;
    q.push(0);
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        for(auto edge : Next[u])
        {
            ch = edge.first;
            v = edge.second;
            j = Link[u];

            while(j != -1 && !Next[j][ch]) j = Link[j];
            if(j != -1) Link[v] = Next[j][ch];
            else Link[v] = 0;

            q.push(v);
            edgeLink[Link[v]].emplace_back(v);
        }
    }
}

void Traverse(string s)
{
    int now = Root;
    int len = s.size();
    for(int i = 0; i < len; i++)
    {
        while(now != -1 && !Next[now][s[i]]) now = Link[now];
        if(now!=-1) now = Next[now][s[i]];
        else now = 0;
        perNodeText[now].emplace_back(i+1);  // using 1 based indexing for text indices
    }
}

// After dfs, the occurence of ith query string will be the count of
// all the occurrence of the subtree under the endNode of ith string
void DFS(int pos)
{
    for(int q : End[pos]) in[q] = Time + 1;
    for(int val : perNodeText[pos]) euler[++Time] = val;
    for(int to : edgeLink[pos])DFS(to);
    for(int q : End[pos]) out[q] = Time;
}

int main()
{
    int i,n;
    string s,p;
    Init();
    cin >> n;
    for(i=1;i<=n;i++)
    {
        cin >> p;
        InsertWord(p,i);
    }
    cin >> s;
    PushLinks();
    Traverse(s);
    DFS(Root);
    return 0;
}
