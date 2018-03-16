#ifndef PRISM_POSTED_EVENT_QUEUE_H_
#define PRISM_POSTED_EVENT_QUEUE_H_

#include "EventQueue.h"

template <typename Receiver, typename EventTp>
class PostedEventQueue : public EventQueue<Receiver, EventTp> {
public:
    virtual const bool  hasPendingEvents() const override;
    virtual void        addEvent(Receiver * receiver, EventTp * event) override;
    virtual std::pair<Receiver *, EventTp *>   getNextEvent() override;
};

// #include "../../../src/eventsystem/PostedEventQueue.cpp"

template <typename Receiver, typename EventTp>
const bool
PostedEventQueue<Receiver, EventTp>::
hasPendingEvents() const {
    return this->m_q.size();
}

template <typename Receiver, typename EventTp>
void
PostedEventQueue<Receiver, EventTp>::
addEvent(Receiver * receiver, EventTp * event) {
    std::pair<Receiver *, EventTp *> pair;
    pair = std::pair<Receiver *, EventTp *>(receiver, event);
    this->m_q.push(pair);
}

template <typename Receiver, typename EventTp>
std::pair<Receiver *, EventTp *>
PostedEventQueue<Receiver, EventTp>::
getNextEvent() {
    std::pair<Receiver *, EventTp *> epair = this->m_q.front();
    this->m_q.pop();
    return epair;
}

#endif // PRISM_POSTED_EVENT_QUEUE_H_
