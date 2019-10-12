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

bool vis[200][10010];
double dp[200][10010];
double a[200][200];
int b[10010],k;
int n,m;
double dfs(int x,int y)
{
    if(y==k)return 1;
    if(vis[x][y])return dp[x][y];
    double ans=a[x][b[y]]*max(dfs(x,y+1),dfs(b[y],y+1));
    vis[x][y]=true;
    return dp[x][y]=ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(m)!=EOF)
    {
        n=m*(m-1)*(m-2)/3/2;
        repne2(i,0,n,j,0,n)scanf("%lf",&a[i][j]);
        readi(k);
        repne(i,0,k)readi(b[i]);
        clr(vis,false);
        double ans=0;
        repne(i,0,n)ans=max(ans,dfs(i,0));
        printf("%.6lf\n",ans);
    }
    return 0;
}