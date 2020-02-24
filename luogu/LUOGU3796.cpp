/**
* Number:luogu3796
* Title:【模板】AC自动机（加强版）
* Status:AC
* Tag:[AC自动机, DP]
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

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 150 * 70 + 10;
struct Edge // 链式前向星模板，用于保存AC自动机的fail树
{
    int from, to, nxt;
} edges[MAXN];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

struct Node // AC自动机的节点，相当于Trie树节点多了fail指针
{
    int fail, nxt[26]; //
    int cnt, end;
} ac[MAXN];
int sz;
inline int makenode()
{
    memset(&ac[++sz], 0, sizeof(Node));
    return sz;
}
int insert(const char *s) //
{
    int u = 0;
    for (auto p = s; *p; p++)
    {
        int &v = ac[u].nxt[*p - 'a'];
        if (!v)
            v = makenode();
        u = v;
    }
    ac[u].end++;
    return u;
}
void build() // 求fail指针，并建立fail树
{
    fill_n(head, sz + 1, -1), edgeid = 0;
    queue<int> Q;
    for (int v : ac[0].nxt)
    {
        if (v)
        {
            addedge(0, v);
            Q.push(v);
        }
    }
    while (!Q.empty())
    {
        Node &fa = ac[Q.front()];
        Q.pop();
        for (int i = 0; i < 26; i++)
        {
            int &v = fa.nxt[i];
            if (v)
            {
                ac[v].fail = ac[fa.fail].nxt[i];
                addedge(ac[v].fail, v);
                Q.push(v);
            }
            else
                v = ac[fa.fail].nxt[i];
        }
    }
}
void walk(const char *s)
{
    int u = 0;
    for (auto p = s; *p; p++)
    {
        u = ac[u].nxt[*p - 'a'];
        ac[u].cnt++;
    }
}
void dfs(int u)
{
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        dfs(v);
        ac[u].cnt += ac[v].cnt;
    }
}

char pat[160][80];
char s[1000010];
int pos[160];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while (readi(n) != EOF && n)
    {
        sz = -1, makenode();
        repne(i, 0, n)
        {
            reads(pat[i]);
            pos[i] = insert(pat[i]);
        }
        build();
        reads(s);
        walk(s);
        dfs(0);
        int ans = 0;
        repne(i, 0, n) ans = max(ans, ac[pos[i]].cnt);
        printf("%d\n", ans);
        repne(i, 0, n) if (ac[pos[i]].cnt == ans) puts(pat[i]);
    }
    return 0;
}