/**
* Number:hdu5753
* Title:Permutation Bo 
* Status:AC
* Tag:[排列组合]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF)
    {
        double ans=0,c;
        double prob1=0,prob2=0;
        if(n==1)
        {
            scanf("%lf",&c);
            ans=c;
        }
        else if(n==2)
        {
            rep(i,2,n)prob1+=(i-1);
            prob1/=n*(n-1);
            rep(i,1,n)
            {
                scanf("%lf",&c);
                ans+=prob1*c;
            }
        }
        else
        {
            rep(i,2,n)prob1+=(i-1);
            prob1/=n*(n-1);
            rep(i,3,n)prob2+=(i-1)*(i-2);
            prob2/=n*(n-1)*(n-2);
            rep(i,1,n)
            {
                scanf("%lf",&c);
                if(i==1 || i==n)ans+=prob1*c;
                else ans+=prob2*c;
            }
        }
        printf("%.6lf\n",ans);
    }
    return 0;
}