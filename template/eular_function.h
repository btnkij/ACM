/**
 * 
 * 欧拉函数
 * 
**/


// 预处理phi(1)~phi(MAXN-1)
const int MAXN = 1000010;
int phi[MAXN];
void init_phi()
{
    phi[1] = 1;
    for(int i = 2; i < MAXN; i++)
    {
        if(phi[i])continue;
        for(int j = i; j < MAXN; j += i)
        {
            if(!phi[j])phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    }
}