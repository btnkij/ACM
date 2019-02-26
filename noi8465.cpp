/**
* Number:noi8465
* Title:马走日
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
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

int dir[]={-33,-31,-14,-18,+14,+18,+31,+33};
bool vis[16*16];
int cnt,ans;
void dfs(int p)
{
    vis[p]=true;
    cnt--;
    if(cnt==0)
    {
        ans++;
    }
    else
    {
        for(int i=0;i<8;i++)
        {
            int t=p+dir[i];
            if(vis[t])continue;
            dfs(t);
        }
    }
    cnt++;
    vis[p]=false;
}
int main()
{
    int T;scanf("%d",&T);
    while(T--)
    {
        memset(vis,true,sizeof(vis));
        int n,m,x,y;
        scanf("%d %d %d %d",&n,&m,&x,&y);
        for(int i=2;i<n+2;i++)
        {
            for(int j=2;j<m+2;j++)
            {
                vis[(i<<4)+j]=false;
            }
        }
        cnt=m*n;
        ans=0;
        dfs(((x+2)<<4)+y+2);
        printf("%d\n",ans);
    }
    return 0;
}