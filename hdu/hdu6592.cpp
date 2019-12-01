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
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=3e5+10;
int n;
struct
{
    int arr[MAXN],small[MAXN],large[MAXN];
    void set(int pos,int val)
    {
        arr[pos]=val;
        for(int i=pos;i<=n;i+=i&-i)
        {
            if(val>arr[small[i]])small[i]=pos;
            if(val>=arr[large[i]])large[i]=pos;
        }
    }
    pair<int,int> query(int pos)
    {
        int tmp=-INF;
        pair<int,int> ans;
        while(pos)
        {
            if(tmp<=arr[small[pos]])
            {
                if(tmp<arr[small[pos]])
                {
                    ans.second=large[pos];
                }
                tmp=arr[small[pos]];
                ans.first=small[pos];
            }
        }
    }
}BIT;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    
    return 0;
}