/**
* Number:LUOGU4113
* Title:[HEOI2012]采花
* Status:AC
* Tag:[树状数组]
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

constexpr int N=2e6+10;
struct Node
{
    int l,r,id;
}q[N];
int ans[N];
int cnt[N],pre[N][2],color[N];
int tree[N];
int n;
inline void update(int x, int val)
{
    for(;x<=n;x+=x&-x)tree[x]+=val;
}
inline int query(int x)
{
    int sum=0;
    for(;x;x^=x&-x)sum+=tree[x];
    return sum;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int c,m; cin>>n>>c>>m;
    for(int i=0;i<n;i++)cin>>color[i];
    for(int i=0;i<m;i++)
    {
        q[i].id=i;
        cin>>q[i].l>>q[i].r;
    }
    sort(q,q+m,[](const Node& lhs, const Node& rhs){
        return lhs.r < rhs.r;
    });
    int ansr=0, k=0;
    for(int r=1;r<=n;r++)
    {
        int cr=color[r-1];
        cnt[cr]++;
        if(cnt[cr]==2)ansr++;
        if(pre[cr][1])update(pre[cr][1], -1);
        pre[cr][1]=pre[cr][0];
        pre[cr][0]=r;
        if(pre[cr][1])update(pre[cr][1], 1);
        for(;k<m && q[k].r==r;k++)
        {
            int ansl=query(q[k].l-1);
            ans[q[k].id]=ansr-ansl;
        }
    }
    for(int i=0;i<m;i++)cout<<ans[i]<<"\n";
    return 0;
}