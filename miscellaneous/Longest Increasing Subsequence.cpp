#include<bits/stdc++.h>

using namespace std;

int len;
vector<int>v,ans;

int FindCeilIndex(int l,int r,int val)
{
    int m;
    while(r-l > 1)
    {
        m=l+((r-l) >> 1);
        if(ans[m] >= val)r=m;
        else l=m;
    }
    return r;
}

void FindLIS()
{
    if(v.empty())return;
    len=1;
    ans.emplace_back(v[0]);
    int i,l=(int)v.size();
    for(i=1; i<l; i++)
    {
        if(v[i] < ans[0])ans[0]=v[i];
        else if(v[i] > ans[len-1])
        {
            ans.emplace_back(v[i]);
            len++;
        }
        else if(v[i] != ans[len-1])ans[FindCeilIndex(-1,len-1,v[i])]=v[i];
    }
}

int main()
{
    int i,x;
    while(cin >> x)v.emplace_back(x);
    FindLIS();
    cout << len << "\n-\n";
    for(i=0; i<len; i++)cout << ans[i] << ' ';
    return 0;
}
