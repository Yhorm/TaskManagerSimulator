#pragma once

#include "Scheduler.h"


namespace OS
{
    class FIFO : public Scheduler
    {
        protected:  

        public:
            FIFO();
            ~FIFO();

            void run(std::chrono::milliseconds tick);
            void runFakeTick(int tick);
    };
}