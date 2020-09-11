/**
* Number:LUOGU1955
* Title: [NOI2015]程序自动分析
* Status:AC
* Tag:[并查集]
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

constexpr int N=2e6+10;
int fa[N];
int findr(int x)
{
    return x==fa[x]?x:fa[x]=findr(fa[x]);
}
void merge(int x,int y)
{
    int rx=findr(x),ry=findr(y);
    if(rx!=ry)fa[rx]=ry;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<int,int> id;
    vector<tuple<int,int>> q;
    int T; cin>>T;
    while(T--)
    {
        int n; cin>>n;
        id.clear();
        q.clear();
        int tot=0;
        while(n--)
        {
            int i,j,e; cin>>i>>j>>e;
            if(!id.count(i))id[i]=++tot,fa[tot]=tot;
            if(!id.count(j))id[j]=++tot,fa[tot]=tot;
            if(e)merge(id[i],id[j]);
            else q.emplace_back(id[i],id[j]);
        }
        bool ok=true;
        for(auto it:q)
        {
            if(findr(get<0>(it))==findr(get<1>(it)))
            {
                ok=false;
                break;
            }
        }
        cout<<(ok?"YES\n":"NO\n");
    }
    return 0;
}