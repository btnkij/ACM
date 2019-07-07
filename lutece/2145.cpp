/**
* Number:2145
* Title:人在地上走，锅从天上来
* Status:AC
* Tag:[set]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
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

struct Seg
{
    int beg,end;
    bool operator<(const Seg& rhs)const
    {
        return end<rhs.beg;
    }
};
set<Seg> S;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    while(n--)
    {
        Seg seg;
        readi(seg.beg, seg.end);
        auto it=S.find(seg);
        if(it==S.end())
        {
            S.insert(seg);
        }
        else
        {
            while(it!=S.end())
            {
                seg.beg=min(seg.beg, it->beg);
                seg.end=max(seg.end, it->end);
                S.erase(it);
                it=S.find(seg);
            }
            S.insert(seg);
        }
        printf("%d\n", S.size());
    }
    return 0;
}

/*
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
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

vector<int> V;
int a[200010],b[200010];
int ufs[200010];
bool vis[200010];
int findr(int x)
{
    return x==ufs[x]?x:ufs[x]=findr(ufs[x]);
}
void link(int from,int to)
{
    int r1=findr(from), r2=findr(to);
    if(r1==r2)return;
    ufs[r1]=r2;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)
    {
        readi(a[i], b[i]);
        V.push_back(a[i]);
        V.push_back(b[i]);
    }
    sort(V.begin(), V.end());
    V.erase(unique(V.begin(), V.end()), V.end());
    rep(i,0,(n<<1)+5)ufs[i]=i;
    int cnt=0;
    repne(i,0,n)
    {
        cnt++;
        int x=lower_bound(V.begin(), V.end(), a[i])-V.begin();
        int y=lower_bound(V.begin(), V.end(), b[i])-V.begin();
        int k=x;
        while(k<=y)
        {
            if(vis[k])
            {
                cnt--;
                k=findr(k);
            }
            vis[k]=true;
            if(k>x)link(k-1,k);
            k++;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
*/