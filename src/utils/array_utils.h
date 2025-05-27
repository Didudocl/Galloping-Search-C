#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <vector>

std::vector<int> generate_array(std::size_t size);
std::vector<int> generate_array_parallel(std::size_t size);
std::vector<int> generate_keys(std::size_t count);

#endif