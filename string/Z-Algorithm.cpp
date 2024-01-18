/*
    ZArray[i]-stores the length of longest common prefix between s and the suffix[i,l-1].
*/
#include<bits/stdc++.h>

using namespace std;

const int N=1e6;

vector<int>ans;
int ZArray[N+5];
string text,pattern,concatedStr;

void MakeZArray()
{
    int i,k,l,r,len=concatedStr.size();
    l=r=0;
    for(i=1; i<len; i++)
    {
        if(i > r)
        {
            l=r=i;
            while(r<len && concatedStr[r-l] == concatedStr[r])r++;
            ZArray[i]=r-l;
            r--;
        }
        else
        {
            k=i-l;
            if(ZArray[k] < r-i+1)ZArray[i]=ZArray[k];
            else
            {
                l=i;
                while(r < len  &&  concatedStr[r-l] == concatedStr[r])r++;
                ZArray[i]=r-l;
                r--;
            }
        }
    }
}

void SearchPatternInText()
{
    ans.clear();
    concatedStr=pattern+"$"+text;
    int i,check=pattern.size(),len=concatedStr.size();

    MakeZArray();

    for(i=0; i<len; i++)
    {
        if(ZArray[i] == check)ans.emplace_back(i-check);
    }
}

int main()
{
    int i,j,t,check;
    cin >> t;
    for(i=1; i<=t; i++)
    {
        cin >> text >> pattern;
        SearchPatternInText();
        check=ans.size();
        if(check == 0)cout << "Not Found" << endl;
        else
        {
            cout << check << '\n' << ans[0];
            for(j=1;j<check;j++)cout << ' ' << ans[j] ;
            cout << '\n';
        }
    }
    return 0;
}
