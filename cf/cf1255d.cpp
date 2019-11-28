#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <map>
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

typedef vector<pair<int,int> > Factor;
map<Factor,int> M;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k; readi(n,k);
    ll ans=0;
    repne(i,0,n)
    {
        int t; readi(t);
        Factor ori,com;
        for(int i=2;i*i<=t;i++)
        {
            int cnt=0;
            while(t%i==0)t/=i,cnt++;
            cnt%=k;
            if(cnt)ori.push_back(make_pair(i,cnt));
        }
        if(t>1)ori.push_back(make_pair(t,1));
        for(auto it:ori)com.push_back(make_pair(it.first,k-it.second));
        ans+=M[com];
        M[ori]++;
    }
    printf("%lld\n",ans);
    return 0;
}