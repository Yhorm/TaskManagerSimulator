#pragma once

#define Round-Robin = RR


namespace Enum
{
    enum class TipoEscalonador
    {
        NONE = 0,
        RR = 1,
        SRTF = 2,
        PRIOc = 3,
        PRIOp = 4,
        PRIOd = 5
    };

    enum class TipoOperacao 
    {
        None = 0,
        IO = 1,
        MutexUnlock = 2,
        MutexLock = 3,
        MsgSend = 4,
        MsgReceive = 5
    };
    enum class TaskState
    {
        ReadyToExecute = 0,
        Executing = 1,
        PausedExecution = 2,
        Finished = 3
    };
}

