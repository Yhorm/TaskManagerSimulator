#pragma once

namespace Enum
{
    enum class TipoEscalonador
    {
        FIFO = 0,
        RR = 1,
        SRTF = 2,
        PRIOc = 3,
        PRIOp = 4,
        PRIOd = 5
    };

    enum class TipoEvento 
    {
        IO = 1,
        MutexUnlock = 2,
        MutexLock = 3,
        MsgSend = 4,
        MsgReceive = 5
    };
    enum class TaskState
    {
        Waiting = 1,
        ReadyToExecute = 2,
        Executing = 3,
        PausedExecution = 4,
        Finished = 5
    };
}

