#ifndef _TASKER_H_
#define _TASKER_H_

#include "task_base.h"
#include "timer.h"
#include "event.h"

class Tasker
{
public:
   static Tasker* GetInstance();
   ~Tasker();

   void AddTask(TaskBase *tsk);

   void Run();

   void SendEvent(Event* pEvt);
   
   TaskBase* GetTask(const char* cstrTaskName);

   TskTimer *TI();

private:
   Tasker();
   std::vector<TaskBase *> m_tasks;
   TskTimer *m_pTskTimer;
   static Tasker* m_pInstance;
};

#endif