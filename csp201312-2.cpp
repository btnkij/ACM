/**
* Number:csp201312-2
* Title:ISBN号码
* Status:AC
* Tag:[基础]
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

char s[20];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(s);
    int i=1;
    char* p=s;
    char chk=0;
    while(i<=9)
    {
        if(*p!='-')
        {
            chk=(chk+(*p&0xF)*i)%11;
            i++;
        }
        p++;
    }
    if(chk==10)chk='X';
    else chk=0x30|chk;
    p=s+strlen(s)-1;
    if(*p==chk)printf("Right");
    else
    {
        *p=chk;
        printf("%s",s);
    }
    return 0;
}