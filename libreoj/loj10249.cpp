/**
* Number:loj10249
* Title:「一本通 1.3 例 5」weight
* Status:?
* Tag:[dfs]
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

int n,m,n2,tot;
int arr[2010];
bool S[510];
int fro[2010], bac[2010];
bool flag;
void dfs(int p, int lt, int rt)
{
    if(lt>rt)
    {
        lt--, rt++;
        if(fro[lt]+bac[rt]!=tot)return;
        flag=true;
        for(int i=1;i<=lt;i++)printf("%d ",fro[i]-fro[i-1]);
        for(int i=rt;i<=n;i++)printf("%d ",bac[i]-bac[i+1]);
        return;
    }
    int t=arr[p]-fro[lt-1];
    if(!flag && 1<=t && t<=500 && S[t])
    {
        fro[lt]=arr[p];
        dfs(p+1,lt+1,rt);
    }
    t=arr[p]-bac[rt+1];
    if(!flag && 1<=t && t<=500 && S[t])
    {
        bac[rt]=arr[p];
        dfs(p+1,lt,rt-1);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n);
    n2=n<<1;
    repne(i,0,n2)readi(arr[i]);
    readi(m);
    repne(i,0,m)
    {
        int t; readi(t);
        S[t]=true;
    }
    sort(arr,arr+n2);
    tot=arr[n2-1];
    flag=false;
    dfs(0,1,n);
    return 0;
}