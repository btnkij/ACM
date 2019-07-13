/**
* Number:poj3304
* Title:Segments
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

inline Vector operator+(const Vector& lhs, const Vector& rhs)
{
    return Vector(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector operator-(const Vector& lhs, const Vector& rhs)
{
    return Vector(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector operator*(const Vector& lhs, double rhs)
{
    return Vector(lhs.x * rhs, lhs.y * rhs);
}

inline Vector operator*(double lhs, const Vector& rhs)
{
    return rhs * lhs;
}

inline Vector operator/(const Vector& lhs, double rhs)
{
    return Vector(lhs.x / rhs, lhs.y / rhs);
}

// 向量的模长
inline double len(const Vector& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

// 向量的点积
inline double operator*(const Vector& lhs, const Vector& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

// 向量的叉积
inline double cross(const Vector& lhs, const Vector& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

// 向量的夹角，弧度制
inline double angle(const Vector& lhs, const Vector& rhs)
{
    return acos(lhs * rhs / len(lhs) / len(rhs));
}

// 法向量
inline Vector normal(const Vector& lhs)
{
    return Vector(-lhs.y, lhs.x);
}

// 单位向量
inline Vector normalized(const Vector& lhs)
{
    double L = len(lhs);
    return Vector(lhs.x / L, lhs.y / L);
}

// 将向量v顺时针旋转theta弧度
inline Vector rotate(const Vector& v, double theta)
{
    double s = sin(theta), c = cos(theta);
    return Vector(v.x * c - v.y * s, v.x * s + v.y * c);
}

// 两点间的距离
inline double dist(const Point& lhs, const Point& rhs)
{
    return len(lhs - rhs);
}

inline bool operator==(const Vector& lhs, const Vector& rhs)
{
    return sgn(dist(lhs, rhs)) == 0;
}

struct Line
{
    Point p1, p2;
};

struct Segment
{
    Point p1, p2;
};

// 点到直线的距离
double dist(const Point& p, const Line& line)
{
    Vector v1 = line.p1 - line.p2, v2 = p - line.p1;
    return fabs(cross(v1, v2)) / len(v1);
}

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

Segment segs[110];
bool check(const Line& line,int n)
{
    repne(i,0,n)
    {
        if(position(line,segs[i])>0)
        {
            return false;
        }
    }
    return true;
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
        int n; readi(n);
        repne(i,0,n)scanf("%lf %lf %lf %lf",
            &segs[i].p1.x,&segs[i].p1.y,&segs[i].p2.x,&segs[i].p2.y);
        bool flag=false;
        for(int i=0;i<2*n&&!flag;i++)
        {
            for(int j=0;j<2*n&&!flag;j++)
            {
                Point p1=((Point*)segs)[i];
                Point p2=((Point*)segs)[j];
                if(p1==p2)continue;
                Line line=(Line){p1,p2};
                if(check(line,n))
                {
                    flag=true;
                }
            }
        }
        if(flag)printf("Yes!\n");
        else printf("No!\n");
    }
    return 0;
}