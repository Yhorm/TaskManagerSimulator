#include "../headers/Scheduler.h"



namespace OS
{
    Scheduler* Scheduler::_instance = nullptr;


    Scheduler::Scheduler() :
        _escalonador(Enum::TipoEscalonador::NONE),
        _quantum(0),
        _color("Green"),
        _clockTimer(0)
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


    Enum::TipoEscalonador Scheduler::StringToScheduler(std::string str)
    {
        if(str.compare("RR"))
        {
            return Enum::TipoEscalonador::RR;
        }
        else if(str.compare("SRTF"))
        {
            return Enum::TipoEscalonador::SRTF;
        }
        else if(str.compare("PRIOd"))
        {
            return Enum::TipoEscalonador::PRIOd;
        }
        else if(str.compare("PRIOp"))
        {
            return Enum::TipoEscalonador::PRIOp;
        }
        else
        {
            return Enum::TipoEscalonador::PRIOc;
        }
    }
    Enum::TipoEvento Scheduler::StringToEvent(std::string str)
    {
        if(str.compare("MU") || str.compare("MutexUnlock"))
        {
            return Enum::TipoEvento::MutexUnlock;
        }
        else if(str.compare("ML") || str.compare("MutexLock"))
        {
            return Enum::TipoEvento::MutexLock;
        }
        else if(str.compare("MsgSend"))
        {
            return Enum::TipoEvento::MsgSend;
        }
        else if(str.compare("MsgReceive"))
        {
            return Enum::TipoEvento::MsgReceive;
        }
        else
        {
            return Enum::TipoEvento::IO;
        }

        /*
        IO = 1,
        MutexUnlock = 2,
        MutexLock = 3,
        MsgSend = 4,
        MsgReceive = 5
        */
    }



    void Scheduler::ParseFile()
    {
        std::ifstream arquivoCfg(Constants::FILE_PATH_CFG);
        if(arquivoCfg.is_open() == false)
        {
            std::cerr << "Erro ao abrir configuração do usuário, abrindo configuração default. \n";
            
        }
        //Começa a ler as strings
        std::string stringCfg;
        if(!std::getline(arquivoCfg, stringCfg))
        {
            std::cerr << "Erro getline, fechando aplicação \n";
            exit(1);
        }

        //utiliza-se do stringstream pra tokenizar.
        /*
            constantes:: separador_strings = ;
                         delimitador de operação = :
                         delimitador de tempo = -
        
        */
        std::stringstream tokens(stringCfg);

        //Escalonador
        std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS);
        this->_escalonador = StringToScheduler(stringCfg);
        
        //Quantum
        std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS);
        this->_quantum = std::stoi(stringCfg);

        //Timer
        if(std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS))
        {
            this->_clockTimer = std::stoi(stringCfg);
        }
        else
        {
            this->_clockTimer = 100;
        }

        //Nova linha

        while(std::getline(arquivoCfg, stringCfg))
        {
            if(stringCfg.empty())
            {
                continue;
            }

            std::stringstream tokens(stringCfg);
            std::string taskId;
            int priority;
            int dur;
            int start;
            //pega o ID
            std::getline(tokens, taskId, Constants::SEPARADOR_STRINGS);
            //pega o tempo de inicio e de duração:
            std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS);
            start = std::stoi(stringCfg);
            
            std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS);
            dur = std::stoi(stringCfg);

            //pega a prioridade
            std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS);
            priority = std::stoi(stringCfg);
            
            //Loop para pegar os eventos:
            std::string stringEvent;
            Task* tarefa = CreateTask(start, dur, priority, taskId);
            while(std::getline(tokens, stringEvent, Constants::SEPARADOR_STRINGS))
            {
                std::stringstream eventTokens(stringEvent);
                Enum::TipoEvento ev = StringToEvent(stringEvent);
                int start = 0;
                int duration = 0;

                if (std::getline(eventTokens, stringEvent, Constants::DELIMITADOR_OPERATION))
                {
                    ev = StringToEvent(stringEvent);

                    if (std::getline(eventTokens, stringEvent, Constants::DELIMITADOR_TEMPO))
                    {
                        start= std::stoi(stringEvent);
                    
                        if (std::getline(eventTokens, stringEvent))
                        {
                            duration = std::stoi(stringEvent);
                        }
                        else
                        {
                            duration = start;
                            start = 0;
                        }
                    }
                }
                tarefa->createEvent(start, duration, ev);
            }

            _taskBlock.push_back(tarefa);
        }

        arquivoCfg.close();
    }

}