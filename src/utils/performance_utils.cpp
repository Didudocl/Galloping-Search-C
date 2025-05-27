#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <sstream>
#include "performance_utils.h"
#include "array_utils.h"
#include "search/binarySearch.h"
#include "search/gallopingSearch.h"

using namespace std;
using namespace std::chrono;

const vector<size_t> CLAVE_COUNTS = {1'000, 5'000, 10'000, 50'000, 100'000};
vector<double> tiempos_binariaIterativa, tiempos_binariaRecursiva, tiempos_galopante;

void test_search_times(const vector<int> &arr)
{
    tiempos_binariaIterativa.clear();
    tiempos_binariaRecursiva.clear();
    tiempos_galopante.clear();

    cout << "========================GENERACIÓN DE CLAVES==========================" << endl;
    for (size_t clave_count : CLAVE_COUNTS)
    {
        vector<int> claves = generate_keys(clave_count);

        cout << "✔ Clave:" << clave_count << endl;

        // Medición tiempo con búsqueda binaria iterativa
        auto tb_start = high_resolution_clock::now();
        for (int clave : claves)
            binarySearchIterative(arr, 0, arr.size() - 1, clave);
        auto tb_end = high_resolution_clock::now();
        double t_binariaI = duration<double, milli>(tb_end - tb_start).count();
        tiempos_binariaIterativa.push_back(t_binariaI);

        // Medición tiempo con búsqueda binaria recursiva
        auto tbr_start = high_resolution_clock::now();
        for (int clave : claves)
            binarySearchRecursive(arr, 0, arr.size() - 1, clave);
        auto tbr_end = high_resolution_clock::now();
        double t_binariaR = duration<double, milli>(tbr_end - tbr_start).count();
        tiempos_binariaRecursiva.push_back(t_binariaR);

        auto tg_start = high_resolution_clock::now();
        for (int clave : claves)
            gallopingSearch(arr, arr.size(), clave);
        auto tg_end = high_resolution_clock::now();
        double t_galopante = duration<double, milli>(tg_end - tg_start).count();
        tiempos_galopante.push_back(t_galopante);
    }
    cout << string(70, '=') << endl;
    cout << "\n"
         << endl;
}

void print_results()
{
    cout << string(95, '=') << endl;
    cout << left << setw(23) << "Numero de Claves"
         << setw(25) << "Búsqueda Binaria I."
         << setw(25) << "Búsqueda Binaria R."
         << setw(25) << "Búsqueda Galopante" << endl;

    ofstream archivo("./resultados.txt");
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    cout << string(95, '=') << endl;

    archivo << string(95, '=') << endl;
    archivo << left << setw(23) << "Numero de Claves"
            << setw(25) << "Búsqueda Binaria I."
            << setw(25) << "Búsqueda Binaria R."
            << setw(25) << "Búsqueda Galopante" << endl;
    archivo << string(95, '=') << endl;

    for (size_t i = 0; i < CLAVE_COUNTS.size(); ++i)
    {
        std::ostringstream ss_binariaIterativa, ss_birariaRecursiva, ss_galopante;
        ss_binariaIterativa << fixed << setprecision(2) << tiempos_binariaIterativa[i] << " ms";
        ss_birariaRecursiva << fixed << setprecision(2) << tiempos_binariaRecursiva[i] << " ms";
        ss_galopante << fixed << setprecision(2) << tiempos_galopante[i] << " ms";

        cout << left << setw(23) << CLAVE_COUNTS[i]
             << setw(25) << ss_binariaIterativa.str()
             << setw(25) << ss_birariaRecursiva.str()
             << setw(25) << ss_galopante.str()
             << endl;

        archivo << left << setw(23) << CLAVE_COUNTS[i]
                << setw(25) << fixed << setprecision(2) << tiempos_binariaIterativa[i]
                << setw(25) << fixed << setprecision(2) << tiempos_binariaRecursiva[i]
                << setw(25) << fixed << setprecision(2) << tiempos_galopante[i]
                << endl;
    }

    archivo.close();
}