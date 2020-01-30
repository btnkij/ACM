/**
* Number:uva1615
* Title:Highway
* Status:AC
* Tag:[greedy]
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

struct Seg
{
    double begin,end;
    bool operator<(const Seg& rhs)const
    {
        return this->end < rhs.end;
    }
};
vector<Seg> v;
int main()
{
    int L,D,N;
    while(scanf("%d %d %d",&L,&D,&N)!=EOF)
    {
        v.clear();
        for(int i=0;i<N;i++)
        {
            double x,y;
            scanf("%lf %lf",&x,&y);
            Seg seg;
            double r=sqrt(D*D-y*y);
            seg.begin=max((double)0,x-r);
            seg.end=min((double)L,x+r);
            v.push_back(seg);
        }
        sort(v.begin(),v.end());
        double rear=-1;
        int ans=0;
        for(Seg& it : v)
        {
            if(it.begin<=rear && rear<=it.end)continue;
            rear=it.end;
            ans++;   
        }
        printf("%d\n",ans);
    }
    return 0;
}