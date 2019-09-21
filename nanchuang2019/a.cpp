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

// const int MAXN=1e8+10;
// int prime[MAXN], *tailp;
// bool is_nonprime[MAXN];
// void init_prime(int n)
// {
//     tailp = prime;
//     is_nonprime[0] = is_nonprime[1] = true;
//     for(int i = 2; i <= n; i++)
//     {
//         if(!is_nonprime[i])
//             *(tailp++) = i;
//         for(int* iter = prime; iter != tailp; iter++)
//         {
//             int t = i * (*iter);
//             if(t > n)break;
//             is_nonprime[t] = true;
//             if(i % *iter == 0)break;
//         }
//     }
// }

const int N=1e8;
int phi[N+10],prime[N+10],tot,ans;    
bool mark[N+10];    
void getphi()    
{    
   int i,j;    
   phi[1]=1;    
   for(i=2;i<=N;i++)//相当于分解质因式的逆过程    
   {    
       if(!mark[i])    
           {    
             prime[++tot]=i;//筛素数的时候首先会判断i是否是素数。    
             phi[i]=i-1;//当 i 是素数时 phi[i]=i-1    
             }    
       for(j=1;j<=tot;j++)    
       {    
          if(i*prime[j]>N)  break;    
          mark[i*prime[j]]=1;//确定i*prime[j]不是素数    
          if(i%prime[j]==0)//接着我们会看prime[j]是否是i的约数    
          {    
             phi[i*prime[j]]=phi[i]*prime[j];break;    
          }    
          else  phi[i*prime[j]]=phi[i]*(prime[j]-1);//其实这里prime[j]-1就是phi[prime[j]]，利用了欧拉函数的积性    
       }    
   }    
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    // init_prime(100000);
    // int n=tailp-prime;
    // int x=-INF;
    // repne(i,1,n)x=max(prime[i]-prime[i-1],x);
    // printf("%d",x);
    getphi();
    for(int i=10000000;i<=10000100;i++)printf("%d\n",phi[i]);
    return 0;
}