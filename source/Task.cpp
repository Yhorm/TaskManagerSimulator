#include "../headers/Task.h"


namespace OS
{
    Task::Task(int strt, int dur) :
        curState(Enum::TaskState::ReadyToExecute),
        start(strt),
        duration(dur),
        lifeTime(0),
        waitTime(0)
    {
        OperationList.clear();
    }
    Task::~Task()
    {}
}