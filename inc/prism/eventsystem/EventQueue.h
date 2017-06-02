#ifndef PRISM_EVENT_QUEUE_H_
#define PRISM_EVENT_QUEUE_H_

#include <utility>
#include <queue>

template <typename Receiver, typename EventTp>
class EventQueue {
public:
    using EventPair = std::pair<Receiver *, EventTp *>;
protected:
    std::queue<std::pair<Receiver *, EventTp *>> m_q;
public:
    virtual             ~EventQueue() {}
    virtual const bool  hasPendingEvents() const = 0;
    virtual void        addEvent(Receiver * receiver, EventTp * event) = 0;
    virtual std::pair<Receiver *, EventTp *>   getNextEvent() = 0;
    virtual const int size() const { return m_q.size(); }
};

#endif // PRISM_EVENT_QUEUE_H_
