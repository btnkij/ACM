/**
* Number:p5496
* Title:【模板】回文自动机（PAM）
* Status:AC
* Tag:[pam, 回文自动机, 回文树]
* desc: 求一字符串每个位置结尾的回文串个数
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

const int MAXN = 5e5 + 10;
struct Node
{
    int len, cnt;         // 以当前节点结尾的最长回文串长度，回文后缀个数
    Node *fail, *nxt[26]; // 后缀链接，子节点
} pam[MAXN], *tail, *last;
#define nullstr (&pam[0])
char s[MAXN];
Node *makenode(int len, Node *fail)
{
    *tail = {len, 0, fail};
    fill_n(tail->nxt, 26, nullstr);
    return tail++;
}
void init()
{
    s[0] = -1;
    tail = last = pam;
    makenode(0, &pam[1]), makenode(-1, nullstr);
}
Node *getfail(Node *pre, int i)
{
    while (s[i - pre->len - 1] != s[i])
        pre = pre->fail;
    return pre;
}
void extend(int i) // 向PAM中添加新字符s[i]
{
    Node *pre = getfail(last, i);
    last = pre->nxt[s[i]];
    if (last == nullstr)
    {
        last = pre->nxt[s[i]] 
            = makenode(pre->len + 2, getfail(pre->fail, i)->nxt[s[i]]);
        last->cnt = last->fail->cnt + 1;
    }
}
#undef nullstr

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(s + 1); // s[0]=-1，作为特殊用途
    int len = strlen(s + 1), ans = 0;
    init(); // 初始化
    rep(i, 1, len)
    {
        s[i] = (s[i] - 97 + ans) % 26 + 97; // 强制在线
        s[i] -= 'a';
        extend(i);
        printf("%d ", ans = last->cnt);
    }
    return 0;
}