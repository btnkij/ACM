/**
* Number:ybt1238
* Title:一元三次方程求解
* Status:AC
* Tag:[盛金公式]
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
    double a,b,c,d;
    cin>>a>>b>>c>>d;
    double A=b*b-3*a*c;
    double B=b*c-9*a*d;
    double C=c*c-3*b*d;
    double D=B*B-4*A*C;
    if(D<0)
    {
        double x[3];
        double T=(2*A*b-3*a*B)/(2*A*sqrt(A));
        double theta=acos(T)/3;
        x[0]=(-b-2*sqrt(A)*cos(theta))/(3*a);
        x[1]=(-b+sqrt(A)*(cos(theta)-sqrt(3)*sin(theta)))/(3*a);
        x[2]=(-b+sqrt(A)*(cos(theta)+sqrt(3)*sin(theta)))/(3*a);
        sort(x,x+2);
        printf("%.2lf %.2lf %.2lf\n",x[0],x[1],x[2]);
    }
    return 0;
}