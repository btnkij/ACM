/**
* Number:luogu3808
* Title:【模板】AC自动机（简单版）
* Status:AC
* Tag:[AC自动机]
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

struct Node
{
    int fail, son[26]; // AC自动机的必要信息：fail-失配链接 son[]-儿子节点
    int end;           // 统计当前节点是多少个单词的结尾
} ac[1000010];
int sz;
inline int makenode()
{
    memset(&ac[++sz], 0, sizeof(Node));
    return sz;
}
void insert(const char *s) // 建Trie树
{
    int u = 0;
    for (const char *p = s; *p; p++)
    {
        int &v = ac[u].son[*p - 'a'];
        if (!v)
            v = makenode();
        u = v;
    }
    ac[u].end++; // 标记单词结尾
}
void build()
{
    queue<int> Q;
    for (int i : ac[0].son)
    {
        if (i)
        {
            ac[i].fail = 0;
            Q.push(i);
        }
    }
    while (!Q.empty())
    {
        Node &nod = ac[Q.front()];
        Q.pop();
        for (int i = 0; i < 26; i++)
        {
            int &v = nod.son[i];
            if (v)
            {
                ac[v].fail = ac[nod.fail].son[i];
                Q.push(v);
            }
            else
                v = ac[nod.fail].son[i];
        }
    }
}
int query(const char *s)
{
    int u = 0, ans = 0;
    for (const char *p = s; *p; p++)
    {
        u = ac[u].son[*p - 'a'];
        ans += ac[u].end;
        ac[u].end = 0; // 防止重复统计
    }
    return ans;
}

char s[1000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n); // 模式串个数
    sz = 0;
    repne(i, 0, n)
    {
        reads(s);
        insert(s); // 建Trie树
    }
    build(); // 求fail指针
    reads(s);
    printf("%d", query(s)); // 多模板匹配
    return 0;
}