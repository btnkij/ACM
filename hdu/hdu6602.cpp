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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=1e5+4;
vector<int> pos[MAXN];
int n,c,k,arr[MAXN];
int getcnt(int lt,int rt,int x)
{
    vector<int>::iterator it1=lower_bound(pos[x].begin(), pos[x].end(), lt);
    vector<int>::iterator it2=upper_bound(pos[x].begin(), pos[x].end(), rt);    
    return distance(it1,it2);
}
int solve(int lt,int rt)
{
    if(rt-lt<k)return 0;
    for(int i=lt;i<rt;i++)
    {
        if(getcnt(lt,rt,arr[i])<k)
        {
            return max(solve(lt,i),solve(i+1,rt));
        }
    }
    return rt-lt;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(n,c,k)!=EOF)
    {
        repne(i,0,MAXN)pos[i].clear();
        repne(i,0,n)
        {
            readi(arr[i]);
            pos[arr[i]].push_back(i);
        }
        int ans=solve(0,n);
        printf("%d\n",ans);
    }
    return 0;
}