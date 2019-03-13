/**
* Number:ybt1394
* Title:连接格点(grid)
* Status:AC
* Tag:[最小生成树]
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

int fa[1010*1010];
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
int m,n;
int dir[][2]={{1,0},{-1,0},{0,1},{0,-1}};
int kruskal()
{
    int ans=0;
    rep2(i,1,m,j,1,n)
    {
        int x=i*1001+j;
        repne(k,0,2)
        {
            int ii=i+dir[k][0], jj=j+dir[k][1];
            if(1<=ii && ii<=m && 1<=jj && jj<=n)
            {
                int y=ii*1001+jj;
                if(merge(x,y))
                {
                    ans+=1;
                }
            }
        }
    }
    rep2(i,1,m,j,1,n)
    {
        int x=i*1001+j;
        repne(k,2,4)
        {
            int ii=i+dir[k][0], jj=j+dir[k][1];
            if(1<=ii && ii<=m && 1<=jj && jj<=n)
            {
                int y=ii*1001+jj;
                if(merge(x,y))
                {
                    ans+=2;
                }
            }
        }
    }
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(m,n);
    repne(i,0,1010*1010)fa[i]=i;
    int x1,y1,x2,y2;
    while(readi(x1,y1,x2,y2)!=EOF)
    {
        int x=x1*1001+y1;
        int y=x2*1001+y2;
        merge(x,y);
    }
    int ans=kruskal();
    printf("%d",ans);
    return 0;
}