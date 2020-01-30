/**
* Number:uva1608
* Title:Non-boring sequences
* Status:AC
* Tag:[分治]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <unordered_map>
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

const int MAXN=200010;
unordered_map<int,int> id;
int last[MAXN],pre[MAXN],nxt[MAXN];
int a[MAXN];
bool solve(int lt,int rt)
{
    if(lt>=rt)return true;
    int i=lt,j=rt;
    while(i<=j)
    {
        if(pre[i]<lt && nxt[i]>rt)
            return solve(lt,i-1) && solve(i+1,rt);
        if(i!=j && pre[j]<lt && nxt[j]>rt)
            return solve(lt,j-1) && solve(j+1,rt);
        i++,j--;
    }
    return false;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        id.clear();
        rep(i,1,n)
        {
            readi(a[i]);
            if(!id.count(a[i]))
                id.insert(make_pair(a[i],id.size()));
        }
        fill_n(last,id.size(),0);
        for(int i=1;i<=n;i++)
        {
            int k=id[a[i]];
            pre[i]=last[k];
            last[k]=i;
        }
        fill_n(last,id.size(),n+1);
        for(int i=n;i>=1;i--)
        {
            int k=id[a[i]];
            nxt[i]=last[k];
            last[k]=i;
        }
        if(solve(1,n))puts("non-boring");
        else puts("boring");
    }
    return 0;
}