    /**
    * Number:ybt1538, loj10116
    * Title:清点人数
    * Status:AC
    * Tag:[前缀和]
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

    int num[1000010];
    int main()
    {
    #ifdef __DEBUG__
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
        int n,k; readi(n,k);
        int ans=0, cur=0;
        while(k--)
        {
            char evt[4]; reads(evt);
            int m,p; readi(m);
            if(evt[0]=='A')
            {
                if(cur<=m)
                {
                    for(;cur<=m;cur++)ans+=num[cur];
                }
                printf("%d\n",ans);
            }
            else if(evt[0]=='B')
            {
                readi(p);
                if(m<cur)ans+=p;
                else num[m]+=p;
            }
            else if(evt[0]=='C')
            {
                readi(p);
                if(m<cur)ans-=p;
                else num[m]-=p;
            }
        }
        return 0;
    }