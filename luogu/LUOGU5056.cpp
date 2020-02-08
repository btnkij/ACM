/**
* Number:p5156
* Title:【模板】插头dp
* Status:AC
* Tag:[插头dp]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <unordered_map>
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

unordered_map<unsigned,int> M;
struct Node
{
    unsigned state;
    ll value;
}Q[2][2<<24];
int cnt[2];
unsigned one[20];
char mat[20][20];
int pre,cur;
void dp(unsigned sta, ll val)
{
    auto it=M.find(sta);
    if(it==M.end())
    {
        M[sta]=cnt[cur];
        Q[cur][cnt[cur]++]=(Node){sta,val};
        return;
    }
    Q[cur][it->second].value+=val;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; scanf("%d %d",&n,&m);
    int lastx,lasty;
    for(int i=0;i<n;i++)
    {
        scanf("%s",mat[i]);
        for(int j=0;j<m;j++)
            if(mat[i][j]=='.')
                lastx=i, lasty=j;
    }
    one[0]=0x1;
    for(int j=1;j<16;j++)
        one[j]=one[j-1]<<2;
    ll ans=0;
    pre=0,cur=1;
    Q[0][0]=(Node){0,1}; cnt[0]=1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<cnt[pre];j++)
            Q[pre][j].state<<=2;
        for(int j=0;j<m;j++)
        {
            M.clear(); cnt[cur]=0;
            for(int k=0;k<cnt[pre];k++)
            {
                unsigned sta=Q[pre][k].state;
                ll val=Q[pre][k].value;
                int left=(sta>>(j<<1))&0x3, down=(sta>>((j+1)<<1))&0x3;
                if(mat[i][j]!='.')
                {
                    if(!left && !down)
                        dp(sta,val);
                }
                else if(!left && !down)
                {
                    if(mat[i+1][j]=='.' && mat[i][j+1]=='.')
                        dp(sta+one[j]+one[j+1]*2,val);
                }
                else if(!left && down)
                {
                    if(mat[i+1][j]=='.')dp(sta-one[j+1]*down+one[j]*down,val);
                    if(mat[i][j+1]=='.')dp(sta,val);
                }
                else if(left && !down)
                {
                    if(mat[i+1][j]=='.')dp(sta,val);
                    if(mat[i][j+1]=='.')dp(sta-one[j]*left+one[j+1]*left,val);
                }
                else if(left==1 && down==1)
                {
                    int nested=1;
                    for(int p=j+2;p<=m;p++)
                    {
                        unsigned b=(sta>>(p<<1))&0x3;
                        if(b==1)nested++;
                        else if(b==2)nested--;
                        if(!nested)
                        {
                            dp(sta-one[j]-one[j+1]-one[p],val);
                            break;
                        }
                    }
                }
                else if(left==2 && down==2)
                {
                    int nested=1;
                    for(int p=j-1;p>=0;p--)
                    {
                        unsigned b=(sta>>(p<<1))&0x3;
                        if(b==1)nested--;
                        else if(b==2)nested++;
                        if(!nested)
                        {
                            dp(sta-one[j]*2-one[j+1]*2+one[p],val);
                            break;
                        }
                    }
                }
                else if(left==2 && down==1)
                {
                    dp(sta-one[j]*2-one[j+1],val);
                }
                else if(i==lastx && j==lasty)
                {
                    ans+=val;
                }
            }
            swap(pre,cur);
        }
    }
    printf("%lld",ans);
    return 0;
}