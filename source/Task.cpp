#include "../headers/Task.h"


namespace OS
{
    Task::Task(long long strt, long long dur, int prio, std::string i) :
        curState(Enum::TaskState::Waiting),
        startTime(strt),
        duration(dur),
        lifeTime(0),
        waitTime(0),
        startingPriority(prio),
        dynamicPriority(prio),
        id(i)
    {
        eventRunning = false;
        eventList.clear();
        curEvent = nullptr;
    }
    Task::~Task()
    {}

    void Task::createEvent(long long strt, long long dur, Enum::TipoEvento t)
    {
        Event* ev = new Event(strt, dur, t);
        addEvent(ev);
        ev = nullptr;
    }

    void Task::runEvent(std::chrono::milliseconds tick)
    {}
}