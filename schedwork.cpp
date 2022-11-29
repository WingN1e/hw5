

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here
bool canWork(const AvailabilityMatrix& avail, const size_t maxShift, DailySchedule& sched, int day, Worker_T worker) {
  unsigned int shifts = 1;
  if(!avail[day][worker]) return false;
  for(int day_ = 0; day_ < (int)sched.size(); day_++){
    for(int worker_ = 0; worker_ < (int)sched[day_].size(); worker_++) {
      if(sched[day_][worker_] == worker) {
        shifts++;
        if(day_ == day) return false;
      }
    }
  }
  if(shifts > maxShift) return false;
  return true;
}

//code taken from Sudoku.cpp in lab 10
bool fixSchedule(const AvailabilityMatrix&avail, DailySchedule& sched, const size_t dailyNeed, const size_t maxShift, int day, Worker_T shift) {
  if((day = (int)sched.size()-1) && ((int) shift == (int) sched[sched.size()-1].size())) return true;
  if(shift == dailyNeed) {
    day++;
    shift = 0;
  }
  for(int i = 0; i < (int) avail[day].size(); i++) {
    if(canWork(avail, maxShift, sched, day, i)) {
      sched[day][shift] = i;
      if(fixSchedule(avail, sched, dailyNeed, maxShift, day, shift+1)) return true;
    }
    sched[day][shift] = INVALID_ID;
  }
  return true;
}

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
  for(int row = 0; row < (int)avail.size(); row++) {
    vector<Worker_T> day(dailyNeed, INVALID_ID);
    sched.push_back(day);
  }
  return fixSchedule(avail, sched, dailyNeed, maxShifts, 0, 0);
}

