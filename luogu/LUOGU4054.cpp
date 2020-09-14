/**
* Number:LUOGU4054
* Title:[JSOI2009]计数问题
* Status:AC
* Tag:[树状数组]
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

int n,m;
struct BIT
{
    int tree[310][310];
    void update(int x,int y,int val)
    {
        for(int i=x;i<=n;i+=i&-i)
            for(int j=y;j<=m;j+=j&-j)
                tree[i][j]+=val;
    }
    int query(int x,int y)
    {
        int ans=0;
        for(int i=x;i;i^=i&-i)
            for(int j=y;j;j^=j&-j)
                ans+=tree[i][j];
        return ans;
    }
    int query2d(int x1,int x2,int y1,int y2)
    {
        return query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1);
    }
}bit[105];
int color[310][310];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            int c; cin>>c;
            bit[c].update(i,j,1);
            color[i][j]=c;
        }
    }
    int q; cin>>q;
    while(q--)
    {
        int op; cin>>op;
        if(op==1)
        {
            int x,y,c; cin>>x>>y>>c;
            bit[c].update(x,y,1);
            bit[color[x][y]].update(x,y,-1);
            color[x][y]=c;
        }
        else if(op==2)
        {
            int x_1,x_2,y_1,y_2,c;
            cin>>x_1>>x_2>>y_1>>y_2>>c;
            cout<<bit[c].query2d(x_1,x_2,y_1,y_2)<<"\n";
        }
    }
    return 0;
}