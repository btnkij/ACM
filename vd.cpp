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

inline int readu()
{
    register int num = 0;
    register char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ num = (num << 3) + (num << 1) + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    return num;
}

int where[100010];

struct PersistentArray
{
    struct Node
    {
        int value;
        int lc, rc;
    };
    vector<Node> tree;
    vector<int> root;
    int n;
    void init(int n)
    {
        this->n = n;
        tree.reserve(20 * 100010);
        tree.clear();
        root.reserve(100010);
        root.clear();
        root.push_back(build(1, n));
    }
    int build(int lt, int rt)
    {
        Node nod;
        memset(&nod, 0, sizeof(Node));
        if(lt == rt)
        {
            nod.value = readu();
        }
        else
        {
            int mid = (lt + rt) >> 1;
            nod.lc = build(lt, mid);
            nod.rc = build(mid + 1, rt);
        }
        tree.push_back(nod);
        return tree.size() - 1;
    }
    int qlt, qrt;
    int qval;
    int updateHelp(int p, int lt, int rt)
    {
        Node nod = tree[p];
        if(lt == rt)
        {
            nod.value = qval;
        }
        else
        {
            int mid = (lt + rt) >> 1;
            if(qlt <= mid)nod.lc = updateHelp(tree[p].lc, lt, mid);
            else nod.rc = updateHelp(tree[p].rc, mid + 1, rt);
        }
        tree.push_back(nod);
        return tree.size() - 1;
    }
    void update(int ver, int pos, int val)
    {
        qlt = pos, qval = val;
        int r = updateHelp(root[ver], 1, n);

        root.push_back(r);
    }
    void clone(int ver)
    {
        tree.push_back(tree[root[ver]]);
        root.push_back(tree.size() - 1);
    }
    int queryHelp(int p, int lt, int rt)
    {
        if(lt == rt)return tree[p].value;
        int mid = (lt + rt) >> 1;
        if(qlt <= mid)return queryHelp(tree[p].lc, lt, mid);
        else return queryHelp(tree[p].rc, mid + 1, rt);
    }
    int query(int ver, int pos)
    {
        qlt = pos;
        return queryHelp(root[ver], 1, n);
    }
}tree;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    tree.init(n);
    int q; readi(q);
    while(q--)
    {
        int op=readu();
        if(op==1)
        {
            int l=readu(), v=readu();

        }
    }
    return 0;
}