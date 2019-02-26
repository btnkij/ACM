#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN=5e5+10;
int arr[MAXN],bit[MAXN];
int n,m;
void add(int p,int val)
{
    while(p<=n)
    {
        bit[p]+=val;
        p+=p&-p;
    }
}
void add_range(int lt,int rt,int val)
{
    add(lt,val);
    add(rt+1,-val);
}
int query(int p)
{
    int ans=0;
    while(p)
    {
        ans+=bit[p];
        p^=p&-p;
    }
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&arr[i]);
        add(i,arr[i]-arr[i-1]);
    }
    while(m--)
    {
        int op; scanf("%d",&op);
        if(op==1)
        {
            int x,y,k; scanf("%d %d %d",&x,&y,&k);
            add_range(x,y,k);
        }
        else if(op==2)
        {
            int x; scanf("%d",&x);
            printf("%d\n",query(x));
        }
    }
}