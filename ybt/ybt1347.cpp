/**
* Number:ybt1347
* Title:【例4-8】格子游戏
* Status:AC
* Tag:[并查集]
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

const int MAXN=210*210;
int fa[MAXN];
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
bool merge(int x,int y)
{
    int rx=find(x),ry=find(y);
    if(rx==ry)return false;
    fa[rx]=ry;
    return true;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    repne(i,1,MAXN)fa[i]=i;
    bool win=false;
    int i;
    for(i=1;i<=m;i++)
    {
        int a,b; readi(a,b);
        char dir[4]; reads(dir);
        int x=a*201+b;
        int y=x;
        if(dir[0]=='D')y+=201;
        else if(dir[0]=='R')y+=1;
        if(!merge(x,y))
        {
            win=true;
            break;
        }
    }
    if(win)printf("%d",i);
    else printf("draw");
    return 0;
}