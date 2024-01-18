#include<bits/stdc++.h>

using namespace std;

string FindAns(string s)
{
    string res="";
    int i,j,len=0,index=0,l=(int)s.size(),ans[l+2][l+2];
    memset(ans,0,sizeof(ans));
    for(i=1; i<=l; i++)
    {
        for(j=i+1; j<=l; j++)
        {
            if(s[i-1] == s[j-1]  &&  ans[i-1][j-1] < (j-i))
            {
                ans[i][j]=ans[i-1][j-1]+1;
                if(ans[i][j] > len)
                {
                    len=ans[i][j];
                    index=max(i,index);
                }
            }
            else ans[i][j]=0;
        }
    }
    if(len > 0)
    {
        for(i=index-len+1;i<=index;i++)res+=(s[i-1]);
    }
    return res;
}

int main()
{
    string s;
    cin >> s;
    s=FindAns(s);
    cout << s.size();
    return 0;
}
