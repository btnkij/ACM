/**
* Number:loj10002
* Title:「一本通 1.1 例 3」喷水装置 
* Status:AC
* Tag:[贪心]
**/

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
#define PI acos(-1)
#define eps 1e-10
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

struct Segment
{
    double a,b;
};
vector<Segment> seg;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        seg.clear();
        int n; readi(n);
        double L,W; scanf("%lf %lf",&L,&W);
        W=W/2;
        repne(i,0,n)
        {
            double p,r; scanf("%lf %lf",&p,&r);
            if(r<=W)continue;
            double d=sqrt(r*r-W*W);
            seg.push_back((Segment){p-d,p+d});
        }
        sort(seg.begin(),seg.end(),[](Segment& lhs,Segment& rhs){
            return lhs.a < rhs.a;
        });
        bool flag=true;
        if(seg.empty() || seg[0].a>0)
        {
            flag=false;
        }
        int ans=0;
        double pre=0, nxt;
        int i,j;
        for(i=0;i<seg.size() && flag;)
        {
            int k=-1;
            nxt=-INF;
            for(j=i;j<seg.size() && flag && seg[j].a<=pre;j++)
            {
                if(seg[j].b>nxt)
                {
                    k=j;
                    nxt=seg[j].b;
                }
            }
            if(k==-1)
            {
                flag=false;
                break;
            }
            ans++;
            if(nxt>=L)break;
            pre=nxt;
            i=j;
        }
        if(!flag || nxt<L)
            printf("-1\n");
        else
            printf("%d\n",ans);
    }
    return 0;
}