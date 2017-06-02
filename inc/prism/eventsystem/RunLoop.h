#ifndef PRISM_RUN_LOOP_H_
#define PRISM_RUN_LOOP_H_

template <typename Receiver, typename EventTp>
class EventQueue;

template <typename Receiver, typename EventTp>
class RunLoop {
protected:
    bool m_isRunning;
    int m_retCode;
    EventQueue<Receiver, EventTp> * m_postedEventQueue;
    EventQueue<Receiver, EventTp> * m_nativeEventQueue;
public:
                        RunLoop(EventQueue<Receiver, EventTp> * postedEventQueue, EventQueue<Receiver, EventTp> * nativeEventQueue);
    virtual             ~RunLoop() {}

    const bool          isRunning() const;
    virtual const int   run();
    void                halt(const int retCode=0);
private:
    void                processEvents();
    void                notify(Receiver * receiver, EventTp * event);
};

// #include "../src/RunLoop.cpp"

template <typename Receiver, typename EventTp>
RunLoop<Receiver, EventTp>::
RunLoop(EventQueue<Receiver, EventTp> * postedEventQueue, EventQueue<Receiver, EventTp> * nativeEventQueue)
:   m_isRunning{false},
    m_postedEventQueue{postedEventQueue},
    m_nativeEventQueue{nativeEventQueue}
{}

template <typename Receiver, typename EventTp>
const bool
RunLoop<Receiver, EventTp>::
isRunning() const {
    return m_isRunning;
}

template <typename Receiver, typename EventTp>
const int
RunLoop<Receiver, EventTp>::
run() {
    m_isRunning = true;
    processEvents();
    return m_retCode;
}

template <typename Receiver, typename EventTp>
void
RunLoop<Receiver, EventTp>::
processEvents() {
    while(isRunning() && m_postedEventQueue->hasPendingEvents()) {
        std::pair<Receiver *, EventTp *> epair = m_postedEventQueue->getNextEvent();
        notify(epair.first, epair.second);
    }
}

template <typename Receiver, typename EventTp>
void
RunLoop<Receiver, EventTp>::
halt(const int retCode) {
    m_isRunning = false;
    m_retCode = retCode;
}

template <typename Receiver, typename EventTp>
void
RunLoop<Receiver, EventTp>::
notify(Receiver * receiver, EventTp * event) {
    receiver->handleEvent(event);
}

#endif // PRISM_RUN_LOOP_H_
