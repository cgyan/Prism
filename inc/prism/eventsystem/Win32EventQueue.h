#ifndef PRISM_WIN32_EVENT_QUEUE_H_
#define PRISM_WIN32_EVENT_QUEUE_H_

#include "EventQueue.h"

template <typename Receiver, typename EventTp>
class Win32EventQueue : public EventQueue<Receiver, EventTp> {
private:
    using EventPair = std::pair<Receiver *, EventTp *>;
public:
    virtual const bool   hasPendingEvents() const override;
    virtual void         addEvent(Receiver * receiver, EventTp * event) override;
    virtual EventPair    getNextEvent() override;
    virtual void         refresh();
};

// #include "../src/Win32EventQueue.cpp"

template <typename Receiver, typename EventTp>
const bool
Win32EventQueue<Receiver, EventTp>::
hasPendingEvents() const {
    return this->m_q.size();
}

template <typename Receiver, typename EventTp>
void
Win32EventQueue<Receiver, EventTp>::
addEvent(Receiver * receiver, EventTp * event) {
    std::pair<Receiver *, EventTp *> epair;
    epair = std::pair<Receiver *, EventTp *>(receiver, event);
    this->m_q.push(epair);
}

template <typename Receiver, typename EventTp>
std::pair<Receiver *, EventTp *>
Win32EventQueue<Receiver, EventTp>::
getNextEvent() {
    std::pair<Receiver *, EventTp *> epair;
    epair = this->m_q.front();
    this->m_q.pop();
    return epair;
}

template <typename Receiver, typename EventTp>
void
Win32EventQueue<Receiver, EventTp>::
refresh() {

}


#endif // PRISM_WIN32_EVENT_QUEUE_H_
