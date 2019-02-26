/**
 * Number:noi1751
 * Title:分解因数 
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

int factor[200],flen;
int ans;
void dfs(int pre,int remain)
{
    // printf("%d %d\n",pre,remain);
    if(remain==1)
    {
        ans++;
        return;
    }
    for(int i=pre;i<flen;i++)
    {
        if(remain%factor[i]!=0)continue;
        if(factor[i]>remain)return;
        dfs(i,remain/factor[i]);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        flen=0;
        for(int i=2;i<=n;i++)
        {
            if(n%i==0)
            {
                factor[flen++]=i;
            }
        }
        ans=0;
        dfs(0,n);
        printf("%d\n",ans);
    }
    return 0;
}