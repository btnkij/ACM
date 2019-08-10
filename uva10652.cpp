/**
* Number:uva10652
* Title:Board Wrapping
* Status:AC
* Tag:[计算几何, 凸包]
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
 * 多边形, 凸包
 * 
************************************************************/

typedef std::vector<Point> Polygen;

// 多边形面积
double area(const Polygen& p)
{
	double ans = 0;
	for(int i = 1; i < (int)p.size() - 1; i++)
		ans += cross(p[i] - p[0], p[i + 1] - p[0]);
	return ans / 2.0;
}

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

const int MAXN=600;
vector<Point> vtx;
Point hull[MAXN*4+4];
double S;
void ReadRect(vector<Point>& vtx)
{
	double x,y,w,h,ang;
	scanf("%lf %lf %lf %lf %lf",&x,&y,&w,&h,&ang);
	ang=degToRad(-ang);
	S+=w*h;
	Point ori(x,y);
	Vector v1=rotate(Vector(w/2,h/2),ang);
	Vector v2=rotate(Vector(w/2,-h/2),ang);
	vtx.push_back(ori+v1);
	vtx.push_back(ori-v1);
	vtx.push_back(ori+v2);
	vtx.push_back(ori-v2);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
	int T;scanf("%d",&T);
	while(T--)
	{
		int n;scanf("%d",&n);
		S=0;
		vtx.clear();
		for(int i=0;i<n;i++)ReadRect(vtx);
		Polygen ch=ConvexHull(vtx);
		double ans=S*100/area(ch);
		printf("%.1lf %%\n",ans);
	}
	#ifdef _DEBUG_
	system("pause");
	#endif
	return 0;
}