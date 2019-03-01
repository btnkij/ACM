/**
 * 
 * 线性素数筛
 * 
**/

int prime[664580], *tailp;
bool is_nonprime[10000010];
void init_prime(int n)
{
    tailp = prime;
    is_nonprime[0] = is_nonprime[1] = true;
    for(int i = 2; i <= n; i++)
    {
        if(!is_nonprime[i])*(tailp++) = i;
        for(int* iter = prime; iter != tailp; iter++)
        {
            int t = i * (*iter);
            if(t > n)break;
            is_nonprime[t] = true;
            if(i % *iter == 0)break;
        }
    }
}