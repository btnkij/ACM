/**
* Number:cf1285e
* Title:Delete a Segment
* Status:AC
* Tag:[扫描线]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
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
    int T; readi(T);
    vector<pair<int,int> > events;
    while(T--)
    {
        int n; readi(n);
        events.clear();
        rep(i,1,n)
        {
            int l,r; readi(l,r);
            events.emplace_back(l,-i);
            events.emplace_back(r,i);
        }
        sort(events.begin(),events.end());
        vector<int> cnt(n+1,0);
        set<int> segs;
        int tot=0;
        for(auto& e:events)
        {
            int i=abs(e.second);
            if(e.second<0)
            {
                if(segs.empty())cnt[i]--;
                segs.insert(i);
            }
            else
            {
                segs.erase(i);
                if(segs.empty())cnt[i]--,tot++;
            }
            if(segs.size()==1)cnt[*segs.begin()]++;
        }
        rep(i,1,n)printf("%d ",cnt[i]);
        puts("");
        printf("%d\n",tot+*max_element(cnt.begin()+1,cnt.end()));
    }
    return 0;
}