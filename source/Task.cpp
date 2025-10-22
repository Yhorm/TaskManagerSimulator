#include "../headers/Task.h"


namespace OS
{
    Task::Task(int strt, int dur, int prio, std::string i) :
        curState(Enum::TaskState::Waiting),
        startTime(strt),
        totalDuration(dur),
        currentDuration(0),
        lifeTime(0),
        waitTime(0),
        startingPriority(prio),
        dynamicPriority(prio),
        id(i)
    {
        eventList.clear();
    }
    Task::~Task()
    {}

    void Task::createEvent(int strt, int dur, Enum::TipoEvento t)
    {
        Event* ev = new Event(strt, dur, t);
        addEvent(ev);
        ev = nullptr;
    }
}