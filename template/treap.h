/**
 * 
 * Treap
 * 
**/

#include <cstdio>
#include <algorithm>

struct Node
{
    int son[2], size, cnt, prior, val;
}tree[10000000];
int node_id;
int makenode(int val)
{
    tree[++node_id] = (Node){0, 0, 1, 1, rand(), val};
    return node_id;
}
void maintain(int p)
{
    Node &m = tree[p], &l = tree[m.son[0]], &r = tree[m.son[1]];
    m.size = l.size + r.size + m.cnt;
}
void rotate(int& root, int d) // d=0左旋, d=1右旋
{
    int p = tree[root].son[d ^ 1];
    tree[root].son[d ^ 1] = tree[p].son[d];
    tree[p].son[d] = root;
    maintain(root); maintain(p);
    root = p;
}
void insert(int& root, int val)
{
    if(root == 0)root = makenode(val);
    else if(tree[root].val == val)tree[root].size++, tree[root].cnt++;
    else
    {
        int d = (int)(val > tree[root].val);
        int& branch = tree[root].son[d];
        insert(branch, val);
        if(tree[root].prior < tree[branch].prior)rotate(root, d ^ 1);
        maintain(root);
    }
}
void remove(int& root, int val)
{
    if(root == 0)return;
    else if(tree[root].val == val)
    {
        int l = tree[root].son[0], r = tree[root].son[1];
        if(!l && !r)
        {
            tree[root].size--, tree[root].cnt--;
            if(tree[root].cnt == 0)root = 0;
        }
        else if(l && r)
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
    while(root)
    {
        Node& m = tree[root];
        if(m.val == val)return ans + tree[m.son[0]].size;
        if(m.val > val)root = m.son[0];
        else ans += tree[m.son[0]].size + m.cnt, root = m.son[1];
    }
    return ans;
}
int kth(int root, int k)
{
    while(root)
    {
        Node& m = tree[root];
        if(tree[m.son[0]].size >= k)root = m.son[0];
        k -= tree[m.son[0]].size;
        if(m.cnt >= k)return m.val;
        k -= m.cnt;
        root = m.son[1];
    }
    return 2147483647;
}
int prev(int root, int val)
{
    if(root == 0)return -2147483647;
    Node& m = tree[root];
    if(m.val >= val)return prev(m.son[0], val);
    return std::max(m.val, prev(m.son[1], val));
}
int nxt(int root, int val)
{
    if(root == 0)return 2147483647;
    Node& m = tree[root];
    if(m.val <= val)return nxt(m.son[1], val);
    return std::min(m.val, nxt(m.son[0], val));
}





/**
 * 
 * FHQ Treap 非旋转平衡树
 * 常数过大，仅用于可持久化
 * 
**/

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