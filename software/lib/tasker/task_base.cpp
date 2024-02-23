
#include "task_base.h"
#include "tasker.h"
#include "event.h"

TaskBase::TaskBase(const char *cstrName) : m_queue(),
                                           m_cstrName(cstrName)
{
}
TaskBase::~TaskBase() {}

void TaskBase::Enqueue(const Event *pEvt)
{
   m_queue.push(pEvt);
}

void TaskBase::Run()
{
   if (m_queue.empty())
   {
      // do fast calls (as fast as possible)
      Entry(nullptr);
   }
   else
   {
      const Event *pEvt = m_queue.front();
      Entry(pEvt);
      m_queue.pop();
      // new and delete will be very slow on this system
      // improve this by using a stativ event pool
      delete pEvt;
   }
}

const char *TaskBase::GetName()
{
   return m_cstrName;
}

void TaskBase::StartTimer(uint32_t uiTimId, uint64_t uiToMs, int32_t iUsrCode, bool bPeriodic)
{
   Tasker::GetInstance()->TI()->StartTimer(this, uiTimId, uiToMs, iUsrCode, bPeriodic);
}

void TaskBase::StopTimer(uint32_t uiTimId, int32_t iUsrCode)
{
   Tasker::GetInstance()->TI()->StopTimer(this, uiTimId, iUsrCode);
}

void TaskBase::StopAllTimers()
{
   Tasker::GetInstance()->TI()->StopAllTimers(this);
}

Tasker* TaskBase::TK()
{
   return Tasker::GetInstance();
}