[TOC]

## 待整理

技巧：树的括号序列表达 luogu2056



## 未分类

### include & define

```c++
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


int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    return 0;
}
```

### 输入输出优化

```c++
// 读非负int
inline int readu()
{
    register int num = 0;
    register char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ 
        num = (num << 3) + (num << 1) + (ch & 0xF); 
        ch = getchar(); 
    }while('0' <= ch && ch <= '9');
    return num;
}

// 读任意int
inline int read()
{
    register int num = 0;
    register char ch;
    register bool sign = false;
    do
    {
        ch = getchar();
        if(ch == '-')sign = true;
    }while(ch < '0' || ch > '9');
    do{ 
        num = (num << 3) + (num << 1) + (ch & 0xF); 
        ch = getchar(); 
    }while('0' <= ch && ch <= '9');
    if(sign)num = -num;
    return num;
}
```

### 排序

#### 快速排序

```c++
void quick_sort(int* begin, int* end) // 传首尾指针，左闭右开区间
{
    if(end - begin <= 1)return;
    std::swap(*begin, *(begin + rand() % (end - begin)));
    int pivot = *begin;
    int *lt = begin, *rt = end - 1;
    while(lt != rt)
    {
        while(rt != lt && *rt > pivot)rt--;
        if(lt == rt)break;
        *lt = *rt; lt++;
        while(lt != rt && *lt < pivot)lt++;
        if(lt == rt)break;
        *rt = *lt; rt--;
    }
    *lt = pivot;
    quick_sort(begin, lt);
    quick_sort(lt + 1, end);
}
```

#### 归并排序

```c++
void merge_sort(int *begin, int *end) // 传首尾指针，左闭右开区间
{
    static int buffer[100010]; // 保证长度大于待排序的数组
    int L = end - begin;
    if(L <= 1)return;
    int* mid = begin + (L >> 1);
    merge_sort(begin, mid);
    merge_sort(mid, end);
    int* plt = begin;
    int* prt = mid;
    int* pbuf = buffer;
    while(plt != mid && prt != end)
    {
        if(*plt <= *prt)*pbuf = *plt, plt++;
        else *pbuf = *prt, prt++;
        pbuf++;
    }
    if(prt == end)std::copy(plt, mid, begin + (pbuf - buffer));
    std::copy(buffer, pbuf, begin);
}
```



### CDQ分治

【题号】LUOGU3810

【题目】定义三维偏序$A(x_1,y_1,z_1) \leq B(x_2,y_2,z_2)$当且仅当$x_1 \leq x_2 \bigwedge y_1 \leq y_2 \bigwedge z_1 \leq z_2$。求比自身小的三元组个数分别为$0 \dots n-1$的三元组个数。

【思路】三元组按照第0维排序。归并排序第1维，每轮归并后，统计右侧的每一个三元组在左侧有多少个比它小的，可使用树状数组统计，也可以再次应用CDQ分治计算。如果再次嵌套CDQ分治，先标记1维排序后的左右元素，第2维归并排序后只统计1维排序时的左边元素对右边的贡献。

```c++
const int MAXN = 2e5 + 10; // 最大三元组个数
const int MAX_DIM = 2; // 第0维排序，只用CDQ分治剩下的两维
struct Node
{
    int v[3], sz, ans;
} nodes[MAXN];
pair<Node *, int> buf[4][MAXN];
void cdq(int beg, int end, int dim)
{
    if (end - beg <= 1)
        return;
    int mid = (beg + end) >> 1;
    cdq(beg, mid, dim); // 分治左部的第dim维
    cdq(mid, end, dim); // 分治右部的第dim维
    // cur[]-当前序列 nxt[]-保存归并后的序列
    pair<Node *, int> *cur = buf[dim], *nxt = buf[dim + 1];
    int i = beg, j = mid, k = beg, cnt = 0;
    while (i < mid || j < end) // 按照第dim维归并排序
    {
        if (j == end || i < mid && cur[i].first->v[dim] <= cur[j].first->v[dim])
        {
            nxt[k] = cur[i];
            // 如果是第一层分治或者拥有左部标记
            if (dim == 1 || dim < MAX_DIM && cur[i].second == 1)
                nxt[k].second = 1; // 继续标记为左部元素
            if (dim == MAX_DIM && nxt[k].second == 1) // 到达最深的CDQ，开始统计答案
                cnt += nxt[k].first->sz;
            i++, k++;
        }
        else
        {
            nxt[k] = cur[j];
            // 如果是第一层分治或者拥有右部标记
            if (dim == 1 || dim < MAX_DIM && cur[j].second == 2)
                nxt[k].second = 2; // 继续标记为右部元素
            if (dim == MAX_DIM && nxt[k].second == 2) // 到达最深的CDQ，开始统计答案
                nxt[k].first->ans += cnt; // 左部比nxt[k]小的三元组有cnt个
            j++, k++;
        }
    }
    copy(nxt + beg, nxt + end, cur + beg);
    if (dim < MAX_DIM) cdq(beg, end, dim + 1); // 处理下一维度
}
int ans[MAXN];
int main()
{
    int n, k; // 三元组数量，分量最大值
    readi(n, k);
    repne(i, 0, n)
    {
        readi(nodes[i].v[0], nodes[i].v[1], nodes[i].v[2]); // 读三元组
        buf[1][i] = make_pair(nodes + i, 0);
    }
    pair<Node *, int> *cur = buf[1];
    sort(cur, cur + n, [](const pair<Node *, int> &lhs, const pair<Node *, int> &rhs) 
    {
        int *v1 = lhs.first->v, *v2 = rhs.first->v;
        if (v1[0] != v2[0])
            return v1[0] < v2[0];
        if (v1[1] != v2[1])
            return v1[1] < v2[1];
        return v1[2] < v2[2];
    }); // 第0维排序
    int tot = 0;
    for (int i = 0; i < n;)
    {
        int cnt = 1;
        while (
            i + 1 < n 
            && cur[i].first->v[0] == cur[i + 1].first->v[0] 
            && cur[i].first->v[1] == cur[i + 1].first->v[1] 
            && cur[i].first->v[2] == cur[i + 1].first->v[2])
        {
            cnt++, i++;
        }
        cur[tot] = cur[i];
        cur[tot].first->sz = cnt;
        tot++, i++;
    }
    cdq(0, tot, 1); // 分治1、2维
    repne(i, 0, tot) 
        ans[cur[i].first->ans + cur[i].first->sz - 1] += cur[i].first->sz;
    repne(i, 0, n) printf("%d\n", ans[i]);
    return 0;
}
```



### 整体二分

【题号】LUOGU1527

【题目】多组询问，求静态矩阵第k小

【思路】对于单次询问，简单的二分可做。多组询问采用整体二分的方法，同时二分答案区间和答案在这个区间的询问。使用二维树状数组快速统计矩阵中小于等于一个数的数字个数。

```c++
// 二维树状数组模板
int n, tree[510][510]; // n-方阵的阶数
inline int lowbit(int x)
{
    return x & -x;
}
void add(int x, int y, int val)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            tree[i][j] += val;
}
int query(int x, int y)
{
    int ans = 0;
    for (int i = x; i; i ^= lowbit(i))
        for (int j = y; j; j ^= lowbit(j))
            ans += tree[i][j];
    return ans;
}

struct Node
{
    int x, y, val; // 行，列，值
    bool operator<(const Node &rhs) const
    {
        return val < rhs.val;
    }
} nodes[510 * 510]; // 按坐标存储矩阵
struct Query
{
    int x1, y1, x2, y2, k, id;
} querys[60010], ql[60010], qr[60010]; // querys-全部询问，ql/qr-buffer
int ans[60010], qltail, qrtail;
// 整体二分，[nbeg,nend)是答案的范围，[qbeg,qend)是询问的范围
void solve(int nbeg, int nend, int qbeg, int qend)
{
    if (qbeg >= qend) // 如果询问为空
        return;
    if (nbeg + 1 == nend) // 如果答案已经确定
    {
        repne(i, qbeg, qend) ans[querys[i].id] = nodes[nbeg].val;
        return;
    }
    int nmid = (nbeg + nend) >> 1;
    for (int i = nbeg; i < nmid; i++) // 二分答案，标记前一半元素
        add(nodes[i].x, nodes[i].y, 1);
    qltail = qrtail = 0;
    for (int i = qbeg; i < qend; i++)
    {
        Query &q = querys[i];
        // 统计询问的子矩阵中被标记的元素个数。容斥原理，奇加偶减。
        int cnt = query(q.x2, q.y2) - query(q.x1 - 1, q.y2) 
            - query(q.x2, q.y1 - 1) + query(q.x1 - 1, q.y1 - 1);
        if (cnt >= q.k)
            ql[qltail++] = q;
        else
        {
            q.k -= cnt;
            qr[qrtail++] = q;
        }
    }
    int qmid = copy(ql, ql + qltail, querys + qbeg) - querys;
    copy(qr, qr + qrtail, querys + qmid);
    for (int i = nbeg; i < nmid; i++) // 还原树状数组
        add(nodes[i].x, nodes[i].y, -1);
    solve(nbeg, nmid, qbeg, qmid);
    solve(nmid, nend, qmid, qend);
}
int main()
{
    int q;
    n = read(), q = read(); // 方阵阶数，询问个数
    int tot = 0;
    rep2(i, 1, n, j, 1, n)
    {
        nodes[tot].x = i, nodes[tot].y = j;
        nodes[tot++].val = read();
    }
    sort(nodes, nodes + tot); // 排序矩阵元素
    repne(i, 0, q)
    {
        Query &t = querys[i];
        t.x1 = read(), t.y1 = read();
        t.x2 = read(), t.y2 = read();
        t.k = read();
        t.id = i;
    }
    solve(0, tot, 0, q); // 整体二分
    repne(i, 0, q) printf("%d\n", ans[i]);
    return 0;
}
```



### Dancing Links

【题号】LUOGU1784

【题目】填写数独

【思路】精确覆盖问题是指：一个二进制串可以覆盖为1的位对应的列，求一种选择一些二进制串恰好覆盖所有列的方案。对于数独问题，为精确覆盖所有列的问题，使用DLX算法求解。规定第$i\times9+j$列表示第$i$行数字$j$已被使用，第$81+i\times9+j$列表示第$i$列数字$j$已被使用，第$81\times2+i\times9+j$表示第$i$个九宫数字$j$已被使用，第$81\times3+i\times9+j$列表示第$i$行$j$列已被填充，“第$x$行$y$列填写数字$i$”的方案对应一个二进制串。

```c++
const int MAX_ROW = 81 * 9;
const int MAX_COL = 81 * 4;
struct dancing_links
{
    struct dlx_node
    {
        int x, y; // 行号，列号
        dlx_node *lef, *rig, *up, *down; // 循环十字链表
    } nodes[MAX_ROW * MAX_COL + MAX_ROW + 10];
    dlx_node *row[MAX_ROW + 10], *col[MAX_COL + 10], *tail; // 行首，列首，尾节点
    int len[MAX_COL + 10]; // 每一列元素个数
    vector<int> ans;       // 选择的行号
    void init(int ncol) // 初始化，建立列首
    {
        tail = nodes + ncol;
        clr(row, 0);
        clr(len, 0);
        for (int i = 0; i <= ncol; i++)
        {
            dlx_node *node = col[i] = &nodes[i];
            *node = {0, i,
                     nodes + (i + ncol) % (ncol + 1),
                     nodes + (i + 1) % (ncol + 1),
                     node, node};
        }
    }
    void append(int x, int y) // 顺序添加节点
    {
        tail++, len[y]++;
        if (!row[x])
            row[x] = tail, tail->lef = tail->rig = tail;
        *tail = {x, y, row[x]->lef, row[x], col[y]->up, col[y]};
        tail->lef->rig = tail->rig->lef = tail;
        tail->up->down = tail->down->up = tail;
    }
    void cover(dlx_node *header) // 覆盖以header为列首的列以及该列中为1的行
    {
        header->lef->rig = header->rig, header->rig->lef = header->lef;
        for (dlx_node *u = header->down; u != header; u = u->down)
            for (dlx_node *v = u->rig; v != u; v = v->rig)
                v->down->up = v->up, v->up->down = v->down, len[v->y]--;
    }
    void uncover(dlx_node *header) // 撤销覆盖
    {
        header->lef->rig = header->rig->lef = header;
        for (dlx_node *u = header->down; u != header; u = u->down)
            for (dlx_node *v = u->rig; v != u; v = v->rig)
                v->down->up = v->up->down = v, len[v->y]++;
    }
    bool dance() // 求解精确覆盖
    {
        dlx_node *header = col[0]->rig;
        for (dlx_node *u = header; u != col[0]; u = u->rig)
            if (len[u->y] < len[header->y])
                header = u; // 选择元素个数最少的列
        if (header == col[0])
            return true; // 有解
        cover(header);
        for (dlx_node *u = header->down; u != header; u = u->down)
        {
            for (dlx_node *v = u->rig; v != u; v = v->rig)
                cover(col[v->y]);
            ans.push_back(u->x);
            if (dance())
                return true; // 有解
            ans.pop_back();
            for (dlx_node *v = u->rig; v != u; v = v->rig)
                uncover(col[v->y]);
        }
        uncover(header);
        return false; // 无解
    }
} dlx;

int suduku[20][20];
struct Node
{
    int x, y, val;
} trans[MAX_ROW + 10];
int main()
{
    rep2(i, 1, 9, j, 1, 9) readi(suduku[i][j]);
    dlx.init(81 * 4); // 初始化，待覆盖的列有81*4个
    int tot = 0;
    rep2(x, 1, 9, y, 1, 9) rep(i, 1, 9) // “第x行y列填写i”对应的二进制串
    {
        if (suduku[x][y] == 0 || i == suduku[x][y]) // 0-待填充，非零-已知数字
        {
            ++tot;
            // 第x行的i被占用
            dlx.append(tot, (x - 1) * 9 + i);
            // 第y列的i被占用
            dlx.append(tot, 81 + (y - 1) * 9 + i);
            // 九宫的i被占用
            dlx.append(tot, 81 * 2 + ((x - 1) / 3 * 3 + (y - 1) / 3) * 9 + i);
            // 格子被填充
            dlx.append(tot, 81 * 3 + (x - 1) * 9 + (y - 1) + 1);
            trans[tot] = {x, y, i};
        }
    }
    dlx.dance();
    for (int i : dlx.ans)
        suduku[trans[i].x][trans[i].y] = trans[i].val;
    rep2(i, 1, 9, j, 1, 9) printf("%d%c", suduku[i][j], j == 9 ? '\n' : ' ');
    return 0;
}
```



### 莫队

【题号】LUOGU1494

【题目】多组询问，区间中任选两个数字，求它们相同的概率

```c++
const int MAXN = 50010;
int sz; // 分块大小
struct Query
{
    int L, R, id;
    bool operator<(const Query &rhs) const
    {
        int b1 = L / sz, b2 = rhs.L / sz;
        if (b1 != b2)
            return b1 < b2; // 不同块内按块号排序
        return (R < rhs.R) ^ (b1 & 1); // 偶数块内R升序，奇数块内R降序
    }
} querys[MAXN];

// 莫队算法
ll sum1, sum2, cnt[MAXN]; // sum1-分子，sum2-总数，cnt[]-每种颜色的数量
ll ans1[MAXN], ans2[MAXN]; // ans1-答案的分子，ans2-答案的分母
void add(int color)
{
    ll &x = cnt[color];
    sum1 = sum1 - (x * (x - 1) / 2) + ((x + 1) * x / 2);
    sum2 = sum2 + 1;
    x++;
}
void erase(int color)
{
    ll &x = cnt[color];
    sum1 = sum1 - (x * (x - 1) / 2) + ((x - 1) * (x - 2) / 2);
    sum2 = sum2 - 1;
    x--;
}

ll gcd(ll a, ll b) // GCD模板
{
    return b == 0 ? a : gcd(b, a % b);
}

int c[MAXN]; // 序列
int main()
{
    int n, m; readi(n, m); // n-序列长度 m-询问数
    rep(i, 1, n) readi(c[i]);
    sz = (int)sqrt(n + 1); // 最优分块复杂度为O(n^(3/2))
    rep(i, 1, m) // 离线所有询问
    {
        readi(querys[i].L, querys[i].R);
        querys[i].id = i;
    }
    sort(querys + 1, querys + m + 1);
    int wndL = 1, wndR = 0; // 当前的滑动窗口[wndL, wndR]，初始化为空集
    rep(i, 1, m)
    {
        Query &q = querys[i];
        while (wndR < q.R) add(c[++wndR]);   // 先扩大窗口
        while (wndL > q.L) add(c[--wndL]);
        while (wndR > q.R) erase(c[wndR--]); // 再缩小窗口
        while (wndL < q.L) erase(c[wndL++]);
        if (sum1 == 0)
            ans1[q.id] = 0, ans2[q.id] = 1;
        else
        {
            ll sum3 = sum2 * (sum2 - 1) / 2;
            ll d = gcd(sum1, sum3);
            ans1[q.id] = sum1 / d, ans2[q.id] = sum3 / d;
        }
    }
    rep(i, 1, m) printf("%lld/%lld\n", ans1[i], ans2[i]);
    return 0;
}
```



### 带修改莫队

【题号】LUOGU1903

【题目】动态维护区间中不同颜色的数量，可离线。

```c++
const int MAXN = 140000;
int sz; // 分块大小
struct Query
{
    int L, R, T, id;
    bool operator<(const Query &rhs) const
    {
        if (L / sz != rhs.L / sz) return L < rhs.L;
        if (R / sz != rhs.R / sz) return R < rhs.R;
        return T < rhs.T; // 注意排序方式与普通莫队的区别
    }
} querys[MAXN];
struct Update
{
    int pos, val;
} updates[MAXN];

int s[MAXN], ans[MAXN];
int cnt[1000010], wnd; // cnt[i]-颜色i出现次数 wnd-当前窗口的答案
int wndL = 1, wndR = 0, wndT = 0;
void add(int color)
{
    if (++cnt[color] == 1) wnd++;
}
void erase(int color)
{
    if (--cnt[color] == 0) wnd--;
}
void change(Update &upd)
{
    if (wndL <= upd.pos && upd.pos <= wndR)
    {
        erase(s[upd.pos]);
        add(upd.val);
    }
    swap(upd.val, s[upd.pos]);
}

int main()
{
    int n = readu(), m = readu();
    rep(i, 1, n) s[i] = readu();
    sz = (int)pow(n + 1, 2.0 / 3.0); // 复杂度O(n^(5/3))
    int len1 = 0, len2 = 0;
    int t = 0;
    while (m--)
    {
        char op[4]; scanf("%s", op);
        int x = readu(), y = readu(); // readu()-读入优化
        if (op[0] == 'Q') // 查询第t次修改前[x, y]有多少种不同的颜色
            querys[len1] = {x, y, t, len1}, len1++;
        else if (op[0] == 'R') // 把x的颜色改为y
            updates[len2++] = {x, y}, t++;
    }
    sort(querys, querys + len1);
    repne(i, 0, len1)
    {
        Query &q = querys[i];
        while (wndT < q.T) change(updates[wndT++]); // 在时间轴上移动
        while (wndT > q.T) change(updates[--wndT]);
        while (wndR < q.R) add(s[++wndR]);
        while (wndL > q.L) add(s[--wndL]);
        while (wndR > q.R) erase(s[wndR--]);
        while (wndL < q.L) erase(s[wndL++]);
        ans[q.id] = wnd;
    }
    repne(i, 0, len1) printf("%d\n", ans[i]);
    return 0;
}
```



## 动态规划

### 数位DP

【题号】LIBREOJ10167

【题目】求[a, b]之间不含"4"和"62"的数的个数

```c++
vector<int> num; // 保存数字的每一位
int dp[20][20];  // 记忆化
int dfs(int dep, int pre, bool bound) // dep-当前填第几个数字 pre-前一个数字 lim-是否到达上界
{
    if (dep == -1) return 1;
    if (!bound && dp[dep][pre] != -1)
        return dp[dep][pre];
    int lim = bound ? num[dep] : 9;
    int ans = 0;
    rep(i, 0, lim)
    {
        if (i == 4 || pre == 6 && i == 2) continue;
        ans += dfs(dep - 1, i, bound && i == lim);
    }
    if (!bound)
        dp[dep][pre] = ans;
    return ans;
}
int query(int x)
{
    num.clear();
    for (; x; x /= 10)
        num.push_back(x % 10);
    return dfs(num.size() - 1, 10, true);
}
int main()
{
    int a, b;
    clr(dp, -1);
    while (readi(a, b) != EOF && a && b)
    {
        printf("%d\n", query(b) - query(a - 1));
    }
    return 0;
}
```



### 树型依赖背包

