#include "../headers/PrioPreemp.h"


namespace OS
{
    PRIOP::PRIOP() :
        Scheduler()
    {
    }

    PRIOP::~PRIOP() 
    {
    }

    int PRIOP::getBestTask()
    {
        if(taskBlock.empty())
        {
            return -1;
        }
        
        int highestPriorityIndex = 0;
        Task* highestPriorityTask = taskBlock[0];

        for(size_t i = 1; i < taskBlock.size(); i++)
        {
            if(taskBlock[i]->getPriority() > highestPriorityTask->getPriority())
            {
                highestPriorityTask = taskBlock[i];
                highestPriorityIndex = i;
            }
        }

        return highestPriorityIndex;
    }

    void PRIOP::Schedule(std::chrono::milliseconds tick)
    {
        int index = getBestTask();
        if(index == -1)
        {
            return;
        }

        Task* highestPriorityTask = taskBlock[index];

        if(curTask == nullptr && !taskBlock.empty())
        {
            curTask = highestPriorityTask;
            taskBlock.erase(taskBlock.begin());
        }
        else if(highestPriorityTask->getPriority() < curTask->getPriority())
        {
            taskBlock.push_back(curTask);
            curTask = highestPriorityTask;
            taskBlock.erase(taskBlock.begin() + index);
        }
    }

    void PRIOP::ScheduleFakeTick(int tick)
    {
        int index = getBestTask();
        if(index == -1)
        {
            return;
        }

        Task* highestPriorityTask = taskBlock[index];

        if(curTask == nullptr && !taskBlock.empty())
        {
            curTask = highestPriorityTask;
            taskBlock.erase(taskBlock.begin());
        }
        else if(highestPriorityTask->getPriority() < curTask->getPriority())
        {
            taskBlock.push_back(curTask);
            curTask = highestPriorityTask;
            taskBlock.erase(taskBlock.begin() + index);
        }
    }


    void PRIOP::run(std::chrono::milliseconds tick)
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

        if(ScheduleFinished())
        {
            return;
        }
    }

    void PRIOP::runFakeTick(int tick)
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

        if(ScheduleFinished())
        {
            return;
        }
    }

}