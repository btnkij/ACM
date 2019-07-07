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

bool vis[20][20];
int n, ans;
bool check(int x, int y)
{
    for(int i=1;x-i>=1;i++)
    {
        if(vis[x-i][y])return false;
        if(y-i>=1 && vis[x-i][y-i])return false;
        if(y+i<=n && vis[x-i][y+i])return false;
    }
    return true;
}
void dfs(int row)
{
    if(row>n)
    {
        ans++;
        printf("# %d\n", ans);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                printf("%d",vis[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return;
    }
    for(int i=1;i<=n;i++)
    {
        if(check(row,i))
        {
            vis[row][i]=true;
            dfs(row+1);
            vis[row][i]=false;
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d",&n);
    memset(vis, false, sizeof(vis));
    ans=0;
    dfs(1);
    return 0;
}