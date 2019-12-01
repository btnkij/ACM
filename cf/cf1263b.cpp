#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
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

bool vis[20][20];
string s[20];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(NULL);
    int T; cin>>T;
    while(T--)
    {
        int n; cin>>n;
        clr(vis,false);
        repne(i,0,n)
        {
            cin>>s[i];
            repne(j,0,4)vis[j][s[i][j]&0xF]=true;
        }
        int ans=0;
        repne(i,0,n)
        {
            if(count(s,s+n,s[i])>1)
            {
                repne2(j,0,4,k,0,10)
                {
                    if(!vis[j][k])
                    {
                        vis[j][k]=true;
                        s[i][j]=0x30|k;
                        goto endfor;
                    }
                }
                endfor:
                ans++;
            }
        }
        cout<<ans<<endl;
        repne(i,0,n)cout<<s[i]<<endl;
    }
    return 0;
}