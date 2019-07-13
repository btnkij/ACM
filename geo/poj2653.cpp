/**
* Number:poj2653
* Title:Pick-up sticks
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
#include <list>
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

// 两线段的位置关系
// 相互穿过 -1, 
// 端点处相交 0, 
// 相离 1
int position(const Segment& lhs, const Segment& rhs)
{
    int rel1 = position(*(Line*)&lhs, rhs);
    int rel2 = position(*(Line*)&rhs, lhs);
    if(rel1 > 0 || rel2 > 0)return 1;
    if(rel1 < 0 && rel2 < 0)return -1;
    return 0;
}

struct Node
{
    Segment seg;
    int id;
};
list<Node> arr;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF && n)
    {
        arr.clear();
        repne(i,0,n)
        {
            double ux,uy,vx,vy;
            scanf("%lf %lf %lf %lf",&ux,&uy,&vx,&vy);
            Segment s=(Segment){Point(ux,uy),Point(vx,vy)};
            for(list<Node>::iterator it=arr.begin();it!=arr.end();)
            {
                if(position(it->seg, s)==-1)
                {
                    list<Node>::iterator tmp=it;
                    it++;
                    arr.erase(tmp);
                }
                else it++;
            }
            arr.push_back((Node){s,i+1});
        }
        printf("Top sticks: ");
        for(list<Node>::iterator it=arr.begin();it!=arr.end();it++)
        {
            if(it!=arr.begin())printf(", ");
            printf("%d",it->id);
        }
        printf(".\n");
    }
    return 0;
}