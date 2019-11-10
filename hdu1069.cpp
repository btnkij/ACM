/**
* Number:hdu1069
* Title:Monkey and Banana
* Status:AC
* Tag:[dp]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
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

struct Rect3D
{
    int l,w,h;
    bool operator<(const Rect3D& rhs)
    {
        return l<rhs.l;
    }
}rect[200];
int dp[200];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,kase=1;
    while(readi(n)!=EOF && n)
    {
        int tot=0;
        rep(i,1,n)
        {
            int a,b,c; readi(a,b,c);
            rect[++tot]=(Rect3D){a,b,c};
            rect[++tot]=(Rect3D){b,a,c};
            rect[++tot]=(Rect3D){a,c,b};
            rect[++tot]=(Rect3D){c,a,b};
            rect[++tot]=(Rect3D){b,c,a};
            rect[++tot]=(Rect3D){c,b,a};
        }
        sort(rect+1,rect+tot+1);
        for(int i=1;i<=tot;i++)
        {
            int tmp=0;
            for(int j=1;j<i;j++)
            {
                if(rect[i].l>rect[j].l && rect[i].w>rect[j].w)
                {
                    tmp=max(tmp,dp[j]);
                }
            }
            dp[i]=tmp+rect[i].h;
        }
        printf("Case %d: maximum height = %d\n",kase++,*max_element(dp+1,dp+tot+1));
    }
    return 0;
}