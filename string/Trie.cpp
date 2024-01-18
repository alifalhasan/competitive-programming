/*

Some words are given.....

Then we have to search some query words if they are present in the given words.

*/



#include<bits/stdc++.h>

using namespace std;

struct Node
{

    int end,child[26];
    Node()
    {
        end=0;
        memset(child,-1,sizeof(child));
    }
};

int availNode;
Node tree[1000002];

void BuildTree(string s)
{
    int i,l=s.size(),check,current=0;
    for(i=0; i<l; i++)
    {
        check=s[i]-'a';
        if(tree[current].child[check] == -1)tree[current].child[check] = ++availNode;
        current=tree[current].child[check];
    }
    tree[current].end++;
}

bool Query(string s)
{
    int i,l=s.size(),check,current=0;
    for(i=0; i<l; i++)
    {
        check=s[i]-'a';
        if(tree[current].child[check] == -1)return 0;
        current=tree[current].child[check];
    }
    if(tree[current].end == 0)return 0;
    return 1;
}

int main()
{
    int i,m,n;
    string s;

    printf("Please enter the number of words : ");
    scanf("%d",&n);

    printf("Please enter the words : ");
    for(i=0; i<n; i++)
    {
        cin >> s;
        BuildTree(s);
    }

    printf("Please enter the number of queries : ");
    scanf("%d",&m);

    printf("Please enter the queries : ");
    for(i=0; i<m; i++)
    {
        cin >> s;
        if(Query(s) == 1)printf("Present\n");
        else printf("Absent\n");
    }
    return 0;
}
