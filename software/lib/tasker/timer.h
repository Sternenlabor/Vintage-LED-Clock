

#ifndef _THR_TIMER_H_
#define _THR_TIMER_H_

#include <map>
#include "task_base.h"

class Event;


class TimerData
{
public:
   TimerData(TaskBase *pSrcTsk, uint64_t uiToMs, uint32_t uiTimId, int32_t iUsrCode, bool bPeriodic, unsigned long tpTim) : m_pSrcTsk(pSrcTsk),
                                                                                                                              m_uiToMs(uiToMs),
                                                                                                                              m_uiTimId(uiTimId),
                                                                                                                              m_iUsrCode(iUsrCode),
                                                                                                                              m_bPeriodic(bPeriodic),
                                                                                                                              tpTim(tpTim)
   {
   }

   TaskBase *m_pSrcTsk;
   uint64_t m_uiToMs{0};
   uint32_t m_uiTimId{0};
   int32_t m_iUsrCode{0};
   bool m_bPeriodic{false};
   unsigned long tpTim;
};

class TskTimer;

class TskTimer : public TaskBase
{
public:
   TskTimer();
   virtual ~TskTimer();

   virtual void Entry(const Event *pEvt) override;

   void StartTimer(TaskBase *pSrcSimpleTask, uint32_t uiTimId, uint64_t uiToMs, int32_t iUsrCode, bool bPeriodic);
   void StopTimer(TaskBase *pSrcSimpleTask, uint32_t uiTimId, int32_t iUsrCode);
   void StopAllTimers(TaskBase *pSrcSimpleTask);

private:
   void AddPeriodicTimerAgain(TimerData timerData);
   std::multimap<unsigned long, TimerData> m_mapTimers;
};

#endif /* _THR_TIMER_H_ */