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
    class Simulador 
    {
        private:
            Enum::TipoEscalonador _escalonador;
            int _quantum;
            std::string _color;
            int _clockTimer;
            std::vector<Task*> _taskBlock;

        public:
        //Construtora
            Simulador();
        //Destrutora
            ~Simulador();
        //Criação de tarefas
            Task* CreateTask(int strt, int dur);
        //Parser de arquivos
            void ParseFile();
        // Funções com relação as configurações
            void ChangeUserConfig();
            void WriteUserConfig();
        //Função principal
            void Run();
        //Funções auxiliares


    };
}