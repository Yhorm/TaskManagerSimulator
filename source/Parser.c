#include "../headers/Parser.h"


/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\//////////////////////////////
ParseFile:
Abre o arquivo de configuração e cria a simulação a partir dele,
caso a função não encontre a cfg de usuário, utiliza-se da cfg base.

O começo da função cria o simulador com os seguintes parametros: 
 - o tipo de escalonador
 - o número de tarefas
 - o quantum

Loop principal
 - Cria as tasks com base nos seguintes parametros:
   - ID
   - Duração(Duração total)
   - Inicio(tempo relativo em que é adicionada) 
   - Prioridade estática(copiada para a dinâmica)
   - Sua lista de operações, que pode ser nula.

////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

struct simulador* ParseFile(void)
{
    struct simulador* taskSim = (struct simulador*) malloc (sizeof(taskSim));
    if(taskSim == NULL)
    {
        fprintf(stderr, "ERRO AO ALOCAR SIMULADOR");
        return NULL;
    }

    FILE* cfg = fopen(FILE_PATH_USER, "r");
    if(cfg == NULL)
    {
        fprintf(stderr, "Arquivo de usuário não encontrado, abrindo configuração default.");
        cfg = fopen(FILE_PATH_DEFAULT, "r");
        if(cfg == NULL)
        {
            fprintf(stderr, "Arquivo default não encontrado, encerrando aplicação.");
            return NULL;
        }
    }

    char string[MAX_STR_SIZE];



    //leitura do cabeçalho:
    //Pega as informações do Algoritmo de escalonamento e o Quantum.

    if(fgets(string, sizeof(string), cfg) != NULL)
    {
        char* token = strtok(string, ';');
        if(token == NULL)
        {
            fprintf(stderr, "Não foi possível tokenizar o algoritmo de escalonamento.");
            free(taskSim);
            return NULL;
        }

        // Alocação e copia dos dados para o algoritmo de escalonamento:

        taskSim->AlgoritmoEscalonamento = (char) malloc(sizeof(char) * 10);
        strncpy(token, string, SIZE_ALG_ESCALONAMENTO_MAX - 1);
        strncpy(string, taskSim->AlgoritmoEscalonamento, sizeof(string));

        //Copia dos dados para o token, já que não é um ponteiro.

        token = strtok(NULL, ';');
        if(token == NULL)
         {  
            free(taskSim->AlgoritmoEscalonamento);
            free(taskSim);
            fprintf(stderr, "Não foi possível tokenizar o quantum.");
            return NULL;
        }

        taskSim->Quantum = atoi(token);

        token = strtok(NULL, ';');
        if(token == NULL)
        {
            fprintf(stderr, "Não foi possível tokenizar a quantidade de tarefas.");
            free(taskSim->AlgoritmoEscalonamento);
            free(taskSim);
            return NULL;
        }

        taskSim->NumberOfTasks = atoi(token);
        
    }

    //Aloca a lista de tarefas de acordo com o NumberOfTasks da configuração:

    taskSim->taskList = (struct Task*) calloc(taskSim->NumberOfTasks, sizeof(struct Task));
    if(taskSim->taskList == NULL)
    {
            fprintf(stderr, "Não foi possível tokenizar o algoritmo de escalonamento.");
            free(taskSim->AlgoritmoEscalonamento);
            free(taskSim);
            return NULL;
    }

    //contador de tarefas adicionadas a lista;
    int8_t countTasksAdded = 0;

    while(fgets(string, sizeof(string), cfg))
    {
        struct Task* tarefa = (struct Task*) malloc(sizeof(struct Task));
        
        tarefa->isCurrentlyLockingResource = 0;

        uint8_t numOperation = 0;
        
        char* token = strtok(string, ';');
        if(token == NULL)
        {
            fprintf(stderr, "Não foi possível tokenizar o ID.");
            free(tarefa);
            return NULL;
        }

        //aloca e copia os dados para o id.
        tarefa->taskId = (char) malloc(sizeof(char) * ID_SIZE);
        strncpy(token, string, ID_SIZE-1);
        strncpy(string, tarefa->taskId, sizeof(string));

        //tokeniza
        token = strtok(NULL, ';');
        if(token == NULL)
        {
            fprintf(stderr, "Não foi possível tokenizar a duração.");
            free(tarefa->taskId);
            free(tarefa);
            return NULL;
        }

        //Copia da duração
        tarefa->taskDuration = atoi(token);

        token = strtok(NULL, ';');
        if(token == NULL)
        {
            fprintf(stderr, "Não foi possível tokenizar a prioridade estática.");
            free(tarefa->taskId);
            free(tarefa);
            return NULL;
        }

        tarefa->staticPriority = atoi(token);
        tarefa->dynamicPriority = tarefa->staticPriority;
        
        //Se o token for diferente de NULL, significa que temos operações de IO/Mutex/mensagens e afins para adicionar.
        token = strtok(NULL, ';');
        if(token != NULL)
        {
            
        }



        taskSim->taskList[countTasksAdded] = *tarefa;
        free(tarefa);
        countTasksAdded++;
    }

    return taskSim;
}

