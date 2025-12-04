#ifndef RECCHECK
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
void scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
    map<size_t, size_t>& numShifts, 
    size_t n, size_t d, int& bs
);

bool isValid(
    const AvailabilityMatrix& avail,
    const size_t maxShifts,
    map<size_t, size_t>& numShifts, 
    size_t n, size_t k
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below
    int badShift=-1;
    for(size_t n=0; n<avail.size(); n++)
    {
        vector<Worker_T> row;
        for(size_t d=0; d<dailyNeed; d++)
            row.push_back(INVALID_ID);
        sched.push_back(row);
    }
    map<size_t, size_t> numShifts;
    scheduleHelper(avail, dailyNeed, maxShifts, sched, numShifts, 0, 0, badShift);

    // cout << "printing sched" << endl;
    // for(int i=0; i<sched.size(); i++)
    // {
    //     for(int j=0; j<sched[i].size(); j++)
    //     {
    //         cout << sched[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "printing avail" << endl;
    // for(int i=0; i<avail.size(); i++)
    // {
    //     for(int j=0; j<avail[i].size(); j++)
    //     {
    //         cout << avail[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // vector<int> inner = *find(sched.begin(), sched.end(), INVALID_ID);
    // if(inner == sched.end()) return false;
    // return ( *find(inner.begin(), inner.end(), INVALID_ID)!= INVALID_ID);
    // vector<int> inner = *find(sched.begin(), sched.end(), INVALID_ID);
    // if(inner == sched.end()) return false;
    
    // return ( find(sched.begin(), sched.end(), INVALID_ID)!= sched.end());
    return (badShift==-1);
    
}

void scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
    map<size_t, size_t>& numShifts, 
    size_t n, size_t d, int& bs
)
{
    
    if(d>=dailyNeed)
    {
        d=0;
        n++;
    }
    if(n>=avail.size()) return;

    for(size_t k=0; k<avail[n].size(); k++)
    {
        numShifts[k] = numShifts[k] + 1;
        // cout << "num shifts is "<< (*numShifts.find(k)).second << endl;
        sched[n][d] = k;
        if(isValid(avail, maxShifts, numShifts, n, k)) 
            return scheduleHelper(avail, dailyNeed, maxShifts, sched, numShifts, n, (d+1), bs);
        numShifts[k] = numShifts[k] - 1;
    }

    sched[n][d] = INVALID_ID;
    bs = d;
}

bool isValid(
    const AvailabilityMatrix& avail,
    const size_t maxShifts,
    map<size_t, size_t>& numShifts, 
    size_t n, size_t k  
)
{
    return avail[n][k] && ((*(numShifts.find(k))).second <= maxShifts);

}