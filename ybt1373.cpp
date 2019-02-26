/**
* Number:ybt1373
* Title:鱼塘钓鱼(fishing）
* Status:AC
* Tag:[枚举, 归并排序]
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

int buf1[4010], buf2[4010], buf3[4010];
int beg[104],decr[104],dis[104];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)readi(beg[i]);
    repne(i,0,n)readi(decr[i]);
    repne(i,1,n)readi(dis[i]);
    int t; readi(t);
    int ans=0;
    int *pcur=buf1, *pnxt=buf2, *pres=buf3;
    int *end=pcur;
    repne(i,0,n)
    {
        t -= dis[i];
        if(t<=0)break;
        int* p=pnxt;
        while(beg[i]>0)
        {
            *p=beg[i];
            beg[i]-=decr[i];
            p++;
        }
        end=merge(pcur,end,pnxt,p,pres,greater<int>());
        if(end>pres+t)end=pres+t;
        int sum=0;
        for(int j=0;j<t;j++)
        {
            if(pres+j==end)break;
            sum+=pres[j];
        }
        ans=max(ans,sum);
        swap(pcur,pres);
    }
    printf("%d\n",ans);
    return 0;
}