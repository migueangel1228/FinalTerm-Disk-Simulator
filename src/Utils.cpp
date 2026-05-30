#include "../include/Utils.h"
#include <random>
#include <vector>

using namespace std;

vector<int> Utils::generateRandomRequests(int count, int min, int max, unsigned int seed) {
    vector<int> requests;
    requests.reserve(count);

    mt19937 generator(seed);
    uniform_int_distribution<int> distribution(min, max);

    for (int i = 0; i < count; ++i) {
        requests.push_back(distribution(generator));
    }

    return requests;
}
