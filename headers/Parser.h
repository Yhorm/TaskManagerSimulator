#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Enums.h"
#include "TaskStruct.h"

#define FILE_PATH_USER "../cfg/user_cfg.txt"
#define FILE_PATH_DEFAULT "../cfg/default_cfg.txt"
#define BUFLIM 255
#define MAX_STR_SIZE 70
#define SIZE_ALG_ESCALONAMENTO_MAX 10
#define ID_SIZE 4


/*

****ARQUIVO FEITO PARA FUNÇÕES QUE LIDAM COM ARQUIVOS.****
struct Simulador criada para segurar os dados lidos.

*/

struct simulador 
{
    char* AlgoritmoEscalonamento;
    uint8_t Quantum;
    struct Task* taskList;
    uint8_t NumberOfTasks;
};

struct simulador* ParseFile(void);



