#pragma once

#include "Enum.h"
#include "Constants.h"
#include "Task.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>


namespace OS
{
    class Scheduler 
    {
        protected:
            std::vector<Task*>  newTasks;
            std::vector<Task*>  taskBlock;
            std::vector<Task*>  usingResource;
            std::vector<Task*>  pausedTasks;
            std::vector<Task*>  finishedTasks;
            static Scheduler*   instance;

            Task*               curTask;

            Scheduler();
        public:
        //Construtora
        //Destrutora
            Scheduler*      getInstance();
            virtual         ~Scheduler();

        //Criação de tarefas
            Task*           CreateTask(int strt, int dur, int prio, std::string id);

        //Get e set da tarefa atual
            Task*           getCurTask() {return curTask; };
            void            setCurTask(Task* tsk) {curTask = tsk;};

        //Funções principais
            virtual void    Schedule(std::chrono::milliseconds tick);
            virtual void    ScheduleFakeTick(int tick);
            bool            ScheduleFinished();
            virtual void    run(std::chrono::milliseconds tick);
            virtual void    runFakeTick(int tick);
            void            checkNewTasks(std::chrono::milliseconds tick);
            void            checkNewTasksFakeTick(int tick);
            void            changeTask(Task* tsk);
        //Funções auxiliares
           void             addTaskToBlock(Task* tsk) { taskBlock.push_back(tsk); };
           void             addTaskToNew(Task* tsk) { newTasks.push_back(tsk);};
           void             addTaskToResource(Task* tsk) { usingResource.push_back(tsk);};
           void             addTaskToPaused(Task* tsk) { pausedTasks.push_back(tsk);};
           void             addTaskToFinished(Task* tsk) { finishedTasks.push_back(tsk); };
    };
}