#include <vector>
#include <iostream>
#include "gallopingSearch.h"
#include "binarySearch.h"
#include <algorithm>

using namespace std;

// Búsqueda galopante/exponencial
int gallopingSearch(const vector<int> &arr, size_t size, int x)
{
    if (size == 0)
        return -1;
    if (arr[0] == x)
        return 0;

    size_t linf = 1;
    while (linf * 2 < size && arr[2 * linf] < x)
    {
        linf *= 2;
    }

    return binarySearch(arr, linf, min(2 * linf, size - 1), x);
}