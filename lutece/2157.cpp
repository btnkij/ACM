/**
* Number:2157
* Title:冬马和纱天下第一
* Status:AC
* Tag:[分块, 区间众数]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_map>
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

int v[40010];
unordered_map<int,int> id;
int sum[210][40010],mode[210][210];
int cnt[40010];
vector<int> vis;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    int tot=1;
    repne(i,0,n)
    {
        int t; readi(t);
        if(!id.count(t))id[t]=tot++;
        v[i]=id[t];
    }
    int sz=(int)sqrt(n+0.5);
    int nblock=n/sz+(n%sz>0);
    rep(i,1,nblock)
    {
        copy(sum[i-1]+1, sum[i-1]+tot+1, sum[i]+1);
        int lt=(i-1)*sz, rt=min(lt+sz, n);
        repne(j,lt,rt)
        {
            sum[i][v[j]]++;
        }
    }
    rep(i,1,nblock)
    {
        int num, tmp=0;
        rep(j,i,nblock)
        {
            int lt=(j-1)*sz, rt=min(lt+sz, n);
            repne(k,lt,rt)
            {
                cnt[v[k]]++;
                if(cnt[v[k]]>tmp)
                {
                    tmp=cnt[v[k]];
                    num=v[k];
                }
            }
            mode[i][j]=num;
        }
        mset(cnt,0);
    }
    int ans=0;
    while(m--)
    {
        int L,R; readi(L,R);
        // L--, R--;
        L=(L+ans-1)%n, R=(R+ans-1)%n;
        if(L>R)swap(L,R);
        int lblock=L/sz+2, rblock=R/sz;
        int num=mode[lblock][rblock];
        int tmp=lblock<=rblock ? sum[rblock][num]-sum[lblock-1][num] : 0;
        while(!vis.empty())
        {
            cnt[vis.back()]=0;
            vis.pop_back();
        }
        for(int i=min(L/sz*sz+sz-1,R);i>=L;i--)
        {
            int t=v[i];
            cnt[t]++;
            vis.push_back(t);
            int s=lblock<=rblock ? sum[rblock][t]-sum[lblock-1][t] : 0;
            tmp=max(tmp, cnt[t]+s);
        }
        if(L/sz<R/sz)
        {
            for(int i=R/sz*sz;i<=R;i++)
            {
                int t=v[i];
                cnt[t]++;
                vis.push_back(t);
                int s=lblock<=rblock ? sum[rblock][t]-sum[lblock-1][t] : 0;
                tmp=max(tmp, cnt[t]+s);
            }
        }
        ans=tmp;
        printf("%d\n",ans);
    }
    return 0;
}