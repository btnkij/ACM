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

int num[10];
int cnt[10];
ll ans[10];
void dfs(int dep,int n)
{
    if(dep>=1)
    {
        bool flag=true;
        for(int i=2;i<=n;i+=2)
        {
            if(cnt[i]%2!=0)
            {
                flag=false;
                break;
            }
        }
        // repne(i,0,n)printf("%d ",num[i]);
        // puts("");
        if(flag)ans[dep]++;
        if(dep==n)return;
    }
    for(int i=1;i<=n;i++)
    {
        cnt[i]++;
        num[dep]=i;
        dfs(dep+1,n);
        cnt[i]--;
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    for(int i=1;i<=8;i++)
    {
        printf("#%d",i);
        clr(ans,0);
        dfs(0,i);
        for(int j=1;j<=i;j++)printf(" %lld",ans[j]);
        puts("");
    }
    return 0;
}