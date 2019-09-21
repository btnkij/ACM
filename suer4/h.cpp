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

ll comb[40][40];
void init_comb(int n)
{
    for(int i = 1; i <= n; i++)
    {
        comb[i][0] = comb[i][i] = 1;
        for(int j = 1; j < i; j++)
        {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
}

int d,h,num[40];
vector<ll> ans;
void dfs(int sum,int pre,int dep)
{
    if(dep>=d && sum>0)return;
    if(sum==0)
    {
        ll prod=1;
        int t=d;
        for(int i=0;i<d;i++)
        {
            prod*=comb[t][num[i]];
            t-=num[i];
        }
        ans.push_back(prod);
        return;
    }
    for(int i=pre;i<=sum;i++)
    {
        if(sum-i<i && dep!=d)continue;
        num[dep]=i;
        dfs(sum-i,i,dep+1);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    init_comb(34);
    readi(d,h);
    dfs(h-1,0,0);
    sort(ans.begin(),ans.end());
    for(ll i:ans)printf("%lld\n",i);
    return 0;
}