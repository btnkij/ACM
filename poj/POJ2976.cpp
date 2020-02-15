/**
* Number:poj2976
* Title:Dropping tests
* Status:AC
* Tag:[二分, 01分数规划]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=1010;
double a[MAXN],b[MAXN],d[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k;
    while(readi(n,k)!=EOF && (n|k))
    {
        repne(i,0,n)scanf("%lf",a+i);
        repne(i,0,n)scanf("%lf",b+i);
        double lt=0,rt=2;
        while(rt-lt>1e-6)
        {
            double mid=(lt+rt)/2;
            repne(i,0,n)d[i]=a[i]-mid*b[i];
            nth_element(d,d+k,d+n);
            if(accumulate(d+k,d+n,0.0)<0)rt=mid;
            else lt=mid;
        }
        printf("%d\n",(int)round(lt*100));
    }
    return 0;
}