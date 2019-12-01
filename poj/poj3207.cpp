/**
* Number:poj2307
* Title:Ikki's Story IV - Panda's Trick
* Status:AC
* Tag:[2-sat, 并查集]
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

int fa[1010];
int findr(int x)
{
    return x==fa[x]?x:fa[x]=findr(fa[x]);
}
void merge(int x,int y)
{
    int rx=findr(x),ry=findr(y);
    if(rx!=ry)fa[rx]=ry;
}

struct Node
{
    int a,b;
}link[510];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    repne(i,0,m)
    {
        readi(link[i].a,link[i].b);
        if(link[i].a>link[i].b)swap(link[i].a,link[i].b);
    }
    repne(i,0,m<<1)fa[i]=i;
    repne2(i,0,m,j,0,i)
    {
        Node &u=link[i],&v=link[j];
        if((u.a<v.a&&v.a<u.b)^(u.a<v.b&&v.b<u.b))
        {
            merge(i<<1,j<<1|1);
            merge(i<<1|1,j<<1);
        }
    }
    repne(i,0,m)
    {
        if(findr(i<<1)==findr(i<<1|1))
        {
            printf("the evil panda is lying again\n");
            return 0;
        }
    }
    printf("panda is telling the truth...\n");
    return 0;
}