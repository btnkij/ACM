/**
 * 
 * 快速排序
 * 
**/

#include <cstdio>
#include <algorithm>

void quick_sort(int* begin, int* end) // 传首尾指针，左闭右开区间
{
    if(end - begin <= 1)return;
    std::swap(*begin, *(begin + rand() % (end - begin)));
    int pivot = *begin;
    int *lt = begin, *rt = end - 1;
    while(lt != rt)
    {
        while(rt != lt && *rt > pivot)rt--;
        if(lt == rt)break;
        *lt = *rt; lt++;
        while(lt != rt && *lt < pivot)lt++;
        if(lt == rt)break;
        *rt = *lt; rt--;
    }
    *lt = pivot;
    quick_sort(begin, lt);
    quick_sort(lt + 1, end);
}