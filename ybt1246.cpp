/**
* Number:ybt1246
* Title:膨胀的木棍
* Status:?
* Tag:[]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1.0)
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

const double eps=1e-14;
double L;
double f(double theta)
{
    return L/sin(theta)*theta*2;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    double n,C;
    cin>>L>>n>>C;
    double L1=(1+n*C)*L;
    if(fabs(L-L1)<1e-10)
    {
        printf("0.000\n");
        return 0;
    }
    L /= 2;
    double lt=0, rt=PI/2;
    while(rt-lt>eps)
    {
        double mid=(lt+rt)/2.0;
        if(f(mid)>L1) rt=mid;
        else lt=mid;
    }
    double r=L1/(2*lt);
    cout<<fixed<<setprecision(3)<<(r-L/tan(lt))<<endl;
    return 0;
}