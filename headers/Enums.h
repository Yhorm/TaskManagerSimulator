#pragma once

enum OperationType
{
    
    NONE = 0,
    MUTEX_LOCK = 1,
    MUTEX_UNLOCK = 2,
    IN_OUT = 3
    
};

enum TranslateInputToOpType
{
    ML = 1,
    MU = 2, 
    IO = 3,
};