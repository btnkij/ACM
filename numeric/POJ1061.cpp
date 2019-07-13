/**
* Number:POJ1061
* Title:青蛙的约会
* Status:AC
* Tag:[数论, exgcd, 同余方程]
**/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

//D
typedef long long ll;
//ax+by==gcd(a,b)
ll exgcd(ll a,ll& x,ll b,ll &y)
{
	if(b==0){x=1;y=0;return a;}
	else
	{
		ll d=exgcd(b,y,a%b,x);
		y-=a/b*x;
		return d;
	}
}
//ax===b mod m
bool LinearCongruent(ll a,ll& x,ll b,ll m)
{
	ll y;
	ll d=exgcd(a,x,m,y);
	if(b%d)return false;
	x=b/d*x;
	ll r=m/d;
	if(r<0)r=-r;
	// x=(x+m)%r; //最小整数解
	x=(x%r+r)%r; //最小正整数解
	// x=(x+m)%r+(d-1)*r; //最大整数解
	return true;
}
int main()
{
	ll x,y,m,n,L;
	cin>>x>>y>>m>>n>>L;
	ll t;
	if(!LinearCongruent(m-n,t,y-x,L))cout<<"Impossible"<<endl;
	else cout<<t<<endl;
	#ifdef _DEBUG_
	system("pause");
	#endif
	return 0;
}