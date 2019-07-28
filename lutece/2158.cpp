/**
* Number:2158
* Title:我永远喜欢冬马和纱
* Status:AC
* Tag:[莫队, 区间众数]
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

int sz;
int v[200010];
unordered_map<int,int> id;
struct Segment
{
    int id,l,r;
    bool operator<(const Segment& rhs)const
    {
        int b1=l/sz, b2=rhs.l/sz;
        if(b1==b2)return b1&1 ? r>rhs.r : r<rhs.r;
        return b1<b2;
    }
}segs[200010];
int cnt[200010],same[200010];
int tmp;
void add(int val)
{
    same[cnt[val]]--;
    cnt[val]++;
    same[cnt[val]]++;
    tmp=max(tmp,cnt[val]);
}
void remove(int val)
{
    same[cnt[val]]--;
    if(cnt[val]==tmp && same[tmp]==0)tmp--;
    cnt[val]--;
    same[cnt[val]]++;
}
int ans[200010];
void solve(int m)
{
    sort(segs,segs+m);
    int lt=0,rt=-1;
    repne(i,0,m)
    {
        Segment& s=segs[i];
        while(rt<s.r)add(v[++rt]);
        while(lt>s.l)add(v[--lt]);
        while(rt>s.r)remove(v[rt--]);
        while(lt<s.l)remove(v[lt++]);
        ans[s.id]=tmp;
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    int tot=1;
    rep(i,1,n)
    {
        int t; readi(t);
        if(!id.count(t))id[t]=tot++;
        v[i]=id[t];
    }
    sz=(int)sqrt(n+0.5);
    repne(i,0,m)
    {
        Segment& s=segs[i];
        readi(s.l, s.r);
        s.id=i;
    }
    solve(m);
    repne(i,0,m)printf("%d\n",ans[i]);
    return 0;
}