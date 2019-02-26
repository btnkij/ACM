/**
* Number:p2761
* Title:软件补丁问题
* Status:AC
* Tag:[dijkstra]
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

struct Patch
{
    int b1,b2,f1,f2;
    int cost;
}patches[104];
struct Node
{
    int bug,dis;
    bool operator<(const Node& rhs)const
    {
        return dis>rhs.dis;
    }
};
int n, m;
int all;
bool vis[1<<20];
int dijkstra()
{
    priority_queue<Node> P;
    P.push((Node){all,0});
    while(!P.empty())
    {
        Node u=P.top(); P.pop();
        if(vis[u.bug])continue;
        if(u.bug==0)return u.dis;
        vis[u.bug]=true;
        for(int i=0;i<m;i++)
        {
            Patch &pt=patches[i];
            if((u.bug&pt.b1)==pt.b1 && (u.bug&pt.b2)==0)
            {
                int nxt = u.bug & ~pt.f1 | pt.f2;
                if(vis[nxt])continue;
                P.push((Node){nxt, u.dis + pt.cost});
            }
        }
    }
    return 0;
}

char s[40];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi2(n,m);
    repne(i,0,m)
    {
        Patch& pt=patches[i];
        readi(pt.cost);
        reads(s);
        repne(j,0,n)
        {
            if(s[j]=='+')pt.b1 |= 1<<j;
            else if(s[j]=='-')pt.b2 |= 1<<j;
        }
        reads(s);
        repne(j, 0, n)
        {
            if (s[j] == '-')pt.f1 |= 1 << j;
            else if (s[j] == '+')pt.f2 |= 1 << j;
        }
    }
    all=(1<<n)-1;
    int ans=dijkstra();
    printf("%d",ans);
    return 0;
}