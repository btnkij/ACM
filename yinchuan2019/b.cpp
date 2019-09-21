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

const double eps = 1e-8;
const double PI = acos(-1);

// 控制精度的比较函数
// x==0返回0, x>0返回1, x<0返回-1
inline int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    return x > 0 ? 1 : -1;
}

/************************************************************
 * 
 * 点, 向量
 * 
************************************************************/

struct Vector
{
    double x, y;
    Vector(){}
    Vector(double _x, double _y) : x(_x), y(_y){}
};
typedef Vector Point;

bool operator==(const Point& lhs, const Point& rhs)
{
    return sgn(lhs.x - rhs.x) == 0 && sgn(lhs.y - rhs.y) == 0;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Point& lhs, const Point& rhs)
{
    return sgn(lhs.x - rhs.x) < 0 || sgn(lhs.x - rhs.x) == 0 && sgn(lhs.y - rhs.y) < 0;
}

inline Vector operator+(const Vector& lhs, const Vector& rhs)
{
    return Vector(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector operator-(const Vector& v)
{
    return Vector(-v.x, -v.y);
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

// 两点间的距离
inline double dist(const Point& lhs, const Point& rhs)
{
    return len(lhs - rhs);
}

// 向量的点积
inline double dot(const Vector& lhs, const Vector& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

// 向量的叉积
inline double cross(const Vector& lhs, const Vector& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

/************************************************************
 * 
 * 直线, 线段
 * 
************************************************************/

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

// 两线段的位置关系
// 规范相交 -1, 
// 非规范相交 0, 
// 相离 1
int position(const Segment& lhs, const Segment& rhs)
{
    int d1 = sgn(cross(lhs.p2 - lhs.p1, rhs.p1 - lhs.p1));
    int d2 = sgn(cross(lhs.p2 - lhs.p1, rhs.p2 - lhs.p1));
    int d3 = sgn(cross(rhs.p2 - rhs.p1, lhs.p1 - rhs.p1));
    int d4 = sgn(cross(rhs.p2 - rhs.p1, lhs.p2 - rhs.p1));
    if((d1 ^ d2) == -2 && (d3 ^ d4) == -2)return -1;
    return !((d1 == 0 && sgn(dot(rhs.p1 - lhs.p1, rhs.p1 - lhs.p2)) <= 0) 
        || (d2 == 0 && sgn(dot(rhs.p2 - lhs.p1, rhs.p2 - lhs.p2)) <= 0) 
        || (d3 == 0 && sgn(dot(lhs.p1 - rhs.p1, lhs.p1 - rhs.p2)) <= 0) 
        || (d4 == 0 && sgn(dot(lhs.p2 - rhs.p1, lhs.p2 - rhs.p2)) <= 0)); 
}

// 两直线的交点，需要保证两直线相交
Point intersect(const Line& lhs, const Line& rhs)
{
    double a1 = lhs.p2.y - lhs.p1.y;
    double b1 = lhs.p1.x - lhs.p2.x;
    double c1 = cross(lhs.p2, lhs.p1);
    double a2 = rhs.p2.y - rhs.p1.y;
    double b2 = rhs.p1.x - rhs.p2.x;
    double c2 = cross(rhs.p2, rhs.p1);
    double d = a1 * b2 - a2 * b1;
    return Point((b1 * c2 - b2 * c1) / d, (c1 * a2 - c2 * a1) / d);
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
        Point p1,p2,p3,p4;
        scanf("%lf %lf",&p1.x,&p1.y);
        scanf("%lf %lf",&p2.x,&p2.y);
        scanf("%lf %lf",&p3.x,&p3.y);
        scanf("%lf %lf",&p4.x,&p4.y);
        if(position((Segment){p1,p2},(Segment){p3,p4})==1)
        {
            printf("0.00\n");
            continue;
        }
        Point a=intersect((Line){p1,p2},(Line){p3,p4});
        if((sgn(p1.y-a.y)<=0 && sgn(p2.y-a.y)<=0) 
            || (sgn(p3.y-a.y)<=0 && sgn(p4.y-a.y)<=0))
        {
            printf("0.00\n");
            continue;
        }
        Point b=sgn(p1.y-a.y)==1?p1:p2;
        Point c=sgn(p3.y-a.y)==1?p3:p4;
        if(sgn(b.y-c.y)==1)swap(b,c);
        Line l=(Line){b,b+Vector(1,0)};
        b=intersect(l,(Line){p1,p2});
        c=intersect(l,(Line){p3,p4});
        double V=dist(a,l)*dist(b,c)/2.0;
        printf("%.2lf\n",V);
    }
    return 0;
}