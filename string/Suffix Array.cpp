#include<bits/stdc++.h>

using namespace std;

const int N=1e5;

/********************Suffix Array Construction********************/

vector<int>SortCyclicShifts(string const& s)
{
    int i,n=s.size();
    const int alphabet=256;
    vector<int>p(n),c(n),cnt(max(alphabet,n),0);
    for(i=0;i<n;i++)++cnt[s[i]];
    for(i=1;i<alphabet;i++)cnt[i]+=cnt[i-1];
    for(i=1;i<n;i++)p[--cnt[s[i]]]=i;
    c[p[0]]=0;
    int classes=1;
    for(i=1;i<n;i++)
    {
        if(s[p[i]] != s[p[i-1]])++classes;
        c[p[i]]=classes-1;
    }
    vector<int>pn(n),cn(n);
    pair<int,int>cur,prev;
    for(int h=0;(1 << h)<n;h++)
    {
        for(i=0;i<n;i++)
        {
            pn[i]=p[i]-(1 << h);
            if(pn[i] < 0)pn[i]+=n;
        }
        fill(cnt.begin(),cnt.begin()+classes,0);
        for(i=0;i<n;i++)++cnt[c[pn[i]]];
        for(i=1;i<classes;i++)cnt[i]+=cnt[i-1];
        for(i=n-1;i>=0;i--)p[--cnt[c[pn[i]]]]=pn[i];
        cn[p[0]]=0;
        classes=1;
        for(i=1;i<n;i++)
        {
            cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<int>SuffixArrayConstruction(string s)
{
    s+="$";
    vector<int>sortedShifts=SortCyclicShifts(s);
    sortedShifts.erase(sortedShifts.begin());
    return sortedShifts;
}

/********************Suffix Array Construction********************/

/********************LCP Array Construction********************/

vector<pair<int,int>>queries;
int _rank[N+2],lg[N+2],minLCP[N+1][22];

vector<int>ConstructLCP(string const& s,vector<int> const& suffixArray)
{
    int i,j,k=0,l=s.size();
    for(i=0;i<l;i++)_rank[suffixArray[i]]=i;
    vector<int>lcp(l-1,0);
    for(i=0;i<l;i++)
    {
        if(_rank[i] == l-1)
        {
            k=0;
            continue;
        }
        j=suffixArray[_rank[i]+1];
        while(i+k < l  &&  j+k < l  &&  s[i+k] == s[j+k])++k;
        lcp[_rank[i]]=k;
        if(k)--k;
    }
    return lcp;
}

void BuildLCPTree(vector<int>const& lcpArray)
{
   int i,j,k,l=lcpArray.size();
   lg[1]=0;
   k=log2(l)+1;
   for(i=0;i<l;i++)minLCP[i][0]=lcpArray[i];
   for(i=2;i<=l;i++)lg[i]=lg[i/2]+1;
   for(j=1;j<=k;j++)
   {
       for(i=0;i+(1 << j)<=l;i++)minLCP[i][j]=min(minLCP[i][j-1],minLCP[i+(1 << (j-1))][j-1]);
   }
}

int LCPQuery(int l,int r)
{
    if(l > r)return INT_MAX;
    int j=lg[r-l+1];
    return min(minLCP[l][j],minLCP[r-(1 << j)+1][j]);
}

void SortSubstrings(string const& s,vector<int>const& lcpArray)
{
    BuildLCPTree(lcpArray);
    sort(queries.begin(),queries.end(),[&](pair<int,int>a,pair<int,int>b)
    {
        int x1=a.first,y1=a.second;
        int x2=b.first,y2=b.second;
        int x=min(_rank[x1],_rank[x2]);
        int y=max(_rank[x1],_rank[x2]);
        int lcp=LCPQuery(x,y-1);
        if(lcp >= y1-x1+1  &&  lcp >= y2-x2+1)
        {
            if(y1-x1 == y2-x2)return a < b;
            return y1-x1 < y2-x2;
        }
        else if(lcp >= y1-x1+1)return true;
        else if(lcp >= y2-x2+1)return false;
        return s[x1+lcp] <= s[x2+lcp];
    });
}

/********************LCP Array Construction********************/

/********************Longest Common Substring********************/

void LongestCommonSubstring(string const& s,string const& p)
{
    string ans="";
    int ls=s.size();
    vector<int>suffixArray=SuffixArrayConstruction(s+'#'+p);
    vector<int>lcpArray=ConstructLCP(s+'#'+p,suffixArray);
    int i,mx=0,sz=lcpArray.size();
    for(i=0;i<sz;i++)
    {
        if(suffixArray[i] < ls  &&  suffixArray[i+1] > ls)
        {
            if(lcpArray[i] == mx)ans=min(ans,s.substr(suffixArray[i],mx));
            else if(lcpArray[i] > mx)mx=lcpArray[i],ans=s.substr(suffixArray[i],mx);
        }
        else if(suffixArray[i] > ls  &&  suffixArray[i+1] < ls)
        {
            if(lcpArray[i] == mx)ans=min(ans,s.substr(suffixArray[i+1],mx));
            else if(lcpArray[i] > mx)mx=lcpArray[i],ans=s.substr(suffixArray[i+1],mx);
        }
    }
    cout << ans;
}

/********************Longest Common Substring********************/

/********************Searching p in s********************/

int Compare(string const& x,string const& y)
{
    if(x == y)return 0;
    if(x > y)return 1;
    return -1;
}

pair<int,int>FindString(string const& s,string const& p,vector<int>const& suffixArray)
{
    string temp;
    int l=0,r=-1,sz=suffixArray.size();
    int check,low,mid,high,ls=s.size(),lp=p.size();
    low=0,high=sz-1;
    while(low <= high)
    {
        mid=(low+high) >> 1;
        temp=s.substr(suffixArray[mid],min(lp,ls-suffixArray[mid]));
        check=Compare(temp,p);
        if(!check)
        {
            l=mid;
            high=mid-1;
        }
        else if(check > 0)high=mid-1;
        else low=mid+1;
    }
    low=0,high=sz-1;
    while(low <= high)
    {
        mid=(low+high) >> 1;
        temp=s.substr(suffixArray[mid],min(lp,ls-suffixArray[mid]));
        check=Compare(temp,p);
        if(!check)
        {
            r=mid;
            low=mid+1;
        }
        else if(check > 0)high=mid-1;
        else low=mid+1;
    }
    return {l,r};//suffixArray[l...r] are the indexes where p occurs
}

/********************Searching p in s********************/



int main()
{
    int n;
    string s,p;
    pair<int,int>ans;
    cin >> s;
    vector<int>suffixArray=SuffixArrayConstruction(s);
    vector<int>lcpArray=ConstructLCP(s,suffixArray);
    cin >> n;
    while(n--)
    {
        cin >> p;
        ans=FindString(s,p,suffixArray);
        cout << ans.second-ans.first+1 << '\n';
    }
    return 0;
}
