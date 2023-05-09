#include "timer.h"
#include "event.h"
#include <Arduino.h>
#include "task_base.h"

TskTimer::TskTimer() : TaskBase("Timer"),
                       m_mapTimers()
{
}

TskTimer::~TskTimer()
{
}

void TskTimer::Entry(const Event *pEvt)
{
   if (!m_mapTimers.empty())
   {
      auto tpNow = millis();
      std::multimap<unsigned long, TimerData>::iterator itTimData;
      while (!m_mapTimers.empty())
      {
         itTimData = m_mapTimers.begin();

         if (tpNow >= itTimData->first)
         {
            // Enqueue Timer event
            EvtTimer *evtTim = new EvtTimer(this, itTimData->second.m_pSrcTsk, itTimData->second.m_uiTimId, itTimData->second.m_iUsrCode);
            itTimData->second.m_pSrcTsk->Enqueue(evtTim);

            if (itTimData->second.m_bPeriodic)
            {
               AddPeriodicTimerAgain(itTimData->second);
            }
            m_mapTimers.erase(itTimData);
         }
         else // no more expired timers
         {
            break;
         }
      }
   }
}

void TskTimer::StartTimer(TaskBase *pSrcTask, uint32_t uiTimId, uint64_t uiToMs, int32_t iUsrCode, bool bPeriodic)
{
   auto tpThen = millis();
   tpThen += uiToMs;
   m_mapTimers.emplace(std::piecewise_construct, std::make_tuple(tpThen), std::make_tuple(pSrcTask, uiToMs, uiTimId, iUsrCode, bPeriodic, tpThen));
}

void TskTimer::AddPeriodicTimerAgain(TimerData timerData)
{
   TickType_t tpThen = timerData.tpTim;
   tpThen += timerData.m_uiToMs;
   timerData.tpTim = tpThen;
   m_mapTimers.emplace(tpThen, timerData);
}

void TskTimer::StopTimer(TaskBase *pSrcTask, uint32_t uiTimId, int32_t iUsrCode)
{
   auto it = m_mapTimers.begin();
   while (it != m_mapTimers.end())
   {
      if (pSrcTask == it->second.m_pSrcTsk &&
          uiTimId == it->second.m_uiTimId &&
          (iUsrCode == 0 ||
           iUsrCode == it->second.m_iUsrCode))
      {
         it = m_mapTimers.erase(it);
      }
      else
      {
         ++it;
      }
   }
}

void TskTimer::StopAllTimers(TaskBase *pSrcTask)
{
   auto it = m_mapTimers.begin();
   while (it != m_mapTimers.end())
   {
      if (pSrcTask == it->second.m_pSrcTsk)
      {
         it = m_mapTimers.erase(it);
      }
      else
      {
         ++it;
      }
   }
}
