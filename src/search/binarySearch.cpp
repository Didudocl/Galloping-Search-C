#include <vector>
#include <iostream>
#include "binarySearch.h"

using namespace std;

// Búsqueda binaria iterativa
int binarySearch(const vector<int> &arr, size_t l, size_t r, int x)
{
    while (r >= l)
    {
        size_t mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}