【题号】HDU1561

```c++
struct Edge
{
    int from, to, nxt;
} edges[1000];
int head[400], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = (Edge){from, to, head[from]};
    head[from] = edgeid++;
}

int r[400], dp[400][400], sz[400];
int dfsid, rdfn[400]; // dfs序为i的节点是rdfn[i]
int dfs(int u)
{
    sz[u] = 1;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        dfs(v);
        sz[u] += sz[v];
    }
    rdfn[++dfsid] = u;
}
int main()
{
    int n, m; // 物品总数，背包容量
    while (readi(n, m) != EOF && (n | m))
    {
        edgeid = 0;
        clr(head, -1);
        rep(i, 1, n)
        {
            int a, b; // a-i依赖于a b-物品的价值
            readi(a, b);
            addedge(a, i);
            r[i] = b;
        }
        dfsid = 0;
        dfs(0); // 所有物品依赖于虚拟物品0
        rep2(i, 1, n + 1, j, 1, m + 1)
        {
            int u = rdfn[i];
            // i - sz[u]: 如果不选u，它的子树都不能选
            dp[i][j] = max(dp[i - 1][j - 1] + r[u], dp[i - sz[u]][j]);
        }
        printf("%d\n", dp[n + 1][m + 1]);
    }
    return 0;
}
```



### 虚树优化的树型DP

【题号】LUOGU2495

【题目】求所有询问点均不能到达根节点的最小割

```c++
const int MAXN = 251000;
struct Edge
{
    int from, to, dis, nxt;
};
struct Graph
{
    Edge edges[MAXN * 2];
    int head[MAXN], edgeid;
    void init()
    {
        clr(head, -1);
        edgeid = 0;
    }
    void addedge(int from, int to, int dis)
    {
        edges[edgeid] = {from, to, dis, head[from]};
        head[from] = edgeid++;
    }
} G, G1; // G-原树 G1-虚树

// LCA模板
int tin[MAXN], tout[MAXN], fa[MAXN][20], dfsid;
ll cut[MAXN]; // cut[u]表示节点u到根节点路径上边权的最小值
void dfs(int u, int pre)
{
    fa[u][0] = pre;
    tin[u] = ++dfsid;
    for (int i = 1; i < 20; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = G.head[u]; ~i; i = G.edges[i].nxt)
    {
        Edge &e = G.edges[i];
        if (e.to == pre) continue;
        cut[e.to] = min((ll)e.dis, cut[u]);
        dfs(e.to, u);
    }
    tout[u] = ++dfsid;
}
bool isAncestor(int x, int y)
{
    return x == 0 || tin[x] <= tin[y] && tout[y] <= tout[x];
}
int lca(int x, int y)
{
    if (isAncestor(x, y)) return x;
    if (isAncestor(y, x)) return y;
    for (int i = 19; i >= 0; i--)
        if (!isAncestor(fa[x][i], y))
            x = fa[x][i];
    return fa[x][0];
}

bool q[MAXN];                  // 是否是询问的点
int h[MAXN], trace[MAXN], top; // 询问的点，栈，栈顶
bool cmp(int x, int y)         // 询问点按照DFS序排序
{
    return tin[x] < tin[y];
}
int build(int k) // 建虚树，只保留询问点及它们的LCA
{
    sort(h, h + k, cmp);
    trace[top = 1] = 1; // 保留根节点
    for (int i = 0; i < k; i++)
    {
        if (top == 1)
        {
            trace[++top] = h[i];
            continue;
        }
        int r = lca(trace[top], h[i]);
        for (; top > 1 && tin[trace[top - 1]] >= tin[r]; top--)
            G1.addedge(trace[top - 1], trace[top], cut[trace[top]]);
        if (trace[top] != r)
        {
            G1.addedge(r, trace[top], cut[trace[top]]);
            trace[top] = r;
        }
        trace[++top] = h[i];
    }
    for (; top > 1; top--)
        G1.addedge(trace[top - 1], trace[top], cut[trace[top]]);
    return trace[1]; // 返回虚树的根节点，本题中恒为1
}

ll dp(int u) // 树型DP
{
    ll ans = 0;
    for (int i = G1.head[u]; ~i; i = G1.edges[i].nxt)
    {
        int v = G1.edges[i].to;
        ans += dp(v);
    }
    if (q[u]) ans = cut[u];
    q[u] = false, G1.head[u] = -1; // O(k)复杂度的清空虚树，注意不要memset
    return min(ans, (ll)cut[u]);
}

int main()
{
    int n; readi(n); // 原树节点个数
    G.init(), G1.init(); // 链式前向星的初始化
    repne(i, 1, n) // n-1条树边
    {
        int u, v, w; readi(u, v, w);
        G.addedge(u, v, w), G.addedge(v, u, w);
    }
    clr(cut, INF);
    dfs(1, 0); // LCA预处理
    int m; readi(m);
    while (m--)
    {
        int k; readi(k); // 询问点个数
        repne(i, 0, k)
        {
            readi(h[i]);    // 读入询问点
            q[h[i]] = true; // 标记询问点
        }
        G1.edgeid = 0;       // 清空虚树的边
        int root = build(k); // 建立虚树
        ll ans = dp(root);   // 树型DP
        printf("%lld\n", ans);
    }
    return 0;
}
```



## 数据结构

### ST表 静态区间最值查询

```c++
const int MAXN = 1e5 + 10;
const int LOGN = 17;
int mm[MAXN];
int dp[MAXN][LOGN]; // dp[i][0]赋值为为原数组
void init(int n) // 初始化 n-数组长度
{
    for (int i = 2; i <= n; i++)
        mm[i] = i & (i - 1) ? mm[i - 1] : mm[i - 1] + 1;
    for (int k = 1; k < LOGN; k++)
    {
        int L = 1 << k;
        for (int i = 1; i + L - 1 <= n; i++)
            dp[i][k] = std::max(dp[i][k - 1], dp[i + (L >> 1)][k - 1]);
    }
}
ll rmq(int lt, int rt) // 查询区间[lt, rt]的最大值
{
    int k = mm[rt - lt];
    return std::max(dp[lt][k], dp[rt - (1 << k) + 1][k]);
}
```



### 树状数组 BIT

```c++
// 一维树状数组
struct binary_indexed_tree
{
    ll data[100010];
    int size; // 最大的下标
    void clear(int size)
    {
        this->size = size;
        memset(data + 1, 0, sizeof(ll) * size);
    }
    // 原数组 arr[idx] += delta
    void add(int idx, ll delta)
    {
        while (idx <= size)
        {
            data[idx] += delta;
            idx += idx & -idx;
        }
    }
    // 查询区间 [1, end] 的和
    ll query_sum(int end)
    {
        ll sum = 0;
        while (end)
        {
            sum += data[end];
            end ^= end & -end;
        }
        return sum;
    }
};

// 二维树状数组
struct binary_indexed_tree_2d
{
    ll data[5010][5010];
    int maxr, maxc; // 最大的下标
    void clear(int maxr, int maxc)
    {
        this->maxr = maxr, this->maxc = maxc;
        for(int i = 0; i <= maxr; i++)
            memset(data[i], 0, sizeof(ll)*maxc);
    }
    // 原数组 arr[r][c] += delta
    void add(int r, int c, ll delta)
    {
        for(int i = r; i <= maxr; i += i & -i)
            for(int j = c; j <= maxc; j += j & -j)
                data[i][j] += delta;
    }
    // 查询区间 [1, 1 : r, c] 的和
    ll query_sum(int r, int c)
    {
        ll sum = 0;
        for(int i = r; i; i ^= i & -i)
            for(int j = c; j; j ^= j & -j)
                sum += data[i][j];
        return sum;
    }
};
```

### 平衡树

#### Treap

```c++
struct Node
{
    int son[2], size, cnt, prior, val;
    // 左右儿子，子树节点个数，值重复次数，随机权值，值
} tree[10000000];
int nodeid; // 最大节点编号
int makenode(int val)
{
    tree[++nodeid] = (Node){0, 0, 1, 1, rand(), val};
    return nodeid;
}
void maintain(int p)
{
    Node &m = tree[p], &l = tree[m.son[0]], &r = tree[m.son[1]];
    m.size = l.size + r.size + m.cnt;
}
void rotate(int &root, int d) // d=0左旋, d=1右旋
{
    int p = tree[root].son[d ^ 1];
    tree[root].son[d ^ 1] = tree[p].son[d];
    tree[p].son[d] = root;
    maintain(root);
    maintain(p);
    root = p;
}
// 插入val，root为根节点，插入操作会更新根节点
void insert(int &root, int val)
{
    if (root == 0) // 如果平衡树为空
        root = makenode(val);
    else if (tree[root].val == val)
        tree[root].size++, tree[root].cnt++;
    else
    {
        int d = (int)(val > tree[root].val);
        int &branch = tree[root].son[d];
        insert(branch, val);
        if (tree[root].prior < tree[branch].prior)
            rotate(root, d ^ 1);
        maintain(root);
    }
}
// 删除val，root为根节点，删除操作会更新根节点
void remove(int &root, int val)
{
    if (root == 0)
        return;
    else if (tree[root].val == val)
    {
        int l = tree[root].son[0], r = tree[root].son[1];
        if (!l && !r)
        {
            tree[root].size--, tree[root].cnt--;
            if (tree[root].cnt == 0)
                root = 0;
        }
        else if (l && r)
        {
            int d = (int)(tree[l].prior > tree[r].prior);
            rotate(root, d);
            remove(tree[root].son[d], val);
        }
        else
        {
            int d = (int)(l > r);
            rotate(root, d);
            remove(tree[root].son[d], val);
        }
    }
    else
    {
        int d = tree[root].val < val;
        remove(tree[root].son[d], val);
    }
    maintain(root);
}
// 值val的排名（小于val的数个数+1）
int order(int root, int val)
{
    int ans = 0;
    while (root)
    {
        Node &m = tree[root];
        if (m.val == val)
            return ans + tree[m.son[0]].size;
        if (m.val > val)
            root = m.son[0];
        else
            ans += tree[m.son[0]].size + m.cnt, root = m.son[1];
    }
    return ans;
}
// 查询排序第k的数
int kth(int root, int k)
{
    while (root)
    {
        Node &m = tree[root];
        if (tree[m.son[0]].size >= k)
            root = m.son[0];
        k -= tree[m.son[0]].size;
        if (m.cnt >= k)
            return m.val;
        k -= m.cnt;
        root = m.son[1];
    }
    return 0x7FFFFFFF; // 如果节点没有k个，返回无穷大
}
// 查询val的前驱（最接近val的、严格小于val的数）
int prev(int root, int val)
{
    if (root == 0)
        return -0x7FFFFFFF;
    Node &m = tree[root];
    if (m.val >= val)
        return prev(m.son[0], val);
    return std::max(m.val, prev(m.son[1], val));
}
// 查询val的后继（最接近val的、严格大于val的数）
int nxt(int root, int val)
{
    if (root == 0)
        return 0x7FFFFFFF;
    Node &m = tree[root];
    if (m.val <= val)
        return nxt(m.son[1], val);
    return std::min(m.val, nxt(m.son[0], val));
}
```



#### FHQ Treap

```c++
template<typename T, int MAXN>
struct Treap
{
    struct Node
    {
        int son[2], size, cnt, w;
        T val;
    }tree[MAXN];
    int node_id, root;
    int makenode(T val)
    {
        Node& nod = tree[++node_id];
        nod = (Node){0, 0, 1, 1, rand(), val};
        return node_id;
    }
    void maintain(int id)
    {
        Node& mid = tree[id];
        const Node& ltree = tree[mid.son[0]];
        const Node& rtree = tree[mid.son[1]];
        mid.size = ltree.size + rtree.size + mid.cnt;
    }
    void splitByValue(T val, int p, int& l, int& r)
    {
        if(p == 0)
        {
            l = r = 0;
            return;
        }
        if(tree[p].val <= val)
        {
            l = p;
            splitByValue(val, tree[p].son[1], tree[l].son[1], r);
        }
        else
        {
            r = p;
            splitByValue(val, tree[p].son[0], l, tree[r].son[0]);
        }
        maintain(p);
    }
    void splitBySize(int size, int p, int& l, int& r)
    {
        if(p == 0)
        {
            l = r = 0;
            return;
        }
        int lsz = tree[tree[p].son[0]].size;
        if(lsz < size)
        {
            l = p;
            splitBySize(size - lsz - tree[p].cnt, tree[p].son[1], tree[l].son[1], r);
        }
        else
        {
            r = p;
            splitBySize(size, tree[p].son[0], l, tree[r].son[0]);
        }
        maintain(p);
    }
    int merge(int l, int r)
    {
        if(l == 0 || r == 0)return l | r;
        int p;
        if(tree[l].w < tree[r].w)
        {
            p = r;
            tree[r].son[0] = merge(l, tree[r].son[0]);
        }
        else
        {
            p = l;
            tree[l].son[1] = merge(tree[l].son[1], r);
        }
        maintain(p);
        return p;
    }
    void insert(T val)
    {
        int l, m, r;
        splitByValue(val, root, l, r);
        splitByValue(val - 1, l, l, m);
        if(m)tree[m].cnt++, tree[m].size++;
        else m = makenode(val);
        root = merge(merge(l, m), r);
    }
    void remove(T val)
    {
        int l, m, r;
        splitByValue(val, root, l, r);
        splitByValue(val - 1, l, l, m);
        if(m)
        {
            if(tree[m].cnt == 1)m = 0;
            else tree[m].cnt--, tree[m].size--;
        }
        root = merge(merge(l, m), r);
    }
    int rank(T val)
    {
        int l, r;
        splitByValue(val - 1, root, l, r);
        int ans = tree[l].size + 1;
        root = merge(l, r);
        return ans;
    }
    T kth(int k)
    {
        int l, r, p;
        splitBySize(k, root, l, r);
        for(p = l; tree[p].son[1]; p = tree[p].son[1]);
        root = merge(l, r);
        return tree[p].val;
    }
    T prev(T val)
    {
        int l, r, p;
        splitByValue(val - 1, root, l, r);
        for(p = l; tree[p].son[1]; p = tree[p].son[1]);
        root = merge(l, r);
        return tree[p].val;
    }
    T next(T val)
    {
        int l, r, p;
        splitByValue(val, root, l, r);
        for(p = r; tree[p].son[0]; p = tree[p].son[0]);
        root = merge(l, r);
        return tree[p].val;
    }
};
```



#### Splay Tree

```c++
template <typename T, int MAXN>
struct SplayTree
{
    struct Node
    {
        T val;
        int sz, cnt;
        Node *fa, *son[2];
    } tree[MAXN];
#define null ((Node *)&tree[0])
#define root tree[0].son[0]
    int nodeid;
    inline Node *makenode(T val)
    {
        tree[++nodeid] = (Node){val, 1, 1, null, null, null};
        return tree + nodeid;
    }
    inline void link(Node *u, Node *fa, int d)
    {
        if (u != null)
            u->fa = fa;
        fa->son[d] = u;
    }
    void init()
    {
        tree[nodeid = 0] = (Node){0, 0, 0, null, null, null};
        root = makenode(INF);
        link(makenode(-INF), root, 0);
    }
    inline void pushup(Node *u)
    {
        u->sz = u->cnt + u->son[0]->sz + u->son[1]->sz;
    }
    inline int dir(Node *u)
    {
        return u->fa->son[1] == u;
    }
    void rotate(Node *u)
    {
        Node *fa = u->fa, *ffa = fa->fa;
        int dfa = dir(u), dffa = dir(fa);
        link(u, ffa, dffa);
        link(u->son[dfa ^ 1], fa, dfa);
        link(fa, u, dfa ^ 1);
        pushup(fa);
        pushup(u);
    }
    void splay(Node *u, Node *top)
    {
        while (u->fa != top)
        {
            if (u->fa->fa != top)
                rotate(dir(u) == dir(u->fa) ? u->fa : u);
            rotate(u);
        }
    }
    Node *findpos(Node *u, T val)
    {
        while (true)
        {
            if (val < u->val && u->son[0] != null)
                u = u->son[0];
            else if (val > u->val && u->son[1] != null)
                u = u->son[1];
            else
                return u;
        }
    }
    bool find(T val)
    {
        splay(findpos(root, val), null);
        return root->val == val;
    }
    Node *prev(T val)
    {
        find(val);
        if (root->val < val)
            return root;
        return findpos(root->son[0], val);
    }
    Node *next(T val)
    {
        find(val);
        if (root->val > val)
            return root;
        return findpos(root->son[1], val);
    }
    void insert(T val)
    {
        Node *u = findpos(root, val), *v;
        if (u->val == val)
            u->cnt++, v = u;
        else
            link(v = makenode(val), u, val > u->val);
        splay(v, null);
    }
    void remove(T val)
    {
        Node *l = prev(val), *r = next(val);
        splay(l, null);
        splay(r, l);
        if (r->son[0]->cnt > 1)
            r->son[0]->cnt--;
        else
            r->son[0] = null;
        splay(r->son[0], null);
    }
    int rank(T val)
    {
        find(val);
        if (root->val >= val)
            return root->son[0]->sz;
        return root->son[0]->sz + root->cnt;
    }
    T kth(int k)
    {
        k++;
        Node *u = root;
        while (true)
        {
            if (u->son[0]->sz >= k)
            {
                u = u->son[0];
                continue;
            }
            k -= u->son[0]->sz;
            if (u->cnt >= k)
                return u->val;
            k -= u->cnt;
            u = u->son[1];
        }
    }
#undef null
#undef root
};
```



#### Scapegoat Tree

```c++
template <typename T, int MAXN>
struct Scapegoat_Tree
{
#define APLHA 0.75 // 平衡因子
    struct Node
    {
        T val;         // 值
        int cnt, sz;   // cnt-节点权值 sz-子树权值
        int rk, rkall; // rk-子树有效节点个数 rkall-子树节点总数
        Node *son[2];  // 左右儿子
        void pushup()
        {
            sz = son[0]->sz + son[1]->sz + cnt;
            rk = son[0]->rk + son[1]->rk + (cnt > 0);
            rkall = son[0]->rkall + son[1]->rkall + 1;
        }
        bool unbalance()
        {
            return ((son[0]->rkall > rkall * APLHA + 5) ||
                    (son[1]->rkall > rkall * APLHA + 5));
        }
    };
    Node tree[MAXN], *root, *tail, *null;
    vector<Node *> trace;
    void init()
    {
        root = tail = null = tree;
        *null = (Node){0, 0, 0, 0, 0, null, null};
    }
    Node *makenode(T val)
    {
        Node *p = ++tail;
        *p = (Node){val, 1, 1, 1, 1, null, null};
        return p;
    }
    void inorder(Node *p)
    {
        if (p == null)
            return;
        inorder(p->son[0]);
        if (p->cnt > 0)
            trace.push_back(p);
        inorder(p->son[1]);
    }
    Node *rebuild_help(int beg, int end)
    {
        if (beg >= end)
            return null;
        int mid = (beg + end) >> 1;
        Node *p = trace[mid];
        p->son[0] = rebuild_help(beg, mid);
        p->son[1] = rebuild_help(mid + 1, end);
        p->pushup();
        return p;
    }
    void rebuild(Node *&nod)
    {
        trace.clear();
        inorder(nod);
        nod = rebuild_help(0, trace.size());
    }
    Node **findnode(T val)
    {
        trace.clear();
        Node **cur = &root;
        while (true)
        {
            trace.push_back((Node *)cur);
            if ((*cur)->val == val || *cur == null)
                break;
            cur = &((*cur)->son[val > (*cur)->val]);
        }
        return cur;
    }
    int rank(T val)
    {
        findnode(val);
        int ans = 1;
        for (int i = 0; i < trace.size(); i++)
        {
            Node *nod = *(Node **)trace[i];
            if (nod->val < val)
                ans += nod->son[0]->sz + nod->cnt;
            else if (nod->val == val)
                ans += nod->son[0]->sz;
        }
        return ans;
    }
    T kth(int k)
    {
        for (Node *cur = root; cur != null;)
        {
            if (cur->son[0]->sz >= k)
                cur = cur->son[0];
            else if (cur->son[0]->sz + cur->cnt >= k)
                return cur->val;
            else
                k -= cur->son[0]->sz + cur->cnt, cur = cur->son[1];
        }
    }
    void insert(T val)
    {
        Node **cur = findnode(val);
        if (*cur == null)
            *cur = makenode(val);
        else
            (*cur)->cnt++;
        for (int i = trace.size() - 1; i >= 0; i--)
            (*(Node **)trace[i])->pushup();
        for (int i = 0; i < trace.size(); i++)
        {
            if ((*(Node **)trace[i])->unbalance())
            {
                rebuild(*(Node **)trace[i]);
                break;
            }
        }
    }
    void remove(T val)
    {
        Node **cur = findnode(val);
        (*cur)->cnt--;
        for (int i = trace.size() - 1; i >= 0; i--)
            (*(Node **)trace[i])->pushup();
        if (root->rk < APLHA * root->rkall)
            rebuild(root);
    }
    T prev(T val)
    {
        return kth(rank(val) - 1);
    }
    T next(T val)
    {
        return kth(rank(val + 1));
    }
#undef APLHA
};
```



