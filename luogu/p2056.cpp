/**
* Number:p2056
* Title:[ZJOI2007]捉迷藏
* Status:AC
* Tag:[线段树, 括号序列]
* desc: 树边无边权，动态维护树上最远两个黑点的距离
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

const int MAXN=1e5+10;
struct Edge
{
    int from,to,nxt;
}edges[MAXN*2];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]={from,to,head[from]};
    head[from]=edgeid++;
}

int s[MAXN*3],pos[MAXN],dfsid; // s[]-括号序列 pos[]-节点在序列中的位置
void dfs(int u,int pre) // 构建树的括号序列
{
    s[++dfsid]=-1; // 左括号
    pos[u]=++dfsid, s[dfsid]=0; // 节点状态：关灯
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs(v,u);
    }
    s[++dfsid]=-2; // 右括号
}

// 树的括号序列表示
// 0))((  )0))(0
// (右括号数a1,左括号数b1) (a2,b2)
// 距离最远的两个“0”的距离记为dis
// dis = max( a1+b2+abs(b1-a2) )
// dis = max( a1+b2+(b1-a2), a1+b2+(a2-b1) )
// dis = max( (a1+b1)+(b2-a2), (a1-b1)+(a2+b2) )
// 线段树维护“0”左侧的max(a+b),max(b-a),右侧的max(a+b),max(a-b)
struct Node
{
    int dis; // dis-最远两个“0”的距离
    int a,b; // a-右括号数量 b-左括号数量
    int l1,l2; // l1-左侧max(a+b) l2-左侧max(b-a)
    int r1,r2; // r1-右侧max(a+b) r2-右侧max(a-b)
}tree[MAXN*3*4];
void pushup(int p)
{
    Node &m=tree[p], &l=tree[p<<1], &r=tree[p<<1|1];
    m.dis=max(max(l.dis, r.dis), max(l.r1+r.l2, l.r2+r.l1));
    if(l.b>r.a)m.a=l.a, m.b=l.b-r.a+r.b;
    else m.a=l.a+r.a-l.b, m.b=r.b;
    m.l1=max(l.l1, max(l.a+l.b+r.l2, l.a-l.b+r.l1));
    m.l2=max(l.l2, l.b-l.a+r.l2);
    m.r1=max(r.r1, max(r.a+r.b+l.r2, r.b-r.a+l.r1));
    m.r2=max(r.r2, r.a-r.b+l.r2);
}
void build(int p,int lt,int rt)
{
    Node& cur=tree[p];
    if(lt==rt)
    {
        if(s[lt]==0)cur={0,0,0,0,0,0,0};
        else if(s[lt]==1)cur={-INF,0,0,-INF,-INF,-INF,-INF};
        else if(s[lt]==-1)cur={-INF,0,1,-INF,-INF,-INF,-INF};
        else if(s[lt]==-2)cur={-INF,1,0,-INF,-INF,-INF,-INF};
        return;
    }
    int mid=(lt+rt)>>1;
    build(p<<1,lt,mid);
    build(p<<1|1,mid+1,rt);
    pushup(p);
}
void update(int p,int lt,int rt,int qpos)
{
    if(lt==rt)
    {
        s[lt]^=1;
        if(s[lt]==0)tree[p]={0,0,0,0,0,0,0};
        else tree[p]={-INF,0,0,-INF,-INF,-INF,-INF};
        return;
    }
    int mid=(lt+rt)>>1;
    if(qpos<=mid)update(p<<1,lt,mid,qpos);
    else update(p<<1|1,mid+1,rt,qpos);
    pushup(p);
}
int query()
{
    return max(-1,tree[1].dis);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n); // 节点个数
    clr(head,-1), edgeid=0;
    repne(i,1,n) // 建树
    {
        int u,v; readi(u,v);
        addedge(u,v), addedge(v,u);
    }
    dfs(1,0); // 生成括号序列
    build(1,1,dfsid); // 在括号序列上建线段树
    int q; readi(q); // 询问数
    while(q--)
    {
        char op[4]; reads(op);
        if(op[0]=='C') // 翻转节点i的颜色
        {
            int i; readi(i);
            update(1,1,dfsid,pos[i]);
        }
        else if(op[0]=='G') // 询问最远两个黑点的距离
        {
            printf("%d\n",query());
        }
    }
    return 0;
}