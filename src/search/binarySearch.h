#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <vector>

int binarySearchIterative(const std::vector<int> &arr, size_t l, size_t r, int x);
int binarySearchRecursive(const std::vector<int> &arr, int l, int r, int x);

#endif