/*
    1-based indexing
    http://adilet.org/blog/palindromic-tree/
    https://arxiv.org/pdf/1506.04862.pdf
    https://paste.ubuntu.com/p/qZzSgzT5FH/?fbclid=IwAR3BXxVm2lMiCk58IZsKiCbtJ2hgWC_xKSn1MwqKVf2vfMk5HoxBpNuN5Rw
*/
#include<bits/stdc++.h>

using namespace std;

const int N=1e5;

struct Data
{
    int len,occ,palSuffixes,rightIdx,suffixLink,next[26];
    //occ stores number of occurrence of this palindrome
    //palSuffixes stores number of palindromic suffixes end at this node
    //rightIdx stores the index of r in s of palindrome[l-r]

    ///for palindromic factorization
    int dif,serialLink;
    pair<int,int>seriesAns;
    Data()
    {
        dif=serialLink=0;
        len=occ=palSuffixes=0;
        seriesAns={INT_MAX,INT_MAX};
        memset(next,0,sizeof(next));
    }
};

char s[N+2];
Data tree[N+2];
pair<int,int>DP[N+2];
int maxSuffix,nodeNumber;
long long totalPalindrome;

void AddLetter(int idx)
{
    int curLetter=s[idx]-'a';
    int curPos=maxSuffix,curLen=0;
    while(true)
    {
        curLen=tree[curPos].len;
        if(idx-curLen-1 > 0  &&  s[idx-curLen-1] == s[idx])break;
        curPos=tree[curPos].suffixLink;
    }
    if(tree[curPos].next[curLetter])
    {
        maxSuffix=tree[curPos].next[curLetter];
        ++tree[maxSuffix].occ;
    }
    else
    {
        maxSuffix=++nodeNumber;
        tree[nodeNumber]=Data();
        tree[nodeNumber].occ++;
        tree[nodeNumber].rightIdx=idx;
        tree[nodeNumber].len=tree[curPos].len+2;
        tree[curPos].next[curLetter]=nodeNumber;
        if(tree[nodeNumber].len == 1)tree[nodeNumber].suffixLink=2;
        else
        {
            while(true)
            {
                curPos=tree[curPos].suffixLink;
                curLen=tree[curPos].len;
                if(idx-curLen-1 > 0  &&  s[idx-curLen-1] == s[idx])
                {
                    tree[nodeNumber].suffixLink=tree[curPos].next[curLetter];
                    break;
                }
            }
        }
        tree[nodeNumber].palSuffixes=tree[tree[nodeNumber].suffixLink].palSuffixes+1;
    ///Update stars for palindromic factorization
        int sLink=tree[nodeNumber].suffixLink;
        tree[nodeNumber].dif=tree[nodeNumber].len-tree[sLink].len;
        if(tree[nodeNumber].dif == tree[sLink].dif)tree[nodeNumber].serialLink=tree[sLink].serialLink;
        else tree[nodeNumber].serialLink=nodeNumber;
    }


    pair<int,int>val;
    int i,sfl,srl,slv;
    DP[idx]={1e9,1e9};
    for(i=maxSuffix;tree[i].len > 0;)
    {
        sfl=tree[i].suffixLink;
        srl=tree[i].serialLink;
        slv=tree[srl].suffixLink;
        tree[i].seriesAns=DP[idx-(tree[slv].len+tree[i].dif)];
        if(tree[i].dif == tree[sfl].dif)
        {
            tree[i].seriesAns.first=min(tree[i].seriesAns.first,tree[sfl].seriesAns.first);
            tree[i].seriesAns.second=min(tree[i].seriesAns.second,tree[sfl].seriesAns.second);
        }
        val=tree[i].seriesAns;
        DP[idx].first=min(DP[idx].first,val.second+1);
        DP[idx].second=min(DP[idx].second,val.first+1);
        i=slv;
    }
    ///Update ends for palindromic factorization
}

void CalculateTotalPalindrome()
{
    for(int i=nodeNumber;i>2;i--)
    {
        totalPalindrome+=tree[i].occ;
        tree[tree[i].suffixLink].occ+=tree[i].occ;
    }
}

void BuildPalindromicTree()
{
    DP[0]={1e9,0};
    maxSuffix=nodeNumber=2;
    tree[1]=Data(),tree[2]=Data();
    tree[1].len=-1,tree[1].suffixLink=1;
    tree[2].len=0,tree[2].suffixLink=1;
    int len=strlen(s+1);
    for(int i=1;i<=len;i++)AddLetter(i);
    CalculateTotalPalindrome();
}

int main()
{
    int i,j,t;
    scanf("%d",&t);
    for(i=1;i<=t;i++)
    {
        scanf("%s",s+1);
        for(j=1;j<=nodeNumber;j++)tree[j]=Data();
        BuildPalindromicTree();
        printf("Case #%d: %d\n",i,nodeNumber-2);
    }
    return 0;
}
