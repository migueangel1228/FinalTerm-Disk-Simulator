#ifndef UTILS_H
#define UTILS_H

#include <vector>

using namespace std;

namespace Utils {
    /**
     * @brief Genera un vector de enteros aleatorios dentro de un rango especificado.
     *
     * @param count Cantidad de enteros aleatorios a generar.
     * @param min Valor minimo de los numeros aleatorios (inclusivo).
     * @param max Valor maximo de los numeros aleatorios (inclusivo).
     * @param seed Semilla para el generador de numeros aleatorios y mantener reproducibilidad.
     * @return Un vector con los enteros aleatorios generados.
     */
    vector<int> generateRandomRequests(int count, int min, int max, unsigned int seed);
}

#endif // UTILS_H
