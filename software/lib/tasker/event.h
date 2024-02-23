#ifndef _EVENT_H_
#define _EVENT_H_

#include "task_base.h"


enum eEVENT_TYPES
{
   EVT_FIRST,
   EVT_INIT = EVT_FIRST,
   EVT_UPDATE,
   EVT_TIMER,
   EVT_LAST
};

class Event
{
public:
   Event(TaskBase *pSrc, TaskBase *pDst) : m_pSrc(pSrc),
                                               m_pDst(pDst)
   {
   }
   virtual ~Event() {}

   virtual uint8_t GetType() const = 0;

   TaskBase *GetSource()
   {
      return m_pSrc;
   }

   TaskBase *GetDestination()
   {
      return m_pDst;
   }

private:
   TaskBase *m_pSrc;
   TaskBase *m_pDst;
};

class EvtTskInit : public Event
{
public:
   EvtTskInit(TaskBase *pSrc, TaskBase *pDst) : Event(pSrc, pDst)
   {
   }

   EvtTskInit() : Event(nullptr, nullptr)
   {
   }

   virtual ~EvtTskInit() {}

   virtual uint8_t GetType() const override
   {
      return EVT_INIT;
   }
};

class EvtUpdate : public Event
{
public:
   EvtUpdate(TaskBase *pSrc, TaskBase *pDst, uint8_t uiData = 0) : Event(pSrc, pDst),
                                                                   m_uiData(uiData)
   {
   }

   virtual ~EvtUpdate() {}

   virtual uint8_t GetType() const override
   {
      return EVT_UPDATE;
   }

   uint8_t GetData()
   {
      return m_uiData;
   }

private:
   uint8_t m_uiData;
};

class EvtTimer : public Event
{
public:
   EvtTimer(TaskBase *pSrc, TaskBase *pDst, uint32_t uiTimId, int32_t iUsrCode) : Event(pSrc, pDst),
                                                                                      m_uiTimId(uiTimId),
                                                                                      m_iUsrCode(iUsrCode) {}

   virtual ~EvtTimer() {}

   virtual uint8_t GetType() const override
   {
      return EVT_TIMER;
   }

   uint32_t GetTimerId() const
   {
      return m_uiTimId;
   }

   int32_t GetUserCode() const
   {
      return m_iUsrCode;
   }

private:
   uint32_t m_uiTimId{0};
   int32_t m_iUsrCode{0};
};

#endif /* _EVENT_H_ */