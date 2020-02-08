/**
* Number:scu4445
* Title:Right turn
* Status:AC
* Tag:[模拟, 二分查找]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

// int dir[][2]={{1,0},{0,-1},{-1,0},{0,1}};
// bool vis[1010][4];
struct Point
{
    int x,y;
}obsx[1010], obsy[1010];
bool cmp1(Point& lhs, Point& rhs)
{
    return lhs.x<rhs.x || lhs.x==rhs.x && lhs.y<rhs.y;
}
bool cmp2(Point& lhs, Point& rhs)
{
    return lhs.y<rhs.y || lhs.y==rhs.y && lhs.x<rhs.x;
}
bool cmp3(const Point& lhs, const Point& rhs)
{
    return lhs.x<rhs.x;
}
bool cmp4(const Point& lhs, const Point& rhs)
{
    return lhs.y<rhs.y;
}
typedef pair<int,int> Pair;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    map<Pair, int> M;
    while(readi(n)!=EOF)
    {
        M.clear();
        rep(i,1,n)
        {
            int x,y; readi(x,y);
            obsx[i]=obsy[i]=(Point){x,y};
        }
        sort(obsx+1, obsx+n+1, cmp1);
        sort(obsy+1, obsy+n+1, cmp2);
        Point s={0,0};
        int fw=0;
        int ans=0;
        bool ok=true;
        while(true)
        {
            M[Pair(s.x,s.y)]++;
            if(M[Pair(s.x,s.y)]>=4)
            {
                ok=false;
                break;
            }
            if(fw==0 || fw==2)
            {
                auto rg=equal_range(obsy+1, obsy+n+1, s, cmp4);
                if(rg.first == rg.second)break;
                else if(fw==0)
                {
                    auto up=upper_bound(rg.first, rg.second, s, cmp3);
                    if(up>=rg.second)break;
                    s.x = up->x - 1;
                    fw = (fw + 1) % 4;
                    ans++;
                }
                else // fw==2
                {
                    auto low=lower_bound(rg.first, rg.second, s, cmp3)-1;
                    if(low<rg.first)break;
                    s.x = low->x + 1;
                    fw = (fw + 1) % 4;
                    ans++;
                }
            }
            else // fw==1 || fw==3
            {
                auto rg=equal_range(obsx+1, obsx+n+1, s, cmp3);
                if(rg.first == rg.second)break;
                else if(fw==1)
                {
                    auto low=lower_bound(rg.first, rg.second, s, cmp4)-1;
                    if(low<rg.first)break;
                    s.y = low->y + 1;
                    fw = (fw + 1) % 4;
                    ans++;
                }
                else // fw==3
                {
                    auto up=upper_bound(rg.first, rg.second, s, cmp4);
                    if(up>=rg.second)break;
                    s.y = up->y - 1;
                    fw = (fw + 1) % 4;
                    ans++;
                }
            }
        }
        if(ok)printf("%d\n",ans);
        else printf("-1\n");
    }
    return 0;
}