/**
 * Number:uva1665
 * Title:Islands
 * Status:AC
 * Tag:[并查集]
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

int par[1000004];
int cnt;
int findRoot(int x)
{
    return x==par[x] ? x : par[x]=findRoot(par[x]);
}
bool merge(int x,int y)
{
    int rx=findRoot(x);
    int ry=findRoot(y);
    if(rx==ry)return false;
    par[rx]=ry;
    cnt--;
    return true;
}

int id[1000004];
int height[1000004];
int t[100004],q;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int r,c;
        scanf("%d %d",&r,&c);
        int n=r*c;
        cnt=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",height+i);
            id[i]=par[i]=i;
        }
        sort(id+1,id+n+1,[](int lhs,int rhs){
            return height[lhs]>height[rhs];
        });
        scanf("%d",&q);
        for(int i=0;i<q;i++)scanf("%d",t+i);
        int last=1;
        for(int j=q-1;j>=0;j--)
        {
            int i;
            for(i=last;i<=n;i++)
            {
                int k=id[i];
                if(height[k]<=t[j])break;
                cnt++;
                if(k%c!=1 && height[k-1]>t[j])merge(k,k-1);
                if(k%c!=0 && height[k+1]>t[j])merge(k,k+1);
                if((k-1)/c+1<r && height[k+c]>t[j])merge(k,k+c);
                if((k-1)/c>0 && height[k-c]>t[j])merge(k,k-c);
            }
            last=i;
            t[j]=cnt;
        }
        for(int i=0;i<q;i++)
        {
            printf("%d ",t[i]);
        }
        putchar('\n');
    }
    return 0;
}