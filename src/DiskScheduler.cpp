#include "../include/DiskScheduler.h"
#include "../include/Utils.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <fstream>

using namespace std;

const int DiskScheduler::TOTAL_CYLINDERS = 5000;
const int DiskScheduler::MAX_CYLINDER = 4999;
const int DiskScheduler::REQUEST_COUNT = 1000;

DiskScheduler::DiskScheduler(int startHeadPosition, Direction startDirection)
    : startHeadPosition(startHeadPosition), initialDirection(startDirection) {
    if (startHeadPosition < 0 || startHeadPosition >= TOTAL_CYLINDERS) {
        throw invalid_argument("Start head position is out of bounds.");
    }
    loadRandomRequests();
}

void DiskScheduler::loadRandomRequests() {
    // Using a fixed seed for reproducibility as requested.
    unsigned int seed = 2023; 
    requests = Utils::generateRandomRequests(REQUEST_COUNT, 0, MAX_CYLINDER, seed);
}

void DiskScheduler::runAllAlgorithms() {
    results.clear();
    results.push_back(calculateFCFS());
    results.push_back(calculateSCAN());
    results.push_back(calculateCSCAN());
}

ScheduleResult DiskScheduler::calculateFCFS() const {
    ScheduleResult result;
    result.algorithmName = "FCFS";
    result.servicedRequests = requests; // Order is preserved
    result.totalMovement = calculateTotalMovement(result.servicedRequests, startHeadPosition);
    return result;
}

ScheduleResult DiskScheduler::calculateSCAN() const {
    ScheduleResult result;
    result.algorithmName = "SCAN";
    
    vector<int> left, right;
    for (int req : requests) {
        if (req < startHeadPosition) {
            left.push_back(req);
        } else {
            right.push_back(req);
        }
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    if (initialDirection == Direction::DOWN) {
        // Move down first, serving requests
        for (int i = left.size() - 1; i >= 0; --i) {
            result.servicedRequests.push_back(left[i]);
        }
        // Hit the beginning of the disk
        if (!left.empty() || !right.empty()) {
             result.servicedRequests.push_back(0);
        }
        // Move up, serving requests
        for (int req : right) {
            result.servicedRequests.push_back(req);
        }
    } else { // Direction::UP
        // Move up first
        for (int req : right) {
            result.servicedRequests.push_back(req);
        }
        // Hit the end of the disk
        if (!left.empty() || !right.empty()) {
            result.servicedRequests.push_back(MAX_CYLINDER);
        }
        // Move down
        for (int i = left.size() - 1; i >= 0; --i) {
            result.servicedRequests.push_back(left[i]);
        }
    }

    result.totalMovement = calculateTotalMovement(result.servicedRequests, startHeadPosition);
    return result;
}

ScheduleResult DiskScheduler::calculateCSCAN() const {
    ScheduleResult result;
    result.algorithmName = "C-SCAN";

    vector<int> left, right;
    for (int req : requests) {
        if (req < startHeadPosition) {
            left.push_back(req);
        } else {
            right.push_back(req);
        }
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Always moves in one direction (e.g., UP)
    // Serve requests to the right of the head
    for (int req : right) {
        result.servicedRequests.push_back(req);
    }

    // If there are requests to be served, jump to the end and then to the beginning
    if (!requests.empty()) {
        result.servicedRequests.push_back(MAX_CYLINDER);
        result.servicedRequests.push_back(0);
    }
    
    // Serve requests from the beginning
    for (int req : left) {
        result.servicedRequests.push_back(req);
    }

    result.totalMovement = calculateTotalMovement(result.servicedRequests, startHeadPosition);
    return result;
}

int DiskScheduler::calculateTotalMovement(const vector<int>& servicedRequests, int initialPosition) const {
    if (servicedRequests.empty()) {
        return 0;
    }
    int totalMovement = 0;
    int currentPosition = initialPosition;
    for (int request : servicedRequests) {
        totalMovement += abs(request - currentPosition);
        currentPosition = request;
    }
    return totalMovement;
}

void DiskScheduler::printAllResults() const {
    cout << "\n--- Disk Scheduling Simulation ---\n";
    cout << "Initial Head Position: " << startHeadPosition << "\n";
    cout << "Total Requests: " << requests.size() << "\n";
    cout << "------------------------------------\n";

    for (const auto& result : results) {
        printAlgorithmResult(result);
    }
}

void DiskScheduler::printAlgorithmResult(const ScheduleResult& result) const {
    cout << "\n--- Algorithm: " << result.algorithmName << " ---\n";
    cout << "Service Order and Movement:\n";
    
    int lastPos = startHeadPosition;
    for(int req : result.servicedRequests) {
        cout << "  Request: " << req << ", Movement: " << abs(req - lastPos) << "\n";
        lastPos = req;
    }

    cout << "Total Head Movement: " << result.totalMovement << " cylinders\n";
    if (!result.servicedRequests.empty()) {
        double avgMovement = static_cast<double>(result.totalMovement) / result.servicedRequests.size();
        cout << "Average Head Movement: " << avgMovement << " cylinders\n";
    }
    cout << "------------------------------------\n";
}

void DiskScheduler::exportResultsToCSV(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }

    outFile << "Algorithm,TotalMovement,AverageMovement\n";
    for (const auto& result : results) {
        double avgMovement = 0;
        if (!result.servicedRequests.empty()) {
            avgMovement = static_cast<double>(result.totalMovement) / result.servicedRequests.size();
        }
        outFile << result.algorithmName << "," << result.totalMovement << "," << avgMovement << "\n";
    }

    outFile.close();
    cout << "\nResults exported to " << filename << endl;
}
