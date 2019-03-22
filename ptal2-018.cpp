/**
* Number:
* Title:
* Status:?
* Tag:[]
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
typedef long long ll;

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

double poly1[1000010], poly2[1000010];
double q[1000010];
char buffer[100];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    int e;
    double c;
    scanf("%d %lf",&e,&c);
    int mag1=e;
    poly1[e]=c;
    repne(i,1,n)
    {
        scanf("%d %lf",&e,&c);
        poly1[e]=c;
    }
    int m; readi(m);
    scanf("%d %lf",&e,&c);
    int mag2=e;
    poly2[e]=c;
    repne(i,1,m)
    {
        scanf("%d %lf",&e,&c);
        poly2[e]=c;
    }
    for(int i=mag1;i>=mag2;i--)
    {
        double t=poly1[i]/poly2[mag2];
        q[i-mag2]=t;
        printf("%lf\n",t);
        for(int j=mag2;j>=0;j--)
        {
            poly1[i-j+mag2]-=poly2[j]*t;
        }
    }
    bool first=true;
    for(int i=mag1-mag2;i>=0;i--)
    {
        double t;
        sprintf(buffer,"%.1lf",q[i]);
        sscanf(buffer,"%lf",&t);
        if(fabs(t)>1e-14)
        {
            if(!first)putchar(' ');
            first=false;
            printf("%d %s",i,buffer);
        }
    }
    putchar('\n');
    first=true;
    for(int i=mag2;i>=0;i--)
    {
        double t;
        sprintf(buffer,"%.1lf",poly1[i]);
        sscanf(buffer,"%lf",&t);
        if(fabs(t)>1e-14)
        {
            if(!first)putchar(' ');
            first=false;
            printf("%d %s",i,buffer);
        }
    }
    return 0;
}