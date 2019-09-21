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

const int MAXN=3e2+10;
char s[MAXN<<1];
int palin[MAXN<<1];
void loadString(const char* str)
{
    char* p = s;
    *(p++) = '#';
    const char* q = str;
    while(*q)
    {
        *(p++) = *(q++);
        *(p++) = '#';
    }
}
void manacher()
{
    int p, far = 0;
    for(int i = 0; s[i]; i++)
    {
        int lt, rt;
        if(i < far)rt = std::min(i + palin[(p << 1) - i] - 1, far);
        else rt = i;
        lt = (i << 1) - rt;
        while(lt >= 0 && s[lt] == s[rt])lt--, rt++;
        if(rt - 1 > far)
        {
            far = rt - 1;
            p = i;
        }
        palin[i] = rt - i;
    }
}

char ss[MAXN];
vector<int> pos[30];
vector<int> v;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(ss);
    int len=strlen(ss)*2+1;
    loadString(ss);
    manacher();
    for(int i=0;i<len;i++)
    {
        if(i&1)palin[i]=(palin[i]+1)/2;
        else palin[i]=palin[i]/2;
    }
    for(int i=1;i<len;i+=2)
    {
        pos[s[i]-'a'].push_back(i);
    }
    ll ans=0;
    for(int i=0;i<len;i++)
    {
        if(palin[i]<=1)continue;
        v.clear();
        for(int j=0;j<26;j++)
        {
            auto it=lower_bound(pos[j].begin(),pos[j].end(),i);
            if(it==pos[j].end())continue;
            int p=*it-i;
            if(s[i]=='#')p=(p+1)/2;
            else p=p/2+1;
            if(p<=palin[i])
            {
                v.push_back(p);
            }
        }
        sort(v.begin(),v.end());
        int pre=0;
        printf("i=%d\n",i);
        int j=0;
        for(;j<v.size();j++)
        {
            printf("pre=%d v[j]=%d\n",pre,v[j]);
            ans+=ll(j+1)*(v[j]-pre);
            printf("ans+=%lld\n",ll(j+1)*(v[j]-pre));
            pre=v[j];
        }
        if(pre!=palin[i])ans+=(ll)j*(palin[i]-pre);
    }
    printf("%lld",ans);
    return 0;
}