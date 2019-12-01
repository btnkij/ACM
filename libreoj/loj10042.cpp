/**
* Number:loj10042
* Title:「一本通 2.1 练习 8」收集雪花 
* Status:AC
* Tag:[unordered_map]
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
typedef int ll;
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

unordered_map<int,int> M;
int arr[1000010];
int pre[1000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    int tot=0;
    rep(i,1,n)
    {
        int t; readi(t);
        auto it = M.find(t);
        if(it!=M.end())
        {
            arr[i]=it->second;
        }
        else
        {
            arr[i]=tot;
            M.insert(pair<int,int>(t,tot));
            tot++;
        }
    }
    int ans=-INF;
    int tmp=0;
    rep(i,1,n)
    {
        tmp = min(tmp+1, i-pre[arr[i]]);
        pre[arr[i]]=i;
        ans=max(ans,tmp);
    }
    printf("%d",ans);
    return 0;
}