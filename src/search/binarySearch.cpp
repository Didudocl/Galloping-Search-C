#include <vector>
#include <iostream>
#include "binarySearch.h"

using namespace std;

// Búsqueda binaria iterativa
int binarySearchIterative(const vector<int> &arr, size_t l, size_t r, int x)
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

// Búsqueda binaria con recursión
int binarySearchRecursive(const vector<int> &arr, int l, int r, int x)
{
    // Caso base
    if (l > r)
        return -1;

    int mid = l + (r - l) / 2;
    if (arr[mid] == x)
        return mid;
    else if (x < arr[mid])
        return binarySearchRecursive(arr, l, mid - 1, x);
    else
        return binarySearchRecursive(arr, mid + 1, r, x);
}