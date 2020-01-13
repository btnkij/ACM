#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

bool drop[1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int n; scanf("%d",&n);
    ll tot=0;
    for(int i=0;i<n;i++)
    {
        int m; scanf("%d",&m);
        int sum=0;
        for(int j=0;j<m;j++)
        {
            int t; scanf("%d",&t);
            if(t>0)
            {
                if(sum!=t && j)drop[i]=true;
                sum=t;
            }
            else sum+=t;
        }
        tot+=sum;
    }
    int d=0,e=0;
    for(int i=0;i<n;i++)
    {
        if(drop[i])d++;
        if(drop[((i-1+n)%n+n)%n] && drop[i] && drop[(i+1)%n])e++;
    }
    printf("%lld %d %d\n",tot,d,e);
    return 0;
}