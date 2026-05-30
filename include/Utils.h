#ifndef UTILS_H
#define UTILS_H

#include <vector>

using namespace std;

namespace Utils {
    /**
     * @brief Generates a vector of random integers within a specified range.
     *
     * @param count The number of random integers to generate.
     * @param min The minimum value of the random numbers (inclusive).
     * @param max The maximum value of the random numbers (inclusive).
     * @param seed The seed for the random number generator for reproducibility.
     * @return A vector containing the generated random integers.
     */
    vector<int> generateRandomRequests(int count, int min, int max, unsigned int seed);
}

#endif // UTILS_H
