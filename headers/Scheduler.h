#pragma once

#include "enum.h"
#include "constants.h"
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
            Enum::TipoEscalonador _escalonador;
            int _quantum;
            std::string _color;
            int _clockTimer;
            std::vector<Task*> _taskBlock;

            static Scheduler* _instance;

            Scheduler();
        public:
        //Construtora
        //Destrutora
            Scheduler* getInstance();
            ~Scheduler();
        //Criação de tarefas
            Task* CreateTask(int strt, int dur, int prio, std::string id);
        //Parser de arquivos
            void ParseFile();
        // Funções com relação as configurações
            void ChangeUserConfig();
            void WriteUserConfig();
            void GenerateUserConfig();

        //Função principal
            virtual void Schedule();
        //Funções auxiliares
            Enum::TipoEscalonador StringToScheduler(std::string str);
            Enum::TipoEvento StringToEvent(std::string str);
    };
}