/**
* Number:loj2427
* Title:「POI2010」珍珠项链 Beads 
* Status:AC
* Tag:[字符串哈希]
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

int arr[200010];
ull hash1[200010], hash2[200010];
const ull base = 1e6+7;
ull powb[200010];
set<ull> S;
vector<int> kk;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    powb[0]=1;
    rep(i,1,n)
    {
        readi(arr[i]);
        powb[i]=powb[i-1]*base;
        hash1[i]=hash1[i-1]*base+arr[i];
    }
    for(int i=n;i>=1;i--)
    {
        hash2[i]=hash2[i+1]*base+arr[i];
    }
    int maxcnt=0;
    for(int k=1;k<=n && n/k>=maxcnt;k++)
    {
        int cnt=0;
        S.clear();
        for(int i=1;i+k-1<=n;i+=k)
        {
            ull h1=hash1[i+k-1]-hash1[i-1]*powb[k];
            ull h2=hash2[i]-hash2[i+k]*powb[k];
            if(S.find(h1)==S.end() && S.find(h2)==S.end())
            {
                cnt++;
                S.insert(h1);
            }
        }
        if(cnt>maxcnt)
        {
            maxcnt=cnt;
            kk.clear();
            kk.push_back(k);
        }
        else if(cnt==maxcnt)kk.push_back(k);
    }
    printf("%d %d\n",maxcnt,kk.size());
    for(int i:kk)printf("%d ",i);
    return 0;
}