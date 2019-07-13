/**
* Number:poj1556
* Title:The Doors
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

inline Vector operator-(const Vector& lhs, const Vector& rhs)
{
    return Vector(lhs.x - rhs.x, lhs.y - rhs.y);
}

// 向量的叉积
inline double cross(const Vector& lhs, const Vector& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
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

Point door[100];
Segment seg[60];
double adj[100][100];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    door[0]=(Point){0,5};
    door[1]=(Point){10,5};
    bool first=true;
    while(readi(n)!=EOF && ~n)
    {
        int dlen=2,slen=0;
        repne(i,0,n)
        {
            double x,a,b,c,d;
            scanf("%lf %lf %lf %lf %lf",&x,&a,&b,&c,&d);
            seg[slen++]=(Segment){Point(x,0),Point(x,a)};
            seg[slen++]=(Segment){Point(x,b),Point(x,c)};
            seg[slen++]=(Segment){Point(x,d),Point(x,10)};
            door[dlen++]=(Point){x,a};
            door[dlen++]=(Point){x,b};
            door[dlen++]=(Point){x,c};
            door[dlen++]=(Point){x,d};
        }
        repne2(i,0,dlen,j,0,dlen)
        {
            if(i==j)adj[i][j]=0;
            else adj[i][j]=1e100;
        }
        repne2(i,0,dlen,j,0,dlen)
        {
            if(sgn(door[i].x-door[j].x)==0)continue;
            Segment s=(Segment){door[i],door[j]};
            bool flag=true;
            repne(k,0,slen)
            {
                if(position(s,seg[k])==-1)
                {
                    flag=false;
                    break;
                }
            }
            if(flag)adj[i][j]=dist(door[i],door[j]);
        }
        repne(k,0,dlen)
        {
            repne2(i,0,dlen,j,0,dlen)
            {
                adj[i][j]=min(adj[i][j],adj[i][k]+adj[k][j]);
            }
        }
        if(!first)putchar('\n');
        first=false;
        printf("%.2lf",adj[0][1]);
    }
    return 0;
}