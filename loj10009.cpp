/**
* Number:loj10009
* Title:「一本通 1.1 练习 5」钓鱼 
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

int st[110], decr[110], dis[110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,H; readi(n,H);
    H=H*60/5;
    repne(i,0,n)readi(st[i]);
    repne(i,0,n)readi(decr[i]);
    repne(i,1,n)readi(dis[i]);
    int ans=0;
    repne(i,0,n)
    {
        H-=dis[i];
        if(H<=0)break;
        int h=H;
        priority_queue<pair<int,int> > Q;
        rep(j,0,i)Q.emplace(st[j], j);
        int tmp=0;
        while(h-- && !Q.empty())
        {
            auto top=Q.top(); Q.pop();
            tmp+=top.first;
            top.first-=decr[top.second];
            if(top.first>0)Q.push(top);
        }
        ans=max(ans,tmp);
    }
    printf("%d",ans);
    return 0;
}