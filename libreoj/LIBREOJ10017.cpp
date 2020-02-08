/**
* Number:loj10017
* Title:「一本通 1.2 练习 4」传送带
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
#define PI acos(-1)
const double eps = 1e-8;
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

inline double dis(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double ax,ay,bx,by,cx,cy,dx,dy;
double p,q,r;
inline double calc(double x1, double y1)
{
    double x2l=cx, x2r=dx, y2l=cy, y2r=dy;
    while(fabs(x2l-x2r)>eps || fabs(y2l-y2r)>eps)
    {
        double x2ml=(x2l+x2r)/2, x2mr=(x2ml+x2r)/2;
        double y2ml=(y2l+y2r)/2, y2mr=(y2ml+y2r)/2;
        double tl=dis(x1,y1,x2ml,y2ml)/r+dis(x2ml,y2ml,dx,dy)/q;
        double tr=dis(x1,y1,x2mr,y2mr)/r+dis(x2mr,y2mr,dx,dy)/q;
        if(tl<tr)x2r=x2mr, y2r=y2mr;
        else x2l=x2ml, y2l=y2ml;
    }
    return dis(ax,ay,x1,y1)/p+dis(x1,y1,x2l,y2l)/r+dis(x2l,y2l,dx,dy)/q;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    cin>>ax>>ay>>bx>>by;
    cin>>cx>>cy>>dx>>dy;
    cin>>p>>q>>r;
    double x1l=ax, x1r=bx, y1l=ay, y1r=by;
    while(fabs(x1l-x1r)>eps || fabs(y1l-y1r)>eps)
    {
        double x1ml=(x1l+x1r)/2, x1mr=(x1ml+x1r)/2;
        double y1ml=(y1l+y1r)/2, y1mr=(y1ml+y1r)/2;
        double tl=calc(x1ml, y1ml);
        double tr=calc(x1mr, y1mr);
        if(tl<tr)x1r=x1mr, y1r=y1mr;
        else x1l=x1ml, y1l=y1ml;
    }
    printf("%.2lf", calc(x1l,y1l));
    return 0;
}