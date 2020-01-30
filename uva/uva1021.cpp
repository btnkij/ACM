/**
* Number:uva1021
* Title:Eurodiffusion
* Status:?
* Tag:[模拟]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <string>
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

struct Country
{
    string name;
    int xl,yl,xh,yh;
    bool fin;
    int t;
    bool operator<(const Country& rhs)const
    {
        return t<rhs.t || t==rhs.t && name<rhs.name;
    }
}coun[24];
struct City
{
    int country;
    int money[24];
    int lazy[24];
    bool fin;
}maze[12][12];
int dir[][2]={{-1,0},{1,0},{0,-1},{0,1}};
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    int kase=1;
    while(readi(n)!=EOF && n)
    {
        rep2(i,1,10,j,1,10)
        {
            City& nod=maze[i][j];
            nod.country=0;
            nod.fin=false;
            mset(nod.money,0);
            mset(nod.lazy,0);
        }
        rep(k,1,n)
        {
            Country& c=coun[k];
            cin>>c.name;
            c.fin=false;
            readi(c.xl,c.yl,c.xh,c.yh);
            rep2(i,c.xl,c.xh,j,c.yl,c.yh)
            {
                City& u=maze[i][j];
                u.country=k;
                u.money[k]=1000000;
            }
        }
        int cnt=0;
        while(true)
        {
            rep2(x,1,10,y,1,10)
            {
                City& u=maze[x][y];
                if(u.country==0)continue;
                rep(j,1,n)
                {
                    u.money[j]+=u.lazy[j];
                    u.lazy[j]=0;
                }
                if(u.fin)continue;
                u.fin=true;
                rep(j,1,n)
                {
                    if(u.money[j]<=0)
                    {
                        u.fin=false;
                        break;
                    }
                }
            }
            // printf("#cnt=%d\n",cnt);
            // rep(x,1,10)
            // {
            //     rep(y,1,10)
            //     {
            //         printf("%d\t",maze[x][y].money[1]);
            //     }
            //     printf("\n");
            // }
            bool ok=true;
            rep(i,1,n)
            {
                Country& c=coun[i];
                if(c.fin)continue;
                c.fin=true;
                rep2(x,c.xl,c.xh,y,c.yl,c.yh)
                {
                    City& u=maze[x][y];
                    rep(j,1,n)
                    {
                        if(!u.fin)
                        {
                            c.fin=false;
                            ok=false;
                            goto outer;
                        }
                    }
                }
                outer:
                if(c.fin)c.t=cnt;
            }
            if(ok)break;
            cnt++;
            rep2(x,1,10,y,1,10)
            {
                City& u=maze[x][y];
                if(u.country==0)continue;
                repne(i,0,4)
                {
                    int x1=x+dir[i][0], y1=y+dir[i][1];
                    City& v=maze[x1][y1];
                    if(v.country==0)continue;
                    rep(j,1,n)
                    {
                        int t=u.money[j]/1000;
                        u.lazy[j]-=t;
                        v.lazy[j]+=t;
                    }
                }
            }
        }
        sort(coun+1,coun+n+1);
        printf("Case Number %d\n",kase++);
        rep(i,1,n)
        {
            printf("   %s   %d\n",coun[i].name.c_str(),coun[i].t);
        }
    }
    return 0;
}