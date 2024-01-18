/*
    lps[i] is the length of the longest proper prefix of the substring s[0…i] which is also a suffix of this substring.
*/
#include<bits/stdc++.h>

using namespace std;

vector<int>pos;

void MakeLPSArray(string p,int lp,int lps[])
{
    int i=1,len=0;
    lps[0]=0;
    while(i < lp)
    {
        if(p[i] == p[len])
        {
            len++;
            lps[i]=len;
            i++;
        }
        else
        {
            if(len != 0)len=lps[len-1];
            else lps[i++]=0;
        }
    }
}

int KMPSearch(string t,string p)
{
    int lt=t.size(),lp=p.size();
    int lps[lp];

    MakeLPSArray(p,lp,lps);

    int i=0,j=0,cnt=0;
    while(i < lt)
    {
        if(p[j] == t[i])i++,j++;
        if(j == lp)
        {
            cnt++;
            pos.emplace_back(i-j+1);
            j=lps[j-1];
        }
        else if(i < lt  &&  p[j] != t[i])
        {
            if(j != 0)j=lps[j-1];
            else i++;
        }
    }
    return cnt;
}

int main()
{
    int i,j,t;
    cin >> t;
    string text,pattern;
    for(i=1; i<=t; i++)
    {
        pos.clear();
        cin >> text >> pattern;
        int ans=KMPSearch(text,pattern);
        if(ans == 0)printf("Not Found\n");
        else
        {
            printf("%d\n",ans);
            printf("%d",pos[0]);
            for(j=1; j<ans; j++)printf(" %d",pos[j]);
            printf("\n");
        }
    }
    return 0;
}
