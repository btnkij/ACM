#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

struct Node
{
    int typ,id,score;
    bool operator<(const Node& rhs)const
    {
        if(score!=rhs.score)return score<rhs.score;
        if(typ==rhs.typ)return id>rhs.id;
        return typ>rhs.typ;
    }
};

set<Node> S[54];
map<pair<int,int>,int> M;
set<Node>::reverse_iterator pos[54];
priority_queue<Node> Q;
int num[54];
vector<int> rec[54];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int m,n; scanf("%d %d",&m,&n);
    for(int i=1;i<=n;i++)
    {
        int id,score; scanf("%d %d",&id,&score);
        for(int j=0;j<m;j++)
        {
            S[j].insert((Node){j,id,score});
            M[make_pair(j,id)]=score;
        }
    }
    int q; scanf("%d",&q);
    while(q--)
    {
        int op,x,y,z;
        pair<int,int> xy;
        scanf("%d %d",&op,&x);
        switch(op)
        {
        case 1:
            scanf("%d %d",&y,&z);
            S[x].insert((Node){x,y,z});
            M[make_pair(x,y)]=z;
            break;
        case 2:
            scanf("%d",&y);
            xy=make_pair(x,y);
            if(!M.count(xy))break;
            z=M[xy];
            S[x].erase((Node){x,y,z});
            M.erase(xy);
            break;
        case 3:
            for(int i=0;i<m;i++)scanf("%d",&num[i]);
            while(!Q.empty())Q.pop();
            for(int i=0;i<m;i++)
            {
                rec[i].clear();
                pos[i]=S[i].rbegin();
                if(num[i]>0 && pos[i]!=S[i].rend())
                {
                    Q.push(*pos[i]);
                    pos[i]++, num[i]--;
                }
            }
            // x=min(1,x);
            while(x-- && !Q.empty())
            {
                auto nod=Q.top(); Q.pop();
                rec[nod.typ].push_back(nod.id);
                if(num[nod.typ]>0 && pos[nod.typ]!=S[nod.typ].rend())
                {
                    Q.push(*pos[nod.typ]);
                    pos[nod.typ]++, num[nod.typ]--;
                }
            }
            for(int i=0;i<m;i++)
            {
                if(rec[i].size()==0)puts("-1");
                else
                {
                    sort(rec[i].begin(),rec[i].end());
                    for(int id:rec[i])printf("%d ",id);
                    puts("");
                }
            }
            break;
        }
    }
    return 0;
}