### 树套树

【题号】LUOGU3380

【题目】在指定区间中询问排名、前驱、后继等信息

```c++
struct Node // Treap模板
{
    // son[]-左右儿子 size-秩 cnt-重复次数 prior-随机权值 val-值
    int son[2], size, cnt, prior, val;
} tree[10000000];
int nodeid;
int makenode(int val)
{
    tree[++nodeid] = (Node){0, 0, 1, 1, rand(), val};
    return nodeid;
}
void maintain(int p)
{
    Node &m = tree[p], &l = tree[m.son[0]], &r = tree[m.son[1]];
    m.size = l.size + r.size + m.cnt;
}
void rotate(int &root, int d) // d=0左旋, d=1右旋
{
    int p = tree[root].son[d ^ 1];
    tree[root].son[d ^ 1] = tree[p].son[d];
    tree[p].son[d] = root;
    maintain(root);
    maintain(p);
    root = p;
}
void insert(int &root, int val)
{
    if (root == 0)
        root = makenode(val);
    else if (tree[root].val == val)
        tree[root].size++, tree[root].cnt++;
    else
    {
        int d = (int)(val > tree[root].val);
        int &branch = tree[root].son[d];
        insert(branch, val);
        if (tree[root].prior < tree[branch].prior)
            rotate(root, d ^ 1);
        maintain(root);
    }
}
void remove(int &root, int val)
{
    if (root == 0) return;
    else if (tree[root].val == val)
    {
        int l = tree[root].son[0], r = tree[root].son[1];
        if (!l && !r)
        {
            tree[root].size--, tree[root].cnt--;
            if (tree[root].cnt == 0)
                root = 0;
        }
        else if (l && r)
        {
            int d = (int)(tree[l].prior > tree[r].prior);
            rotate(root, d);
            remove(tree[root].son[d], val);
        }
        else
        {
            int d = (int)(l > r);
            rotate(root, d);
            remove(tree[root].son[d], val);
        }
    }
    else
    {
        int d = tree[root].val < val;
        remove(tree[root].son[d], val);
    }
    maintain(root);
}
int order(int root, int val)
{
    int ans = 0;
    while (root)
    {
        Node &m = tree[root];
        if (m.val == val)
            return ans + tree[m.son[0]].size;
        if (m.val > val)
            root = m.son[0];
        else
            ans += tree[m.son[0]].size + m.cnt, root = m.son[1];
    }
    return ans;
}
int kth(int root, int k)
{
    while (root)
    {
        Node &m = tree[root];
        if (tree[m.son[0]].size >= k)
            root = m.son[0];
        k -= tree[m.son[0]].size;
        if (m.cnt >= k) return m.val;
        k -= m.cnt;
        root = m.son[1];
    }
    return 2147483647;
}
int prev(int root, int val)
{
    if (root == 0) return -2147483647;
    Node &m = tree[root];
    if (m.val >= val)
        return prev(m.son[0], val);
    return max(m.val, prev(m.son[1], val));
}
int nxt(int root, int val)
{
    if (root == 0) return 2147483647;
    Node &m = tree[root];
    if (m.val <= val)
        return nxt(m.son[1], val);
    return min(m.val, nxt(m.son[0], val));
}

int arr[50010];
int seg[50010 << 2]; // 线段树
void build(int p, int l, int r)
{
    for (int i = l; i <= r; i++)
    	insert(seg[p], arr[i]);
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}
void update(int p, int l, int r, int qpos, int qval)
{
    remove(seg[p], arr[qpos]);
    insert(seg[p], qval);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (qpos <= mid)
        update(p << 1, l, mid, qpos, qval);
    else
        update(p << 1 | 1, mid + 1, r, qpos, qval);
}
int query_order(int p, int l, int r, int ql, int qr, int qval)
{
    if (ql <= l && r <= qr)
        return order(seg[p], qval);
    int mid = (l + r) >> 1, ans = 0;
    if (ql <= mid)
        ans += query_order(p << 1, l, mid, ql, qr, qval);
    if (mid < qr)
        ans += query_order(p << 1 | 1, mid + 1, r, ql, qr, qval);
    return ans;
}
int query_kth(int l, int r, int ql, int qr, int k)
{
    int low = 0, high = 1e8;
    while (low < high)
    {
        int mid = (low + high + 1) >> 1;
        if (query_order(1, l, r, ql, qr, mid) + 1 > k)
            high = mid - 1;
        else
            low = mid;
    }
    return low;
}
int query_prev(int p, int l, int r, int ql, int qr, int qval)
{
    if (ql <= l && r <= qr)
        return prev(seg[p], qval);
    int mid = (l + r) >> 1, ans = -2147483647;
    if (ql <= mid)
        ans = max(ans, query_prev(p << 1, l, mid, ql, qr, qval));
    if (mid < qr)
        ans = max(ans, query_prev(p << 1 | 1, mid + 1, r, ql, qr, qval));
    return ans;
}
int query_nxt(int p, int l, int r, int ql, int qr, int qval)
{
    if (ql <= l && r <= qr)
        return nxt(seg[p], qval);
    int mid = (l + r) >> 1, ans = 2147483647;
    if (ql <= mid)
        ans = min(ans, query_nxt(p << 1, l, mid, ql, qr, qval));
    if (mid < qr)
        ans = min(ans, query_nxt(p << 1 | 1, mid + 1, r, ql, qr, qval));
    return ans;
}

int main()
{
    srand(time(NULL));
    int n, m; readi(n, m); // 序列长度，操作次数
    rep(i, 1, n) readi(arr[i]); // 要维护的序列
    build(1, 1, n);
    while (m--)
    {
        int op; readi(op);
        int l, r, k, pos;
        switch (op)
        {
        case 1: // 查询k在区间[l, r]内的排名
            readi(l, r, k);
            printf("%d\n", query_order(1, 1, n, l, r, k) + 1);
            break;
        case 2: // 查询区间[l, r]内排名为k的值
            readi(l, r, k);
            printf("%d\n", query_kth(1, n, l, r, k));
            break;
        case 3: // 修改序列pos位置的值为k
            readi(pos, k);
            update(1, 1, n, pos, k);
            arr[pos] = k;
            break;
        case 4: // 查询k在区间[l, r]内的前驱
            readi(l, r, k);
            printf("%d\n", query_prev(1, 1, n, l, r, k));
            break;
        case 5: // 查询k在区间[l, r]内的后继
            readi(l, r, k);
            printf("%d\n", query_nxt(1, 1, n, l, r, k));
            break;
        }
    }
    return 0;
}
```



### 可持久化线段树

【题号】LUOGU3834

【题目】静态区间第k小

```c++
const int MAXN = 2e5 + 10;
struct Node
{
    int sum, lc, rc; // 计数，左右儿子编号
} tree[MAXN * 20]; // 空间复杂度O(nlogn)
int root[MAXN], rootid; // 根节点，版本数量
/* // 建树
void build(int &u, int lt, int rt)
{
    u = ++rootid;
    if (lt == rt)
        return;
    int mid = (lt + rt) >> 1;
    build(tree[u].lc, lt, mid);
    build(tree[u].rc, mid + 1, rt);
}
*/
// 单点修改 pos-修改的位置 u-旧版本的根节点 返回新的根节点
int add(int pos, int u, int lt, int rt)
{
    int id = ++rootid;
    Node &nod = tree[id];
    nod = tree[u]; // 复制节点u
    nod.sum++; // 修改u的副本
    if (lt != rt)
    {
        int mid = (lt + rt) >> 1;
        if (pos <= mid)
            nod.lc = add(pos, nod.lc, lt, mid);
        else
            nod.rc = add(pos, nod.rc, mid + 1, rt);
    }
    return id;
}
// qlt,qrt-查询区间左右端点 lt,rt-当前区间左右端点 k-查询第k小
int query(int qlt, int qrt, int lt, int rt, int k)
{
    if (lt == rt) return lt;
    // 区间左儿子的数字个数
    int cnt = tree[tree[qrt].lc].sum - tree[tree[qlt].lc].sum;
    int mid = (lt + rt) >> 1;
    if (cnt >= k) // 如果>=k，查询左儿子
        return query(tree[qlt].lc, tree[qrt].lc, lt, mid, k);
    else // 否则查询右儿子
        return query(tree[qlt].rc, tree[qrt].rc, mid + 1, rt, k - cnt);
}

int a[MAXN], b[MAXN];
int main()
{
    int n, m; readi(n, m); // 序列长度，询问数
    repne(i, 0, n)
    {
        readi(a[i]); // 要查询的序列
        b[i] = a[i];
    }
    sort(b, b + n);
    int tot = unique(b, b + n) - b; // 离散化
    repne(i, 0, n)
    {
        int ord = lower_bound(b, b + tot, a[i]) - b + 1;
        root[i + 1] = add(ord, root[i], 1, tot);
    }
    while (m--)
    {
        int lt, rt, k; readi(lt, rt, k); // 查询闭区间[lt, rt]的第k小
        printf("%d\n", b[query(root[lt - 1], root[rt], 1, tot, k) - 1]);
    }
    return 0;
}
```



### 可持久化平衡树

【题号】LUOGU3835

```c++
const int MAXN = 1e6 + 10;
struct Node // FHQTreap模板
{
    int son[2], size, cnt, prior, val;
} tree[MAXN * 30];
int node_id;
int clone(int ori)
{
    tree[++node_id] = tree[ori];
    return node_id;
}
int makenode(int val)
{
    tree[++node_id] = (Node){0, 0, 1, 1, rand(), val};
    return node_id;
}
void maintain(int p)
{
    tree[p].size = 
        tree[tree[p].son[0]].size + tree[tree[p].son[1]].size + tree[p].cnt;
}
void split(int val, int p, int &l, int &r)
{
    if (p == 0)
    {
        l = r = 0;
        return;
    }
    int id = clone(p); // 只加这一行代码就可实现可持久化
    if (tree[id].val <= val)
    {
        l = id;
        split(val, tree[id].son[1], tree[l].son[1], r);
    }
    else
    {
        r = id;
        split(val, tree[id].son[0], l, tree[r].son[0]);
    }
    maintain(id);
}
int merge(int l, int r)
{
    if (l == 0 || r == 0) return l | r;
    int p;
    if (tree[l].prior < tree[r].prior)
    {
        p = r;
        tree[r].son[0] = merge(l, tree[r].son[0]);
    }
    else
    {
        p = l;
        tree[l].son[1] = merge(tree[l].son[1], r);
    }
    maintain(p);
    return p;
}
void insert(int &root, int val)
{
    int l, m, r;
    split(val, root, l, r);
    split(val - 1, l, l, m);
    if (m) tree[m].cnt++, tree[m].size++;
    else m = makenode(val);
    root = merge(merge(l, m), r);
}
void remove(int &root, int val)
{
    int l, m, r;
    split(val, root, l, r);
    split(val - 1, l, l, m);
    if (m)
    {
        if (tree[m].cnt == 1) m = 0;
        else tree[m].cnt--, tree[m].size--;
    }
    root = merge(merge(l, m), r);
}
int order(int &root, int val)
{
    int l, r;
    split(val - 1, root, l, r);
    int ans = tree[l].size + 1;
    root = merge(l, r);
    return ans;
}
int kth(int root, int k)
{
    int p = root;
    while (true)
    {
        if (tree[tree[p].son[0]].size >= k)
        {
            p = tree[p].son[0];
            continue;
        }
        k -= tree[tree[p].son[0]].size;
        if (k <= tree[p].cnt)
            return tree[p].val;
        k -= tree[p].cnt;
        p = tree[p].son[1];
    }
}
int prev(int &root, int val)
{
    int l, r, p;
    split(val - 1, root, l, r);
    for (p = l; tree[p].son[1]; p = tree[p].son[1]);
    root = merge(l, r);
    return tree[p].val;
}
int nxt(int &root, int val)
{
    int l, r, p;
    split(val, root, l, r);
    for (p = r; tree[p].son[0]; p = tree[p].son[0]);
    root = merge(l, r);
    return tree[p].val;
}

int root[MAXN], ver;
int main()
{
    srand(233333);
    int n; readi(n);
    insert(root[0], -2147483647);
    insert(root[0], 2147483647);
    for (ver = 1; ver <= n; ver++)
    {
        int v, opt, x;
        readi(v, opt, x);
        root[ver] = root[v]; // 在版本v的基础上操作
        switch (opt)
        {
        case 1: // 插入x数
            insert(root[ver], x);
            break;
        case 2: // 删除x数(若有多个相同的数，因只删除一个，如果没有请忽略该操作)
            remove(root[ver], x);
            break;
        case 3: // 查询x数的排名
            printf("%d\n", order(root[ver], x) - 1);
            break;
        case 4: // 查询排名为x的数
            printf("%d\n", kth(root[ver], x + 1));
            break;
        case 5: // 求x的前驱(前驱定义为小于x，且最大的数，如不存在输出-2147483647)
            printf("%d\n", prev(root[ver], x));
            break;
        case 6: // 求x的后继(后继定义为大于x，且最小的数，如不存在输出2147483647)
            printf("%d\n", nxt(root[ver], x));
            break;
        }
    }
    return 0;
}
```



```c++
// 另解：可持久化权值线段树+二分
const int MAXN=5e5+10;
struct Node
{
    Node *lson,*rson;
    int val;
}tree[MAXN*20];
int node_id;
Node* clone(Node* ori)
{
    tree[++node_id]=*ori;
    return &tree[node_id];
}
Node* update(Node* p,int lt,int rt,int qpos,int qval)
{
    Node* nod=clone(p);
    if(lt==rt)
    {
        nod->val=max(0, nod->val+qval);
        return nod;
    }
    int mid=(lt+rt)>>1;
    if(qpos<=mid)nod->lson=update(nod->lson,lt,mid,qpos,qval);
    else nod->rson=update(nod->rson,mid+1,rt,qpos,qval);
    nod->val=nod->lson->val+nod->rson->val;
}
int query(Node* p,int lt,int rt,int qlt,int qrt)
{
    if(qlt<=lt && rt<=qrt)return p->val;
    int mid=(lt+rt)>>1;
    int sum=0;
    if(qlt<=mid)sum+=query(p->lson,lt,mid,qlt,qrt);
    if(mid<qrt)sum+=query(p->rson,mid+1,rt,qlt,qrt);
    return sum;
}

int v[MAXN],opt[MAXN],x[MAXN],ord[MAXN],tot;
Node* root[MAXN];
void init()
{
    node_id=0;
    tree[0]=(Node){&tree[0],&tree[0],0};
    root[0]=&tree[0];
    root[0]=update(root[0],1,tot-1,1,1);
    root[0]=update(root[0],1,tot-1,tot-1,1);
}
int nth(Node* p,int lt,int rt,int n)
{
    if(lt==rt)return ord[lt];
    int mid=(lt+rt)>>1;
    if(p->lson->val > n)return nth(p->lson,lt,mid,n);
    else return nth(p->rson, mid+1, rt, n - p->lson->val);
}

int main()
{
    int n; readi(n);
    ord[1]=x[1]=-2147483647, ord[n+2]=x[n+2]=2147483647;
    rep(i,1,n)
    {
        readi(v[i],opt[i],x[i+1]);
        ord[i+1]=x[i+1];
    }
    sort(ord+1,ord+n+3);
    tot=unique(ord+1,ord+n+3)-ord;
    init();
    rep(i,1,n)
    {
        int id=lower_bound(ord+1,ord+tot,x[i+1])-ord;
        int k;
        switch(opt[i])
        {
        case 1: // 插入
            root[i]=update(root[v[i]],1,tot-1,id,1);
            break;
        case 2: // 删除
            root[i]=update(root[v[i]],1,tot-1,id,-1);
            break;
        case 3: // 排名
            root[i]=root[v[i]];
            printf("%d\n",query(root[v[i]],1,tot-1,1,id-1));
            break;
        case 4: // 第k小
            root[i]=root[v[i]];
            printf("%d\n",nth(root[v[i]],1,tot-1,x[i+1]));
            break;
        case 5: // 前驱
            root[i]=root[v[i]];
            k=query(root[v[i]],1,tot-1,1,id-1);
            printf("%d\n",nth(root[v[i]],1,tot-1,k-1));
            break;
        case 6: // 后继
            root[i]=root[v[i]];
            k=query(root[v[i]],1,tot-1,1,id);
            printf("%d\n",nth(root[v[i]],1,tot-1,k));
            break;
        }
    }
    return 0;
}
```



### 左偏树

【题号】LUOGU3377

【题目】维护n个小根堆，支持合并堆、弹出最小值的操作

```c++
const int MAXN = 1e5 + 10;
struct Node // 左偏树节点
{
    int dis, son[2]; // 左偏树节点必要信息：dis-到最近空节点的距离 son[]-左右儿子
    int val, pos;    // val-值 pos-位置
    bool operator<(const Node &rhs) const
    {
        return val < rhs.val || val == rhs.val && pos < rhs.pos;
    }
} tree[MAXN];
int join(int x, int y) // 合并x,y所在的堆，保证x,y都是堆顶，返回新的根
{
    if (!x || !y) return x | y; // 若x,y其中一个为空节点，返回另外一个节点
    if (tree[y] < tree[x]) swap(x, y); // 保证小根堆的性质
    int &lc = tree[x].son[0], &rc = tree[x].son[1];
    rc = join(rc, y);
    if (tree[lc].dis < tree[rc].dis) swap(lc, rc); // 保证左偏性：左链长于右链
    tree[x].dis = tree[rc].dis + 1;
    return x;
}

int fa[MAXN];
int findr(int x) // 并查集模板
{
    return x == fa[x] ? x : fa[x] = findr(fa[x]);
}

bool del[MAXN]; // 标记节点是否被删除
int main()
{
    int n, m; readi(n, m); // n-小根堆个数 m-操作数
    tree[0].dis = -1; // 左偏树初始化：空节点的dis=-1
    iota(fa, fa + n + 1, 0); // 并查集的初始化
    rep(i, 1, n)
    {
        readi(tree[i].val); // 初始每个节点单独成堆
        tree[i].pos = i;
    }
    while (m--)
    {
        int op; readi(op);
        if (op == 1) // 合并x,y所在的堆
        {
            int x, y; readi(x, y);
            if (del[x] || del[y] || findr(x) == findr(y)) continue; // 无效操作
            x = findr(x), y = findr(y); // 找到堆顶
            fa[x] = fa[y] = join(x, y); // 注意维护并查集
        }
        else if (op == 2) // 弹出x所在堆的最小值
        {
            int x; readi(x);
            if (del[x]) { puts("-1"); continue; } // 无效操作
            x = findr(x); // 找到堆顶
            printf("%d\n", tree[x].val); // 输出最小值
            int lc = tree[x].son[0], rc = tree[x].son[1];
            fa[x] = fa[lc] = fa[rc] = join(lc, rc); // 合并左右儿子，即弹出堆顶
            del[x] = true; // 删除标记
        }
    }
    return 0;
}
```



### K-D Tree

【题号】LUOGU4357

【题目】求平面第k远的点对的欧式距离的平方

【思路】建K-D Tree，维护每个划分区域的最远距离，启发式搜索。

