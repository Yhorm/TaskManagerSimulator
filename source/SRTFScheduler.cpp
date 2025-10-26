#include "../headers/SRTFScheduler.h"

namespace OS
{
    
    SRTF::SRTF() :
        Scheduler()
    {}
    SRTF::~SRTF() {}

    int SRTF::getBestTask()
    {
        
        int lowestDurationIndex = 0;
        Task* lowestDurationTask = taskBlock[0];
        if(taskBlock.empty())
        {
            return -1;
        }

        for( size_t i = 1; i < taskBlock.size(); i++)
        {
            if(lowestDurationTask->getDuration() > taskBlock[i]->getDuration())
            {
                lowestDurationTask = taskBlock[i];
                lowestDurationIndex = i;
            }
        }

        return lowestDurationIndex;
    }

    void SRTF::Schedule(std::chrono::milliseconds tick)
    {
        int index = getBestTask();
        if(index == -1)
        {
            return;
        }

        Task* lowestDurationTask = taskBlock[index];

        if(curTask == nullptr && !taskBlock.empty())
        {
            curTask = lowestDurationTask;
            taskBlock.erase(taskBlock.begin());
        }
        else if(lowestDurationTask->getDuration() < curTask->getDuration())
        {
            curTask->ChangeState(Enum::TaskState::PausedExecution);
            taskBlock.push_back(curTask);
            curTask = lowestDurationTask;
            curTask->ChangeState(Enum::TaskState::Executing);
            taskBlock.erase(taskBlock.begin() + index);
        }
    }

    void SRTF::ScheduleFakeTick(int tick)
    {
        int index = getBestTask();
        if(index == -1)
        {
            return;
        }

        Task* lowestDurationTask = taskBlock[index];

        if(curTask == nullptr && !taskBlock.empty())
        {
            curTask = lowestDurationTask;
            taskBlock.erase(taskBlock.begin());
        }
        else if(lowestDurationTask->getDuration() < curTask->getDuration())
        {
            curTask->ChangeState(Enum::TaskState::PausedExecution);
            taskBlock.push_back(curTask);
            curTask = lowestDurationTask;
            curTask->ChangeState(Enum::TaskState::Executing);
            taskBlock.erase(taskBlock.begin() + index);
        }
    }

    void SRTF::run(std::chrono::milliseconds tick)
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

     void SRTF::runFakeTick(int tick)
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