#include "Scheduler.h"

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timer.setupPeriod(((unsigned long)basePeriod)*1000);  
  nTasks = 0;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}
  
void Scheduler::schedule(){
  timer.waitForNextTick();
  //Serial.println("prova");
  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->updateAndCheckTime(basePeriod)){
      taskList[i]->tick();
    }
  }
}