#include "../headers/System.h"


namespace OS
{
    System::System() :
        _tick(),
        _quantum(),
        _sched(nullptr),
        fakeTick(0)
    {
        ParseFile();
    }

    System::~System()
    {

    }


    Enum::TipoEscalonador System::StringToScheduler(std::string str)
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
    Enum::TipoEvento System::StringToEvent(std::string str)
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

    void System::ParseFile()
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
        Enum::TipoEscalonador schedType = StringToScheduler(stringCfg);
        this->_sched = createScheduler(schedType);

        //Quantum
        std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS);
        this->_quantum = std::stoi(stringCfg);

        //Timer
        if(std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS))
        {
            _tick.setTickRate(std::stoll(stringCfg));
        }
        else
        {
            _tick.setTickRate(Constants::DEFAULT_TICK_RATE);
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
            if(std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS))
            {
                start = std::stoi(stringCfg);
            }
            else
            {
                start = 0;
            }
            
            std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS);
            dur = std::stoi(stringCfg);

            //pega a prioridade
            std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS);
            priority = std::stoi(stringCfg);
            
            //Loop para pegar os eventos:
            std::string stringEvent;
            Task* tarefa = _sched->CreateTask(start, dur, priority, taskId);
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
                            duration = Constants::DEFAULT_DURATION;
                        }
                    }
                    else
                    {
                        start = 0;
                    }
                }
                tarefa->createEvent(start, duration, ev);
            }

           _sched->addTaskToNew(tarefa);
        }

        arquivoCfg.close();
    }

    Scheduler* System::createScheduler(Enum::TipoEscalonador sched)
    {
        Scheduler* newSched = nullptr;
        PRIOP* priopSched = nullptr;
        SRTF* SRTFsched = nullptr;
        FIFO* FIFOsched = nullptr;

        switch(sched)
        {
            case(Enum::TipoEscalonador::PRIOp):
            {
                priopSched = new PRIOP();
                newSched = dynamic_cast<Scheduler*>(priopSched);
            }
            case(Enum::TipoEscalonador::SRTF):
            {
                SRTFsched = new SRTF();
                newSched = dynamic_cast<Scheduler*>(SRTFsched);
            }
            case(Enum::TipoEscalonador::FIFO):
            {
                FIFOsched = new FIFO();
                newSched = dynamic_cast<Scheduler*>(FIFOsched);
            }
            default:
            {
                FIFOsched = new FIFO();
                newSched = dynamic_cast<Scheduler*>(FIFOsched);
            }
        }
        return newSched;
    }
}