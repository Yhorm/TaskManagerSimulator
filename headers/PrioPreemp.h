#pragma once

#include "Scheduler.h"


namespace OS
{
    class PRIOP : public Scheduler
    {
        protected:  

        public:
            PRIOP();
            ~PRIOP();

            void run(std::chrono::milliseconds tick);
            void runFakeTick(int tick);
            
            int getBestTask();

            void Schedule(std::chrono::milliseconds tick);
            void ScheduleFakeTick(int tick);
    };

    

}