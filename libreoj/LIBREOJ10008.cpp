/**
* Number:loj10008
* Title:「一本通 1.1 练习 4」家庭作业 
* Status:AC
* Tag:[贪心, 并查集]
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
    int ddl, reward;
    bool operator<(const Node& rhs)const
    {
        return reward>rhs.reward;
    }
}nods[1000010];

int fa[700010];
int find(int x)
{
    return fa[x]==x ? x : fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
    int rx=find(x), ry=find(y);
    if(rx!=ry)fa[rx]=ry;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)readi(nods[i].ddl, nods[i].reward);
    sort(nods, nods+n);
    repne(i,0,700005)fa[i]=i;
    int ans=0;
    repne(i,0,n)
    {
        int k=find(nods[i].ddl);
        if(k)
        {
            ans+=nods[i].reward;
            merge(k,k-1);
        }
    }
    printf("%d",ans);
    return 0;
}