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

struct Node
{
    int val,nxt;
}nodes[200010];
int head[100010],tail[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    int tot;
    while(T--)
    {
        int n,k; readi(n,k);
        if(n%k!=0)
        {
            printf("no\n");
            continue;
        }
        printf("yes\n");
        int p=1,dir=1;
        tot=k+1;
        for(int i=1;i<=k;i++)head[i]=tail[i]=i;
        for(int i=1;i<=n;i++)
        {
            Node& nod=nodes[tail[p]];
            nod.val=i;
            nod.nxt=tail[p]=tot++;
            if(p==k && dir>0)dir=-dir;
            else if(p==1 && dir<0)dir=-dir;
            else p+=dir;
        }
        for(int i=1;i<=k;i++)
        {
            for(int j=head[i];j!=tail[i];j=nodes[j].nxt)
            {
                if(j!=head[i])putchar(' ');
                printf("%d",nodes[j].val);
            }
            putchar('\n');
        }
    }
    return 0;
}