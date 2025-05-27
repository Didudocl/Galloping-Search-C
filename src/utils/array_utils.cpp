#include <omp.h>
#include <iostream>
#include <vector>
#include <random>
#include "array_utils.h"

const int MIN_VALUE = 1;
const int MAX_VALUE = 10'000'000;

// Generar arreglo paralelo con OpenMP
std::vector<int> generate_array_parallel(size_t size)
{
    std::vector<int> arr(size);

#pragma omp parallel
    {
        std::mt19937 gen(1234 + omp_get_thread_num());
        std::uniform_int_distribution<> dis(MIN_VALUE, MAX_VALUE);

#pragma omp for schedule(static)
        for (size_t i = 0; i < size; ++i)
        {
            arr[i] = dis(gen);
        }
    }

    return arr;
}

// Generar arreglo sin paralelismo
std::vector<int> generate_array(size_t size)
{
    std::vector<int> arr(size);
    std::mt19937 gen(1234);
    std::uniform_int_distribution<> dis(MIN_VALUE, MAX_VALUE);

    for (size_t i = 0; i < size; ++i)
    {
        arr[i] = dis(gen);
    }

    return arr;
}

// Generar claves aleatorias para búsqueda
std::vector<int> generate_keys(size_t count)
{
    std::vector<int> keys(count);
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(MIN_VALUE, MAX_VALUE);
    for (size_t i = 0; i < count; ++i)
    {
        keys[i] = dis(gen);
    }

    return keys;
}