```c++
const int MAX_DIM = 2; // 问题空间为二维平面
int dim;               // 当前划分的维度

struct Point
{
    int x[MAX_DIM];
    bool operator<(const Point &rhs) const
    {
        return x[dim] < rhs.x[dim];
    }
} pos[100010];
ll dis(const Point &lhs, const Point &rhs) // 欧式距离
{
    ll ans = 0;
    for (int i = 0; i < MAX_DIM; i++)
        ans += (ll)(lhs.x[i] - rhs.x[i]) * (lhs.x[i] - rhs.x[i]);
    return ans;
}

struct Node
{
    Point p, ul, br; // p-当前点 ul(br)-划分空间的最小（最大）坐标
    Node *son[2];    // 左右儿子
    void pushup()
    {
        ul = br = p;
        for (int d = 0; d < 2; d++)
        {
            if (son[d])
            {
                for (int i = 0; i < MAX_DIM; i++)
                {
                    ul.x[i] = min(ul.x[i], son[d]->ul.x[i]);
                    br.x[i] = max(br.x[i], son[d]->br.x[i]);
                }
            }
        }
    }
} tree[100010], *root, *tail;
void init()
{
    root = tail = tree;
}
void build(Node *&u, Point *beg, Point *end, int dep)
{
    if (beg >= end) return;
    dim = dep % MAX_DIM;
    Point *mid = beg + (end - beg) / 2;
    nth_element(beg, mid, end); // 找中位数
    u = tail++;
    u->p = *mid;
    build(u->son[0], beg, mid, dep + 1);
    build(u->son[1], mid + 1, end, dep + 1);
    u->pushup();
}

priority_queue<ll, vector<ll>, greater<ll>> topk;
ll h(const Point &p, const Node *u) // 估计函数：点到u的空间的最大距离
{
    return max(
        max(dis(p, u->ul), dis(p, (Point){u->ul.x[0], u->br.x[1]})),
        max(dis(p, u->br), dis(p, (Point){u->br.x[0], u->ul.x[1]})));
}
void dfs(const Node *u, const Point &p)
{
    ll hm = dis(p, u->p);
    if (hm > topk.top())
    {
        topk.pop();
        topk.push(hm);
    }
    for (int i = 0; i < 2; i++)
    {
        if (u->son[i] && h(p, u->son[i]) > topk.top())
        {
            dfs(u->son[i], p);
        }
    }
}

int main()
{
    int n, k; readi(n, k); // n个点，求第k远
    repne(i, 0, n) readi(pos[i].x[0], pos[i].x[1]);
    init(); // 初始化K-D Tree的一些指针
    build(root, pos, pos + n, 0);
    repne(i, 0, k << 1) topk.push(0); // 由于对称性，一个点对会被统计两次，所以应该求第2k远
    repne(i, 0, n) dfs(root, pos[i]);
    printf("%lld\n", topk.top());
    return 0;
}
```



### 字典树 Trie

```c++
struct Trie
{
    struct Node
    {
        int count; // 当前节点是多少个单词的结尾
        Node* nxt[26];
    }nodes[100010];
    int sz; // 节点总数
    Node* root; // 根节点
    Node* createNode()
    {
        Node* nod = &nodes[sz++];
        memset(nod, 0, sizeof(Node));
        return nod;
    }
    void init() // 初始化，清空字典树
    {
        sz = 0;
        root = createNode();
    }
    inline int id(char ch) // 字符映射到边
    {
        return ch - 'a';
    }
    int insert(const char* s) // 插入单词
    {
        Node* nod = root;
        const char* p = s;
        while(*p)
        {
            int v = id(*p);
            if(!nod->nxt[v])
            {
                nod->nxt[v] = createNode();
            }
            nod = nod->nxt[v];
            p++;
        }
        return nod->count++;
    }
    int find(const char* s) // 查找单词，返回出现次数
    {
        Node* nod = root;
        const char* p = s;
        while(*p)
        {
            int v = id(*p);
            if(!nod->nxt[v])return 0;
            nod = nod->nxt[v];
            p++;
        }
        return nod->count;
    }
};
```



## 树

### DSU-On-Tree

【题号】CF600E

【题目】树上每个节点一种颜色，求所有子树中数量最多的颜色，多个颜色最多时输出它们的和

【思路】暴力DFS统计，回溯时保留重儿子的统计信息，只需重新统计轻儿子。复杂度O(nlogn)。

```c++
const int MAXN = 1e5 + 10;
vector<int> adj[MAXN];  // 邻接表
int c[MAXN], son[MAXN]; // 节点颜色，重儿子

int dfs(int u, int pre) // 重链剖分
{
    int sum = 1, tmp = 0;
    for (int v : adj[u])
    {
        if (v == pre) continue;
        int t = dfs(v, u);
        sum += t;
        if (t > tmp) tmp = t, son[u] = v;
    }
    return sum;
}

int prior;                        // 重儿子
ll cnt[MAXN], curmax;             // 当前每种颜色的数量，当前最大值
ll sum, ans[MAXN];                // 当前答案，最终答案
void calc(int u, int pre, int op) // 统计颜色数量，op=1表示统计，-1表示清除
{
    cnt[c[u]] += op;
    if (cnt[c[u]] > curmax)
        curmax = cnt[c[u]], sum = c[u];
    else if (cnt[c[u]] == curmax)
        sum += c[u];
    for (int v : adj[u])
        if (v != pre && v != prior)
            calc(v, u, op);
}
void dfs1(int u, int pre, bool rst) // DSU-On-Tree rst表示计算完后是否清空cnt[]
{
    for (int v : adj[u])
        if (v != pre && v != son[u]) // 重儿子的cnt[]已经保留，不用统计
            dfs1(v, u, true);        // 轻儿子算完要清空
    if (son[u])
        dfs1(son[u], u, false); // 重儿子算完保留cnt[]
    prior = son[u];
    calc(u, pre, 1);
    ans[u] = sum;
    if (rst)
    {
        prior = -1;
        calc(u, pre, -1);
        curmax = -INF; // 注意当前最大值也要清空
    }
}

int main()
{
    int n; readi(n); // 节点数
    rep(i, 1, n) readi(c[i]); // 每个节点的颜色
    repne(i, 1, n)
    {
        int x, y; readi(x, y); // 树边
        adj[x].push_back(y), adj[y].push_back(x);
    }
    dfs(1, -1); // 重链剖分
    dfs1(1, -1, false); // DSU-On-Tree统计答案
    rep(i, 1, n) printf("%lld ", ans[i]);
    return 0;
}
```



### 最近公共祖先 LCA

【题号】LIBEROJ10134

【题目】静态维护树上链的长度

```c++
const int MAXN = 1e4 + 10;
const int MAXM = 2e4 + 10;
const int LOGN = 15;
struct Edge // 链式前向星模板
{
    int from, to, dis, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to, int dis)
{
    edges[edgeid] = (Edge){from, to, dis, head[from]};
    head[from] = edgeid++;
}

int tin[MAXN], tout[MAXN], dfsid; // dfs进入时间，离开时间
int fa[MAXN][LOGN]; // fa[i][j]: i的(1<<j)级祖先
ll dis[MAXN];       // dis[i]: i到根结点的距离
void dfs(int u, int pre)
{
    tin[u] = ++dfsid;
    fa[u][0] = pre;
    for (int i = 1; i < LOGN; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v != pre)
        {
            dis[v] = dis[u] + edges[i].dis;
            dfs(v, u);
        }
    }
    tout[u] = ++dfsid;
}
void init_lca(int root) // LCA的预处理
{
    memset(fa, 0, sizeof(fa));
    dfsid = 0;
    dfs(root, 0);
}
bool isAncestor(int fa, int x) // fa是否是x的祖先
{
    return !fa || (tin[fa] <= tin[x] && tout[x] <= tout[fa]);
}
int lca(int x, int y) // 求x、y的最近公共祖先
{
    if (isAncestor(x, y)) return x;
    if (isAncestor(y, x)) return y;
    for (int i = LOGN - 1; i >= 0; i--) // 倍增
        if (!isAncestor(fa[x][i], y))
            x = fa[x][i];
    return fa[x][0];
}

int main()
{
    int n, m; readi(n, m); // 节点数，询问数
    clr(head, -1), edgeid = 0; // 链式前向星的初始化
    repne(i, 1, n)
    {
        int u, v, w; readi(u, v, w); // 边的起止节点，长度
        addedge(u, v, w), addedge(v, u, w);
    }
    init_lca(1);
    while (m--)
    {
        int u, v; readi(u, v);
        int ans = dis[u] + dis[v] - 2 * dis[lca(u, v)]; // u到v的距离
        printf("%d\n", ans);
    }
    return 0;
}
```

###  树链剖分

【题号】LUOGU3384

【题目】动态维护链和子树的点权和

```c++
const int MAXN = 1e5 + 10;
struct Edge
{
    int from, to, nxt;
} edges[MAXN << 1];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = (Edge){from, to, head[from]};
    head[from] = edgeid++;
}

struct QTreeNode // 树链剖分
{
    ll val;           // 节点的权值
    int dep, sz, pos; // 深度、秩、在线段树中的位置
    int fa, son, top; // 父节点，重儿子，重链顶端节点
} nodes[MAXN];
int dfsid = 0, rpos[MAXN]; // 线段树中i位置对应的节点编号为rpos[i]，与pos互逆
void dfs1(int u, int pre) // u-当前节点 pre-父节点
{
    QTreeNode &cur = nodes[u];
    cur.fa = pre;
    cur.dep = nodes[pre].dep + 1;
    cur.sz = 1;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre) continue;
        dfs1(v, u);
        cur.sz += nodes[v].sz;
        if (nodes[v].sz >= nodes[cur.son].sz)
            cur.son = v;
    }
}
void dfs2(int u, int top) // u-当前节点 top-重链顶端节点
{
    QTreeNode &cur = nodes[u];
    cur.pos = ++dfsid, rpos[dfsid] = u;
    cur.top = top;
    if (cur.son)            // 如果不是叶节点
        dfs2(cur.son, top); // 先剖重链
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == cur.fa || v == cur.son) continue;
        dfs2(v, v); // 再剖轻链
    }
}

ll mod;
struct SegTreeNode // 线段树
{
    ll sum, lazy; // 区间和，lazy标记
} segtree[MAXN << 2];
void push_up(int p)
{
    segtree[p].sum = (segtree[p << 1].sum + segtree[p << 1 | 1].sum) % mod;
}
void push_down(int p, int lt, int rt)
{
    if (!segtree[p].lazy)
        return;
    int lc = p << 1, rc = lc | 1;
    int mid = (lt + rt) >> 1;
    segtree[lc].sum = (segtree[lc].sum + segtree[p].lazy * (mid - lt + 1)) % mod;
    segtree[lc].lazy = (segtree[lc].lazy + segtree[p].lazy) % mod;
    segtree[rc].sum = (segtree[rc].sum + segtree[p].lazy * (rt - mid)) % mod;
    segtree[rc].lazy = (segtree[rc].lazy + segtree[p].lazy) % mod;
    segtree[p].lazy = 0;
}
void build(int p, int lt, int rt)
{
    if (lt == rt)
    {
        segtree[p].sum = nodes[rpos[lt]].val;
        return;
    }
    int mid = (lt + rt) >> 1;
    build(p << 1, lt, mid);
    build(p << 1 | 1, mid + 1, rt);
    push_up(p);
}
// 线段树区间修改 qlt-区间左边界 qrt-区间右边界 qval-加多少
void add_range(int p, int lt, int rt, int qlt, int qrt, ll qval)
{
    if (qlt <= lt && rt <= qrt)
    {
        segtree[p].sum = (segtree[p].sum + qval * (rt - lt + 1)) % mod;
        segtree[p].lazy = (segtree[p].lazy + qval) % mod;
        return;
    }
    push_down(p, lt, rt);
    int lc = p << 1, rc = lc | 1;
    int mid = (lt + rt) >> 1;
    if (qlt <= mid)
        add_range(lc, lt, mid, qlt, qrt, qval);
    if (mid < qrt)
        add_range(rc, mid + 1, rt, qlt, qrt, qval);
    push_up(p);
}
// 线段树区间查询 qlt-区间左边界 qrt-区间右边界 返回区间和
ll query_range(int p, int lt, int rt, int qlt, int qrt)
{
    if (qlt <= lt && rt <= qrt)
        return segtree[p].sum;
    push_down(p, lt, rt);
    int lc = p << 1, rc = lc | 1;
    int mid = (lt + rt) >> 1;
    ll ans = 0;
    if (qlt <= mid)
        ans = query_range(lc, lt, mid, qlt, qrt);
    if (mid < qrt)
        ans = (ans + query_range(rc, mid + 1, rt, qlt, qrt)) % mod;
    return ans;
}
// 树链修改 n-节点总数 x,y-链的端点 qval-加多少
void add_chain(int n, int x, int y, ll qval)
{
    int topx = nodes[x].top, topy = nodes[y].top;
    while (topx != topy) // 如果不在一条链上
    {
        if (nodes[topx].dep > nodes[topy].dep) // 始终保证x是较浅的节点
            swap(topx, topy), swap(x, y);
        add_range(1, 1, n, nodes[topy].pos, nodes[y].pos, qval);
        y = nodes[topy].fa, topy = nodes[y].top;
    }
    if (nodes[x].dep > nodes[y].dep) swap(x, y);
    add_range(1, 1, n, nodes[x].pos, nodes[y].pos, qval);
}
// 树链查询 n-节点总数 x,y-链的端点
ll query_chain(int n, int x, int y)
{
    ll ans = 0;
    int topx = nodes[x].top, topy = nodes[y].top;
    while (topx != topy)
    {
        if (nodes[topx].dep > nodes[topy].dep)
            swap(topx, topy), swap(x, y);
        ans = (ans + query_range(1, 1, n, nodes[topy].pos, nodes[y].pos)) % mod;
        y = nodes[topy].fa, topy = nodes[y].top;
    }
    if (nodes[x].dep > nodes[y].dep) swap(x, y);
    ans = (ans + query_range(1, 1, n, nodes[x].pos, nodes[y].pos)) % mod;
    return ans;
}

int main()
{
    int n, m, r; readi(n, m, r); // 节点数、询问数、根节点编号
    scanf("%lld", &mod); // 取模
    rep(i, 1, n) scanf("%lld", &nodes[i].val);
    clr(head, -1);
    repne(i, 1, n) // 建树
    {
        int x, y; readi(x, y);
        addedge(x, y);
        addedge(y, x);
    }
    dfs1(r, 0), dfs2(r, r); // 两遍dfs完成树链剖分
    build(1, 1, n); // 建线段树
    while (m--)
    {
        int op; readi(op);
        int x, y; ll z;
        switch (op)
        {
        case 1: // 从x到y的链节点权值加上z
            readi(x, y); scanf("%lld", &z);
            add_chain(n, x, y, z);
            break;
        case 2: // 查询x到y的链的和
            readi(x, y);
            printf("%lld\n", query_chain(n, x, y));
            break;
        case 3: // 以x为根的子树节点权值加z
            readi(x); scanf("%lld", &z);
            add_range(1, 1, n, nodes[x].pos, nodes[x].pos + nodes[x].sz - 1, z);
            break;
        case 4: // 查询以x为根节点的子树的节点权值和
            readi(x);
            printf("%lld\n", 
                query_range(1, 1, n, nodes[x].pos, nodes[x].pos + nodes[x].sz - 1));
            break;
        }
    }
    return 0;
}
```



### 点分治

【题号】LUOGU2634

【题目】求树上任选一条链，链上边权和是3的倍数的概率

【思路】找到树的重心，只统计跨过重心的链，然后如此分治子树。复杂度O(nlogn)。

```c++
const int MAXN = 2e4 + 10;
struct Edge // 链式前向星模板
{
    int from, to, w, nxt;
} edges[MAXN * 2];
int head[MAXN], edgeid;
void addedge(int from, int to, int w)
{
    edges[edgeid] = (Edge){from, to, w, head[from]};
    head[from] = edgeid++;
}

int root, maxrk, rk[MAXN], totrk; // rk[]-子树的秩 totrk-当前子树的节点数
bool cg[MAXN];                    // 是否是分治过的重心
void getcg(int u, int pre)
{
    rk[u] = 1;
    int tmp = -INF;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre || cg[v]) continue;
        getcg(v, u);
        tmp = max(tmp, rk[v]);
        rk[u] += rk[v];
    }
    tmp = max(tmp, totrk - rk[u]);
    if (tmp < maxrk)
        root = u, maxrk = tmp;
}
int a, b;              // 是3的倍数的方案数，总方案数
int allcnt[4], cnt[4]; // 之前所有子树中、当前子树中模3为i的方案数
void dfs(int u, int sum, int pre) // u-当前节点 sum-root到u的链权值之和 pre-父节点
{
    sum = (sum % 3 + 3) % 3;
    cnt[sum]++;
    if (sum == 0)
        a += allcnt[0] + 1;
    else
        a += allcnt[3 - sum];
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre || cg[v]) continue;
        int w = edges[i].w;
        int t = sum + w;
        dfs(v, t, u);
    }
}
void solve(int u, int totrk) // u-子树中任意点 totrk-子树的总节点数
{
    maxrk = INF, ::totrk = totrk; // 注意getcg前的全局变量初始化
    getcg(u, -1);
    cg[u = root] = true; // root是全局变量，为防止被修改，getcg后将root复制给u
    clr(allcnt, 0);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (cg[v]) continue;
        clr(cnt, 0);
        dfs(v, edges[i].w, -1);
        for (int i = 0; i < 3; i++)
            allcnt[i] += cnt[i];
    }
    for (int i = head[u]; ~i; i = edges[i].nxt) // 分治root的每个子树
    {
        int v = edges[i].to;
        if (cg[v]) continue;
        if (rk[v] > rk[u]) // root上方的子树rk不正确，需在这里修正
            rk[v] = totrk - rk[u];
        solve(v, rk[v]);
    }
}

int gcd(int a, int b) // GCD模板
{
    return b == 0 ? a : gcd(b, a % b);
}
int main()
{
    int n; readi(n); // 节点数
    clr(head, -1), edgeid=0; // 链式前向星的初始化
    repne(i, 1, n)
    {
        int x, y, w; readi(x, y, w); // 边的起点，终点，权值
        addedge(x, y, w), addedge(y, x, w);
    }
    solve(1, n); // 点分治
    b = n * n;     // 总方案数
    a = a * 2 + n; // 加上对称和单个节点的方案数
    int d = gcd(a, b);
    printf("%d/%d", a / d, b / d);
    return 0;
}
```



### 动态点分治

【题号】SPOJ2939

【题目】多次询问树上一个点到最近白点的距离

```c++
const int MAXN = 1e5 + 10;
struct Edge // 链式前向星模板
{
    int from, to, nxt;
} edges[MAXN * 2];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

struct Heap // 小根堆，multiset很慢，请勿替代
{
    priority_queue<int, vector<int>, greater<int>> open, close;
    int size() { return open.size() - close.size(); }
    void push(int val) { open.push(val); }
    void pop(int val) { close.push(val); }
    int top()
    {
        while (!close.empty() && open.top() == close.top())
            open.pop(), close.pop();
        return open.top();
    }
};

struct Node // 点分树的节点
{
    int color;           // 节点颜色 1-白色 0-黑色
    int fa, dep, up[20]; // fa-父节点 dep-深度 up[i]-到深度为i的重心的距离
    Heap dis;            // 分治子树中所有节点到分治重心的距离
} tree[MAXN];
int root, totrk, rk[MAXN], maxrk;
bool cg[MAXN];
void getcg(int u, int pre) // 点分治模板：计算树的重心，答案保存到root中
{
    rk[u] = 1;
    int tmp = -INF;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre || cg[v]) continue;
        getcg(v, u);
        tmp = max(tmp, rk[v]);
        rk[u] += rk[v];
    }
    tmp = max(tmp, totrk - rk[u]);
    if (tmp < maxrk)
        maxrk = tmp, root = u;
}
void dfs(int u, int pre, int dep) // 计算up[]
{
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre || cg[v]) continue;
        tree[v].up[dep] = tree[u].up[dep] + 1;
        dfs(v, u, dep);
    }
}
// 建点分树：u-当前节点 pre-上一级分治重心 dep-深度 totrk-当前子树大小
void build(int u, int pre, int dep, int totrk)
{
    ::totrk = totrk, maxrk = INF; // 注意调用getcg前的全局变量初始化
    getcg(u, 0);
    cg[u = root] = true; // 注意root是全局变量，可能更改，所以先赋值给u
    Node &cur = tree[u];
    cur.fa = pre, cur.dep = dep, cur.color = 0;
    dfs(u, 0, dep);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (cg[v])
            continue;
        if (rk[v] > rk[u]) // root上方的子树rk计算不正确，需在这里修正
            rk[v] = totrk - rk[u];
        build(v, u, dep + 1, rk[v]);
    }
}
void change(int u) // 切换节点的颜色
{
    Node &nod = tree[u];
    nod.color ^= 1;
    if (nod.color == 1) // 如果变成白点，自底向上添加u到上级重心的距离
        for (int x = u; x; x = tree[x].fa) // 包括到自身的距离
            tree[x].dis.push(nod.up[tree[x].dep]);
    else // 如果变成白点，自底向上删除距离信息
        for (int x = u; x; x = tree[x].fa)
            tree[x].dis.pop(nod.up[tree[x].dep]);
}
int query(int u) // 查询离u最近的白点的距离
{
    int ans = INF;
    for (int x = u; x; x = tree[x].fa)
        if (tree[x].dis.size())
            ans = min(ans, tree[u].up[tree[x].dep] + tree[x].dis.top());
    return ans == INF ? -1 : ans;
}

int main()
{
    int n; readi(n); // 节点数
    clr(head, -1), edgeid = 0; // 链式前向星的初始化
    repne(i, 1, n)
    {
        int u, v; readi(u, v);
        addedge(u, v), addedge(v, u);
    }
    build(1, 0, 1, n); // 建点分树
    int q; readi(q); // 询问数
    while (q--)
    {
        int op, x; readi(op, x);
        if (op == 0) // 切换节点x的颜色
            change(x);
        else if (op == 1) // 查询与x最近的白点的距离
            printf("%d\n", query(x));
    }
    return 0;
}
```



