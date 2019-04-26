/**
* Number:scu2574
* Title:cards
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

struct Node
{
    int prior,sign,a,b;
    bool operator<(const Node& rhs)const
    {
        return prior<rhs.prior;
    }
}nodes[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF)
    {
        repne(i,0,n)
        {
            Node& p=nodes[i];
            readi(p.a, p.b);
            p.prior=INF;
            if(p.a<p.prior)
            {
                p.sign=1;
                p.prior=p.a;
            }
            if(-p.a<p.prior)
            {
                p.sign=-1;
                p.prior=-p.a;
            }
            if(p.b<p.prior)
            {
                p.sign=1;
                p.prior=p.b;
            }
            if(-p.b<p.prior)
            {
                p.sign=-1;
                p.prior=-p.b;
            }
            if(p.prior==0)
            {
                p.prior=INF;
            }
        }
        sort(nodes,nodes+n);
        int pos=n>>1, neg=n>>1;
        int ans=0;
        int i;
        for(i=0;i<n && pos && neg;i++)
        {
            Node& p=nodes[i];
            ans+=p.prior;
            if(p.sign==1)pos--;
            else neg--;
        }
        if(pos)for(;i<n;i++)ans+=min(nodes[i].a,nodes[i].b);
        else for(;i<n;i++)ans+=min(-nodes[i].a,-nodes[i].b);
        printf("%d\n",ans);
    }
    return 0;
}