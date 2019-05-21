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

int dir[][2]={{1,0},{-1,0},{0,1},{0,-1}};
int maze[60][60];
int vis[60][60];
int calc(int x,int y,int i)
{
    int h=maze[x][y];
    int h1=vis[x+dir[i][0]][y+dir[i][1]];
    vis[x+dir[i][0]][y+dir[i][1]]=max(h,h1);
    if(h1==0)return h;
    if(h1+1>=h)return 0;
    return h-h1-1;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        mset(maze,0);
        mset(vis,0);
        int n,m; readi(n,m);
        rep2(i,1,n,j,1,m)
        {
            readi(maze[i][j]);
            vis[i][j]=maze[i][j];
        }
        int ans=0;
        rep2(i,1,n,j,1,m)
        {
            if(maze[i][j])
            {
                repne(k,0,4)ans+=calc(i,j,k);
                ans+=2;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}