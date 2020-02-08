/**
* Number:p1177
* Title:【模板】快速排序
* Status:AC
* Tag:[快速排序]
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
int read()
{
    int num = 0;
    char ch;
    bool sign = false;
    do
    {
        ch = getchar();
        if(ch == '-')sign = true;
    }while(ch < '0' || ch > '9');
    do{ num = num * 10 + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    if(sign)num = -num;
    return num;
}
void quick_sort(int* begin, int* end)
{
    if(end - begin <= 1)return;
    swap(*begin, *(begin + rand() % (end - begin)));
    int pivot = *begin;
    int *lt = begin, *rt = end - 1;
    while(lt != rt)
    {
        while(rt != lt && *rt > pivot)rt--;
        if(lt == rt)break;
        *lt = *rt; lt++;
        while(lt != rt && *lt < pivot)lt++;
        if(lt == rt)break;
        *rt = *lt; rt--;
    }
    *lt = pivot;
    quick_sort(begin, lt);
    quick_sort(lt + 1, end);
}
int arr[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)arr[i]=read();
    quick_sort(arr,arr+n);
    repne(i,0,n)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}