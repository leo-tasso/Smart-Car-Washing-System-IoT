#ifndef __TASK__
#define __TASK__

class Task {
  Task(int period){
    myPeriod = period;
    timeElapsed = 0;
  }
public:
  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }
  
private:

  int myPeriod;
  int timeElapsed;

};

#endif