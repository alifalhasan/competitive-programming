#include<bits/stdc++.h>

using namespace std;

vector<int>oddPalindromes(string const& s)
{
    int i,j,l=0,r=-1,len=s.size();
    vector<int>v(len);
    for(i=0;i<len;i++)
    {
        if(i > r)j=1;
        else j=min(v[l+r-i],r-i+1);
        while(i-j >= 0  &&  i+j < len  &&  s[i-j] == s[i+j])j++;
        v[i]=j--;
        if(i+j > r)l=i-j,r=i+j;
    }
    return v;
}

vector<int>evenPalindromes(string const& s)
{
    int i,j,l=0,r=-1,len=s.size();
    vector<int>v(len);
    for(i=0;i<len;i++)
    {
        if(i > r)j=0;
        else j=min(v[l+r-i+1],r-i+1);
        while(i-j-1 >= 0  &&  i+j < len  &&  s[i-j-1] == s[i+j])j++;
        v[i]=j--;
        if(i+j > r)l=i-j-1,r=i+j;
    }
    return v;
}

int main()
{
    return 0;
}
