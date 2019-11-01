/**
 * 
 * 可持久化数组
 * 
**/

#include <cstring>

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
    do
    { 
        num = (num << 3) + (num << 1) + (ch & 0xF);
        ch = getchar(); 
    }while('0' <= ch && ch <= '9');
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