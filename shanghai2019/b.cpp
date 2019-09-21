#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <set>
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

// const int MAXN=1e6+10;
// map<int,int> cnt,zero,flip;
// void pushup(int p)
// {
//     cnt[p]=cnt[p<<1]+cnt[p<<1|1];
// }
// void pushdown(int p,int lt,int rt)
// {
//     int mid=(lt+rt)>>1;
//     int lc=p<<1,rc=lc|1;
//     if(zero[p])
//     {
//         cnt[lc]=cnt[rc]=0;
//         zero[lc]=zero[rc]=1;
//         flip[lc]=flip[rc]=0;
//         zero[p]=0;
//     }
//     if(flip[p])
//     {
//         cnt[lc]=mid-lt+1-cnt[lc];
//         cnt[rc]=rt-mid-cnt[rc];
//         flip[lc]^=1, flip[rc]^=1;
//         flip[p]=0;
//     }
// }
// void clear()
// {
//     cnt[1]=flip[1]=0;
//     zero[1]=1;
// }
// void rev(int p,int lt,int rt,int qlt,int qrt)
// {
//     if(qlt<=lt && rt<=qrt)
//     {
//         cnt[p]=rt-lt+1-cnt[p];
//         flip[p]^=1;
//         return;
//     }
//     pushdown(p,lt,rt);
//     int mid=(lt+rt)>>1;
//     int lc=p<<1,rc=lc|1;
//     if(qlt<=mid)rev(lc,lt,mid,qlt,qrt);
//     if(mid<qrt)rev(rc,mid+1,rt,qlt,qrt);
//     pushup(p);
// }
// int query(int p,int lt,int rt,int qlt,int qrt)
// {
//     if(qlt<=lt && rt<=qrt)
//     {
//         return cnt[p];
//     }
//     pushdown(p,lt,rt);
//     int mid=(lt+rt)>>1;
//     int lc=p<<1,rc=lc|1;
//     int ans=0;
//     if(qlt<=mid)ans+=query(lc,lt,mid,qlt,qrt);
//     if(mid<qrt)ans+=query(rc,mid+1,rt,qlt,qrt);
//     return ans;
// }

// struct Seg
// {
//     int l,r;
//     bool operator<(const Seg& rhs)const
//     {
//         return r+1<rhs.l || l-1>rhs.r;
//     }
// };
// set<Seg> tree;

map<int,int> tree;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    rep(kase,1,T)
    {
        int n,m; readi(n,m);
        tree.clear();
        while(m--)
        {
            int l,r; readi(l,r);
            tree[l-1]^=1;
            tree[r]^=1;
        }
        int ans=0,pre=n,flip=0;
        for(auto it=tree.rbegin();it!=tree.rend();it++)
        {
            // printf("%d %d\n",it->first,it->second);
            if(it->second==0)continue;
            if(flip)ans+=pre-(it->first);
            flip^=(it->second);
            pre=(it->first);
        }
        if(pre>=0 && flip)ans+=pre+1;
        printf("Case #%d: %d\n",kase,ans);
    }
    return 0;
}