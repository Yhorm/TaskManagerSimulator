#include "../headers/Scheduler.h"



namespace OS
{
    Scheduler* Scheduler::_instance = nullptr;


    Scheduler::Scheduler()
    {
        _taskBlock.clear();
        getInstance();
    }

    Scheduler* Scheduler::getInstance()
    {
        if(_instance == nullptr)
        {
            _instance = new Scheduler();
        }

        return _instance;
    }

    Scheduler::~Scheduler() {}

    Task* Scheduler::CreateTask(int strt, int dur, int prio, std::string id)
    {
        Task* tarefa = nullptr;
        tarefa = new Task(strt, dur, prio, id);
        tarefa->setLifeTime(0);
        tarefa->setWaitTime(0);
        return tarefa; 
    }

}