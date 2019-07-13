/**
* Number:poj1410
* Title:Intersection
* Status:AC
* Tag:[计算几何, 线段与线段的位置关系]
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

// 两点间的距离
inline double dist(const Point& lhs, const Point& rhs)
{
    return len(lhs - rhs);
}

inline bool operator==(const Vector& lhs, const Vector& rhs)
{
    return sgn(dist(lhs, rhs)) == 0;
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

// 向量的夹角，弧度制
inline double angle(const Vector& lhs, const Vector& rhs)
{
    return acos(dot(lhs, rhs) / len(lhs) / len(rhs));
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

// 点到线段的距离
double dist(const Point& p, const Segment& seg)
{
    if(seg.p1 == seg.p2)return len(p - seg.p1);
    Vector dir = seg.p2 - seg.p1;
    Vector v1 = p - seg.p1, v2 = p - seg.p2;
    if(sgn(cross(dir, v1)) < 0)return len(v1);
    if(sgn(cross(dir, v2)) > 0)return len(v2);
    return fabs(cross(dir, v1)) / len(dir);
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
// 点在线段上 1
int position(const Point& p, const Segment& seg)
{
    if(position(p, *(Line*)&seg) == 0)return -1;
    double x_1 = std::min(seg.p1.x, seg.p2.x);
    double x_2 = std::max(seg.p1.x, seg.p2.x);
    double y_1 = std::min(seg.p1.y, seg.p2.y);
    double y_2 = std::max(seg.p1.y, seg.p2.y);
    return x_1 <= p.x && p.x <= x_2 && y_1 <= p.y && p.y <= y_2;
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
// 相互穿过 -1, 
// 相交且共线 0, 
// 相离 1
int position(const Segment& lhs, const Segment& rhs)
{
    int rel1 = position(*(Line*)&lhs, rhs);
    int rel2 = position(*(Line*)&rhs, lhs);
    if(rel1 > 0 || rel2 > 0)return 1;
    if(rel1 < 0 && rel2 < 0)return -1;
    return !(position(lhs.p1, rhs) || position(lhs.p2, rhs));
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

typedef std::vector<Point> Polygen;

// 点与多边形的位置关系
// 点在多边形外部 -1,
// 在边上 0,
// 在内部 1
int position(const Point& p, const Polygen& poly)
{
    int k = 0, n = poly.size();
    for(int i = 0; i < n; i++)
    {
        const Point &p1 = poly[i], &p2 = poly[(i + 1) % n];
        if(position(p, (Segment){p1, p2}) == 1)return 0;
        int d = sgn(cross(p - p1, p2 - p1));
        int s1 = sgn(p1.y - p.y);
        int s2 = sgn(p2.y - p.y);
        if(d > 0 && s1 < 0 && s2 >= 0)k++;
        else if(d < 0 && s2 < 0 && s1 >= 0)k--;
    }
    return k ? 1 : -1;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    Segment seg;
    Polygen rect;
    while(T--)
    {
        double xstart,ystart,xend,yend,xleft,ytop,xright,ybottom;
        cin>>xstart>>ystart>>xend>>yend>>xleft>>ytop>>xright>>ybottom;
        if(xleft>xright)swap(xleft,xright);
        if(ytop<ybottom)swap(ytop,ybottom);
        seg=(Segment){Point(xstart,ystart),Point(xend,yend)};
        rect.clear();
        rect.push_back((Point){xleft,ytop});
        rect.push_back((Point){xleft,ybottom});
        rect.push_back((Point){xright,ybottom});
        rect.push_back((Point){xright,ytop});
        bool flag=false;
        if(xleft<=xstart && xstart<=xright && ybottom<=ystart && ystart<=ytop)flag=true;
        else if(xleft<=xend && xend<=xright && ybottom<=yend && yend<=ytop)flag=true;
        else
        {
            repne(i,0,4)
            {
                if(position(seg,(Segment){rect[i],rect[(i+1)%4]})<=0)
                {
                    flag=true;
                    break;
                }
            }
        }
        if(flag)printf("T\n");
        else printf("F\n");
    }
    return 0;
}