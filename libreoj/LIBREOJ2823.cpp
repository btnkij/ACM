/**
* Number:loj2823
* Title:「BalticOI 2014 Day 1」三个朋友 
* Status:AC
* Tag:[字符串哈希]
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
typedef unsigned long long ull;

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

struct string_hash
{
    ull _hashc[2000010], *hashc;
    const ull base = 233;
    ull powb[2000010] = {1};
    void init(char* s)
    {
        hashc = _hashc + 1;
        for(int i = 0; s[i]; i++)
        {
            powb[i + 1] = powb[i] * base;
            hashc[i] = hashc[i - 1] * base + s[i];
        }
    }
    ull range(int lt, int rt)
    {
        return hashc[rt] - hashc[lt - 1] * powb[rt - lt + 1];
    }
    ull concat(int lt1, int rt1, int lt2, int rt2)
    {
        if(lt1 > rt1 && lt2 > rt2)return 0ULL;
        if(lt1 > rt1)return range(lt2, rt2);
        if(lt2 > rt2)return range(lt1, rt1);
        return range(lt1, rt1) * powb[rt2 - lt2 + 1] + range(lt2, rt2);
    }
}solver;

char s[2000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int len; readi(len);
    if(len<3 || len%2==0)
    {
        printf("NOT POSSIBLE\n");
        return 0;
    }
    reads(s);
    solver.init(s);
    int mid=(len>>1);
    int cnt=0, k;
    ull pre=0;
    repne(i,0,len)
    {
        ull fro,bac;
        if(i<mid)fro=solver.concat(0,i-1,i+1,mid);
        else fro=solver.range(0,mid-1);
        if(i<=mid)bac=solver.range(mid+1,len-1);
        else bac=solver.concat(mid,i-1,i+1,len-1);
        if(fro==bac && fro!=pre)
        {
            pre=fro;
            cnt++;
            k=i;
            if(cnt>1)break;
        }
    }
    if(cnt==0)printf("NOT POSSIBLE\n");
    else if(cnt>1)printf("NOT UNIQUE\n");
    else
    {
        cnt=0;
        mid=len>>1;
        repne(i,0,len)
        {
            if(i!=k)
            {
                putchar(s[i]);
                cnt++;
                if(cnt==mid)break;
            }
        }
    }
    return 0;
}