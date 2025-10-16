#include "../headers/Simulador.h"



namespace OS
{
    Simulador::Simulador() :
        _escalonador(Enum::TipoEscalonador::NONE),
        _quantum(0),
        _color("Green"),
        _clockTimer(0)
    {
        _taskBlock.clear();
    }

    Simulador::~Simulador() {}

    Task* Simulador::CreateTask(int strt, int dur)
    {
        Task* tarefa = nullptr;
        tarefa = new Task(strt, dur);
        tarefa->setLifeTime(0);
        tarefa->setWaitTime(0);
        return tarefa; 
    }

    void Simulador::ParseFile()
    {
        std::ifstream arquivoCfg(Constants::FILE_PATH_CFG);
        if(arquivoCfg.is_open() == false)
        {
            std::cerr << "Erro ao abrir configuração do usuário, abrindo configuração default. \n";
            arquivoCfg.open(Constants::FILE_PATH_CFG);
            if(arquivoCfg.is_open() == false)
            {
                std::cerr << "Erro ao abrir ambas as configurações, encerrando o problema.\n";
                exit(1);
            }
        }
         
        std::string stringCfg;
        if(!std::getline(arquivoCfg, stringCfg))
        {
            std::cerr << "Erro getline, fechando aplicação \n";
            exit(1);
        }

        std::stringstream tokens(stringCfg);

        std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS);
        if(stringCfg.compare("RR"))
        {
            this->_escalonador = Enum::TipoEscalonador::RR;
        }
        else if(stringCfg.compare("SRTF"))
        {
            this->_escalonador = Enum::TipoEscalonador::SRTF;
        }
        else if(stringCfg.compare("PRIOc"))
        {
            this->_escalonador = Enum::TipoEscalonador::PRIOc;
        }
        else if(stringCfg.compare("PRIOp"))
        {
            this->_escalonador = Enum::TipoEscalonador::PRIOp;
        }
        else
        {
            this->_escalonador = Enum::TipoEscalonador::PRIOd;
        }
        

        std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS);
        this->_quantum = std::stoi(stringCfg);

        std::getline(tokens, stringCfg, Constants::SEPARADOR_STRINGS);
        this->_clockTimer = std::stoi(stringCfg);


        arquivoCfg.close();
    }
    
    void Simulador::Run()
    {
        ParseFile();

    }

}