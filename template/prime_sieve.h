/**
 * 
 * 线性素数筛
 * 
**/

int prime[664580], *tailp;
bool is_nonprime[10000010];
int nxt[10000010]; // nxt[i]: i的最小质因子
void init_prime(int n)
{
    tailp = prime;
    is_nonprime[0] = is_nonprime[1] = true;
    nxt[1] = 1;
    for(int i = 2; i <= n; i++)
    {
        if(!is_nonprime[i])
            *(tailp++) = nxt[i] = i;
        for(int* iter = prime; iter != tailp; iter++)
        {
            int t = i * (*iter);
            if(t > n)break;
            is_nonprime[t] = true;
            nxt[t] = *iter;
            if(i % *iter == 0)break;
        }
    }
}