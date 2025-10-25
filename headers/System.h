#pragma once

#include "Constants.h"
#include "Enum.h"

#include "Clock.h"
#include "Scheduler.h"
#include "FifoScheduler.h"
#include "PrioPreemp.h"
#include "SRTFScheduler.h"


namespace OS
{

    class System
    {
        private:
            OS::Scheduler* _sched;
            Clock _tick;
            
            int fakeTick; 
            int _quantum;



        public:
            System();
            ~System();

            //Leitura de arquivos e funções auxiliares
            void ParseFile();
            void ChangeUserConfig();
            void WriteUserConfig();
            void GenerateUserConfig();

            //Função principal
            void tick();

            //Auxiliares de conversão
            Enum::TipoEscalonador StringToScheduler(std::string str);
            Enum::TipoEvento StringToEvent(std::string str);
            //Auxiliares de criação
            Scheduler* createScheduler(Enum::TipoEscalonador sched);

    };
}