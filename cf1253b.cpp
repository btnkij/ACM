#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
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

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    set<int> inque,vis;
    vector<int> ans;
    int len=0;
    bool ok=true;
    repne(i,0,n)
    {
        int t; readi(t);
        if(t<0 && inque.count(-t))
        {
            inque.erase(-t);
        }
        else if(t>0 && !vis.count(t))
        {
            vis.insert(t);
            inque.insert(t);
        }
        else
        {
            ok=false;
            break;
        }
        len++;
        if(inque.size()==0)
        {
            ans.push_back(len);
            vis.clear();
            inque.clear();
            len=0;
        }
    }
    ok=ok&&!inque.size();
    if(ok)
    {
        printf("%d\n",ans.size());
        for(int i:ans)printf("%d ",i);
    }
    else
    {
        printf("-1");
    }
    return 0;
}