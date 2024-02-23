#ifndef _TASK_BASE_H_
#define _TASK_BASE_H_

#include <string>
#include <queue>

class Event;
class Tasker;

class TaskBase
{
public:
   TaskBase(const char *cstrName);
   void Enqueue(const Event *pEvt);

   void Run();

   const char *GetName();
   ~TaskBase();

   virtual void Entry(const Event *pEvt) = 0;

protected:
   void StartTimer(uint32_t uiTimId, uint64_t uiToMs, int32_t iUsrCode = 0, bool bPeriodic = false);
   void StopTimer(uint32_t uiTimId, int32_t iUsrCode = 0);
   void StopAllTimers();
   Tasker* TK();

private:
   std::queue<const Event *> m_queue;
   const char *m_cstrName;
};

#endif /* _TASK_BASE_H_ */