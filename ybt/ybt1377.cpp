/**
* Number:ybt1377
* Title:最优乘车(travel)
* Status:AC
* Tag:[floyd]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <string>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)

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

int adj[550][550];
void floyd(int n)
{
    for(int k = 1; k <= n; k++)
    {
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(adj[i][k]==INF || adj[k][j]==INF)continue;
                if(adj[i][j]>adj[i][k]+adj[k][j])
                    adj[i][j]=adj[i][k]+adj[k][j];
            }
        }
    }
}

int st[1000],tail;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m,n; scanf("%d%d",&m,&n);
    getchar();
    mset(adj,INF);
    rep(i,1,n)adj[i][i]=0;
    rep(i,1,m)
    {
        tail=0;
        string s;
        getline(cin,s);
        stringstream ss(s);
        int t;
        while(ss>>t)
        {
            repne(i,0,tail)
            {
                adj[st[i]][t]=1;
            }
            st[tail++]=t;
        }
    }
    floyd(n);
    if(adj[1][n]!=INF)printf("%d",adj[1][n]-1);
    else printf("NO");
    return 0;
}

/*
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <ctime>
#include <vector>
#include <fstream>
#include <list>
#include <iomanip>
#include <numeric>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pi acos(-1)
const int inf = 0x3f3f3f3f;
const int N=1005;
int a[N],g[N][N];
int main() 
{
#ifdef __DEBUG__
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int n,m;
    scanf("%d%d\n",&m,&n);//注意获取换行
    memset(g,inf,sizeof(g));
    for(int i=1;i<=n;i++){
        g[i][i]=0;
    }
    while(m--){
        string str;
        getline(cin,str);
        stringstream in(str);
        int tmp,cnt=0;
        while(in>>tmp){
            a[++cnt]=tmp;
        }
        for(int i=1;i<=cnt;i++){
            for(int j=i+1;j<=cnt;j++){
                g[a[i]][a[j]]=1;
            }
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
            }
        }
    }
    if(g[1][n]==inf){
        cout<<"NO";
    }else{
        cout<<g[1][n]-1<<endl;
    }
    puts("");
    return 0;
}
//获取读入经典题!
*/