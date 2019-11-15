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

int a[200010];
struct Node
{
    int p,s;
    bool operator<(const Node& rhs)const
    {
        return p>rhs.p;
    }
}nodes[200010];
int p[200010],tot;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        repne(i,0,n)readi(a[i]);
        int m; readi(m);
        repne(i,0,m)readi(nodes[i].p,nodes[i].s);
        sort(nodes,nodes+m);
        tot=0;
        repne(i,0,m)
        {
            for(;tot<nodes[i].s;tot++)
            {
                p[tot]=nodes[i].p;
            }
        }
        int ans=0;
        int i=0;
        while(i<n)
        {
            int j=0,pre=a[i];
            while(j<tot && pre<=p[j] && a[i+j]<=p[j])
            {
                pre=max(pre,a[i+j]);
                j++;
            }
            if(j==0)
            {
                ans=-1;
                break;
            }
            ans++;
            i+=j;
        }
        printf("%d\n",ans);
    }
    return 0;
}