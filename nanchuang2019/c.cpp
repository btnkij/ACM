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

const int MAXN=2e5+10;
char s[MAXN];
vector<int> pos0,pos1,pos2;
int sum8[MAXN],sum9[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,q; readi(n,q);
    reads(s+1);
    pos0.push_back(-INF);
    pos1.push_back(-INF);
    pos2.push_back(-INF);
    rep(i,1,n)
    {
        sum8[i]=sum8[i-1], sum9[i]=sum9[i-1];
        if(s[i]=='8')sum8[i]++;
        else if(s[i]=='9')sum9[i]++;
        else if(s[i]=='0')pos0.push_back(i);
        else if(s[i]=='1')pos1.push_back(i);
        else if(s[i]=='2')pos2.push_back(i);
    }
    while(q--)
    {
        int l,r; readi(l,r);
        int last2=*(upper_bound(pos2.begin(),pos2.end(),r)-1);
        if(last2<l || last2>r)
        {
            printf("-1\n");
            continue;
        }
        int last0=*(upper_bound(pos0.begin(),pos0.end(),last2-1)-1);
        if(last0<l || last0>last2)
        {
            printf("-1\n");
            continue;
        }
        int last1=*(upper_bound(pos1.begin(),pos1.end(),last0-1)-1);
        if(last1<l || last1>last0 || sum9[last1]-sum9[l-1]<=0)
        {
            printf("-1\n");
            continue;
        }
        printf("%d\n",sum8[last1]-sum8[l-1]);
    }
    return 0;
}