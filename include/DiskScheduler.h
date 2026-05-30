#ifndef DISKSCHEDULER_H
#define DISKSCHEDULER_H

#include "ScheduleResult.h"
#include <vector>
#include <string>

using namespace std;

class DiskScheduler {
public:
    // Constants
    inline static const int TOTAL_CYLINDERS = 5000;
    inline static const int MAX_CYLINDER = 4999;
    inline static const int REQUEST_COUNT = 1000;

    enum class Direction { UP, DOWN };

    // Constructor
    DiskScheduler(int startHeadPosition, Direction startDirection = Direction::UP);

    // Public interface
    void runAllAlgorithms();
    void printAllResults() const;
    void exportResultsToCSV(const string& filename) const;

private:
    // Attributes
    int startHeadPosition;
    Direction initialDirection;
    vector<int> requests;
    vector<ScheduleResult> results;

    // Private methods
    void loadRandomRequests();

    // Scheduling algorithms
    ScheduleResult calculateFCFS() const;
    ScheduleResult calculateSCAN() const;
    ScheduleResult calculateCSCAN() const;

    // Helper methods
    void printAlgorithmResult(const ScheduleResult& result) const;
    int calculateTotalMovement(const vector<int>& servicedRequests, int initialPosition) const;
};

#endif // DISKSCHEDULER_H