### 动态树 Link-Cut-Tree

【题号】LUOGU1501

【题目】在动态连边和删边的树上，维护链上的节点权值和

```c++
const int MAXN = 1e5 + 10;
const int MOD = 51061;
struct Node // LCT维护无根树，有换根操作
{
    int flip, fa, son[2]; // LCT节点必要的信息：flip-翻转标记 fa-父节点 son[]-左右儿子
    ll val, ans;          // val-节点的值 ans-子树的答案
    ll add, mul;          // add-加法lazy标记 mul-乘法lazy标记
    int sz;               // 子树大小
} tree[MAXN];
inline void pushup(int u) // 计算要维护的信息
{
    int l = tree[u].son[0], r = tree[u].son[1];
    tree[u].sz = tree[l].sz + tree[r].sz + 1;
    tree[u].ans = (tree[l].ans + tree[r].ans + tree[u].val) % MOD;
}
inline void pushflip(int u)
{
    Node &nod = tree[u];
    swap(nod.son[0], nod.son[1]);
    nod.flip ^= 1;
}
inline void pushadd(int u, ll lazy) // 传递加法标记
{
    Node &nod = tree[u];
    nod.val = (nod.val + lazy) % MOD;
    nod.ans = (nod.ans + lazy * nod.sz) % MOD;
    nod.add = (nod.add + lazy) % MOD;
}
inline void pushmul(int u, ll lazy) // 传递乘法标记
{
    Node &nod = tree[u];
    nod.val = (nod.val * lazy) % MOD;
    nod.ans = (nod.ans * lazy) % MOD;
    nod.mul = (nod.mul * lazy) % MOD;
    nod.add = (nod.add * lazy) % MOD;
}
inline void pushdown(int u) // 传递所有标记
{
    Node &nod = tree[u];
    if (nod.flip == 1)
    {
        pushflip(nod.son[0]), pushflip(nod.son[1]);
        nod.flip = 0;
    }
    if (nod.mul != 1)
    {
        pushmul(nod.son[0], nod.mul), pushmul(nod.son[1], nod.mul);
        nod.mul = 1;
    }
    if (nod.add != 0)
    {
        pushadd(nod.son[0], nod.add), pushadd(nod.son[1], nod.add);
        nod.add = 0;
    }
}
inline int dir(int u) // 节点u在它父节点的哪一支
{
    return tree[tree[u].fa].son[1] == u;
}
inline bool isroot(int u) // 节点u是否是SplayTree的根节点
{
    int *son = tree[tree[u].fa].son;
    return son[0] != u && son[1] != u;
}
inline void rotate(int u)
{
    int fa = tree[u].fa, dfa = dir(u);
    int ffa = tree[fa].fa, dffa = dir(fa);
    int sub = tree[u].son[dfa ^ 1];
    tree[u].fa = ffa;            // 子-父连边
    if (!isroot(fa))             // 如果fa不是根节点
        tree[ffa].son[dffa] = u; // 连父-子实边，否则只有子-父虚边
    tree[u].son[dfa ^ 1] = fa, tree[fa].fa = u;
    tree[fa].son[dfa] = sub, tree[sub].fa = fa;
    pushup(fa), pushup(u); // 注意pushup的顺序
}
void splay(int u)
{
    static int up[MAXN];
    int tot = 0;
    for (int x = u;; x = tree[x].fa)
    {
        up[tot++] = x;
        if (isroot(x)) break;
    }
    while (tot--) // 自顶向下传递标记
        pushdown(up[tot]);
    while (!isroot(u))
    {
        int fa = tree[u].fa;
        if (!isroot(fa))
            rotate(dir(u) == dir(fa) ? fa : u);
        rotate(u);
    }
}
void access(int u) // 使根节点-u的链在一棵SplayTree上，u为最深的节点
{
    for (int rson = 0; u; rson = u, u = tree[u].fa)
    {
        splay(u);
        tree[u].son[1] = rson;
        pushup(u);
    }
}
void makeroot(int u) // 使u成为原树的根节点
{                    // makeroot操作后，u也是SplayTree的根节点，u无左儿子
    access(u);
    splay(u);
    pushflip(u);
}
int findroot(int u) // 返回u在原树中的根节点
{                   // findroot操作后，u为SplayTree的根节点
    access(u);
    splay(u);
    while (true)
    {
        pushdown(u);
        if (!tree[u].son[0]) return u;
        u = tree[u].son[0];
    }
}
void split(int x, int y) // 计算链x-y的信息，答案为tree[y].ans
{                        // split操作后，根节点y无右儿子，左儿子为以x为根的子树
    makeroot(x);
    access(y);
    splay(y);
}
void link(int x, int y) // 连接x、y两个节点，已连通则无效果
{
    makeroot(x);
    if (findroot(y) != x)
        tree[x].fa = y;
}
void cut(int x, int y) // 断开x、y两个节点，已连通则无效果
{
    split(x, y);
    if (tree[y].son[0] == x)
    {
        tree[x].fa = tree[y].son[0] = 0;
        pushup(y);
    }
}

int main()
{
    int n, q;  readi(n, q); // n-节点数 q-询问数
    rep(i, 1, n) tree[i].val = tree[i].ans = tree[i].mul = tree[i].sz = 1;
    repne(i, 1, n)
    {
        int u, v; readi(u, v);
        link(u, v); // 连初始边
    }
    while (q--)
    {
        char op[4]; reads(op);
        if (op[0] == '+') // 链u-v所有节点权值+c
        {
            int u, v, c; readi(u, v, c);
            split(u, v);	// 先分离出链u-v
            pushadd(v, c);	// 再将加法作用于根节点
        }
        else if (op[0] == '-') // 删边u1-v1，再加边u2-v2
        {
            int u1, v1, u2, v2; readi(u1, v1, u2, v2);
            cut(u1, v1); link(u2, v2);
        }
        else if (op[0] == '*') // 链u-v所有节点权值*c
        {
            int u, v, c; readi(u, v, c);
            split(u, v);
            pushmul(v, c);
        }
        else if (op[0] == '/') // 询问链u-v节点的权值和
        {
            int u, v; readi(u, v);
            split(u, v); // 分离出询问链后答案在根节点v上
            printf("%lld\n", tree[v].ans);
        }
    }
    return 0;
}
```



【题号】SPOJ16580

【题目】树上有黑白两色点，询问节点的同色连通块中的最大点权

【思路】两个LCT维护黑树和白树，节点的颜色记录在边上。比如在黑色LCT中，一个节点与父节点连边，表示该节点是黑色。这样，连通块中除根节点外其他节点都同色，根的儿子维护了所在子树的答案。

```c++
const int MAXN = 1e5 + 10;
struct Edge // 链式前向星模板
{
    int from, to, nxt;
} edges[MAXN * 2];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

struct Heap
{
    priority_queue<int> open, close;
    void push(int val) { open.push(val); }
    void pop(int val) { close.push(val); }
    int top()
    {
        while (!close.empty() && open.top() == close.top())
            open.pop(), close.pop();
        return open.size() ? open.top() : -INF; // maxwi为空时返回-INF
    }
};

int w[MAXN]; // 节点的权值
struct Node  // 有根树，不需要flip翻转标记
{
    int fa, son[2]; // LCT必要节点信息：fa-父节点 son[]-左右儿子
    int maxw;       // 实节点的最大权值
    Heap maxwi;     // 虚节点的最大权值，注意在access虚实转换时维护
};
struct LCT // LCT维护有根树，注意不能makeroot换根
{
    Node tree[MAXN];
    inline void pushup(int u) // 更新maxw
    {
        Node &nod = tree[u];
        nod.maxw = max(
            max(w[u], nod.maxwi.top()),
            max(tree[nod.son[0]].maxw, tree[nod.son[1]].maxw));
    }
    inline int dir(int u)
    {
        return tree[tree[u].fa].son[1] == u;
    }
    inline bool isroot(int u)
    {
        int *son = tree[tree[u].fa].son;
        return son[0] != u && son[1] != u;
    }
    inline void rotate(int u)
    {
        int fa = tree[u].fa, dfa = dir(u);
        int ffa = tree[fa].fa, dffa = dir(fa);
        int sub = tree[u].son[dfa ^ 1];
        tree[u].fa = ffa;
        if (!isroot(fa))
            tree[ffa].son[dffa] = u;
        tree[u].son[dfa ^ 1] = fa, tree[fa].fa = u;
        tree[fa].son[dfa] = sub, tree[sub].fa = fa;
        pushup(fa), pushup(u);
    }
    void splay(int u)
    {
        while (!isroot(u))
        {
            int fa = tree[u].fa;
            if (!isroot(fa))
                rotate(dir(u) == dir(fa) ? fa : u);
            rotate(u);
        }
    }
    void access(int u)
    {
        for (int rson = 0; u; rson = u, u = tree[u].fa)
        {
            splay(u);
            if (rson) // 维护虚儿子的信息
                tree[u].maxwi.pop(tree[rson].maxw);
            if (tree[u].son[1])
                tree[u].maxwi.push(tree[tree[u].son[1]].maxw);
            tree[u].son[1] = rson;
            pushup(u);
        }
    }
    int findroot(int u)
    {
        access(u), splay(u);
        while (tree[u].son[0])
            u = tree[u].son[0];
        return u;
    }
    void link(int x, int y) // 连有向边，y为父节点
    {                       // 维护的是有根树，不能使用makeroot，注意写法上的区别
        access(y), splay(y), splay(x);      // x无父节点，fa一定为空，不需要access(x)
        tree[x].fa = y, tree[y].son[1] = x; // 有向树上可以直接连实边
        pushup(y);
    }
    void cut(int x, int y) // 删有向边，y为父节点
    {
        access(x), splay(y);
        tree[y].son[1] = tree[x].fa = 0;
        pushup(y);
    }
} lct[2]; // lct[0]维护黑点组成的动态树，lct[1]维护白点的

int color[MAXN], fa[MAXN]; // color[]-节点的颜色 fa[]-原树中的父节点
void build(int u, int pre)
{
    fa[u] = pre;
    lct[color[u]].link(u, pre); // 节点的颜色记录在连向父节点的边上
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre) continue;
        build(v, u);
    }
}

int main()
{
    int n; readi(n); // 节点数
    clr(head, -1), edgeid = 0;
    repne(i, 1, n)
    {
        int u, v; readi(u, v);
        addedge(u, v), addedge(v, u);
    }
    rep(i, 1, n) readi(color[i]); // 读入每个节点的颜色
    rep(i, 1, n) readi(w[i]);     // 读入每个节点的权值
    w[0] = w[n + 1] = -INF;
    rep2(i, 0, 1, j, 0, n + 1) lct[i].tree[j].maxw = w[j];
    build(1, n + 1); // 根据有根树建LCT，规定根节点1的父节点为(n+1)
    int q; readi(q); // 询问数
    while (q--)
    {
        int op, u;
        readi(op, u);
        LCT &T = lct[color[u]];
        if (op == 0) // 询问u的同色连通块的最大点权
        {
            int r = T.findroot(u);
            T.splay(r); // 根一定与u不同色，右儿子是答案
            printf("%d\n", T.tree[T.tree[r].son[1]].maxw);
        }
        else if (op == 1) // 切换u的颜色
        {
            T.cut(u, fa[u]);
            lct[color[u] ^= 1].link(u, fa[u]);
        }
        else if (op == 2) // 修改u的权值
        {
            T.access(u), T.splay(u);                  // 将u转到根
            readi(w[u]);                              // 读入新的权值
            T.pushup(u), lct[color[u] ^ 1].pushup(u); // 注意pushup另一棵LCT
        }
    }
    return 0;
}
```



## 图

### 并查集

【题号】CF688C

【题目】判定一个图是否是二分图，输出左右支的节点

```c++
int fa[100100], rel[100100]; // fa[]-父节点 rel[]-与父节点的关系
int findr(int x) // 查询x所在树的根节点
{
    if (x == fa[x]) return x;
    int rx = findr(fa[x]);
    rel[x] = rel[x] ^ rel[fa[x]]; // 路径压缩，fa[x]更新为x的根节点，同时更新rel[x]
    return fa[x] = rx;
}
bool merge(int x, int y, int r) // 合并x和y，它们的关系为r
{
    int rx = findr(x), ry = findr(y);
    if (rx == ry)
        return (rel[x] ^ rel[y]) == r;
    rel[rx] = rel[x] ^ rel[y] ^ r;
    fa[rx] = ry;
    return true;
}
int main()
{
    int n, m; readi(n, m); // 节点数，边数
    rep(i, 1, n) fa[i] = i; // 并查集的初始化
    while (m--)
    {
        int u, v; readi(u, v); // (u, v)无向边
        if (!merge(u, v, 1)) // 如果合并时出现矛盾
        {
            puts("-1"); // 不是二分图
            return 0;
        }
    }
    rep(i, 1, n) findr(i); // 更新fa[]和rel[]
    int cnt = count(rel + 1, rel + n + 1, 0);
    printf("%d\n", cnt);
    rep(i, 1, n) if (rel[i] == 0) printf("%d ", i); // 左支
    printf("\n%d\n", n - cnt);
    rep(i, 1, n) if (rel[i] == 1) printf("%d ", i); // 右支
    return 0;
}
```

### 最短路

#### Dijkstra

【题目】LUOGU4779

```c++
const int MAXN = 1e5 + 10;
const int MAXM = 2e5 + 10;
struct Edge
{
    int from, to;
    ll dis;
    int nxt;
} edges[MAXM]; // 图的存储：链式前向星
int head[MAXN], edgeid;
void addedge(int from, int to, ll dis) // 添加从from到to、长度为dis的有向边
{
    edges[edgeid] = {from, to, dis, head[from]};
    head[from] = edgeid++;
}

struct HeapNode
{
    int pos; // 当前位置
    ll cost; // 到达这个位置的花费
    bool operator<(const HeapNode &rhs) const
    {
        return cost > rhs.cost;
    }
};
ll dis[MAXN];
void dijkstra(int src) // 求src到所有点的最短路，答案保存在dis[]
{
    priority_queue<HeapNode> Q;
    Q.push({src, 0});
    clr(dis, INF), dis[src] = 0;
    while (!Q.empty())
    {
        HeapNode cur = Q.top();
        Q.pop();
        if (cur.cost != dis[cur.pos])
            continue;
        for (int i = head[cur.pos]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (cur.cost + e.dis < dis[e.to])
            {
                dis[e.to] = cur.cost + e.dis;
                Q.push({e.to, dis[e.to]});
            }
        }
    }
}
int main()
{
    int n, m, s; readi(n, m, s); // 点数，边数，起点
    edgeid = 0, fill_n(head, n + 1, -1); // 链式前向星的初始化
    rep(i, 1, m)
    {
        int u, v, w; readi(u, v, w);
        addedge(u, v, w);
    }
    dijkstra(s); // 求s到所有点的最短路
    rep(i, 1, n) printf("%lld ", dis[i]);
    return 0;
}
```



#### SPFA

```c++
// LUOGU4779 SPFA解法
ll dis[MAXN];
bool vis[MAXN];
void spfa(int src)
{
    queue<int> Q;
    Q.push(src);
    clr(dis, INF), dis[src] = 0;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (dis[u] + e.dis >= dis[e.to]) continue;
            dis[e.to] = dis[u] + e.dis;
            if (!vis[e.to])
            {
                Q.push(e.to); // 如果一个点入队超过n次，则存在负环
                vis[e.to] = true;
            }
        }
    }
}
```



####  SPFA DFS判负环

```c++
int n, dis[510];
bool vis[510];
bool spfa(int u)
{
    vis[u] = true;
    bool ans = false;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to, c = edges[i].dis;
        if (dis[u] + c < dis[v]) // 改为“>”则判正环
        {
            dis[v] = dis[u] + c;
            if (vis[v] || spfa(v))
            {
                ans = true;
                break;
            }
        }
    }
    vis[u] = false;
    return ans;
}
bool check() // 存在负环返回true
{
    std::fill(dis, dis + n + 1, 0); // n-节点个数。增加超级源点，到其他点距离为0
    for (int i = 1; i <= n; i++) if (spfa(i)) return true;
    return false;
}
```



#### Floyd

```c++
ll adj[510][510]; // 邻接矩阵，下标从1开始
void floyd(int n) // 求任意两点的最短路，n为点的个数
{
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}
```



### 最小生成树

#### Kruskal

【题号】LUOGU3366

```c++
const int MAXN = 5e3 + 10;
const int MAXM = 2e5 + 10;
struct Edge
{
    int u, v, w;
    bool operator<(const Edge &rhs) const
    {
        return w < rhs.w;
    }
} edges[MAXM]; // 无向图

int fa[MAXN]; // 并查集模板
int findr(int x)
{
    return x == fa[x] ? x : fa[x] = findr(fa[x]);
}
bool merge(int x, int y)
{
    int rx = findr(x), ry = findr(y);
    if (rx == ry) return false;
    fa[rx] = ry;
    return true;
}

int kruskal(int n, int m) // 有解返回MST的权值，无解返回-1
{
    sort(edges, edges + m);
    int cnt = 1, ans = 0;
    repne(i, 0, m)
    {
        Edge &e = edges[i];
        if (merge(e.u, e.v))
            ans += e.w, cnt++;
    }
    return cnt == n ? ans : -1;
}
int main()
{
    int n, m; readi(n, m); // 点数，边数
    repne(i, 0, m) readi(edges[i].u, edges[i].v, edges[i].w);
    iota(fa + 1, fa + n + 1, 1); // 并查集初始化
    int ans = kruskal(n, m);
    if (ans != -1) printf("%d", ans);
    else printf("orz");
    return 0;
}
```



#### Prim

```c++
// LUOGU3366 Prim解法
struct Edge
{
    int from, to, w, nxt;
} edges[MAXM * 2]; // 双向边
int head[MAXN], edgeid;
void addedge(int from, int to, int w)
{
    edges[edgeid] = {from, to, w, head[from]};
    head[from] = edgeid++;
}
void addedge2(int u, int v, int w)
{
    addedge(u, v, w);
    addedge(v, u, w);
}

struct HeapNode
{
    int id, dis;
    bool operator<(const HeapNode &rhs) const
    {
        return dis > rhs.dis;
    }
};
bool vis[MAXN];
int prim(int n)
{
    priority_queue<HeapNode> Q;
    for (int i = head[1]; ~i; i = edges[i].nxt)
        Q.push({i, edges[i].w});
    fill_n(vis, n + 1, false), vis[1] = true;
    int cnt = 1, ans = 0;
    while (!Q.empty())
    {
        HeapNode node = Q.top();
        Q.pop();
        int u = edges[node.id].to;
        if (vis[u])
            continue;
        ans += node.dis;
        vis[u] = true, cnt++;
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (!vis[e.to])
                Q.push({i, e.w});
        }
    }
    return cnt == n ? ans : -1;
}

int main()
{
    int n, m; readi(n, m);
    edgeid = 0, fill_n(head, n + 1, -1); // 链式前向星的初始化
    rep(i, 1, m)
    {
        int u, v, w;
        readi(u, v, w);
        addedge2(u, v, w);
    }
    int ans = prim(n);
    if (ans != -1) printf("%d", ans);
    else printf("orz");
    return 0;
}
```



### 连通分量 Tarjan

#### 单连通分量

【题号】LUOGU3387

【题目】求有向图上一条点权和最大的链

【思路】在一个单连通分量中，任意两点可相互到达，采取贪心策略一定会经过分量中的所有点。将有向图的单连通分量缩成一个点，权值为原来所有点权之和，得到的新图是DAG，然后在DAG上DP。

