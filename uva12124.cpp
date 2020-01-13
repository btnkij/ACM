/**
* Number:uva12124
* Title:Assemble
* Status:?
* Tag:[二分, map]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
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

map<string,vector<pair<int,int> > > M;
bool check(int mid,int b)
{
    int ans=0;
    for(auto& parts:M)
    {
        int minp=INF;
        for(auto& it:parts.second)
        {
            if(it.second>=mid && it.first<minp)
            {
                minp=it.first;
            }
        }
        ans+=minp;
    }
    return ans<=b;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin>>T;
    while(T--)
    {
        int n,b; cin>>n>>b;
        int lt=INF,rt=-INF;
        M.clear();
        repne(i,0,n)
        {
            string t,n; int p,q;
            cin>>t>>n>>p>>q;
            M[t].emplace_back(p,q);
            lt=min(lt,q); rt=max(rt,q);
        }
        while(lt<rt)
        {
            int mid=(lt+rt+1)>>1;
            if(check(mid,b))lt=mid;
            else rt=mid-1;
        }
        printf("%d\n",lt);
    }
    return 0;
}