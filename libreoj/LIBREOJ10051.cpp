/**
* Number:loj40001051
* Title:「一本通 2.3 例 3」Nikitosh 和异或 
* Status:AC
* Tag:[trie]
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

struct Node
{
    int to[2];
}nodes[400010*32];
int tot;
int find(int s)
{
    int p=0;
    int ans=0;
    for(int i=30;i>=0;i--)
    {
        int b=(s>>i)&1;
        if(nodes[p].to[b^1])b^=1;
        ans|=(b<<i)^(s&(1<<i));
        p=nodes[p].to[b];
    }
    return ans;
}
void insert(int s)
{
    int p=0;
    for(int i=30;i>=0;i--)
    {
        int b=(s>>i)&1;
        if(!nodes[p].to[b])
        {
            nodes[p].to[b]=tot;
            nodes[tot]=(Node){0,0};
            tot++;
        }
        p=nodes[p].to[b];
    }
}

int num[400010];
int sum[400010];
int fro[400010], bac[400010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)readi(num[i]);
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]^num[i];
    tot=1;
    insert(0);
    for(int i=1;i<=n;i++)
    {
        fro[i]=max(fro[i-1], find(sum[i]));
        insert(sum[i]);
    }
    tot=1;
    nodes[0]=(Node){0,0};
    insert(0);
    for(int i=n;i>=1;i--)
    {
        bac[i]=max(bac[i+1], find(sum[n]^sum[i-1]));
        insert(sum[n]^sum[i-1]);
    }
    int ans=0;
    for(int i=1;i<n;i++)
    {
        ans=max(ans, fro[i]+bac[i+1]);
    }
    printf("%d",ans);
    return 0;
}