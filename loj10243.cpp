/**
* Number:loj10243
* Title:「一本通 6.7 例 3」移棋子游戏
* Status:AC
* Tag:[sg函数, Sprague-Grundy]
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

struct Edge
{
    int from,to;
}edges[6010];
int head[2010], nxt[6010], tot;
void addEdge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
}
int n;
int ans[2010];
int sg(int p)
{
    if(~ans[p])return ans[p];
    vector<int> num;
    for(int i=head[p];~i;i=nxt[i])
    {
        int v=edges[i].to;
        num.push_back(sg(v));
    }
    sort(num.begin(),num.end());
    if(num.empty() || num[0]!=0)return ans[p]=0;
    for(int i=1;i<num.size();i++)
    {
        if(num[i]-num[i-1]>1)
        {
            ans[p]=num[i-1]+1;
            break;
        }
    }
    if(ans[p]==-1)ans[p]=num.back()+1;
    // printf("sg(%d)=%d\n", p, ans[p]);
    return ans[p];
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(head,-1);
    mset(ans,-1);
    int m,k; readi(n,m,k);
    repne(i,0,m)
    {
        int u,v; readi(u,v);
        addEdge(u,v);
    }
    int sum=0;
    repne(i,0,k)
    {
        int p; readi(p);
        sum^=sg(p);
    }
    if(sum==0)printf("lose");
    else printf("win");
    return 0;
}