```c++
const int MAXN = 1e4 + 10;
const int MAXM = 1e5 + 10;
struct Edge
{
    int from, to, nxt;
};
struct Graph
{
    Edge edges[MAXM];
    int head[MAXN], edgeid;
    Graph() // 链式前向星的初始化
    {
        clr(head, -1), edgeid = 0;
    }
    void addedge(int from, int to)
    {
        edges[edgeid] = {from, to, head[from]};
        head[from] = edgeid++;
    }
} G, G1; // G-原图 G1-缩点后的DAG

int w[MAXN], w1[MAXN]; // w[]-原图的点权 w1[]-缩点后的点权
int dfn[MAXN], low[MAXN], dfsid; // dfn[]-DFS序 low[]-可以连接的最小祖先
int grp[MAXN], grpid; // grp[]-缩点后每个节点的单连通分量编号，有向图缩点后得到DAG
vector<int> trace; // 维护tarjan递归的链
void tarjan(int u)
{
    dfn[u] = low[u] = ++dfsid;
    trace.push_back(u);
    for (int i = G.head[u]; ~i; i = G.edges[i].nxt)
    {
        int v = G.edges[i].to;
        if (!dfn[v])
        {
            tarjan(v); // 如果节点v没有访问，先计算它的low[v]
            low[u] = min(low[u], low[v]);
        }
        else if (!grp[v]) // 如果v访问过，且没有分组，即在当前的DFS链中
            low[u] = min(low[u], dfn[v]); // 更新最小祖先
    }
    if (dfn[u] == low[u]) // 如果u最小连接到自身，即是连通分量的根
    {
        grp[u] = ++grpid; // trace末尾直到u都属于一个连通分量
        w1[grpid] = w[u];
        while (trace.back() != u)
        {
            grp[trace.back()] = grpid;
            w1[grpid] += w[trace.back()]; // 更新缩点后的权值
            trace.pop_back();
        }
        trace.pop_back();
    }
}

int dp[MAXN];
int dfs(int u) // DAG上的DP
{
    if (~dp[u]) return dp[u];
    int tmp = 0;
    for (int i = G1.head[u]; ~i; i = G1.edges[i].nxt)
    {
        int v = G1.edges[i].to;
        tmp = max(tmp, dfs(v));
    }
    return dp[u] = w1[u] + tmp;
}

struct pair_hash // 自定义Hash函数
{
    size_t operator()(const pair<int, int> &x) const
    {
        return x.first * MAXN + x.second;
    }
};
int main()
{
    int n, m; readi(n, m); // n-节点数 m-边数
    rep(i, 1, n) readi(w[i]); // 节点的权值
    rep(i, 1, m)
    {
        int u, v; readi(u, v);
        G.addedge(u, v); // 原图的边
    }
    rep(i, 1, n) if (!dfn[i]) tarjan(i); // 计算强联通分量
    unordered_set<pair<int, int>, pair_hash> vis; // 防止G1中连重边
    repne(i, 0, G.edgeid)
    {
        int u = grp[G.edges[i].from], v = grp[G.edges[i].to];
        if (u != v && !vis.count({u, v}))
        {
            vis.insert({u, v});
            G1.addedge(u, v); // 建立缩点后的图
        }
    }
    int ans = 0;
    clr(dp, -1);
    rep(i, 1, grpid) ans = max(ans, dfs(i));
    printf("%d\n", ans);
    return 0;
}
```



#### 双连通分量

【题号】LIBREOJ10098

【题目】一个无向图，至少需要添加几条边，使得任意两个节点之间至少存在两条路径。

```c++
const int MAXN = 5e3 + 10;
const int MAXM = 1e4 + 10;
struct Edge
{
    int from, to, nxt;
} edges[MAXM * 2];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

// 无向图双连通分量的Tarjan，注意与单连通分量的区别
int dfn[MAXN], low[MAXN], dfsid;
int grp[MAXN], grpid; // 无向图缩点后得到有重边的树
vector<int> trace;
void tarjan(int u, int pre) // pre-父节点经过哪条边到达u
{
    dfn[u] = low[u] = ++dfsid;
    trace.push_back(u);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        if ((i ^ 1) == pre) continue; // 不经过反向边，保证求出来的双连通，注意运算符优先级
        int v = edges[i].to;
        if (!dfn[v])
        {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], dfn[v]); // 无向图中DFS，u、v一定在DFS链上
    }
    if (dfn[u] == low[u])
    {
        for (grp[u] = ++grpid; trace.back() != u; trace.pop_back())
            grp[trace.back()] = grpid;
        trace.pop_back();
    }
}

int main()
{
    int n, m; readi(n, m); // n-节点数 m-边数
    clr(head, -1), edgeid = 0; // 链式前向星的初始化
    while (m--)
    {
        int u, v; readi(u, v);
        addedge(u, v), addedge(v, u);
    }
    rep(i, 1, n) if (!dfn[i]) tarjan(i, -1); // Tarjan求双连通分量
    vector<int> deg(grpid + 1, 0); // 记录每个双连通分量的度
    for_each(edges, edges + edgeid, [&](const Edge &e) {
        if (grp[e.from] != grp[e.to])
            deg[grp[e.to]]++;
    });
    int k = count(deg.begin() + 1, deg.end(), 1); // 度为1的双连通分量个数
    printf("%d\n", (k + 1) / 2); // 度为1的分量两两连边，如果单一个，它与任意节点连边
    return 0;
}
```



#### 割点

```c++
bool cut[MAXN]; // cut[i]=true表示i是割点
int dfn[MAXN], low[MAXN], dfsid;
void tarjan(int u, int pre) // pre-父节点
{
    dfn[u] = low[u] = ++dfsid;
    int son = 0;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre) continue; // 不能直接走反向边
        if (!dfn[v])
        {
            son++; // 统计u有多少个互不连通的儿子
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            // 如果v不能通过其他路径绕到u上方，那么u是割点
            if (low[v] >= dfn[u]) cut[u] = true;
        }
        else low[u] = min(low[u], dfn[v]); // 无向图中DFS，u、v一定在一条DFS链上
    }
    if (pre == 0 && son < 2) // 如果是根节点并且连通分量小于2
        cut[u] = false;      // 则根节点不是割点
}
```



#### 割边

```c++
bool cut[MAXM * 2]; // cut[i]=true表示边i是割边
int dfn[MAXN], low[MAXN], dfsid;
void tarjan(int u, int pre)
{
    dfn[u] = low[u] = ++dfsid;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        if ((i ^ 1) == pre) continue; // 不直接走反向边，注意运算符优先级
        int v = edges[i].to;
        if (!dfn[v])
        {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            // 如果v不能绕到u或u的上方，那么i是割边
            if (low[v] > dfn[u]) cut[i] = cut[i ^ 1] = true;
        }
        else low[u] = min(low[u], dfn[v]);
    }
}
```



### 2-SAT

【题号】LIBREOJ10097

【题目】$n$个党派，第$i \in [1,n]$个党派有$2i-1$、$2i$两名代表，所有代表中，有$m$对存在矛盾，不能同时选择，求一种每个党派选出一名代表的方案。

```c++
const int MAXN = 8010;
const int MAXM = 20010;
struct Edge
{
    int from, to, nxt;
} edges[MAXM * 4];
int head[MAXN * 2], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

int dfn[MAXN * 2], low[MAXN * 2], dfsid;
int grp[MAXN * 2], grpid; // grp[]实际上是拓扑排序的逆序
vector<int> trace;
void tarjan(int u) // Tarjan强连通分量模板
{
    dfn[u] = low[u] = ++dfsid;
    trace.push_back(u);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (!dfn[v]) tarjan(v);
        if (!grp[v]) low[u] = min(low[u], low[v]); // 注意只有求有向图单连通分量时可以这样写
    }
    if (dfn[u] == low[u])
    {
        for (grp[u] = ++grpid; trace.back() != u; trace.pop_back())
            grp[trace.back()] = grpid;
        trace.pop_back();
    }
}

int main()
{
    int n, m; readi(n, m); // n-节点数 m-边数
    clr(head, -1), edgeid = 0; // 链式前向星的初始化
    repne(i, 0, m)
    {
        int u, v; readi(u, v); // u和v不能同时选
        u--, v--;          // 从0开始计数，与u同属一个党派的是u^1
        addedge(u, v ^ 1); // u->v^1：选了u就必须选v^1
        addedge(v, u ^ 1); // v->u^1：选了v就必须选u^1
        // 不能推出 u^1->v, v^1->u 这些关系
    }
    repne(i, 0, n << 1) if (!dfn[i]) tarjan(i);
    for (int i = 0; i < (n << 1); i += 2)
    {
        if (grp[i] == grp[i ^ 1]) // 出现矛盾，i与i^1在同一连通分量中
        {
            puts("NIE"); // 无解
            return 0;
        }
    }
    for (int i = 0; i < (n << 1); i++)
        if (grp[i] < grp[i ^ 1])   // 可能存在i^1->i的路径，表示如果选了i^1，那么i也必须选
            printf("%d\n", i + 1); // 所以只能选i，输出时记得+1
    }
    return 0;
}
```



### 圆方树

【题号】LibreOJ2587

【题目】求无向图中有多少个有序三元组$(s,c,f)$满足存在简单路径从$s$经过$c$到$f$。

【思路】建广义圆方树，每个圆点权值为-1，方点权值为双连通分量的大小。这样，选定起点$s$和终点$f$后，它们之间可以选择的中间点$c$的个数为圆方树上从$s$到$f$路径的点权和。DP计算每个点对答案的贡献。

```c++
const int MAXN = 1e5 + 10;
const int MAXM = 2e5 + 10;
struct Edge
{
    int from, to, nxt;
};
struct Graph // 链式前向星模板
{
    Edge edges[MAXM * 4];
    int head[MAXN * 2], edgeid;
    void init()
    {
        clr(head, -1), edgeid = 0;
    }
    void addedge(int from, int to)
    {
        edges[edgeid] = {from, to, head[from]};
        head[from] = edgeid++;
    }
} G, G1;

int dfn[MAXN], low[MAXN], dfsid;
int grpid;
vector<int> trace;
int w[MAXN * 2], totsz; // w[]-圆方树上节点权值 totsz-统计连通分量的节点数
void tarjan(int u) // 双连通分量缩点建圆方树
{
    dfn[u] = low[u] = ++dfsid;
    trace.push_back(u);
    totsz++;
    for (int i = G.head[u]; ~i; i = G.edges[i].nxt)
    {
        int v = G.edges[i].to; // 可以经过反向边到父节点
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u])
            {
                w[++grpid] = 1;
                G1.addedge(grpid, u), G1.addedge(u, grpid); // 连“圆点-方点”边
                for (int x; x != v; trace.pop_back()) // 注意不是退栈到u
                {
                    x = trace.back();
                    G1.addedge(x, grpid), G1.addedge(grpid, x);
                    ++w[grpid];
                }
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}

ll ans; // 最终答案
int n, m, sz[MAXN * 2]; // sz[]-子树中圆点的个数
void dp(int u, int pre) // 圆方树上的DP
{
    sz[u] = int(u <= n);
    ll cnt = 0; // 统计有多少条路径经过u
    for (int i = G1.head[u]; ~i; i = G1.edges[i].nxt)
    {
        int v = G1.edges[i].to;
        if (v == pre) continue;
        dp(v, u);
        cnt += (ll)sz[u] * sz[v];
        sz[u] += sz[v];
    }
    cnt += (ll)sz[u] * (totsz - sz[u]);
    ans += cnt * w[u];
}

int main()
{
    readi(n, m); // n-节点数 m-边数
    G.init(), G1.init();
    repne(i, 0, m)
    {
        int u, v; readi(u, v);
        G.addedge(u, v), G.addedge(v, u);
    }
    fill(w + 1, w + n + 1, -1); // 所有圆点权值设为-1
    grpid = n; // 方点从n+1开始编号
    rep(i, 1, n) if (!dfn[i]) // 处理每一个连通分量
    {
        totsz = 0; trace.clear(); // 注意Tarjan前的初始化
        tarjan(i); dp(i, -1); // 建圆方树后DP求答案
    }
    printf("%lld\n", ans * 2);
    return 0;
}
```



### 二分图匹配

#### 最大匹配 Hungary

【题号】UVA11419

【题目】一次可以消灭一行或一列网格中的敌人，最少几次可以消灭所有敌人

```c++
const int MAXN = 2e3 + 10;
const int MAXM = 2e6 + 10;
struct Edge
{
    int from, to, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = (Edge){from, to, head[from]};
    head[from] = edgeid++;
}

int lef[MAXN];  // 右支节点对应左支的匹配点，0表示未匹配
bool vis[MAXN]; // 是否是匈牙利树上的节点
bool augment(int u) // 増广 u-匈牙利树的根节点
{
    vis[u] = true;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (vis[v]) continue;
        vis[v] = true;
        if (!lef[v] || dfs(lef[v]))
        {
            lef[u] = v, lef[v] = u;
            return true;
        }
    }
    return false;
}
int maxmatch(int nx, int ny) // 计算最大匹配数 nx-左支节点数量 ny-右支节点数量
{
    int ans = 0;
    fill_n(lef, nx + ny + 1, 0);
    for (int i = 1; i <= nx; i++)
    {
        fill_n(vis, nx + ny + 1, false);
        ans += augment(i);
    }
    return ans;
}
void mincover(int nx, int ny) // 输出匹配方案 nx-左支节点数量 ny-右支节点数量
{
    fill_n(vis, nx + ny + 1, false);
    for (int i = 1; i <= nx; i++)
        if (!lef[i]) augment(i);
    for (int i = 1; i <= nx; i++)
        if (!vis[i]) printf(" r%d", i); // 左支
    for (int i = 1; i <= ny; i++)
        if (vis[nx + i]) printf(" c%d", i); // 右支
}
int main()
{
    int r, c, n;
    while (readi(r, c, n) != EOF && (r | c | n)) // 行数、列数、敌人数
    {
        clr(head, -1), edgeid = 0;
        repne(i, 0, n)
        {
            int x, y; readi(x, y);
            addedge(x, r + y); // 离散建图 左侧节点表示一行，右侧表示一列，连边表示矩阵中的点
        }
        printf("%d", maxmatch(r, c)); // 最少次数
        mincover(r, c);               // 选择的行列
        puts("");
    }
    return 0;
}
```



#### 最大匹配 Hopcroft Karp

```c++
const int MAXN = 100010;
const int MAXM = 300010;
struct Edge
{
    int from, to, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = (Edge){from, to, head[from]};
    head[from] = edgeid++;
}

int nx, ny, m; // 左支点数, 右支点数, 边数
int dep[MAXN], d;
int match[MAXN]; // i和谁匹配
bool vis[MAXN];
bool bfs()
{
    d = INF;
    std::queue<int> Q;
    std::fill_n(dep, nx + ny + 1, 0);
    for (int i = 1; i <= nx; i++)
    {
        if (!match[i])
        {
            dep[i] = 1;
            Q.push(i);
        }
    }
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        if (dep[u] > d)
            break;
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            int v = edges[i].to;
            if (dep[v])
                continue;
            dep[v] = dep[u] + 1;
            if (!match[v])
                d = dep[v];
            else
            {
                dep[match[v]] = dep[v] + 1;
                Q.push(match[v]);
            }
        }
    }
    return d != INF;
}
int dfs(int u)
{
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (vis[v] || dep[u] + 1 != dep[v])
            continue;
        vis[v] = true;
        if (match[v] && dep[v] == d)
            continue;
        if (!match[v] || dfs(match[v]))
        {
            match[u] = v, match[v] = u;
            return 1;
        }
    }
    return 0;
}
int hopcroft_karp() // 返回最大匹配数
{
    int ans = 0;
    while (bfs())
    {
        std::fill_n(vis, nx + ny + 1, false);
        for (int i = 1; i <= nx; i++)
        {
            if (!match[i])
                ans += dfs(i);
        }
    }
    return ans;
}
```



#### 最佳完美匹配 KM

【题号】HDU6346

【题目】$n$阶方阵$a_{ij}$，求$\max_{1 \leq i,j \leq n}\{\sum x_i + \sum y_j\}\ s.t.\ x_i+y_j \leq a_{ij}$

```c++
const int MAXN = 210;
int n;                 // 邻接矩阵大小
ll adj[MAXN][MAXN];    // 邻接矩阵
ll lx[MAXN], ly[MAXN]; // 顶标，满足lx[u]+ly[v]==adj[u][v]
ll slack[MAXN];
bool visy[MAXN];
int pre[MAXN];
int match[MAXN];      // 与右侧v匹配的是match[v]
void augment(int src) // BFS増广
{
    fill_n(visy, n + 1, false);
    fill_n(slack, n + 1, INF);
    int y = 0;
    match[0] = src;
    do
    {
        visy[y] = true;
        int u = match[y], tmpy;
        ll delta = INF;
        for (int v = 1; v <= n; v++)
        {
            if (visy[v]) continue;
            if (lx[u] + ly[v] - adj[u][v] < slack[v])
                slack[v] = lx[u] + ly[v] - adj[u][v], pre[v] = y;
            if (slack[v] < delta)
                delta = slack[v], tmpy = v;
        }
        for (int v = 0; v <= n; v++)
        {
            if (visy[v])
                lx[match[v]] -= delta, ly[v] += delta;
            else
                slack[v] -= delta;
        }
        y = tmpy;
    } while (~match[y]);
    for (; y; y = pre[y])
        match[y] = match[pre[y]];
}
ll km() // 返回最大匹配权值，match为匹配结果
{
    rep(i, 1, n) lx[i] = *max_element(adj[i] + 1, adj[i] + n + 1);
    fill_n(ly, n + 1, 0);
    fill_n(match, n + 1, -1);
    rep(i, 1, n) augment(i);
    ll ans = 0;
    rep(i, 1, n) ans += lx[i] + ly[i];
    return ans;
}

int main()
{
    int T; readi(T);
    rep(kase, 1, T)
    {
        readi(n); // 方阵阶数
        rep2(i, 1, n, j, 1, n)
        {
            int w; readi(w);
            adj[i][j] = -w; // 取反，求最小匹配
        }
        ll ans = km();
        printf("Case #%d: %lld\n", kase, -ans);
    }
    return 0;
}
```



### 网络流

#### 最大流 Dinic

【题号】LUOGU3376

【题目】网络流最大流模板题，求源点到汇点的最大流

```c++
const int MAXN = 10010;
const int MAXM = 200010;
struct Edge
{
    int from, to, flow, nxt; // 起点，终点，容量
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to, int flow)
{
    edges[edgeid] = (Edge){from, to, flow, head[from]};
    head[from] = edgeid++;
}
void addflow(int from, int to, int flow) // 添加一条流量
{
    addedge(from, to, flow);
    addedge(to, from, 0); // 反向边残量为0
}

int dep[MAXN], cur[MAXN]; // 分层，当前弧
bool bfs(int n, int src, int dst)
{
    fill_n(dep, n + 1, 0);
    dep[src] = 1;
    queue<int> Q;
    Q.push(src);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (dep[e.to] || e.flow <= 0) continue;
            dep[e.to] = dep[u] + 1;
            Q.push(e.to);
        }
    }
    return dep[dst] > 0;
}
int dfs(int u, int dst, int flow)
{
    if (u == dst) return flow;
    for (int &i = cur[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (dep[e.to] != dep[u] + 1 || e.flow <= 0) continue;
        int f = dfs(e.to, dst, min(flow, e.flow));
        if (f)
        {
            e.flow -= f;
            edges[i ^ 1].flow += f;
            return f;
        }
    }
    return 0;
}
int dinic(int n, int src, int dst)
{
    int ans = 0, f;
    while (bfs(n, src, dst))
    {
        copy(head, head + n + 1, cur);
        while (f = dfs(src, dst, INF)) ans += f;
    }
    return ans;
}

int main()
{
    int n, m, s, t; readi(n, m, s, t); // 点数，边数，源点，汇点
    clr(head, -1); // 链式前向星的初始化
    while (m--)
    {
        int a, b, f; readi(a, b, f); // 起点，终点，容量
        addflow(a, b, f);
    }
    printf("%d\n", dinic(n, s, t));
    // printf("%d\n", isap(n, s, t)); // 算法模板见下面，调用方式与Dinic一致
    return 0;
}
```



#### 最大流 ISAP

```c++
// LUOGU3376 ISAP解法，main函数同Dinic解法，见上
int dep[MAXN], cur[MAXN], num[MAXN], pre[MAXN];
void bfs(int n, int dst)
{
    fill_n(dep, n + 1, n);
    dep[dst] = 0;
    queue<int> Q;
    Q.push(dst);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i ^ 1];
            if (dep[e.from] < n || e.flow <= 0) continue;
            dep[e.from] = dep[u] + 1;
            Q.push(e.from);
        }
    }
}
int augment(int src, int dst)
{
    int f = INF;
    for (int u = dst; u != src; u = edges[pre[u]].from)
        f = min(f, edges[pre[u]].flow);
    for (int u = dst; u != src; u = edges[pre[u]].from)
    {
        edges[pre[u]].flow -= f;
        edges[pre[u] ^ 1].flow += f;
    }
    return f;
}
int isap(int n, int src, int dst)
{
    fill_n(num, n + 1, 0);
    bfs(n, dst);
    for (int i = 1; i <= n; i++)
    {
        num[dep[i]]++;
        cur[i] = head[i];
    }
    int u = src;
    int ans = 0;
    while (dep[src] < n)
    {
        if (u == dst)
        {
            ans += augment(src, dst);
            u = src;
            continue;
        }
        bool found = false;
        for (int &i = cur[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (dep[e.to] + 1 != dep[u] || e.flow <= 0) continue;
            found = true;
            u = e.to;
            pre[u] = i;
            break;
        }
        if (!found)
        {
            int mindep = n - 1;
            for (int i = head[u]; ~i; i = edges[i].nxt)
            {
                Edge &e = edges[i];
                if (e.flow > 0) mindep = min(mindep, dep[e.to]);
            }
            if (--num[dep[u]] == 0) break;
            num[dep[u] = mindep + 1]++;
            cur[u] = head[u];
            if (u != src) u = edges[pre[u]].from;
        }
    }
    return ans; // 返回最大流的值
}
```



