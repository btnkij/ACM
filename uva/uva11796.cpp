/**
* Number:uva11796
* Title:Dog Distance
* Status:?
* Tag:[计算几何, 点到线段的距离, 相对运动]
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

const double eps = 1e-10;
const double PI = acos(-1);

// 控制精度的比较函数
// x==0返回0, x>0返回1, x<0返回-1
inline int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    return x > 0 ? 1 : -1;
}

inline double radToDeg(double ang)
{
    return ang / PI * 180.;
}

inline double degToRad(double ang)
{
    return ang / 180. * PI;
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
    friend istream& operator>>(istream& in, Vector& v)
    {
        in >> v.x >> v.y;
        return in;
    }
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

// 向量的倾斜角，弧度制
inline double angle(const Vector& v)
{
    return atan2(v.y, v.x);
}

// 向量的夹角，弧度制
inline double angle(const Vector& lhs, const Vector& rhs)
{
    return acos(dot(lhs, rhs) / len(lhs) / len(rhs));
}

// 单位向量
inline Vector normalized(const Vector& lhs)
{
    double L = len(lhs);
    return Vector(lhs.x / L, lhs.y / L);
}

// 单位法向量，在lhs左侧
inline Vector normal(const Vector& lhs)
{
    return normalized(Vector(-lhs.y, lhs.x));
}

// 将向量v顺时针旋转theta弧度
inline Vector rotate(const Vector& v, double theta)
{
    double s = sin(theta), c = cos(theta);
    return Vector(v.x * c - v.y * s, v.x * s + v.y * c);
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

// 直线line的倾斜角
double angle(const Line& line)
{
    Vector v = line.p2 - line.p1;
    return atan2(v.y, v.x);
}

// 直线line的单位法向量
Vector normal(const Line& line)
{
    Vector v = normal(line.p2 - line.p1);
    return normalized(v);
}

// 将line沿法向量方向平移d
Line shift(const Line& line, double d)
{
    Vector dir = normal(line);
    return (Line){line.p1 + dir * d, line.p2 + dir* d};
}

// 点到直线的距离
double dist(const Point& p, const Line& line)
{
    Vector v1 = line.p1 - line.p2, v2 = p - line.p1;
    return fabs(cross(v1, v2)) / len(v1);
}

// 点到线段的距离
double dist(const Point& p, const Segment& seg)
{
    if(seg.p1 == seg.p2)return len(p - seg.p1);
    Vector dir = seg.p2 - seg.p1;
    Vector v1 = p - seg.p1, v2 = p - seg.p2;
    if(sgn(dot(dir, v1)) < 0)return len(v1);
    if(sgn(dot(dir, v2)) > 0)return len(v2);
    return fabs(cross(dir, v1)) / len(dir);
}

// 直线line的一般方程ax+by+c=0
void equation(const Line& line, double& a, double& b, double& c)
{
    a = line.p2.y - line.p1.y;
    b = line.p1.x - line.p2.x;
    c = -a * line.p1.x - b * line.p1.y;
}

// 点p在直线line上的投影
Point project(const Point& p, const Line& line)
{
    Vector v = line.p2 - line.p1;
    return line.p1 + v * (dot(v, p - line.p1) / dot(v,v));
}

// 点与直线的位置关系
// 点在直线外 0
// 点在直线上 1
int position(const Point& p, const Line& line)
{
    return sgn(cross(p - line.p1, p - line.p2)) == 0;
}

// 点与线段的位置关系
// 点在线段外 -1
// 点在线段的延长线上 0
// 点在线段端点上 1
// 点在线段内部 2
int position(const Point& p, const Segment& seg)
{
    if(position(p, *(Line*)&seg) == 0)return -1;
    int d = sgn(dot(p - seg.p1, p - seg.p2));
    if(d > 0)return 0;
    if(d == 0)return 1;
    return 2;
}

// 直线与直线的位置关系
// 相交 -1, 
// 重合 0, 
// 平行 1
int position(const Line& lhs, const Line& rhs)
{
    if(sgn(cross(lhs.p2 - lhs.p1, rhs.p2 - rhs.p1)) == 0)
    {
        if(sgn(cross(lhs.p2 - lhs.p1, rhs.p1 - lhs.p1)) == 0)return 0;
        else return 1;
    }
    return -1;
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

Point A[60],B[60];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    rep(kase,1,T)
    {
        int n,m; cin>>n>>m;
        repne(i,0,n)scanf("%lf %lf",&A[i].x,&A[i].y);
        repne(i,0,m)scanf("%lf %lf",&B[i].x,&B[i].y);
        double lenA=0, lenB=0;
        repne(i,1,n)lenA+=dist(A[i-1],A[i]);
        repne(i,1,m)lenB+=dist(B[i-1],B[i]);
        double ansmax=dist(A[0],B[0]),ansmin=ansmax;
        Point pA=A[0], pB=B[0], curB=B[0];
        int i=1, j=1;
        while(i<n && j<m)
        {
            double t1=dist(pA,A[i])/lenA;
            double t2=dist(pB,B[j])/lenB;
            Vector vA=normalized(A[i]-pA)*lenA;
            Vector vB=normalized(B[j]-pB)*lenB;
            Vector v=vB-vA;
            if(t1<=t2)
            {
                Point nxtB=curB+v*t1;
                ansmax=max(ansmax,max(len(curB-A[0]),len(nxtB-A[0])));
                ansmin=min(ansmin,dist(A[0],(Segment){curB,nxtB}));
                pA=A[i];
                i++;
                pB=pB+vB*t1;
                curB=nxtB;
                if(curB==B[j])j++;
            }
            else
            {
                Point nxtB=curB+v*t2;
                ansmax=max(ansmax,max(len(curB-A[0]),len(nxtB-A[0])));
                ansmin=min(ansmin,dist(A[0],(Segment){curB,nxtB}));
                pB=B[j];
                j++;
                pA=pA+vA*t2;
                curB=nxtB;
                if(curB==B[j])j++;
            }
        }
        printf("Case %d: %.0f\n",kase,ansmax-ansmin);
    }
    return 0;
}