#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "Enums.h"
/*

****ARQUIVO CRIADO PARA FUNÇÕES E STRUCTS RELACIONADOS AS TAREFAS****




****A STRUCT "TASK" POSSUI OS CAMPOS:****

taskId                              ID

color                               COR DA BARRA ENQUANTO ESTÁ ATIVA

startTime                           QUANDO ELA SERÁ ADICIONADA A FILA

lifeTime                            TEMPO DE VIDA TOTAL

waitTime                            TEMPO EM QUE A TAREFA ESTÁ EM ESPERA

execTime                            TEMPO EM QUE A TAREFA ESTÁ EM EXECUÇÃO, SEMPRE SERÁ MENOR OU IGUAL A DURAÇÃO.

taskDuration                        TEMPO DE DURAÇÃO DA TAREFA, SEMPRE SERÁ FIXO.

staticPriority                      PRIORIDADE ESTÁTICA

dynamicPriority                     CASO HAJA NECESSIDADE DE UTILIZAR UM ESCALONADOR COM PRIORIDADE DINAMICA

listaOps                            CASO A TAREFA POSSUA NECESSIDADE DE UTILIZAR UM MUTEX E/OU UMA OPERAÇÃO DE ENTRADA E SAIDA ESTÁ LISTA SERÁ CRIADA.

isCurrentlyLockingResource          VALOR BOOLEANO, VERDADEIRO SE A TAREFA ESTÁ BLOQUEANDO ALGUM RECURSO OU UTILIZANDO MUTEX.

****A STRUCT "OPERATION" POSSUI OS CAMPOS:****

OperationType                       UM ENUM QUE RELACIONA OS TIPOS DEFAULT, MUTEX_LOCK, MUTEX_UNLOCK E IO
                                    COM INTEIROS DE 0-3, FEITO PARA FACILITAR A LEITURA DE ARQUIVOS.

startOp                             UM VALOR INTEIRO RELATIVO AO TEMPO DE EXECUÇÃO DA TAREFA
                                    startOp DIZ QUANDO A OPERAÇÃO VAI COMEÇAR OU COMEÇOU A SER EXECUTADA.

opDuration                          VALOR FIXO, DIZ QUANTO TEMPO DE DURAÇÃO A OPERAÇÃO TEM.
*/

struct Operation
{
    // ##Tipo de operação
    enum OperationType;
    
    // Inicio e Duração
    uint8_t startOp;
    uint8_t opDuration;
    
};

struct Task
{
    //id da tarefa:
    char* taskId;
    
    //Cor representativa da tarefa enquanto está ativa:
    char* color;

    //Tempo em que foi adicionada a fila:
    uint8_t startTime;

    //Tempo de duração:
    
    uint8_t taskDuration;

    //Prioridades - prioridade estática nem sempre será utilizada, mas existe dentro da struct de qualquer forma.
    uint8_t staticPriority;
    uint8_t dynamicPriority;

    //Se a tarefa está bloqueando algum recurso:
    bool isCurrentlyLockingResource;
    enum OperationType ResourceInUse;

    //Lista de operações
    struct Operation* listaOps;

};