#### 最小费用最大流

【题号】LUOGU3381

【题目】最小费用最大流模板题，求源点到汇点的最小费用最大流

```c++
const int MAXN = 5010;
const int MAXM = 100010;
struct Edge
{
    int from, to, flow, dis, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to, int flow, int dis)
{
    edges[edgeid] = (Edge){from, to, flow, dis, head[from]};
    head[from] = edgeid++;
}
void addflow(int from, int to, int flow, int dis)
{
    addedge(from, to, flow, dis);
    addedge(to, from, 0, -dis);
}

int dis[MAXN], pre[MAXN]; // 最短路长度，最短路树
bool vis[MAXN];
bool spfa(int n, int src, int dst)
{
    fill_n(dis, n + 1, INF);
    dis[src] = 0;
    queue<int> Q;
    Q.push(src);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        vis[u] = false;
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (e.flow <= 0 || dis[u] + e.dis >= dis[e.to]) continue;
            dis[e.to] = dis[u] + e.dis;
            pre[e.to] = i;
            if (!vis[e.to])
            {
                Q.push(e.to);
                vis[e.to] = true;
            }
        }
    }
    return dis[dst] < INF;
}
int maxflow, mincost; // 最大流，取得最大流的最小费用
void mcmf(int n, int src, int dst) // 答案保存在maxflow和mincost中
{
    maxflow = mincost = 0;
    while (spfa(n, src, dst))
    {
        int f = INF;
        for (int u = dst; u != src; u = edges[pre[u]].from)
            f = min(f, edges[pre[u]].flow);
        for (int u = dst; u != src; u = edges[pre[u]].from)
        {
            edges[pre[u]].flow -= f;
            edges[pre[u] ^ 1].flow += f;
            mincost += f * edges[pre[u]].dis;
        }
        maxflow += f;
    }
}

int main()
{
    int n, m, s, t; readi(n, m, s, t); // 点数，边数，源点，汇点
    clr(head, -1);
    while (m--)
    {
        int u, v, w, f; readi(u, v, w, f); // 起点，终点，容量，费用
        addflow(u, v, w, f);
    }
    mcmf(n, s, t);
    printf("%d %d", maxflow, mincost);
    return 0;
}
```



#### 无源汇有上下界可行流（需再整理）

【题号】LibreOJ115

【题目】无源汇有上下界可行流模板题，求无源汇有上下界可行流，输出每条边的流量。

```c++
const int MAXN = 400;
const int MAXM = 10210;
struct Edge
{
    int from, to, flow, nxt;
} edges[MAXM * 6]; // 注意开6倍
int head[MAXN], edgeid;
void addedge(int from, int to, int flow)
{
    edges[edgeid] = {from, to, flow, head[from]};
    head[from] = edgeid++;
}
int isrc, idst; // isrc-虚拟源点 idst-虚拟汇点
void addflow(int from, int to, int flow)
{
    // if (flow == 0) return; // 本题为找边方便没有加这个优化
    addedge(from, to, flow);
    addedge(to, from, 0);
}
void addflow(int from, int to, int lower, int upper)
{
    addflow(from, to, upper - lower); // from到to连分离出来的流量
    addflow(isrc, to, lower); // 虚拟源点将下界流量送到to
    addflow(from, idst, lower); // from将下界流量送到虚拟汇点
}
// 省略Dinic模板...
int main()
{
    int n, m; readi(n, m); // n-节点数 m-边数
    isrc = n + 1, idst = isrc + 1; // 定义虚拟源汇点
    clr(head, -1), edgeid = 0; // 链式前向星的初始化
    int sum = 0;
    repne(i, 0, m)
    {
        int u, v, lower, upper;
        readi(u, v, lower, upper);
        addflow(u, v, lower, upper);
        sum += lower; // 统计下界流量
    }
    if (dinic(idst, isrc, idst) == sum) // 如果虚拟源汇的流量能流满，则有可行解
    {
        puts("YES");
        for (int i = 0; i < edgeid; i += 6) // 可行流量=分离边的流量+下界流量
        {
            printf("%d\n", edges[i + 1].flow
                 + edges[i + 2].flow + edges[i + 3].flow);
        }
    }
    else puts("NO"); // 无解
    return 0;
}
```



#### 有源汇有上下界最大流

【题号】LibreOJ116

【题目】有源汇有上下界最大流模板题

```c++
const int MAXN = 400;
const int MAXM = 10010;
struct Edge
{
    int from, to, flow, nxt;
} edges[MAXM * 6]; // 注意开6倍
int head[MAXN], edgeid;
void addedge(int from, int to, int flow)
{
    edges[edgeid] = {from, to, flow, head[from]};
    head[from] = edgeid++;
}

int isrc, idst; // isrc-虚拟源点 idst-虚拟汇点
void addflow(int from, int to, int flow)
{
    if (flow == 0) return;
    addedge(from, to, flow);
    addedge(to, from, 0);
}
void addflow(int from, int to, int lower, int upper)
{
    addflow(from, to, upper - lower); // from到to连分离出来的流量
    addflow(isrc, to, lower);         // 虚拟源点将下界流量送到to
    addflow(from, idst, lower);       // from将下界流量送到虚拟汇点
}

int dep[MAXN], cur[MAXN];
bool bfs(int n, int src, int dst)
{
    fill_n(dep, n + 1, 0);
    dep[src] = 1;
    queue<int> Q;
    Q.push(src);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (e.to == 0) continue; // 跳过被删除的边
            if (dep[e.to] || e.flow <= 0) continue;
            dep[e.to] = dep[u] + 1;
            Q.push(e.to);
        }
    }
    return dep[dst] > 0;
}
int dfs(int u, int dst, int flow)
{
    if (u == dst)
        return flow;
    for (int &i = cur[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (e.to == 0) continue; // 跳过被删除的边
        if (dep[e.to] != dep[u] + 1 || e.flow <= 0) continue;
        int f = dfs(e.to, dst, min(flow, e.flow));
        if (f)
        {
            e.flow -= f, edges[i ^ 1].flow += f;
            return f;
        }
    }
    return 0;
}
int dinic(int n, int src, int dst)
{
    int ans = 0, f;
    while (bfs(n, src, dst))
    {
        copy(head, head + n + 1, cur);
        while (f = dfs(src, dst, INF))
            ans += f;
    }
    return ans;
}

int main()
{
    int n, m, src, dst; readi(n, m, src, dst); // src-源点 dst-汇点
    isrc = n + 1, idst = isrc + 1; // 定义虚拟源汇点
    clr(head, -1); // 链式前向星的初始化
    int sum = 0;
    repne(i, 0, m)
    {
        int u, v, lower, upper;
        readi(u, v, lower, upper);
        addflow(u, v, lower, upper);
        sum += lower; // 统计下界流量
    }
    int id = edgeid;
    addflow(dst, src, INF); // 汇点向源点连容量为INF的边，并记录这条边的ID
    if (dinic(idst, isrc, idst) == sum) // 如果虚拟源汇的流量能流满，则有可行解
    {
        for (int i = head[isrc]; ~i; i = edges[i].nxt)
            edges[i].to = 0;
        for (int i = head[idst]; ~i; i = edges[i].nxt)
            edges[i].to = 0;
        edges[id].to = edges[id ^ 1].to = 0; // 删除点isrc、点idst和边id
        int ans = edges[id ^ 1].flow;  // 答案先加上可行流
        ans += dinic(n + 2, src, dst); // 再加残量网络上的源点到汇点的最大流
        printf("%d", ans);
    }
    else puts("please go home to sleep"); // 无解
    return 0;
}
```



#### 有源汇有上下界最小流

【题号】LibreOJ117

【题目】有源汇有上下界最小流模板题

```c++
const int MAXN = 50010;
const int MAXM = 125100;
struct Edge
{
    int from, to, flow, nxt;
} edges[MAXM * 6]; // 注意开6倍
int head[MAXN], edgeid;
void addedge(int from, int to, int flow)
{
    edges[edgeid] = {from, to, flow, head[from]};
    head[from] = edgeid++;
}

int isrc, idst; // isrc-虚拟源点 idst-虚拟汇点
void addflow(int from, int to, int flow)
{
    if (flow == 0)
        return;
    addedge(from, to, flow);
    addedge(to, from, 0);
}
void addflow(int from, int to, int lower, int upper)
{
    addflow(from, to, upper - lower); // from到to连分离出来的流量
    addflow(isrc, to, lower);         // 虚拟源点将下界流量送到to
    addflow(from, idst, lower);       // from将下界流量送到虚拟汇点
}

int dep[MAXN], cur[MAXN];
bool bfs(int n, int src, int dst)
{
    fill_n(dep, n + 1, 0);
    dep[src] = 1;
    queue<int> Q;
    Q.push(src);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (e.to == 0) continue;
            if (dep[e.to] || e.flow <= 0) continue;
            dep[e.to] = dep[u] + 1;
            Q.push(e.to);
        }
    }
    return dep[dst] > 0;
}
int dfs(int u, int dst, int flow)
{
    if (u == dst) return flow;
    for (int &i = cur[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (e.to == 0) continue;
        if (dep[e.to] != dep[u] + 1 || e.flow <= 0) continue;
        int f = dfs(e.to, dst, min(flow, e.flow));
        if (f)
        {
            e.flow -= f, edges[i ^ 1].flow += f;
            return f;
        }
    }
    return 0;
}
int dinic(int n, int src, int dst)
{
    int ans = 0, f;
    while (bfs(n, src, dst))
    {
        copy(head, head + n + 1, cur);
        while (f = dfs(src, dst, INF)) ans += f;
    }
    return ans;
}

int main()
{
    int n, m, src, dst; readi(n, m, src, dst);
    isrc = n + 1, idst = isrc + 1; // 定义虚拟源汇点
    clr(head, -1); // 链式前向星的初始化
    int sum = 0;
    repne(i, 0, m)
    {
        int u, v, lower, upper;
        readi(u, v, lower, upper);
        addflow(u, v, lower, upper);
        sum += lower; // 统计下界流量
    }
    int id = edgeid;
    addflow(dst, src, INF);             // 汇点向源点连容量为INF的边，并记录这条边的ID
    if (dinic(idst, isrc, idst) == sum) // 如果虚拟源汇的流量能流满，则有可行解
    {
        for (int i = head[isrc]; ~i; i = edges[i].nxt)
            edges[i].to = edges[i ^ 1].to = 0;
        for (int i = head[idst]; ~i; i = edges[i].nxt)
            edges[i].to = edges[i ^ 1].to = 0;
        edges[id].to = edges[id ^ 1].to = 0;   // 删除点isrc、点idst和边id
        int ans = edges[id ^ 1].flow;
        ans -= dinic(idst, dst, src); // ans=可行流-汇点到源点的最大流
        printf("%d", ans);
    }
    else puts("please go home to sleep"); // 无解
    return 0;
}
```



## 字符串

### Hash

```c++
struct string_hash
{
    ull _hashc[2000010], *hashc;
    const ull base = 233; // 大于字符种类数的质数
    ull powb[2000010] = {1};
    void init(char *s) // 初始化，计算powb、hashc
    {
        hashc = _hashc + 1;
        for (int i = 0; s[i]; i++)
        {
            powb[i + 1] = powb[i] * base;
            hashc[i] = hashc[i - 1] * base + s[i];
        }
    }
    ull substr(int lt, int rt) // 子串s[lt : rt]的哈希值
    {
        return hashc[rt] - hashc[lt - 1] * powb[rt - lt + 1];
    }
    ull concat(int lt1, int rt1, int lt2, int rt2) //s[lt1:rt1] + s[lt2:rt2]的哈希值
    {
        if (lt1 > rt1 && lt2 > rt2)
            return 0ULL;
        if (lt1 > rt1)
            return substr(lt2, rt2);
        if (lt2 > rt2)
            return substr(lt1, rt1);
        return substr(lt1, rt1) * powb[rt2 - lt2 + 1] + substr(lt2, rt2);
    }
};
```

### KMP

```c++
struct kmp
{
    int nxt[1000010];
    void init_nxt(const char* pat) // 初始化，计算nxt数组
    {
        int pre = -1, cur = 0;
        nxt[0] = -1;
        while(pat[cur])
        {
            if(pre == -1 || pat[pre] == pat[cur])
            {
                pre++, cur++;
                // next数组优化，表示最终回退位置
                nxt[cur] = (pat[pre] == pat[cur] ? nxt[pre] : pre);
                //不优化，表示最大前后缀长度
                // nxt[cur] = pre;
            }
            else
            {
                pre = nxt[pre];
            }
        }
    }
    void operator()(const char* dst, const char* pat) // 匹配
    {
        int i = 0, j = 0;
        while(dst[i])
        {
            if(j == -1 || dst[i] == pat[j])
            {
                i++, j++;
                if(pat[j] == '\0')
                {
                    // 匹配dst[i-j:i-1]
                    j=nxt[j];
                }
            }
            else j = nxt[j];
        }
    }
};
```

### 扩展KMP

```c++
struct extend_kmp
{
    int nxt[100010] /* 最长前缀 */, ext[100010];
    void init_nxt(const char* pat) // 初始化，计算nxt数组
    {
        int p = 0, mx = 0, i;
        for(i = 1; pat[i]; i++)
        {
            int k = i > mx ? i : i + nxt[i - p] - 1;
            if(k < mx)nxt[i] = nxt[i - p];
            else
            {
                k = mx + 1;
                int j = i > mx ? 0 : k - i;
                while(pat[k] && pat[k] == pat[j])k++, j++;
                p = i;
                mx = std::max(p, k - 1);
                nxt[i] = k - i;
            }
        }
        nxt[0] = i;
    }
    void operator()(const char* dst, const char* pat) // 匹配，计算ext数组
    {
        int p, mx = -1, i;
        for(i = 0; dst[i]; i++)
        {
            int k = i > mx ? i : i + nxt[i - p] - 1;
            if(k < mx)ext[i] = nxt[i - p];
            else
            {
                int k = mx + 1;
                int j = k - i;
                while(dst[k] && dst[k] == pat[j])k++, j++;
                p = i;
                mx = std::max(p, k - 1);
                ext[i] = k - i;
            }
        }
    }
};
```

### Manacher

```c++
struct manacher
{
    char s[2000100]; // #分隔的字符串
    int palin[2000100]; // 以i为对称轴的回文串长度为palin[i]-1
    void loadString(const char* str)
    {
        char* p = s;
        *(p++) = '#';
        const char* q = str;
        while(*q)
        {
            *(p++) = *(q++);
            *(p++) = '#';
        }
    }
    void calc_palin() // 计算palin数组
    {
        int p, far = 0;
        for(int i = 0; s[i]; i++)
        {
            int lt, rt;
            if(i < far)rt = std::min(i + palin[(p << 1) - i] - 1, far);
            else rt = i;
            lt = (i << 1) - rt;
            while(lt >= 0 && s[lt] == s[rt])lt--, rt++;
            if(rt - 1 > far)
            {
                far = rt - 1;
                p = i;
            }
            palin[i] = rt - i;
        }
    }
};
```



### 后缀自动机 SAM

【题号】SPOJ1812

【题目】求多个字符串的最长公共子串长度

```c++
const int MAXN = 1e5 + 10;
struct Node
{
    int link, len, nxt[26]; // 后缀链接，当前节点可以表示的最长子串长度
} sam[MAXN << 1];
int sz = 1, last = 1; // 后缀自动机节点个数，最新的节点编号
void extend(int ch)
{
    int cur = ++sz, pre = last;
    sam[cur].len = sam[pre].len + 1;
    while (pre && !sam[pre].nxt[ch])
    {
        sam[pre].nxt[ch] = cur;
        pre = sam[pre].link;
    }
    if (!pre) sam[cur].link = 1;
    else
    {
        int ori = sam[pre].nxt[ch];
        if (sam[ori].len == sam[pre].len + 1)
            sam[cur].link = ori;
        else
        {
            int clone = ++sz;
            sam[clone] = sam[ori];
            sam[clone].len = sam[pre].len + 1;
            sam[cur].link = sam[ori].link = clone;
            while (pre && sam[pre].nxt[ch] == ori)
            {
                sam[pre].nxt[ch] = clone;
                pre = sam[pre].link;
            }
        }
    }
    last = cur;
}

char s[MAXN];
int bin[MAXN], ord[MAXN << 1];       // 桶，节点的拓扑序
int dp[MAXN << 1], dpall[MAXN << 1]; // 当前串与第一个串在节点i匹配的最大长度
int main()
{
    reads(s);
    int L = strlen(s);
    for (char *p = s; *p; p++)
        extend(*p - 'a');            // 建第一个字符串的后缀自动机
    rep(i, 2, sz) bin[sam[i].len]++; // 桶排序，节点按len排序就是拓扑序
    rep(i, 1, L) bin[i] += bin[i - 1];
    rep(i, 2, sz) ord[bin[sam[i].len]--] = i; // 排序后第i个节点编号是ord[i]
    clr(dpall, INF);
    while (reads(s) != EOF)
    {
        clr(dp, 0);
        int cur = 1, len = 0;
        for (char *p = s; *p; p++)
        {
            int ch = *p - 'a';
            if (sam[cur].nxt[ch]) // 匹配，长度+1
            {
                cur = sam[cur].nxt[ch];
                len++;
                dp[cur] = max(dp[cur], len);
                continue;
            }
            while (cur && !sam[cur].nxt[ch])
                cur = sam[cur].link; // 失配，沿后缀链接后退
            if (cur == 0)
                cur = 1, len = 0; // 如果退到空串
            else
            {
                len = sam[cur].len + 1;
                cur = sam[cur].nxt[ch];
                dp[cur] = max(dp[cur], len);
            }
        }
        for (int i = sz - 1; i >= 1; i--) // dp沿后缀链接向上传递
        {
            int u = ord[i];
            // 如果字符串u可以匹配，它的后缀一定可以匹配
            if (dp[u]) dp[sam[u].link] = sam[sam[u].link].len;
        }
        rep(i, 2, sz) dpall[i] = min(dpall[i], dp[i]);
    }
    int ans = *max_element(dpall + 2, dpall + sz + 1);
    printf("%d", ans);
    return 0;
}
```



### 回文自动机 PAM

【题号】LUOGU5496

【题目】求一字符串每个位置结尾的回文串个数

```c++
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
```

## 数学

### 高斯消元

```c++
const int MAXN = 104;
const double eps = 1e-15;
struct gauss_elimination
{
    double* mat[MAXN];
    // 保证系数矩阵为方阵，化为行最简矩阵
    int operator()(double arr[][MAXN], int nequ) // 系数矩阵，行数
    {
        for(int i = 0; i < nequ; i++)
            mat[i] = arr[i];
        int nvar = 0;
        for(int c = 0; c < nequ; c++)
        {
            int k = -1;
            double tmp = 0;
            for(int r = nvar; r < nequ; r++)
                if(fabs(mat[r][c]) > tmp)
                    tmp = fabs(mat[r][c]), k = r;
            if(k == -1)continue;
            std::swap(mat[nvar], mat[k]);
            for(int r = 0; r < nequ; r++)
            {
                if(fabs(mat[r][c]) < eps || r == nvar)continue;
                for(int i = c + 1; i <= nequ; i++)
                {
                    mat[r][i] -= mat[nvar][i] / mat[nvar][c] * mat[r][c];
                }
                mat[r][c] = 0;
            }
            nvar++;
        }
        for(int r = 0; r < nvar; r++)
        {
            bool zero = true;
            for(int c = r; c < nequ; c++)
            {
                if(fabs(mat[r][c]) > eps)
                {
                    zero = false;
                    break;
                }
            }
            if(zero && fabs(mat[r][nequ]) > eps)return 0; // 无解
        }
        return nvar; // 返回主元个数
    }
};
```



## 计算几何（未完整测试，不保证正确性）

### 通用

```c++
const double eps = 1e-8; // 精度
const double PI = acos(-1); // 圆周率

// 控制精度的比较函数
// x==0返回0, x>0返回1, x<0返回-1
inline int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    return x > 0 ? 1 : -1;
}

inline double radToDeg(double ang)
{
    return ang / PI * 180.;
}

inline double degToRad(double ang)
{
    return ang / 180. * PI;
}
```



