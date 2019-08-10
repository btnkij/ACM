/**
* Number:uva10256
* Title:The Great Divide
* Status:AC
* Tag:[计算几何, 凸包的位置关系]
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


const double eps = 1e-8;
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
    if(sgn(cross(dir, v1)) < 0)return len(v1);
    if(sgn(cross(dir, v2)) > 0)return len(v2);
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
    return !(d1 == 0 && sgn(dot(rhs.p1 - lhs.p1, rhs.p1 - lhs.p2)) <= 0) 
        || (d2 == 0 && sgn(dot(rhs.p2 - lhs.p1, rhs.p2 - lhs.p2)) <= 0) 
        || (d3 == 0 && sgn(dot(lhs.p1 - rhs.p1, lhs.p1 - rhs.p2)) <= 0) 
        || (d4 == 0 && sgn(dot(lhs.p2 - rhs.p1, lhs.p2 - rhs.p2)) <= 0); 
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


/************************************************************
 * 
 * 多边形, 凸包
 * 
************************************************************/

typedef std::vector<Point> Polygen;

// 多边形的周长
double circumference(const Polygen& poly)
{
    int n = poly.size();
    double ans = 0;
    for(int i = 0; i < n; i++)
    {
        ans += len(poly[i] - poly[(i + 1) % n]);
    }
    return ans;
}

// 多边形面积
double area(const Polygen& p)
{
	double ans = 0;
	for(int i = 1; i < (int)p.size() - 1; i++)
		ans += cross(p[i] - p[0], p[i + 1] - p[0]);
	return ans / 2.0;
}

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

// 凸包
Polygen ConvexHull(std::vector<Point>& points)
{
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    if(points.size() <= 2)return points;
    int n = points.size();
    Polygen ans({points[0], points[1]});
    int sz;
    for(int i = 2; i < n; i++) {
        while((sz = ans.size()) >= 2 && 
            sgn(cross(ans[sz - 1] - ans[sz - 2], points[i] - ans[sz - 2])) <= 0)
            ans.pop_back();
        ans.push_back(points[i]);
    }
    int sz0 = ans.size();
    for(int i = n - 2; i >= 0; i--) {
        while((sz = ans.size()) > sz0 && 
            cross(ans[sz - 1] - ans[sz - 2], points[i] - ans[sz - 2]) <= 0)
            ans.pop_back();
        ans.push_back(points[i]);
    }
    if(n > 1)ans.pop_back();
    return ans;
}

// 多边形与多边形的位置关系,
// lhs内含于rhs -2,
// lhs与rhs相交 -1,
// lhs包含rhs 0
// 相离 1
int position(const Polygen& lhs, const Polygen& rhs)
{
    int n = lhs.size(), m = rhs.size();
    for(int i = 0; i < n; i++)
    {
        if(position(lhs[i], rhs) >= 0)return -2;
    }
    for(int i = 0; i < m; i++)
    {
        if(position(rhs[i], lhs) >= 0)return 0;
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(position((Segment){lhs[i], lhs[(i + 1) % n]}, 
                (Segment){rhs[j], rhs[(j + 1) % m]}) <= 0)
            {
                return -1;
            }
        }
    }
    return 1;
}

vector<Point> A,B;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m;
    while(readi(n,m)!=EOF && (n|m))
    {
        A.clear();
        B.clear();
        repne(i,0,n)
        {
            int x,y; readi(x,y);
            A.push_back(Point(x,y));
        }
        repne(i,0,m)
        {
            int x,y; readi(x,y);
            B.push_back(Point(x,y));
        }
        Polygen HA=ConvexHull(A);
        Polygen HB=ConvexHull(B);
        printf("%s\n",position(HA,HB)==1 ? "Yes" : "No");
    }
    return 0;
}