/**
* Number:loj2591
* Title:「NOIP2009」靶形数独
* Status:AC
* Tag:[dfs]
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

int w[][9]={
    {6,6,6,6,6,6,6,6,6},
    {6,7,7,7,7,7,7,7,6},
    {6,7,8,8,8,8,8,7,6},
    {6,7,8,9,9,9,8,7,6},
    {6,7,8,9,10,9,8,7,6},
    {6,7,8,9,9,9,8,7,6},
    {6,7,8,8,8,8,8,7,6},
    {6,7,7,7,7,7,7,7,6},
    {6,6,6,6,6,6,6,6,6}
};
bool hvis[10][10], vvis[10][10], bvis[3][3][10];
int sd[10][10];
int ans=-1;
void dfs(int dep)
{
    if(dep==0)
    {
        int tmp=0;
        repne2(i,0,9,j,0,9)
            tmp+=sd[i][j]*w[i][j];
        ans=max(ans, tmp);
        return;
    }
    int m=-INF, x, y;
    repne2(i,0,9,j,0,9)
    {
        int cnt=0;
        rep(k,1,9)
        {
            if(hvis[i][k] || vvis[j][k] || bvis[i/3][j/3][k])
            {
                cnt++;
            }
        }
        if(sd[i][j]==0 && cnt>m)
        {
            m=cnt;
            x=i, y=j;
        }
    }
    rep(k,1,9)
    {
        if(!hvis[x][k] && !vvis[y][k] && !bvis[x/3][y/3][k])
        {
            sd[x][y]=k;
            hvis[x][k]=vvis[y][k]=bvis[x/3][y/3][k]=true;
            dfs(dep-1);
            hvis[x][k]=vvis[y][k]=bvis[x/3][y/3][k]=false;
            sd[x][y]=0;
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n=81;
    repne2(i,0,9,j,0,9)
    {
        int t; readi(t);
        if(t)
        {
            n--;
            hvis[i][t]=vvis[j][t]=bvis[i/3][j/3][t]=true;
            sd[i][j]=t;
        }
    }
    dfs(n);
    printf("%d",ans);
    return 0;
}