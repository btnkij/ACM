/**
* Number:p3804
* Title:【模板】后缀自动机
* Status:AC
* Tag:[后缀自动机, SAM]
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 1e6 * 2 + 10;
ll rk[MAXN];
struct SAM
{
    inline int _hash(char ch)
    {
        return ch - 'a';
    }
    struct State
    {
        int length, parent;
        int nxt[26];
    }dfa[MAXN];
    int size, last;
    void init()
    {
        size = 1;
        last = 0;
        dfa[0].length = 0;
        dfa[0].parent = -1;
    }
    void append(char ch)
    {
        int e = _hash(ch);
        int pre = last;
        int cur = size++;
        rk[cur]=1;
        dfa[cur].length = dfa[last].length + 1;
        while(pre != -1 && !dfa[pre].nxt[e])
        {
            dfa[pre].nxt[e] = cur;
            pre = dfa[pre].parent;
        }
        if(pre == -1)
        {
            dfa[cur].parent = 0;
        }
        else
        {
            int origin = dfa[pre].nxt[e];
            if(dfa[pre].length + 1 == dfa[origin].length)
            {
                dfa[cur].parent = origin;
            }
            else
            {
                int clone = size++;
                dfa[clone].length = dfa[pre].length + 1;
                dfa[clone].parent = dfa[origin].parent;
                memcpy(dfa[clone].nxt, dfa[origin].nxt, sizeof(dfa[origin].nxt));
                dfa[cur].parent = dfa[origin].parent = clone;
                while(pre != -1 && dfa[pre].nxt[e] == origin)
                {
                    dfa[pre].nxt[e] = clone;
                    pre = dfa[pre].parent;
                }
            }
        }
        last = cur;
    }
}sam;

struct Edge
{
    int from,to,nxt;
}edges[MAXN];
int head[MAXN], edge_id;
void addedge(int from,int to)
{
    edges[++edge_id] = (Edge){from,to,head[from]};
    head[from] = edge_id;
}

ll ans;
void dfs(int u)
{
    for(int i=head[u];i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        dfs(v);
        rk[u]+=rk[v];
    }
    if(rk[u]!=1)
    {
        ans=max(ans,rk[u]*sam.dfa[u].length);
    }
}

char s[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%s", s);
    int len=strlen(s);
    sam.init();
    for(int i=0;i<len;i++)sam.append(s[i]);
    for(int i=1;i<sam.size;i++)
    {
        addedge(sam.dfa[i].parent, i);
    }
    ans=-INF;
    dfs(0);
    printf("%lld",ans);
    return 0;
}