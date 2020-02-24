/**
* Number:luogu5357
* Title:【模板】AC自动机（二次加强版）
* Status:AC
* Tag:[AC自动机, 树型DP]
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

const int MAXN = 2e5 + 10;
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
    int fail, nxt[26]; // AC自动机的必要信息：fail-失配链接 nxt[]-指向儿子或fail
    int cnt;           // 当前子串匹配的次数
} ac[MAXN];
int sz;
inline int makenode()
{
    memset(&ac[++sz], 0, sizeof(Node));
    return sz;
}
int insert(const char *s) // 在Trie树上插入单词s
{
    int u = 0;
    for (auto p = s; *p; p++)
    {
        int &v = ac[u].nxt[*p - 'a'];
        if (!v)
            v = makenode();
        u = v;
    }
    return u; // 返回单词在AC自动机上的位置
}
void build() // 求fail指针，并建立fail树
{
    fill_n(head, sz + 1, -1), edgeid = 0; // 链式前向星的初始化
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
void walk(const char *s) // 在AC自动机上按照字符串s转移
{
    int u = 0;
    for (auto p = s; *p; p++)
    {
        u = ac[u].nxt[*p - 'a'];
        ac[u].cnt++;
    }
}
void dfs(int u) // fail树上的DP，沿fail指针向上传递
{
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        dfs(v);
        ac[u].cnt += ac[v].cnt; // v匹配了，后缀u也会匹配
    }
}

char s[2000010];
int pos[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while (readi(n) != EOF)
    {
        sz = -1, makenode(); // AC自动机的初始化
        repne(i, 0, n)
        {
            reads(s);
            pos[i] = insert(s); // 记录单词在AC自动机上的位置
        }
        build(); // 建fail树
        reads(s);
        walk(s); // 多模板匹配
        dfs(0);  // 统计每个单词匹配的次数
        repne(i, 0, n) printf("%d\n", ac[pos[i]].cnt);
    }
    return 0;
}