/**
 * 
 * 归并排序
 * 
**/

#include <algorithm>

int buffer[100010];
void merge_sort(int* begin, int* end)
{
    int L = end - begin;
    if(L <= 1)return;
    int* mid = begin + (L >> 1);
    merge_sort(begin, mid);
    merge_sort(mid, end);
    int* plt = begin;
    int* prt = mid;
    int* pbuf = buffer;
    while(plt != mid && prt != end)
    {
        if(*plt <= *prt)*pbuf = *plt, plt++;
        else *pbuf = *prt, prt++;
        pbuf++;
    }
    if(prt == end)std::copy(plt, mid, begin + (pbuf - buffer));
    std::copy(buffer, pbuf, begin);
}