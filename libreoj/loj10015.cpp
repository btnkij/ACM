/**
* Number:loj10015
* Title:「一本通 1.2 练习 2」扩散
* Status:AC
* Tag:[并查集, 模拟]
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Point
{
    int x,y;
}pos[60];

int fa[60];
int findr(int x)
{
    return x==fa[x]?x:fa[x]=findr(fa[x]);
}
bool merge(int x,int y)
{
    int rx=findr(x),ry=findr(y);
    if(rx==ry)return false;
    fa[rx]=ry;
    return true;
}

struct Evt
{
    int t,a,b;
    bool operator<(const Evt& rhs)const
    {
        return t<rhs.t;
    }
}evt[60*60];

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)
    {
        fa[i]=i;
        readi(pos[i].x, pos[i].y);
    }
    int tot=0;
    rep2(i,1,n,j,i+1,n)
        evt[tot++]=(Evt){
            (abs(pos[i].x-pos[j].x)+abs(pos[i].y-pos[j].y)-1)/2+1
            , i, j};
    sort(evt,evt+tot);
    repne(i,0,tot)
    {
        Evt& e=evt[i];
        if(merge(e.a, e.b))
        {
            n--;
            if(n==1)
            {
                printf("%d",e.t);
                break;
            }
        }
    }
    return 0;
}