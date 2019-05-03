/**
* Number:p3919
* Title:【模板】可持久化数组（可持久化线段树/平衡树）
* Status:?
* Tag:[]
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

template<typename T>
T read()
{
    register T num = 0;
    register char ch;
    register bool sign = false;
    do
    {
        ch = getchar();
        if(ch == '-')sign = true;
    }while(ch < '0' || ch > '9');
    do{ num = (num << 3) + (num << 1) + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    if(sign)num = -num;
    return num;
}

template<typename T>
struct PersistentArray
{
    struct Node
    {
        T value;
        int lc, rc;
        // Node(T _val, int _lc, int _rc) : value(_val), lc(_lc), rc(_rc){}
    };
    vector<Node> tree;
    vector<int> root;
    int n;
    void init(int n)
    {
        this->n = n;
        tree.reserve(20 * 1000010);
        tree.clear();
        root.reserve(1000010);
        root.clear();
        root.push_back(build(1, n));
    }
    int build(int lt, int rt)
    {
        Node nod;
        memset(&nod, 0, sizeof(Node));
        if(lt == rt)
        {
            nod.value = read<T>();
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
    T qval;
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
    void update(int ver, int pos, T val)
    {
        qlt = pos, qval = val;
        root.push_back(updateHelp(root[ver], 1, n));
    }
    void clone(int ver)
    {
        tree.push_back(tree[root[ver]]);
        root.push_back(tree.size() - 1);
    }
    T queryHelp(int p, int lt, int rt)
    {
        if(lt == rt)return tree[p].value;
        int mid = (lt + rt) >> 1;
        if(qlt <= mid)return queryHelp(tree[p].lc, lt, mid);
        else return queryHelp(tree[p].rc, mid + 1, rt);
    }
    T query(int ver, int pos)
    {
        qlt = pos;
        return queryHelp(root[ver], 1, n);
    }
};

PersistentArray<int> arr;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n=read<int>(), m=read<int>();
    arr.init(n);
    repne(i,0,m)
    {
        int v,op,loc,value;
        v=read<int>();
        op=read<int>();
        loc=read<int>();
        if(op==1)
        {
            value=read<int>();
            arr.update(v,loc,value);
        }
        else if(op==2)
        {
            printf("%d\n",arr.query(v,loc));
            arr.clone(v);
        }
    }
    return 0;
}