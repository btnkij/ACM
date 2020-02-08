/**
* Number:p3391
* Title:【模板】文艺平衡树（Splay）
* Status:AC
* Tag:[splay-tree, 伸展树]
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

struct Node
{
    int val,sz,lazy,fa,son[2];
}tree[100010];
int sz;
void link(int u,int fa,int d)
{
    if(u)tree[u].fa=fa;
    tree[fa].son[d]=u;
}
int dir(int u)
{
    return tree[tree[u].fa].son[1]==u;
}
void pushup(int u)
{
    int* son=tree[u].son;
    tree[u].sz=tree[son[0]].sz+tree[son[1]].sz+1;
}
void rotate(int u)
{
    int fa=tree[u].fa, dfa=dir(u);
    int ffa=tree[fa].fa, dffa=dir(fa);
    int son=tree[u].son[dfa^1];
    link(u,ffa,dffa); link(fa,u,dfa^1); link(son,fa,dfa);
    pushup(fa); pushup(u);
}
void splay(int u,int top)
{
    while(tree[u].fa!=top)
    {
        int fa=tree[u].fa;
        int ffa=tree[fa].fa;
        if(ffa!=top)rotate(dir(u)==dir(fa)?fa:u);
        rotate(u);
    }
}
int build(int lt,int rt,int pre)
{
    if(lt>rt)return 0;
    int mid=(lt+rt)/2;
    int u=++sz,ls=build(lt,mid-1,u),rs=build(mid+1,rt,u);
    tree[u]=(Node){mid,1,0,pre,ls,rs};
    pushup(u);
    return u;
}
void pushdown(int u)
{
    if(!tree[u].lazy)return;
    int* son=tree[u].son;
    swap(son[0],son[1]);
    if(son[0])tree[son[0]].lazy^=1;
    if(son[1])tree[son[1]].lazy^=1;
    tree[u].lazy=0;
}
int findpos(int k)
{
    int u=tree[0].son[0];
    while(true)
    {
        pushdown(u);
        int* son=tree[u].son;
        if(k<=tree[son[0]].sz)u=son[0];
        else if(k<=tree[son[0]].sz+1)return u;
        else
        {
            k-=tree[son[0]].sz+1;
            u=son[1];
        }
    }
}
void flip(int lt,int rt)
{
    lt=findpos(lt-1),rt=findpos(rt+1);
    splay(lt,0); 
    splay(rt,lt);
    tree[tree[rt].son[0]].lazy^=1;
}

void dfs(int n,int u)
{
    if(!u)return;
    pushdown(u);
    dfs(n,tree[u].son[0]);
    if(tree[u].val!=1 && tree[u].val!=n+2)printf("%d ",tree[u].val-1);
    dfs(n,tree[u].son[1]);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    link(build(1,n+2,0),0,0);
    while(m--)
    {
        int l,r; readi(l,r);
        flip(l+1,r+1);
    }
    dfs(n,tree[0].son[0]);
    return 0;
}