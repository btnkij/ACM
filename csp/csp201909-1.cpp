#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

int a[1010][1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int n,m; scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=m-1;j>=1;j--)
        {
            a[i][j]+=a[i][j+1];
        }
    }
    ll sum=0,k,p=-INF;
    for(int i=1;i<=n;i++)
    {
        sum+=a[i][0]+a[i][1];
        if(-a[i][1]>p)
        {
            p=-a[i][1];
            k=i;
        }
    }
    printf("%lld %lld %lld\n",sum,k,p);
    return 0;
}