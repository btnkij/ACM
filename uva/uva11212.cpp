/**
* Number:uva11212
* Title:Editing a Book 
* Status:AC
* Tag:[IDA*,迭代加深搜索,A*]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

int n;
bool IsSorted(int *a)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != i + 1)
            return false;
    }
    return true;
}
int h(int *a)
{
    int ans = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] != a[i - 1] + 1)
            ans++;
    }
    if (a[0] != 1)
        ans++;
    if (a[n - 1] == n)
        ans--;
    return ans;
}
bool dfs(int *a, int curdep, int maxdep)
{
    // printf("cur=%d\n", curdep);
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d ", a[i]);
    // }
    // printf("\n");
    if (curdep == maxdep && IsSorted(a))
        return true;
    if (h(a) >= (maxdep - curdep) * 3)
        return false;
    curdep++;
    int b[16];
    int buffer[16];
    for (int lt = 0; lt < n; lt++)
    {
        for (int rt = lt + 1; rt <= n; rt++)
        {
            int p = 0;
            for (int i = 0; i < lt; i++)
                buffer[p++] = a[i];
            for (int i = rt; i < n; i++)
                buffer[p++] = a[i];
            for (int i = 0; i <= n - (rt - lt); i++)
            {
                if (i == lt)
                    continue;
                p = 0;
                for (int j = 0; j < i; j++)
                    b[p++] = buffer[j];
                for (int j = lt; j < rt; j++)
                    b[p++] = a[j];
                for (int j = i; p < n; j++)
                    b[p++] = buffer[j];
                if (dfs(b, curdep, maxdep))
                    return true;
            }
        }
    }
    return false;
}
int main()
{
    int a[16];
    int kase = 1;
    while (scanf("%d", &n) != EOF && n)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d", a + i);
        }
        for (int maxdep = 0; maxdep < 9; maxdep++)
        {
            if (dfs(a, 0, maxdep))
            {
                printf("Case %d: %d\n", kase++, maxdep);
                break;
            }
        }
    }
    return 0;
}

/*//贪心WA了
struct Seg
{
    int begin,end;
};
Seg seg[10]; int len;
Seg buffer[10];

void Move(int from1,int from2,int to)
{
    if(to>from2)
    {
        memcpy(buffer,seg+from1,sizeof(Seg)*(from2-from1+1));
        memcpy(seg+from1,seg+from2+1,sizeof(Seg)*(to-from2));
        memcpy(seg+from1+to-from2,buffer,sizeof(Seg)*(from2-from1+1));
    }
    else
    {
        memcpy(buffer,seg+to,sizeof(Seg)*(from1-to));
        memcpy(seg+to,seg+from1,sizeof(Seg)*(from2-from1+1));
        memcpy(seg+from2-(from1-to)+1,buffer,sizeof(Seg)*(from1-to));
    }
}

int Merge()
{
    int tail=0;
    int i=0;
    while(i<len)
    {
        seg[tail].begin=seg[i].begin;
        i++;
        while(i<len && seg[i].begin==seg[i-1].end+1)i++;
        seg[tail].end=seg[i-1].end;
        tail++;
    }
    len=tail;
}

int CountMerge(int from1,int from2,int to)
{
    int cnt=0;
    if(from1>0 && from2<len-1 && seg[from1-1].end==seg[from2+1].begin-1)cnt++;
    if(seg[to].end==seg[from1].begin-1)cnt++;
    if(to<len-1 && seg[from2].end==seg[to+1].begin-1)cnt++;
    return cnt;
}

int main()
{
    int kase=1;
    while(scanf("%d",&len)!=EOF && len)
    {
        for(int i=0;i<len;i++)
        {
            int t;
            scanf("%d",&t);
            seg[i].begin=seg[i].end=t;
        }
        Merge();
        int ans=0;
        while(len>1)
        {
            int from1=-1,from2=-1,to=-1,n=0;
            for(int i=0;i<len;i++)
            {
                for(int j=i;j<len;j++)
                {
                    for(int k=0;k<len;k++)
                    {
                        if(i<=k && k<=j)continue;
                        int cnt=CountMerge(i,j,k);
                        if(cnt>n)from1=i,from2=j,to=k,n=cnt;
                    }
                }
            }
            Move(from1,from2,to);
            Merge();
            ans++;
        }
        printf("Case %d: %d\n",kase++,ans);
    }
    return 0;
}
*/