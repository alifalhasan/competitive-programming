#include<bits/stdc++.h>

using namespace std;

int EGCD(int A,int B,int *X,int *Y)
{
    int q,r,r1,r2,x,x1,x2,y,y1,y2;
    x1=y2=0;
    x2=y1=1;
    for(r2=A,r1=B;r1 != 0;r2=r1,r1=r,x2=x1,x1=x,y2=y1,y1=y)
    {
        q=r2/r1;
        r=r2%r1;
        x=x2-(q*x1);
        y=y2-(q*y1);
    }
    *X=x2,*Y=y2;
    return r2;
}

int main()
{
    return 0;
}
