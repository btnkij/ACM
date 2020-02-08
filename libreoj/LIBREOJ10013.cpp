/**
* Number:loj10013
* Title:「一本通 1.2 例 3」曲线
* Status:AC
* Tag:[三分]
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
const double PI = acos(-1);
const double eps = 1e-10;
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int n;
double a[10010],b[10010],c[10010];
double f(double x)
{
    double ans=-1e100;
    repne(i,0,n)
        ans=max(ans, a[i]*x*x+b[i]*x+c[i]);
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        readi(n);
        repne(i,0,n)
        {
            scanf("%lf %lf %lf",a+i,b+i,c+i);
        }
        double lt=0, rt=1000;
        while(rt-lt>eps)
        {
            double mid1=(lt+rt)/2;
            double mid2=(mid1+rt)/2;
            if(f(mid1)>f(mid2))lt=mid1;
            else rt=mid2;
        }
        printf("%.4lf\n",f(lt));
    }
    return 0;
}