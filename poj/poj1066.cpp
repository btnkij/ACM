/**
* Number:poj1066
* Title:Treasure Hunt
* Status:AC
* Tag:[计算几何, 直线与线段的位置关系]
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
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const double eps = 1e-8;

// 控制精度的比较函数
// x==0返回0, x>0返回1, x<0返回-1
inline int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    return x > 0 ? 1 : -1;
}

struct Vector
{
    double x, y;
    Vector(){}
    Vector(double _x, double _y) : x(_x), y(_y){}
};
typedef Vector Point;

inline Vector operator-(const Vector& lhs, const Vector& rhs)
{
    return Vector(lhs.x - rhs.x, lhs.y - rhs.y);
}

// 向量的叉积
inline double cross(const Vector& lhs, const Vector& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

struct Line
{
    Point p1, p2;
};

struct Segment
{
    Point p1, p2;
};

// 直线与线段的位置关系
// 线段跨过直线 -1, 
// 线段至少一个端点在直线上 0, 
// 相离 1
int position(const Line& line, const Segment& seg)
{
    Vector dir = line.p2 - line.p1;
    Vector v1 = seg.p1 - line.p1, v2 = seg.p2 - line.p1;
    return sgn(cross(dir, v1)) * sgn(cross(dir, v2));
}

Line lines[40];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    if(n==0)
    {
        printf("Number of doors = 0");
        return 0;
    }
    repne(i,0,n)
    {
        scanf("%lf %lf %lf %lf",
            &lines[i].p1.x,&lines[i].p1.y,&lines[i].p2.x,&lines[i].p2.y);
    }
    Point dst;
    scanf("%lf %lf",&dst.x,&dst.y);
    int mm=n<<2;
    int ans=INF;
    repne(i,0,mm)
    {
        Segment path=(Segment){((Point*)lines)[i],dst};
        int cnt=1;
        repne(j,0,n)
        {
            if(position(lines[j], path)<0)cnt++;
        }
        ans=min(ans,cnt);
    }
    printf("Number of doors = %d",ans);
    return 0;
}