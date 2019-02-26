/**
* Number:ybt1225
* Title:金银岛
* Status:AC
* Tag:[贪心]
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Item
{
    double w,c;
    double r;
    bool operator<(const Item& rhs)const
    {
        return r>rhs.r;
    } 
}items[104];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        double v; scanf("%lf",&v);
        int n; readi(n);
        repne(i,0,n)
        {
            scanf("%lf %lf", &items[i].w, &items[i].c);
            items[i].r=items[i].c/items[i].w;
        }
        sort(items,items+n);
        double ans=0;
        for(int i=0; i<n; i++)
        {
            if(v>=items[i].w)
            {
                v-=items[i].w;
                ans+=items[i].c;
            }
            else
            {
                ans+=items[i].r*v;
                break;
            }
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}