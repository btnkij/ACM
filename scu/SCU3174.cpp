/**
* Number:scu3174
* Title:Good game
* Status:AC
* Tag:[博弈, 记忆化搜索]
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
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

bool vis[1000010];
bool win[1000010];
int ans[1000010];
bool dfs(int num)
{
    if(vis[num])return win[num];
    int d[8], cnt=0;
    int tmp=num;
    win[num]=false;
    ans[num]=INF;
    while(tmp)
    {
        d[cnt++]=tmp%10;
        tmp/=10;
    }
    for(int i=0;i<cnt;i++)
    {
        for(int j=0;j<=i;j++)
        {
            int sub=0;
            for(int k=i;k>=j;k--)
            {
                sub=sub*10+d[k];
            }
            if(sub==0 || sub==num)continue;
            if(dfs(num-sub)^1)
            {
                win[num]=true;
                ans[num]=min(ans[num],sub);
            }
        }
    }
    vis[num]=true;
    return win[num];
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    rep(i,0,9)
    {
        vis[i]=true;
        win[i]=false;
    }
    int n; readi(n);
    while(n--)
    {
        int num; readi(num);
        dfs(num);
        if(win[num])printf("%d\n",ans[num]);
        else printf("Bad Game\n");
    }
    return 0;
}