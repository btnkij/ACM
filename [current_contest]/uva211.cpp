/**
* Number:uva211
* Title:The Domino Effect
* Status:AC
* Tag:[回溯, 搜索, dfs]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
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

int maze[10][10];
int id[10][10];
int pat[10][10],ans;
bool vis[100];
void dfs(int x,int y)
{
    if(pat[x][y])
    {
        int p=x*8+y;
        while(p<=55 && pat[p/8][p%8])p++;
        if(p<55)x=p/8,y=p%8;
        else
        {
            ans++;
            rep(i,0,6)
            {
                rep(j,0,7)printf("%4d",pat[i][j]);
                puts("");
            }
            printf("\n\n");
            return;
        }
    }
    if(!pat[x+1][y])
    {
        int d1=maze[x][y],d2=maze[x+1][y];
        if(!vis[id[d1][d2]])
        {
            vis[id[d1][d2]]=true;
            pat[x][y]=pat[x+1][y]=id[d1][d2];
            dfs(x,y+1);
            vis[id[d1][d2]]=false;
            pat[x][y]=pat[x+1][y]=0;
        }
    }
    if(!pat[x][y+1])
    {
        int d1=maze[x][y],d2=maze[x][y+1];
        if(!vis[id[d1][d2]])
        {
            vis[id[d1][d2]]=true;
            pat[x][y]=pat[x][y+1]=id[d1][d2];
            dfs(x,y+1);
            vis[id[d1][d2]]=false;
            pat[x][y]=pat[x][y+1]=0;
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int tot=1;
    rep2(i,0,6,j,i,6)id[i][j]=id[j][i]=tot++;
    clr(pat,-1);
    rep2(i,0,6,j,0,7)pat[i][j]=0;
    int kase=1;
    while(scanf("%d",&maze[0][0])!=EOF)
    {
        if(kase!=1)printf("\n\n\n\n\n");
        rep(i,1,7)readi(maze[0][i]);
        rep2(i,1,6,j,0,7)readi(maze[i][j]);
        printf("Layout #%d:\n\n\n",kase);
        rep(i,0,6)
        {
            rep(j,0,7)printf("%4d",maze[i][j]);
            puts("");
        }
        printf("\n");
        printf("Maps resulting from layout #%d are:\n\n\n",kase);
        ans=0, dfs(0,0);
        printf("There are %d solution(s) for layout #%d.\n",ans,kase++);
    }
    return 0;
}