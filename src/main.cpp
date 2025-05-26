#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include "utils/array_utils.h"
#include "search/gallopingSearch.h"
#include "search/binarySearch.h"
#include "sort/quickSort.h"
#include <fstream>

using namespace std;
using namespace std::chrono;

const vector<size_t> CLAVE_COUNTS = {1000, 5000, 10000, 50000, 100000};
vector<double> tiempos_binaria;
vector<double> tiempos_galopante;

int main()
{
    cout << "==========================================" << endl;

    auto t1 = high_resolution_clock::now();
    vector<int> arr = generate_array_parallel();
    auto t2 = high_resolution_clock::now();
    cout << "✔ Arreglo generado con paralelismo en " << duration<double>(t2 - t1).count() << " segundos." << endl;

    auto t3 = high_resolution_clock::now();
    vector<int> arr1 = generate_array();
    auto t4 = high_resolution_clock::now();
    cout << "✔ Arreglo generado sin paralelismo en " << duration<double>(t4 - t3).count() << " segundos." << endl;

    // Ordenar arr con std::sort
    cout << "Ordenando arreglo paralelo con std::sort" << endl;
    auto t_sort_start = high_resolution_clock::now();
    sort(arr.begin(), arr.end());
    auto t_sort_end = high_resolution_clock::now();
    cout << "✔ Ordenamiento con std::sort completado en " << duration<double>(t_sort_end - t_sort_start).count() << " segundos." << endl;

    // Ordenar arr1 con quickSort
    cout << "Ordenando arreglo sin paralelismo con quickSort" << endl;
    auto t_quick_start = high_resolution_clock::now();
    if (!arr1.empty())
    {
        quickSort(arr1, 0, arr1.size() - 1);
    }
    auto t_quick_end = high_resolution_clock::now();
    cout << "✔ Ordenamiento con quickSort completado en " << duration<double>(t_quick_end - t_quick_start).count() << " segundos." << endl;

    for (size_t clave_count : CLAVE_COUNTS)
    {
        vector<int> claves = generate_keys(clave_count);

        auto tb_start = high_resolution_clock::now();
        for (int clave : claves)
            binarySearch(arr, 0, arr.size() - 1, clave);
        auto tb_end = high_resolution_clock::now();
        double t_binaria = duration<double, milli>(tb_end - tb_start).count();
        tiempos_binaria.push_back(t_binaria);

        auto tg_start = high_resolution_clock::now();
        for (int clave : claves)
            gallopingSearch(arr, arr.size(), clave);
        auto tg_end = high_resolution_clock::now();
        double t_galopante = duration<double, milli>(tg_end - tg_start).count();
        tiempos_galopante.push_back(t_galopante);
    }

    // Mostrar tabla final
    cout << left << setw(25) << "Numero de Claves"
         << setw(25) << "Busqueda Binaria (ms)"
         << setw(25) << "Busqueda Galopante (ms)" << endl;

    ofstream archivo("resultados.txt");
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return 1;
    }
    archivo << left << setw(25) << "Numero de Claves"
            << setw(25) << "Busqueda Binaria (ms)"
            << setw(25) << "Busqueda Galopante (ms)" << endl;

    cout << string(65, '-') << endl;
    archivo << string(65, '-') << endl;

    for (size_t i = 0; i < CLAVE_COUNTS.size(); ++i)
    {
        cout << left << setw(25) << CLAVE_COUNTS[i]
             << setw(25) << fixed << setprecision(2) << tiempos_binaria[i]
             << setw(25) << fixed << setprecision(2) << tiempos_galopante[i] << endl;

        archivo << left << setw(25) << CLAVE_COUNTS[i]
                << setw(25) << fixed << setprecision(2) << tiempos_binaria[i]
                << setw(25) << fixed << setprecision(2) << tiempos_galopante[i] << endl;
    }

    archivo.close();
    return 0;
}