#pragma GCC optimize("Ofast")

#include <map>
#include <set>
#include <cmath>
#include <deque>
#include <stack>
#include <queue>
#include <bitset>
#include <chrono>
#include <random>
#include <vector>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename temp>using ordered_set = tree<temp, null_type, less<temp>, rb_tree_tag,tree_order_statistics_node_update>;
//order_of_key (k) : Number of items strictly smaller than k .
//find_by_order(k) : K-th element in a set (counting from zero).//*(ost.find_by_order(k))


/// Unordered Map
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
unordered_map<long long, int, custom_hash> safe_map;


//int dx[]={-1,1,0,0};
//int dy[]={0,0,-1,1};
//int dx[]= {-1,0,1,-1,1,-1,0,1};
//int dy[]= {1,1,1,0,0,-1,-1,-1};



string sum_of_two_strings(string a,string b);
string division_of_string(string a,long long divisor);
string multiplication_of_two_strings(string s1,string s2);






int main()
{
//    freopen("input.txt","r",stdin);
//    freopen("output.txt","w",stdout);

    /// best random number generator
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int bestRand = uniform_int_distribution<int>(0, 10)(rng);

    return 0;
}

// To set stack size unlimited: ulimit -s unlimited
// To go to directory: cd /mnt/(drive_name)
// command line compile: g++ -o program program.cpp
// command line execute: ./program








long long BigMod(long long val,long long pow,long long mod)
{
    long long res = 1;
    val = val % mod;
    while(pow > 0)
    {
        if(pow & 1)res = (res*val) % mod;
        pow = pow >> 1;
        val = (val*val) % mod;
    }
    return res;
}

string sum_of_two_strings(string a,string b)
{
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    char c;
    string ans="";
    int length_of_a=(int)a.size(),length_of_b=(int)b.size();
    int i,carry=0,sum,length=max(length_of_a,length_of_b);
    for(i=0; i<length; i++)
    {
        if(i >= length_of_a)sum=(b[i]-48)+carry;
        else if(i >= length_of_b)sum=(a[i]-48)+carry;
        else sum=(a[i]-48)+(b[i]-48)+carry;
        carry=sum/10,sum%=10,c=sum+48,ans+=c;
    }
    if(carry > 0)ans+=(carry+48);
    reverse(ans.begin(),ans.end());
    return ans;
}

string division_of_string(string a,long long divisor)
{
    string ans="";
    int i=0,l=(int)a.size();
    long long temp=a[0]-'0';
    while(temp < divisor)temp=temp*10+(a[++i]-'0');
    while(i < l)
    {
        ans+=((temp/divisor)+'0');
        temp=(temp%divisor)*10+(a[++i]-'0');
    }
    if(!ans.size())return "0";
    return ans;
}

string multiplication_of_two_strings(string s1,string s2)
{
    if((s1[0] == '-'  ||  s2[0] == '-')  &&  (s1[0] != '-'  ||  s2[0] != '-'))cout << '-';
    if(s1[0] == '-')s1=s1.substr(1);
    if(s2[0] == '-')s2=s2.substr(1);
    int len1=s1.size();
    int len2=s2.size();
    if(len1 == 0  ||  len2 == 0)return "0";
    vector<int>result(len1+len2,0);
    int i,j,n1,n2,i_n1=0,i_n2=0,sum,carry;
    for(i=len1-1; i>=0; i--)
    {
        carry=0;
        n1=s1[i]-'0';
        i_n2=0;
        for(j=len2-1; j>=0; j--)
        {
            n2=s2[j]-'0';
            sum=n1*n2+result[i_n1+i_n2]+carry;
            carry=sum/10;
            result[i_n1+i_n2]=sum%10;
            i_n2++;
        }
        if(carry > 0)result[i_n1+i_n2]+=carry;
        i_n1++;
    }
    i=result.size()-1;
    while(i >= 0  &&  result[i] == 0)i--;
    if(i == -1)return "0";
    string s="";
    while(i >= 0)s+=(result[i--]+48);
    return s;
}
