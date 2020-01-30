/**
* Number:ybt1370
* Title:最小函数值(minval)
* Status:AC
* Tag:[优先队列]
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Node
{
    int id, x, y;
    bool operator<(const Node& rhs)const
    {
        return y>rhs.y;
    }
};
int a[10004],b[10004],c[10004];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    priority_queue<Node> Q;
    int n,m; readi2(n,m);
    repne(i,0,n)
    {
        readi3(a[i],b[i],c[i]);
        Q.push((Node){i,1,a[i]+b[i]+c[i]});
    }
    while(m--)
    {
        Node node=Q.top(); Q.pop();
        printf("%d ",node.y);
        int x=node.x+1;
        int y=a[node.id]*x*x+b[node.id]*x+c[node.id];
        Q.push((Node){node.id,x,y});
    }
    return 0;
}