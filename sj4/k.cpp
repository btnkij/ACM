#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
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

const int MAXN=1e9+5;
struct BIT
{
    map<int, map<int,int> > tree;
    void add(int x,int y)
    {
        for(int i = x; i < MAXN; i += i & -i)
        {
            for(int j = y; j < MAXN; j += j & -j)
            {
                tree[i][j] += 1;
            }
        }
    }
    int query(int x,int y)
    {
        int sum = 0;
        for(int i = x; i; i ^= i & -i)
        {
            for(int j = y; j; j ^= j & -j)
            {
                sum += tree[i][j];
            }
        }
        return sum;
    }
}P,Rect1,Rect2;
typedef pair<int,int> Point;
ll ans;
void addPoint(int x,int y)
{
    ans+=Rect1.query(x,y)-Rect2.query(x-1,MAXN-4)-Rect2.query(MAXN-4,y-1)+Rect2.query(x-1,y-1);
    P.add(x,y);
}
void addRect(int x_1,int y_1,int x_2,int y_2)
{
    ans+=P.query(x_2,y_2)-P.query(x_1-1,y_2)-P.query(x_1,y_1-1)+P.query(x_1-1,y_1-1);
    Rect1.add(x_1,y_1);
    Rect2.add(x_2,y_2);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    while(n--)
    {
        int op; readi(op);
        if(op==1)
        {
            int x,y; readi(x,y);
            addPoint(x,y);
        }
        else if(op==2)
        {
            int x_1,y_1,x_2,y_2;
            readi(x_1,y_1,x_2,y_2);
            if(x_1==x_2 && y_1==y_2)addPoint(x_1,y_1);
            else addRect(x_1,y_1,x_2,y_2);
            // addRect(x_1,y_1,x_2,y_2);
        }
        printf("%lld\n",ans);
    }
    return 0;
}