#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


//Add prototypes for any helper functions here
bool scheduleH(const AvailabilityMatrix& avail, const size_t maxShifts, DailySchedule& sched, 
std::vector<size_t> shiftCount);
bool specialRow(const DailySchedule& avail, int r );

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    std::vector<size_t> shiftCount; 
    for (size_t row = 0; row < avail.size(); row++)
    {
        sched.push_back(std::vector<Worker_T>());
        for (int col = 0; col < dailyNeed; col++)
        {
            sched[row].push_back(-1);
        }
    }
    for (size_t i = 0; i < avail[0].size(); i++)
    {
        shiftCount.push_back(0);
    }
    return scheduleH(avail, maxShifts, sched, shiftCount);
}

