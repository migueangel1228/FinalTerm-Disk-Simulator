#ifndef DISKSCHEDULER_H
#define DISKSCHEDULER_H

#include "ScheduleResult.h"
#include <vector>
#include <string>

using namespace std;

class DiskScheduler {
public:
    // Constantes
    static const int TOTAL_CYLINDERS;
    static const int MAX_CYLINDER;
    static const int REQUEST_COUNT;

    enum class Algorithm { FCFS, SCAN, CSCAN };
    enum class Direction { UP, DOWN };

    // Constructor
    DiskScheduler(int startHeadPosition, Algorithm selectedAlgorithm, unsigned int requestSeed, Direction startDirection = Direction::UP);

    // Interfaz publica
    void runAllAlgorithms();
    void runSelectedAlgorithm();
    void printAllResults() const;
    void printSummary() const;
    void exportResultsToCSV(const string& filename) const;

private:
    // Atributos
    int startHeadPosition;
    Algorithm selectedAlgorithm;
    Direction initialDirection;
    unsigned int requestSeed;
    vector<int> requests;
    vector<ScheduleResult> results;

    // Metodos privados
    void loadRandomRequests();
    ScheduleResult calculateSelectedAlgorithm() const;

    // Algoritmos de planificacion
    ScheduleResult calculateFCFS() const;
    ScheduleResult calculateSCAN() const;
    ScheduleResult calculateCSCAN() const;

    // Metodos auxiliares
    void printAlgorithmResult(const ScheduleResult& result) const;
    int calculateTotalMovement(const vector<int>& servicedRequests, int initialPosition) const;
};

#endif // DISKSCHEDULER_H
