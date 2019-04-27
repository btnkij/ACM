/**
* Number:loj10004
* Title:「一本通 1.1 例 4」加工生产调度 
* Status:AC
* Tag:[贪心]
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
    int b,w;
};
Node nodes[510];
bool vis[510];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m,n; readi(m,n);
    repne(i,0,n)readi(nodes[i].b);
    repne(i,0,n)readi(nodes[i].w);
    sort(nodes,nodes+n,[](Node& lhs, Node& rhs){
        return lhs.w > rhs.w;
    });
    for(int i=0;i<n;i++)
    {
        int k=-1;
        for(int j=nodes[i].b;j>=1;j--)
        {
            if(!vis[j])
            {
                k=j;
                break;
            }
        }
        if(k==-1)m-=nodes[i].w;
        else vis[k]=true;
    }
    printf("%d",m);
    return 0;
}