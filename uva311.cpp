/**
* Number:uva311
* Title:Packets 
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

ll parcel[10];
int main()
{
    while(cin >> parcel[1] >> parcel[2] >> parcel[3] >> parcel[4] >> parcel[5] >> parcel[6]
        && (parcel[1] || parcel[2] || parcel[3] || parcel[4] || parcel[5] || parcel[6]))
    {
        ll ans=parcel[6]+parcel[5]+parcel[4];

        parcel[1]-=parcel[5]*11;

        parcel[2]-=parcel[4]*5;
        if(parcel[2]<0)parcel[1]+=parcel[2]*4;
        parcel[2]=max(parcel[2], 0LL);
        parcel[1]=max(parcel[1], 0LL);

        ans+=parcel[3]/4;
        parcel[3]%=4;
        if(parcel[3]>0)
        {
            ans++;
            parcel[3]=4-parcel[3];
            if(parcel[3]==3)
            {
                parcel[2]-=5;
                parcel[1]-=7;
            }
            else if(parcel[3]==2)
            {
                parcel[2]-=3;
                parcel[1]-=6;
            }
            else
            {
                parcel[2]-=1;
                parcel[1]-=5;
            }
            if(parcel[2]<0)parcel[1]+=parcel[2]*4;
        }
        
        if(parcel[2]>0)
        {
            ans+=parcel[2]/9;
            parcel[2]%=9;
            if(parcel[2]>0)
            {
                ans++;
                parcel[2]=9-parcel[2];
                parcel[1]-=parcel[2]*4;
            }
        }

        if(parcel[1]>0)
        {
            ans+=(parcel[1]+35)/36;
        }

        cout<<ans<<endl;
    }
    return 0;
}