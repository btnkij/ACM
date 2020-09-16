/**
* Number:LUOGU3960
* Title:列队
* Status:AC
* Tag:[动态开点, 线段树]
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

struct Node
{
    int son[2];
    ll id;
    int sz;
}tree[600010*20];
int nodeid;
int makenode(ll id, int sz)
{
    tree[++nodeid]={0,0,id,sz};
    return nodeid;
}

struct SegTree
{
    int root, sz, maxsz;
    ll beg;
    void build(ll beg, int sz, int maxsz)
    {
        this->beg = beg;
        this->sz = sz;
        this->maxsz = maxsz;
    }
    ll popHelp(int &p, int lt, int rt, int rk)
    {
        if(!p)p=makenode(beg+lt-1, rt-lt+1);
        tree[p].sz--;
        if(lt==rt)return tree[p].id;
        int mid=(lt+rt)>>1;
        ll id;
        int lsz=tree[p].son[0]?tree[tree[p].son[0]].sz:mid-lt+1;
        if(lsz>=rk) id=popHelp(tree[p].son[0], lt, mid, rk);
        else id=popHelp(tree[p].son[1], mid+1, rt, rk-lsz);
        return id;
    }
    ll pop(int rk)
    {
        return popHelp(root, 1, maxsz, rk);
    }
    void insertHelp(int &p, int lt, int rt, int qpos, ll id)
    {
        if(!p)p=makenode(0, rt-lt+1);
        if(lt==rt)
        {
            tree[p].id=id;
            return;
        }
        int mid=(lt+rt)>>1;
        if(qpos<=mid)insertHelp(tree[p].son[0], lt, mid, qpos, id);
        else insertHelp(tree[p].son[1], mid+1, rt, qpos, id);
    }
    void insert(ll id)
    {
        insertHelp(root, 1, maxsz, ++sz, id);
    }
};

SegTree segs[300010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m,q; cin>>n>>m>>q;
    segs[0].build(0, 0, n+q);
    for(int i=1;i<=n;i++)
    {
        segs[i].build(ll(i-1)*m+1, m-1, m-1+q);
        segs[0].insert((ll)i*m);
    }
    while(q--)
    {
        int x,y; cin>>x>>y;
        if(y==m)
        {
            ll id=segs[0].pop(x);
            cout<<id<<"\n";
            segs[0].insert(id);
        }
        else
        {
            ll id=segs[x].pop(y);
            cout<<id<<"\n";
            ll tail=segs[0].pop(x);
            segs[x].insert(tail);
            segs[0].insert(id);
        }
    }
    return 0;
}