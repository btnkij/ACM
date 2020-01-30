/**
* Number:uva11168
* Title:Airport
* Status:AC
* Tag:[计算几何, 凸包]
**/

#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const double eps=1e-8,oo=1e15;
double cmp(double x)
{
    if (x>eps) return 1;
    if (fabs(x)<eps) return 0;
    return -1;
}
struct vector
{
    double x,y;
    void rd()
    {
        scanf("%lf%lf",&x,&y);
    }
    bool operator < (const vector &v) const
    {
        return cmp(x-v.x)==-1||(cmp(x-v.x)==0&&cmp(y-v.y)==-1);
    }
    bool operator == (const vector &v) const
    {
        return cmp(x-v.x)==0&&cmp(y-v.y)==0;
    }
    vector operator + (const vector &v) const
    {
        return (vector){x+v.x,y+v.y};
    }
    vector operator - (const vector &v) const
    {
        return (vector){x-v.x,y-v.y};
    }
    vector operator * (const double &k) const
    {
        return (vector){x*k,y*k};
    }
    vector operator / (const double &k) const
    {
        return (vector){x/k,y/k};
    }
}a[10010],f[10010];
typedef vector point;
double dot(vector v,vector u)
{
    return v.x*u.x+v.y*u.y;
}
double cross(vector v,vector u)
{
    return v.x*u.y-v.y*u.x;
}
void line(point p1,point p2,double &A,double &B,double &C)
{
    A=p2.y-p1.y;
    B=p1.x-p2.x;
    C=p2.x*p1.y-p1.x*p2.y;
}
double solve()
{
    int m,n,mm,nn;
    double sx=0,sy=0,ans=oo,A,B,C;
    scanf("%d",&n);
    nn=n;
    for (int i=1;i<=n;i++) a[i].rd(),sx+=a[i].x,sy+=a[i].y;
    sort(a+1,a+n+1);
    n=unique(a+1,a+n+1)-a-1;
    if (n==1) return 0;
    m=0;
    for (int i=1;i<=n;i++)
    {
        while (m>1&&cmp(cross(f[m]-f[m-1],a[i]-f[m-1]))==-1) m--;
        f[++m]=a[i];
    }
    mm=m;
    for (int i=n-1;i;i--)
    {
        while (m>mm&&cmp(cross(f[m]-f[m-1],a[i]-f[m-1]))==-1) m--;
        f[++m]=a[i];
    }
    for (int i=1;i<=m-1;i++)
    {
        line(f[i],f[i+1],A,B,C);
        ans=min(ans,fabs(A*sx+B*sy+nn*C)/sqrt(A*A+B*B));
    }
    return ans/nn;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T,K;
    scanf("%d",&T);
    for (int K=1;K<=T;K++)
        printf("Case #%d: %.3f\n",K,solve());
}