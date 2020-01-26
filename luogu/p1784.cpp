/**
* Number:p1784
* Title:数独
* Status:AC
* Tag:[dancing links]
* desc: 9*9数独
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

const int MAX_ROW = 81 * 9;
const int MAX_COL = 81 * 4;
struct dancing_links
{
    struct dlx_node
    {
        int x, y;                        // 行号，列号
        dlx_node *lef, *rig, *up, *down; // 十字链表
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
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    rep2(i, 1, 9, j, 1, 9) readi(suduku[i][j]);
    dlx.init(81 * 4); // 初始化，待覆盖的列有81*4个
    int tot = 0;
    rep2(x, 1, 9, y, 1, 9) rep(i, 1, 9)
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