### 点 向量

```c++
struct Vector
{
    double x, y;
    Vector(){}
    Vector(double _x, double _y) : x(_x), y(_y){}
};
typedef Vector Point;

bool operator==(const Point& lhs, const Point& rhs)
{
    return sgn(lhs.x - rhs.x) == 0 && sgn(lhs.y - rhs.y) == 0;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Point& lhs, const Point& rhs)
{
    return sgn(lhs.x - rhs.x) < 0 || sgn(lhs.x - rhs.x) == 0 && sgn(lhs.y - rhs.y) < 0;
}

inline Vector operator+(const Vector& lhs, const Vector& rhs)
{
    return Vector(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector operator-(const Vector& v)
{
    return Vector(-v.x, -v.y);
}

inline Vector operator-(const Vector& lhs, const Vector& rhs)
{
    return Vector(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector operator*(const Vector& lhs, double rhs)
{
    return Vector(lhs.x * rhs, lhs.y * rhs);
}

inline Vector operator*(double lhs, const Vector& rhs)
{
    return rhs * lhs;
}

inline Vector operator/(const Vector& lhs, double rhs)
{
    return Vector(lhs.x / rhs, lhs.y / rhs);
}

// 向量的模长
inline double len(const Vector& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

// 两点间的距离
inline double dist(const Point& lhs, const Point& rhs)
{
    return len(lhs - rhs);
}

// 向量的点积
inline double dot(const Vector& lhs, const Vector& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

// 向量的叉积
inline double cross(const Vector& lhs, const Vector& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

// 向量的倾斜角，弧度制
inline double angle(const Vector& v)
{
    return atan2(v.y, v.x);
}

// 向量的夹角，弧度制
inline double angle(const Vector& lhs, const Vector& rhs)
{
    return acos(dot(lhs, rhs) / len(lhs) / len(rhs));
}

// 单位向量
inline Vector normalized(const Vector& lhs)
{
    double L = len(lhs);
    return Vector(lhs.x / L, lhs.y / L);
}

// 单位法向量，在lhs左侧
inline Vector normal(const Vector& lhs)
{
    return normalized(Vector(-lhs.y, lhs.x));
}

// 将向量v顺时针旋转theta弧度
inline Vector rotate(const Vector& v, double theta)
{
    double s = sin(theta), c = cos(theta);
    return Vector(v.x * c - v.y * s, v.x * s + v.y * c);
}
```



### 直线 线段

```c++
struct Line
{
    Point p1, p2;
};

struct Segment
{
    Point p1, p2;
};

// 直线line的倾斜角
double angle(const Line& line)
{
    Vector v = line.p2 - line.p1;
    return atan2(v.y, v.x);
}

// 直线line的单位法向量
Vector normal(const Line& line)
{
    Vector v = normal(line.p2 - line.p1);
    return normalized(v);
}

// 将line沿法向量方向平移d
Line shift(const Line& line, double d)
{
    Vector dir = normal(line);
    return (Line){line.p1 + dir * d, line.p2 + dir* d};
}

// 点到直线的距离
double dist(const Point& p, const Line& line)
{
    Vector v1 = line.p1 - line.p2, v2 = p - line.p1;
    return fabs(cross(v1, v2)) / len(v1);
}

// 点到线段的距离
double dist(const Point& p, const Segment& seg)
{
    if(seg.p1 == seg.p2)return len(p - seg.p1);
    Vector dir = seg.p2 - seg.p1;
    Vector v1 = p - seg.p1, v2 = p - seg.p2;
    if(sgn(dot(dir, v1)) < 0)return len(v1);
    if(sgn(dot(dir, v2)) > 0)return len(v2);
    return fabs(cross(dir, v1)) / len(dir);
}

// 直线line的一般方程ax+by+c=0
void equation(const Line& line, double& a, double& b, double& c)
{
    a = line.p2.y - line.p1.y;
    b = line.p1.x - line.p2.x;
    c = -a * line.p1.x - b * line.p1.y;
}

// 点p在直线line上的投影
Point project(const Point& p, const Line& line)
{
    Vector v = line.p2 - line.p1;
    return line.p1 + v * (dot(v, p - line.p1) / dot(v,v));
}

// 点与直线的位置关系
// 点在直线外 0
// 点在直线上 1
int position(const Point& p, const Line& line)
{
    return sgn(cross(p - line.p1, p - line.p2)) == 0;
}

// 点与线段的位置关系
// 点在线段外 -1
// 点在线段的延长线上 0
// 点在线段端点上 1
// 点在线段内部 2
int position(const Point& p, const Segment& seg)
{
    if(position(p, *(Line*)&seg) == 0)return -1;
    int d = sgn(dot(p - seg.p1, p - seg.p2));
    if(d > 0)return 0;
    if(d == 0)return 1;
    return 2;
}

// 直线与直线的位置关系
// 相交 -1, 
// 重合 0, 
// 平行 1
int position(const Line& lhs, const Line& rhs)
{
    if(sgn(cross(lhs.p2 - lhs.p1, rhs.p2 - rhs.p1)) == 0)
    {
        if(sgn(cross(lhs.p2 - lhs.p1, rhs.p1 - lhs.p1)) == 0)return 0;
        else return 1;
    }
    return -1;
}

// 直线与线段的位置关系
// 线段跨过直线 -1, 
// 线段至少一个端点在直线上 0, 
// 相离 1
int position(const Line& line, const Segment& seg)
{
    Vector dir = line.p2 - line.p1;
    Vector v1 = seg.p1 - line.p1, v2 = seg.p2 - line.p1;
    return sgn(cross(dir, v1)) * sgn(cross(dir, v2));
}

// 两线段的位置关系
// 规范相交 -1, 
// 非规范相交 0, 
// 相离 1
int position(const Segment& lhs, const Segment& rhs)
{
    int d1 = sgn(cross(lhs.p2 - lhs.p1, rhs.p1 - lhs.p1));
    int d2 = sgn(cross(lhs.p2 - lhs.p1, rhs.p2 - lhs.p1));
    int d3 = sgn(cross(rhs.p2 - rhs.p1, lhs.p1 - rhs.p1));
    int d4 = sgn(cross(rhs.p2 - rhs.p1, lhs.p2 - rhs.p1));
    if((d1 ^ d2) == -2 && (d3 ^ d4) == -2)return -1;
    return !((d1 == 0 && sgn(dot(rhs.p1 - lhs.p1, rhs.p1 - lhs.p2)) <= 0) 
        || (d2 == 0 && sgn(dot(rhs.p2 - lhs.p1, rhs.p2 - lhs.p2)) <= 0) 
        || (d3 == 0 && sgn(dot(lhs.p1 - rhs.p1, lhs.p1 - rhs.p2)) <= 0) 
        || (d4 == 0 && sgn(dot(lhs.p2 - rhs.p1, lhs.p2 - rhs.p2)) <= 0)); 
}

// 两直线的交点，需要保证两直线相交
Point intersect(const Line& lhs, const Line& rhs)
{
    double a1 = lhs.p2.y - lhs.p1.y;
    double b1 = lhs.p1.x - lhs.p2.x;
    double c1 = cross(lhs.p2, lhs.p1);
    double a2 = rhs.p2.y - rhs.p1.y;
    double b2 = rhs.p1.x - rhs.p2.x;
    double c2 = cross(rhs.p2, rhs.p1);
    double d = a1 * b2 - a2 * b1;
    return Point((b1 * c2 - b2 * c1) / d, (c1 * a2 - c2 * a1) / d);
}
```



### 多边形 凸包

```c++
typedef std::vector<Point> Polygen;

// 多边形的周长
double circumference(const Polygen& poly)
{
    int n = poly.size();
    double ans = 0;
    for(int i = 0; i < n; i++)
    {
        ans += len(poly[i] - poly[(i + 1) % n]);
    }
    return ans;
}

// 多边形面积
double area(const Polygen& p)
{
	double ans = 0;
	for(int i = 1; i < (int)p.size() - 1; i++)
		ans += cross(p[i] - p[0], p[i + 1] - p[0]);
	return ans / 2.0;
}

// 点与多边形的位置关系
// 点在多边形外部 -1,
// 在边上 0,
// 在内部 1
int position(const Point& p, const Polygen& poly)
{
    int k = 0, n = poly.size();
    for(int i = 0; i < n; i++)
    {
        const Point &p1 = poly[i], &p2 = poly[(i + 1) % n];
        if(position(p, (Segment){p1, p2}) == 1)return 0;
        int d = sgn(cross(p - p1, p2 - p1));
        int s1 = sgn(p1.y - p.y);
        int s2 = sgn(p2.y - p.y);
        if(d > 0 && s1 < 0 && s2 >= 0)k++;
        else if(d < 0 && s2 < 0 && s1 >= 0)k--;
    }
    return k ? 1 : -1;
}

// 凸包
Polygen ConvexHull(std::vector<Point>& points)
{
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    if(points.size() <= 2)return points;
    int n = points.size();
    Polygen ans({points[0], points[1]});
    int sz;
    for(int i = 2; i < n; i++) {
        while((sz = ans.size()) >= 2 && 
            sgn(cross(ans[sz - 1] - ans[sz - 2], points[i] - ans[sz - 2])) <= 0)
            ans.pop_back();
        ans.push_back(points[i]);
    }
    int sz0 = ans.size();
    for(int i = n - 2; i >= 0; i--) {
        while((sz = ans.size()) > sz0 && 
            cross(ans[sz - 1] - ans[sz - 2], points[i] - ans[sz - 2]) <= 0)
            ans.pop_back();
        ans.push_back(points[i]);
    }
    if(n > 1)ans.pop_back();
    return ans;
}

// 旋转卡壳，求凸包直径
double rotatingCalipers(const Polygen& poly)
{
    int n = poly.size(), p = 1;
    double ans = 0;
    for(int i = 0; i < n; i++)
    {
        Vector b = poly[(i + 1) % n] - poly[i];
        while(cross(b, poly[(p + 1) % n] - poly[i])
            > cross(b, poly[p] - poly[i]))
            p = (p + 1) % n;
        ans = std::max(ans, std::max(len(poly[p] - poly[i]), 
            len(poly[(p + 1) % n] - poly[i])));
    }
    return ans;
}

// 多边形与多边形的位置关系,
// lhs内含于rhs -2,
// lhs与rhs相交 -1,
// lhs包含rhs 0
// 相离 1
int position(const Polygen& lhs, const Polygen& rhs)
{
    int n = lhs.size(), m = rhs.size();
    for(int i = 0; i < n; i++)
    {
        if(position(lhs[i], rhs) >= 0)return -2;
    }
    for(int i = 0; i < m; i++)
    {
        if(position(rhs[i], lhs) >= 0)return 0;
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(position((Segment){lhs[i], lhs[(i + 1) % n]}, 
                (Segment){rhs[j], rhs[(j + 1) % m]}) <= 0)
            {
                return -1;
            }
        }
    }
    return 1;
}
```



### 圆

```c++
struct Circle
{
    Point c; // 圆心
    double r; // 半径
};

// 获取circle在圆心角ang处的点
Point getPoint(const Circle& circle, double ang)
{
    return Point(circle.c.x + circle.r * cos(ang), 
        circle.c.y + circle.r * sin(ang));
}

// 从from到to的弧长
double arc(const Circle& circle, const Point& from, const Point& to)
{
    Vector v1 = from - circle.c, v2 = to - circle.c;
    double ang1 = angle(v1), ang2 = angle(v2);
    if(ang2 < ang1)ang2 += 2 * PI;
    return circle.r * (ang2 - ang1);
}

// 直线与圆交点, 输出参数ans[]，返回交点个数
int intersect(const Line& L, const Circle& C, Point ans[])
{
    Vector v = L.p2 - L.p1;
    double a = v.x, b = L.p1.x - C.c.x, c = v.y, d = L.p1.y - C.c.y;
    double e = a * a + c * c;
    double f = 2 * (a * b + c * d);
    double g = b * b + d * d - C.r * C.r;
    double delta = f * f - 4. * e * g;
    int s = sgn(delta);
    if(s < 0) return 0; // 相离
    else if(s == 0) // 相切
    {
        ans[0] = L.p1 + (-f / (2. * e)) * v;
        return 1;
    }
    else // 相交
    {
        ans[0] = L.p1 + ((-f - sqrt(delta)) / (2. * e)) * v;
        ans[1] = L.p1 + ((-f + sqrt(delta)) / (2. * e)) * v;
        return 2;
    }
}

// 圆与圆交点，返回交点个数，
// -1表示无穷多个交点
int intersect(const Circle& C1, const Circle& C2, Point ans[])
{
    double d = len(C1.c - C2.c);
    if(sgn(d) == 0)
    {
        if(sgn(C1.r - C2.r) == 0)return -1; //重合
        return 0;
    }
    if(sgn(C1.r + C2.r - d) < 0)return 0;
    if(sgn(fabs(C1.r - C2.r) - d) > 0)return 0;
    double a = angle(C2.c - C1.c);
    double da = acos((C1.r * C1.r + d * d-C2.r * C2.r) / (2 * C1.r * d));
    Point p1 = getPoint(C1, a - da),p2 = getPoint(C1, a + da);
    ans[0] = p1;
    if(p1 == p2)return 1;
    ans[1] = p2;
    return 2;
}

// P到圆C的切线，ans[]储存切线的方向向量
int tangent(const Circle& C, const Point& p, Point ans[])
{
    Point u = C.c - p;
    double dist = len(u);
    if(dist < C.r)return 0;
    else if(sgn(dist - C.r) == 0)
    {
        ///p在圆上仅有一条切线
        ans[0] = rotate(u, PI / 2);
        return 1;
    }
    else
    {
        double ang = asin(C.r / dist);
        ans[0] = rotate(u, -ang);
        ans[1] = rotate(u, ang);
        return 2;
    }
}

// 两圆公切线，a[] b[]分别为公切线在圆A B上的切点，返回公切线条数
int tangent(Circle A, Circle B, Point* a, Point* b)
{
    int cnt = 0;
    if(A.r < B.r) { std::swap(A, B); std::swap(a, b); }
    int d2 = (A.c.x - B.c.x) * (A.c.x - B.c.x)+(A.c.y - B.c.y) * (A.c.y - B.c.y);
    int rdiff = A.r - B.r;
    int rsum = A.r+B.r;
    if(d2 < rdiff * rdiff)return 0; // 内含
    double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
    if(d2 == 0 && A.r == B.r)return -1; ///无穷多
    if(d2 == rdiff * rdiff) // 内切 1条
    {
        a[cnt] = getPoint(A, base); b[cnt] = getPoint(B, base); cnt++;
        return 1;
    }
    // 外切
    double ang = acos((A.r - B.r) / sqrt(d2));
    a[cnt] = getPoint(A, base + ang); b[cnt] = getPoint(B, base + ang); cnt++;
    a[cnt] = getPoint(A, base - ang); b[cnt] = getPoint(B, base - ang); cnt++;
    if(d2 == rsum * rsum) // one
    {
        a[cnt] = getPoint(A, base); b[cnt] = getPoint(B, PI+base); cnt++;
    }
    else if(d2 > rsum * rsum) // two
    {
        double ang = acos((A.r - B.r) / sqrt(d2));
        a[cnt] = getPoint(A, base + ang);
        b[cnt] = getPoint(B, PI + base+ang);
        cnt++;
        a[cnt] = getPoint(A, base - ang);
        b[cnt] = getPoint(B, PI+base - ang);
        cnt++;
    }
    return cnt;
}

// 三角形外接圆
Circle CircumscribedCircle(const Point& p1, const Point& p2, const Point& p3)
{
    double Bx = p2.x - p1.x, By = p2.y - p1.y;
    double Cx = p3.x - p1.x, Cy = p3.y - p1.y;
    double D = 2 * (Bx * Cy - By * Cx);
    double cx = (Cy * (Bx * Bx + By * By) - By * (Cx * Cx + Cy * Cy))/D + p1.x;
    double cy = (Bx * (Cx * Cx + Cy * Cy) - Cx * (Bx * Bx + By * By))/D + p1.y;
    Point p = Point(cx, cy);
    return (Circle){p, len(p1 - p)};
}

// 三角形内切圆
Circle InscribedCircle(const Point& p1, const Point& p2, const Point& p3)
{
    double a = len(p2 - p3);
    double b = len(p3 - p1);
    double c = len(p1 - p2);
    Point p = (p1 * a + p2 * b + p3 * c)/(a + b + c);
    return (Circle){p, dist(p, (Line){p1, p2})};
}
```



## C++ STL

### unordered_set / unordered_map

自定义Hash函数的方法

```c++
#include <unordered_set>
struct pair_hash // 自定义Hash函数
{
    size_t operator()(const pair<int, int> &x) const // 返回值类型要求为size_t
    {
        return x.first * 131 + x.second;
    }
};
std::unordered_set<pair<int, int>, pair_hash> custom_set;
```

防止默认Hash函数被卡的方法

```c++
#include <unordered_map>
#include <chrono>
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = 
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
std::unordered_map<long long, int, custom_hash> safe_map;
```



### regex

```c++
#include <iostream>
#include <string>
#include <regex>
int main()
{
    // Simple regular expression matching
    const std::string fnames[] = {"foo.txt", "bar.txt", "baz.dat", "zoidberg"};
    const std::regex txt_regex("[a-z]+\\.txt");
 
    for (const auto &fname : fnames) {
        std::cout << fname << ": " << std::regex_match(fname, txt_regex) << '\n';
    }   
 
    // Extraction of a sub-match
    const std::regex base_regex("([a-z]+)\\.txt");
    std::smatch base_match;
 
    for (const auto &fname : fnames) {
        if (std::regex_match(fname, base_match, base_regex)) {
            // The first sub_match is the whole string; the next
            // sub_match is the first parenthesized expression.
            if (base_match.size() == 2) {
                std::ssub_match base_sub_match = base_match[1];
                std::string base = base_sub_match.str();
                std::cout << fname << " has a base of " << base << '\n';
            }
        }
    }
    // Extraction of several sub-matches
    const std::regex pieces_regex("([a-z]+)\\.([a-z]+)");
    std::smatch pieces_match;
 
    for (const auto &fname : fnames) {
        if (std::regex_match(fname, pieces_match, pieces_regex)) {
            std::cout << fname << '\n';
            for (size_t i = 0; i < pieces_match.size(); ++i) {
                std::ssub_match sub_match = pieces_match[i];
                std::string piece = sub_match.str();
                std::cout << "  submatch " << i << ": " << piece << '\n';
            }   
        }   
    }   
}
```

```c++
int main()
{
    std::string lines[] = {"Roses are #ff0000",
                           "violets are #0000ff",
                           "all of my base are belong to you"};
    std::regex color_regex("#([a-f0-9]{2})"
                            "([a-f0-9]{2})"
                            "([a-f0-9]{2})");
    // simple match
    for (const auto &line : lines) {
        std::cout << line << ": " << std::boolalpha
                  << std::regex_search(line, color_regex) << '\n';
    }   
    std::cout << '\n';
    // show contents of marked subexpressions within each match
    std::smatch color_match;
    for (const auto& line : lines) {
        if(std::regex_search(line, color_match, color_regex)) {
            std::cout << "matches for '" << line << "'\n";
            std::cout << "Prefix: '" << color_match.prefix() << "'\n";
            for (size_t i = 0; i < color_match.size(); ++i) 
                std::cout << i << ": " << color_match[i] << '\n';
            std::cout << "Suffix: '" << color_match.suffix() << "\'\n\n";
        }
    }
    // repeated search (see also std::regex_iterator)
    std::string log(R"(
        Speed:	366
        Mass:	35
        Speed:	378
        Mass:	32
        Speed:	400
	Mass:	30)");
    std::regex r(R"(Speed:\t\d*)");
    std::smatch sm;
    while(regex_search(log, sm, r))
    {
        std::cout << sm.str() << '\n';
        log = sm.suffix();
    }
    // C-style string demo
    std::cmatch cm;
    if(std::regex_search("this is a test", cm, std::regex("test"))) 
        std::cout << "\nFound " << cm[0] << " at position " << cm.prefix().length();
}
```

```c++
#include <iterator>
#include <regex>
int main()
{
   std::string text = "Quick brown fox";
   std::regex vowel_re("a|e|i|o|u");
   // write the results to an output iterator
   std::regex_replace(std::ostreambuf_iterator<char>(std::cout),
                      text.begin(), text.end(), vowel_re, "*");
   // construct a string holding the results
   std::cout << '\n' << std::regex_replace(text, vowel_re, "[$&]") << '\n';
}
```

