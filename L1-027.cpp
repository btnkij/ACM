/**
* Number:L1-027
* Title:出租
* Status:AC
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
typedef int ll;

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

char num[20];
char arr[20];
int ord[20];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(num);
    strcpy(arr,num);
    sort(arr,arr+11);
    char* end=unique(arr,arr+11);
    sort(arr,end,greater<int>());
    for(char* p=arr;p!=end;p++)
    {
        ord[(*p)&0xF]=p-arr;
    }
    printf("int[] arr = new int[]{");
    for(char* p=arr;p!=end;p++)
    {
        if(p!=arr)putchar(',');
        putchar(*p);
    }
    printf("};\n");
    printf("int[] index = new int[]{");
    for(char *p=num;*p;p++)
    {
        if(p!=num)putchar(',');
        printf("%d",ord[(*p)&0xF]);
    }
    printf("};");
    return 0;
}