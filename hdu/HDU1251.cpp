/**
* Number:hdu1251
* Title:统计难题
* Status:?
* Tag:[]
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
    int cnt, son[26];
} trie[5010 * 26 * 20];
int sz;
int makenode()
{
    memset(&trie[++sz], 0, sizeof(Node));
    return sz;
}
void insert(const char *s)
{
    int u = 0;
    for (const char *p = s; *p; p++)
    {
        int &v = trie[u].son[*p - 'a'];
        if (!v)
            v = makenode();
        trie[v].cnt++;
        u = v;
    }
}
int query(const char *s)
{
    int u = 0;
    for (const char *p = s;; p++)
    {
        if (!*p)
            return trie[u].cnt;
        u = trie[u].son[*p - 'a'];
        if (!u)
            return 0;
    }
}

char s[20];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    sz = 0; // Trie的初始化
    while (gets(s), s[0])
    {
        insert(s);
    }
    while (reads(s) != EOF)
    {
        printf("%d\n", query(s));
    }
    return 0;
}