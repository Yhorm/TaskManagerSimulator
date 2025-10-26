#include "../headers/Scheduler.h"



namespace OS
{
    Scheduler* Scheduler::instance = nullptr;


    Scheduler::Scheduler()
    {
        taskBlock.clear();
        newTasks.clear();
        usingResource.clear();
        pausedTasks.clear();
        getInstance();
    }

    Scheduler* Scheduler::getInstance()
    {
        if(instance == nullptr)
        {
            instance = new Scheduler();
        }

        return instance;
    }

     void Scheduler::checkNewTasks(std::chrono::milliseconds tick)
     {
        for(auto i = newTasks.begin(); i != newTasks.end(); i++)
        {
            if(std::chrono::milliseconds((*i)->getStart()) == tick)
            {
                addTaskToBlock(*i);
                (*i)->ChangeState(Enum::TaskState::ReadyToExecute);
            }
        }
     }

     void Scheduler::checkNewTasksFakeTick(int tick)
     {
        for(auto i = newTasks.begin(); i != newTasks.end(); i++)
        {
            if((*i)->getStart() == (long long)tick)
            {
                addTaskToBlock(*i);
                (*i)->ChangeState(Enum::TaskState::ReadyToExecute);
            }
        }
     }


    Task* Scheduler::CreateTask(int strt, int dur, int prio, std::string id)
    {
        Task* tarefa = nullptr;
        tarefa = new Task(strt, dur, prio, id);
        tarefa->setLifeTime(0);
        tarefa->setWaitTime(0);
        return tarefa; 
    }
    void Scheduler::changeTask(Task* tsk)
    {
        curTask = tsk;
    }


    void Scheduler::Schedule(std::chrono::milliseconds tick)
    {
        if(curTask == nullptr && !taskBlock.empty())
        {
            curTask->ChangeState(Enum::TaskState::Executing);
            curTask = taskBlock.front();
            taskBlock.erase(taskBlock.begin());
        }
        else
            return;
    }

    void Scheduler::ScheduleFakeTick(int tick)
    {
        if(curTask == nullptr && !taskBlock.empty())
        {
            curTask->ChangeState(Enum::TaskState::Executing);
            curTask = taskBlock.front();
            taskBlock.erase(taskBlock.begin());
        }
        else
            return;
    }
}