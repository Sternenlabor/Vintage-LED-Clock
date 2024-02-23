
#include "tasker.h"
#include "event.h"
#include "string.h"

/* Null, because instance will be initialized on demand. */
Tasker *Tasker::m_pInstance = nullptr;

Tasker::Tasker() : m_pTskTimer(nullptr)
{
}

Tasker::~Tasker()
{
   for (auto el : m_tasks)
   {
      delete el;
   }
   m_tasks.clear();
}

void Tasker::AddTask(TaskBase *tsk)
{
   m_tasks.push_back(tsk);
}

void Tasker::Run()
{
   // not yet initialized start timer and push EvtTskInit 
   if (m_pTskTimer == nullptr)
   {
      m_pTskTimer = new TskTimer();
      m_tasks.push_back(m_pTskTimer);
      for (TaskBase *el : m_tasks)
      {
         el->Enqueue(new EvtTskInit());
      }
   }

   for (TaskBase *el : m_tasks)
   {
      el->Run();
   }
}

void Tasker::SendEvent(Event* pEvt)
{
   pEvt->GetDestination()->Enqueue(pEvt);
}

TskTimer *Tasker::TI()
{
   return m_pTskTimer;
}

Tasker *Tasker::GetInstance()
{
   if (m_pInstance == nullptr)
   {
      m_pInstance = new Tasker();
   }
   return m_pInstance;
}

TaskBase* Tasker::GetTask(const char* cstrTaskName)
{
   TaskBase* pRetTsk = nullptr;
   for(auto pTsk : m_tasks)
   {
      if (strcmp(pTsk->GetName(), cstrTaskName) == 0)
      {
         pRetTsk = pTsk;
         break;
      }
   }
   return pRetTsk;
}