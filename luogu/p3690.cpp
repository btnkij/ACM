/**
* Number:p3690
* Title:【模板】Link Cut Tree （动态树）
* Status:AC
* Tag:[lct, 动态树]
* desc: lct模板题，维护链上的异或和
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
    int val,sum,flip; // 节点的值、子树的异或和、翻转标记
    int fa,son[2]; // 父节点、左右儿子
}tree[100010];
inline int dir(int u)
{
    return tree[tree[u].fa].son[1]==u;
}
inline void pushup(int u) // 计算要维护的信息
{
    int* son=tree[u].son;
    tree[u].sum=tree[son[0]].sum^tree[son[1]].sum^tree[u].val;
}
inline void pushdown(int u) // 下放翻转标记
{
    if(!tree[u].flip)return;
    int* son=tree[u].son;
    swap(son[0],son[1]);
    tree[u].flip=0;
    tree[son[0]].flip^=1;
    tree[son[1]].flip^=1;
}
inline bool isroot(int u) // 判断u是否是根节点
{
    int* son=tree[tree[u].fa].son;
    return son[0]!=u && son[1]!=u;
}
inline void rotate(int u)
{
    int fa=tree[u].fa, dfa=dir(u);
    int ffa=tree[fa].fa, dffa=dir(fa);
    int sub=tree[u].son[dfa^1];
    tree[u].fa=ffa;
    if(!isroot(fa))tree[ffa].son[dffa]=u; // 两个SplayTree之间连虚边
    tree[u].son[dfa^1]=fa, tree[fa].fa=u;
    tree[fa].son[dfa]=sub, tree[sub].fa=fa;
    pushup(fa); pushup(u);
}
void splay(int u)
{
    static int up[100010];
    int tot=0;
    for(int i=u;;i=tree[i].fa) // 之上而下释放翻转标记
    {
        up[tot++]=i;
        if(isroot(i))break;
    }
    while(tot--)pushdown(up[tot]);
    while(!isroot(u))
    {
        int fa=tree[u].fa;
        if(!isroot(fa))rotate(dir(u)==dir(fa)?fa:u);
        rotate(u);
    }
}
void access(int u) // 使根节点-u的链在一棵SplayTree上，u为最深的节点
{
    for(int rson=0;u;rson=u,u=tree[u].fa)
    {
        splay(u);
        tree[u].son[1]=rson;
        pushup(u);
    }
}
void makeroot(int u) // 使u成为根节点
{
    access(u);
    splay(u);
    tree[u].flip^=1;
}
int findroot(int u) // 返回u的根节点
{
    access(u);
    splay(u);
    while(true)
    {
        pushdown(u);
        if(!tree[u].son[0])return u;
        u=tree[u].son[0];
    }
}
void split(int x,int y) // 计算链x-y的信息，答案为tree[y].sum
{                       // split操作后，y无右儿子，y的左儿子为以x为根的子树
    makeroot(x);
    access(y);
    splay(y);
}
void link(int x,int y) // 连接x, y两个节点
{
    makeroot(x);
    if(findroot(y)!=x)tree[x].fa=y;
}
void cut(int x,int y) // 断开x, y两个节点，不必保证x, y连通
{
    split(x,y);
    if(tree[y].son[0]==x)
    {
        tree[x].fa=tree[y].son[0]=0;
        pushup(y);
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m); // 节点数、询问数
    rep(i,1,n) // 输入每个节点的权值
    {
        readi(tree[i].val);
        tree[i].sum=tree[i].val;
    }
    while(m--)
    {
        int op,x,y; readi(op,x,y);
        if(op==0) // 链x-y的异或和
        {
            split(x,y);
            printf("%d\n",tree[y].sum);
        }
        else if(op==1) // 连接x, y
        {
            link(x,y);
        }
        else if(op==2) // 断开x, y
        {
            cut(x,y);
        }
        else if(op==3) // 将节点x的权值修改为y
        {
            splay(x);
            tree[x].val=y;
            pushup(x);
        }
    }
    return 0;
}