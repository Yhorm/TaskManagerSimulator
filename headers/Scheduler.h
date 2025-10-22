#pragma once

#include "Enum.h"
#include "Constants.h"
#include "Task.h"

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

namespace OS
{
    class Scheduler 
    {
        private:
            std::vector<Task*> _taskBlock;
            std::vector<Task*> _newTasks;
            std::vector<Task*> _usingResource;
            std::vector<Task*> _pausedTasks;
            static Scheduler* _instance;

            Scheduler();
        public:
        //Construtora
        //Destrutora
            Scheduler* getInstance();
            ~Scheduler();
        //Criação de tarefas
            Task* CreateTask(int strt, int dur, int prio, std::string id);
        //Parser de arquivos &  Funções com relação as configurações

        //Função principal
            virtual void Schedule();
        //Funções auxiliares
           void addTaskToBlock(Task* tsk) { _taskBlock.push_back(tsk);};
           void addTaskToNew(Task* tsk) { _newTasks.push_back(tsk);};
           void addTaskToResource(Task* tsk) { _usingResource.push_back(tsk);};
           void addTaskToPaused(Task* tsk) { _pausedTasks.push_back(tsk);};
    };
}