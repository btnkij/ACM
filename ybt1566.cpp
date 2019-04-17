/**
* Number:
* Title:
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MOD=1e6;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    set<int> S;
    int type=0;
    int ans=0;
    while(n--)
    {
        int a, b; readi(a, b);
        if(a==type || S.empty())
        {
            S.insert(b);
            type=a;
        }
        else
        {
            set<int>::iterator it=S.lower_bound(b);
            if(it==S.end())
            {
                it--;
                ans=(ans+abs(b-*it))%MOD;
                S.erase(it);
            }
            else if(it==S.begin())
            {
                ans=(ans+abs(b-*it))%MOD;
                S.erase(it);
            }
            else
            {
                set<int>::iterator it2=it;
                it2--;
                if(abs(b-*it2)<=abs(b-*it))
                {
                    ans=(ans+abs(b-*it2))%MOD;
                    S.erase(it2);
                }
                else
                {
                    ans=(ans+abs(b-*it))%MOD;
                    S.erase(it);
                }
            }
        }
    }
    printf("%d",ans);
    return 0;
}