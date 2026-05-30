#ifndef SCHEDULERESULT_H
#define SCHEDULERESULT_H

#include <string>
#include <vector>

using namespace std;

struct ScheduleResult {
    string algorithmName;
    int totalMovement = 0;
    vector<int> servicedRequests;
};

#endif // SCHEDULERESULT_H
