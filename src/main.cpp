#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "utils/array_utils.h"
#include "sort/quickSort.h"
#include "utils/performance_utils.h"

using namespace std;
using namespace std::chrono;

int main()
{
     cout << "\n"
          << endl;
     cout << "========================GENERACIÓN DE ARREGLO=========================" << endl;

     // Arreglos a generar
     size_t size = 5'000'000'000ULL; // U = unsigned - LL = long long (entero de 64 bits)

     // Generación de arreglo con paralelismo
     auto t1 = high_resolution_clock::now();
     vector<int> arr = generate_array_parallel(size);
     auto t2 = high_resolution_clock::now();
     cout << "✔ Arreglo generado con paralelismo en " << duration<double, milli>(t2 - t1).count() << " milisegundos." << endl;

     // Generación de arreglo sin paralelismo
     auto t3 = high_resolution_clock::now();
     vector<int> arr1 = generate_array(size);
     auto t4 = high_resolution_clock::now();
     cout << "✔ Arreglo generado sin paralelismo en " << duration<double, milli>(t4 - t3).count() << " milisegundos." << endl;

     cout << string(70, '=') << endl;
     cout << "\n"
          << endl;

     vector<int> arr_quick = arr; // Copia de array para ordenar con quickSort()

     cout << "========================ORDENAMIENTO DE ARREGLO=======================" << endl;

     // Ordenamiento por método de librería algorithms -> sort()
     auto t5 = high_resolution_clock::now();
     sort(arr.begin(), arr.end());
     auto t6 = high_resolution_clock::now();
     cout << "✔ Arreglo ordenado con sort() en " << duration<double, milli>(t6 - t5).count() << " milisegundos." << endl;

     // Ordenamiento con quickSort()
     auto t7 = high_resolution_clock::now();
     if (!arr.empty())
          quickSort(arr_quick, 0, arr_quick.size() - 1);
     auto t8 = high_resolution_clock::now();
     cout << "✔ Arreglo ordenado con quickSort() en " << duration<double, milli>(t8 - t7).count() << " milisegundos." << endl;

     cout << string(70, '=') << endl;
     cout << "\n"
          << endl;

     test_search_times(arr_sort);
     print_results();

     cout << string(95, '=') << endl;
     cout << "\n"
          << endl;

     return 0;
}
