/*
    Solves equation of form : Axy + Bx + Cy = D.
*/
#include<bits/stdc++.h>

using namespace std;

bool isValid(int a,int b,int c,int p,int div)
{
    if(((div-c)%a) != 0)return 0;///x=(div-c) / a
    if(((p-b*div)%(a*div)) != 0)return 0;///y=(p-b*div) / (a*div)
    return 1;
}

int HyperbolicDiophantine(int a,int b,int c,int d)
{
    int p=a*d+b*c;
    if(!p)///ad+bc=0
    {
        if(-c%a == 0)return -1;///Infinite solutions(-c/a,k)
        if(-b%a == 0)return -1;///Infinite solutions(k,-b/a)
        return 0;///No solution
    }
    else
    {
        int i,cnt=0,rt=sqrt(p);
        for(i=1;i<=rt;i++)
        {
            if(p%i == 0)
            {
                ///Check if divisors i,-i,p/i,-p/i produce valid solutions
                if(isValid(a,b,c,p,i))++cnt;
                if(isValid(a,b,c,p,-i))++cnt;
                if(p/i != i)
                {
                    if(isValid(a,b,c,p,p/i))++cnt;
                    if(isValid(a,b,c,p,-p/i))++cnt;
                }
            }
        }
        return cnt;
    }
}

int main()
{
    int A,B,C,D;
    cin >> A >> B >> C >> D;
    cout << HyperbolicDiophantine(A,B,C,D);
    return 0;
}
