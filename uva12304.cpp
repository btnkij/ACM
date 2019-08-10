/**
* Number:uva12304
* Title:2D Geometry 110 in 1!
* Status:AC
* Tag:[计算几何, 圆, 切线]
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

const double eps = 1e-6;

// 控制精度的比较函数
// x==0返回0, x>0返回1, x<0返回-1
inline int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    return x > 0 ? 1 : -1;
}


/**
 * 
 * 点, 向量
 * 
**/

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


/**
 * 
 * 直线, 线段
 * 
**/

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


/**
 * 
 * 圆
 * 
**/

const double PI = acos(-1);

struct Circle
{
    Point c; // 圆心
    double r; // 半径
};

// 获取circle在圆心角ang处的点
Point getPoint(const Circle& circle, double ang)
{
    return Point(circle.c.x + circle.r * cos(ang), 
        circle.c.y + circle.r * sin(ang));
}

// 从from到to的弧长
double arc(const Circle& circle, const Point& from, const Point& to)
{
    Vector v1 = from - circle.c, v2 = to - circle.c;
    double ang1 = angle(v1), ang2 = angle(v2);
    if(ang2 < ang1)ang2 += 2 * PI;
    return circle.r * (ang2 - ang1);
}

// 直线与圆交点, 输出参数ans[]，返回交点个数
int intersect(const Line& L, const Circle& C, Point ans[])
{
    Vector v = L.p2 - L.p1;
    double a = v.x, b = L.p1.x - C.c.x, c = v.y, d = L.p1.y - C.c.y;
    double e = a * a + c * c;
    double f = 2 * (a * b + c * d);
    double g = b * b + d * d - C.r * C.r;
    double delta = f * f - 4. * e * g;
    int s = sgn(delta);
    if(s < 0) return 0; // 相离
    else if(s == 0) // 相切
    {
        ans[0] = L.p1 + (-f / (2. * e)) * v;
        return 1;
    }
    else // 相交
    {
        ans[0] = L.p1 + ((-f - sqrt(delta)) / (2. * e)) * v;
        ans[1] = L.p1 + ((-f + sqrt(delta)) / (2. * e)) * v;
        return 2;
    }
}

// 圆与圆交点，返回交点个数，
// -1表示无穷多个交点
int intersect(const Circle& C1, const Circle& C2, Point ans[])
{
    double d = len(C1.c - C2.c);
    if(sgn(d) == 0)
    {
        if(sgn(C1.r - C2.r) == 0)return -1; //重合
        return 0;
    }
    if(sgn(C1.r + C2.r - d) < 0)return 0;
    if(sgn(fabs(C1.r - C2.r) - d) > 0)return 0;
    double a = angle(C2.c - C1.c);
    double da = acos((C1.r * C1.r + d * d-C2.r * C2.r) / (2 * C1.r * d));
    Point p1 = getPoint(C1, a - da),p2 = getPoint(C1, a + da);
    ans[0] = p1;
    if(p1 == p2)return 1;
    ans[1] = p2;
    return 2;
}

// P到圆C的切线，ans[]储存切线的方向向量
int tangent(const Circle& C, const Point& p, Point ans[])
{
    Point u = C.c - p;
    double dist = len(u);
    if(dist < C.r)return 0;
    else if(sgn(dist - C.r) == 0)
    {
        ///p在圆上仅有一条切线
        ans[0] = rotate(u, PI / 2);
        return 1;
    }
    else
    {
        double ang = asin(C.r / dist);
        ans[0] = rotate(u, -ang);
        ans[1] = rotate(u, ang);
        return 2;
    }
}

// 两圆公切线，a[] b[]分别为公切线在圆A B上的切点，返回公切线条数
int tangent(Circle A, Circle B, Point* a, Point* b)
{
    int cnt = 0;
    if(A.r < B.r) { std::swap(A, B); std::swap(a, b); }
    int d2 = (A.c.x - B.c.x) * (A.c.x - B.c.x)+(A.c.y - B.c.y) * (A.c.y - B.c.y);
    int rdiff = A.r - B.r;
    int rsum = A.r+B.r;
    if(d2 < rdiff * rdiff)return 0; // 内含
    double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
    if(d2 == 0 && A.r == B.r)return -1; ///无穷多
    if(d2 == rdiff * rdiff) // 内切 1条
    {
        a[cnt] = getPoint(A, base); b[cnt] = getPoint(B, base); cnt++;
        return 1;
    }
    // 外切
    double ang = acos((A.r - B.r) / sqrt(d2));
    a[cnt] = getPoint(A, base + ang); b[cnt] = getPoint(B, base + ang); cnt++;
    a[cnt] = getPoint(A, base - ang); b[cnt] = getPoint(B, base - ang); cnt++;
    if(d2 == rsum * rsum) // one
    {
        a[cnt] = getPoint(A, base); b[cnt] = getPoint(B, PI+base); cnt++;
    }
    else if(d2>rsum * rsum) // two
    {
        double ang = acos((A.r - B.r) / sqrt(d2));
        a[cnt] = getPoint(A, base + ang); b[cnt] = getPoint(B, PI + base+ang); cnt++;
        a[cnt] = getPoint(A, base - ang); b[cnt] = getPoint(B, PI+base - ang); cnt++;
    }
    return cnt;
}

