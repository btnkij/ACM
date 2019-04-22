/**
* Number:scu2188
* Title:A multiplication game 
* Status:AC
* Tag:[博弈, 记忆化搜索]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
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

map<ll,bool> M;
ll n;
bool dfs(int p)
{
    if(p>=n)return false;
    map<ll,bool>::iterator it=M.find(p);
    if(it!=M.end())return it->second;
    if(!dfs(p*2) || !dfs(p*9)){M[p]=true; return true;}
    else {M[p]=false; return false;}
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(scanf("%lld",&n)!=EOF)
    {
        M.clear();
        printf("%s\n", dfs(1) ? "Stan wins." : "Ollie wins.");
    }
    return 0;
}