/**
* Number:ybt1237
* Title:求排列的逆序数
* Status:AC
* Tag:[归并排序]
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

ll ans;
int num[100010];
int buffer[100010];
void merge_sort(int* begin, int* end)
{
    int L = end - begin;
    if(L <= 1)return;
    int* mid = begin + (L >> 1);
    merge_sort(begin, mid);
    merge_sort(mid, end);
    int* plt = begin;
    int* prt = mid;
    int* pbuf = buffer;
    while(plt != mid && prt != end)
    {
        if(*plt <= *prt)*pbuf = *plt, plt++;
        else
        {
            *pbuf = *prt, prt++;
            ans += mid - plt;
        }
        pbuf++;
    }
    if(prt == end)copy(plt, mid, begin + (pbuf - buffer));
    copy(buffer, pbuf, begin);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)readi(num[i]);
    merge_sort(num, num+n);
    printf("%lld\n",ans);
    return 0;
}