// 三角形外接圆
Circle CircumscribedCircle(const Point& p1, const Point& p2, const Point& p3)
{
    double Bx = p2.x - p1.x, By = p2.y - p1.y;
    double Cx = p3.x - p1.x, Cy = p3.y - p1.y;
    double D = 2 * (Bx * Cy - By * Cx);
    double cx = (Cy * (Bx * Bx + By * By) - By * (Cx * Cx + Cy * Cy))/D + p1.x;
    double cy = (Bx * (Cx * Cx + Cy * Cy) - Cx * (Bx * Bx + By * By))/D + p1.y;
    Point p = Point(cx, cy);
    return (Circle){p, len(p1 - p)};
}

// 三角形内切圆
Circle InscribedCircle(const Point& p1, const Point& p2, const Point& p3)
{
    double a = len(p2 - p3);
    double b = len(p3 - p1);
    double c = len(p1 - p2);
    Point p = (p1 * a + p2 * b + p3 * c)/(a + b + c);
    return (Circle){p, dist(p, (Line){p1, p2})};
}

inline double radToDeg(double ang)
{
    return ang / PI * 180.;
}

char op[200];
double a[10];
Point v[10];
double degree[10];
vector<Point> sol;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(scanf("%s",op)!=EOF)
    {
        if(strcmp(op,"CircumscribedCircle")==0)
        {
            for(int i=0;i<6;i++) scanf("%lf",a+i);
            Circle C=CircumscribedCircle(Point(a[0],a[1]),Point(a[2],a[3]),Point(a[4],a[5]));
            printf("(%.6lf,%.6lf,%.6lf)\n",C.c.x,C.c.y,C.r);
        }
        else if(strcmp(op,"InscribedCircle")==0)
        {
            for(int i=0;i<6;i++) scanf("%lf",a+i);
            Circle C=InscribedCircle(Point(a[0],a[1]),Point(a[2],a[3]),Point(a[4],a[5]));
            printf("(%.6lf,%.6lf,%.6lf)\n",C.c.x,C.c.y,C.r);
        }
        else if(strcmp(op,"TangentLineThroughPoint")==0)
        {
            for(int i=0;i<5;i++) scanf("%lf",a+i);
            int sz=tangent((Circle){Point(a[0],a[1]),a[2]},Point(a[3],a[4]),v);
            for(int i=0;i<sz;i++)
            {
                double de=radToDeg(angle(v[i]));
                if(sgn(de)<0) de=180.+de;
                else while(sgn(de-180.)>=0) de-=180.;
                degree[i]=de;
            }
            sort(degree,degree+sz);
            putchar('[');if(sz==0) putchar(']');
            for(int i=0;i<sz;i++) printf("%.6lf%c",degree[i],(i!=sz-1)?',':']');
            putchar(10);
        }
        else if(strcmp(op,"CircleThroughAPointAndTangentToALineWithRadius")==0)
        {
            for(int i=0;i<7;i++) scanf("%lf",a+i);
            Point A=Point(a[2],a[3]),B=Point(a[4],a[5]);
            Circle C=(Circle){Point(a[0],a[1]),a[6]};
            Point n=normal(B-A)*a[6];
            Line l1=(Line){A+n,B+n};
            Line l2=(Line){A-n,B-n};
            sol.clear();
            Point t[2];
            int aa=intersect(l1,C,t);
            repne(i,0,aa)sol.push_back(t[i]);
            int bb=intersect(l2,C,t);
            repne(i,0,bb)sol.push_back(t[i]);
            sort(sol.begin(),sol.end());
            putchar('[');
            for(int i=0,sz=sol.size();i<sz;i++)
            {
                if(i) putchar(',');
                printf("(%.6lf,%.6lf)",sol[i].x,sol[i].y);
            }
            putchar(']'); putchar(10);
        }
        else if(strcmp(op,"CircleTangentToTwoLinesWithRadius")==0)
        {
            for(int i=0;i<9;i++) scanf("%lf",a+i);
            Line LA=(Line){Point(a[0],a[1]),Point(a[2],a[3])};
            Line LB=(Line){Point(a[4],a[5]),Point(a[6],a[7])};
            Line la1=shift(LA,a[8]),la2=shift(LA,-a[8]);
            Line lb1=shift(LB,a[8]),lb2=shift(LB,-a[8]);
            Point sol[4];
            sol[0]=intersect(la1,lb1);
            sol[1]=intersect(la1,lb2);
            sol[2]=intersect(la2,lb1);
            sol[3]=intersect(la2,lb2);
            sort(sol,sol+4);
            putchar('[');
            for(int i=0;i<4;i++)
            {
                if(i) putchar(',');
                printf("(%.6lf,%.6lf)",sol[i].x,sol[i].y);
            }
            putchar(']'); putchar(10);

        }
        else if(strcmp(op,"CircleTangentToTwoDisjointCirclesWithRadius")==0)
        {
            for(int i=0;i<7;i++) scanf("%lf",a+i);
            Circle C1=(Circle){Point(a[0],a[1]),a[2]+a[6]};
            Circle C2=(Circle){Point(a[3],a[4]),a[5]+a[6]};
            sol.clear();
            Point sol[2];
            int cnt=intersect(C1,C2,sol);
            sort(sol,sol+cnt);
            putchar('[');
            for(int i=0;i<cnt;i++)
            {
                if(i) putchar(',');
                printf("(%.6lf,%.6lf)",sol[i].x,sol[i].y);
            }
            putchar(']'); putchar(10);
        }
    }
    return 0;
}