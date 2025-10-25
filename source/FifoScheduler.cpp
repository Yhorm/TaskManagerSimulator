#include "../headers/FifoScheduler.h"


namespace OS
{
    FIFO::FIFO() :
        Scheduler()
    {
    }
    FIFO::~FIFO() 
    {
    }

    void FIFO::run(std::chrono::milliseconds tick)
    {
        checkNewTasks(tick);
        Schedule(tick);

        if(curTask != nullptr)
        {
            curTask->lowerDuration();
            if(curTask->getDuration() == 0)
            {
                addTaskToFinished(curTask);
                curTask = nullptr;
            }
        }
    }

    void FIFO::runFakeTick(int tick)
    {
        checkNewTasksFakeTick(tick);
        ScheduleFakeTick(tick);

        if(curTask != nullptr)
        {
            curTask->lowerDuration();
            if(curTask->getDuration() == 0)
            {
                addTaskToFinished(curTask);
                curTask = nullptr;
            }
        }
    }
}