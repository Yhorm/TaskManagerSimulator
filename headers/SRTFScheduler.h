#pragma once

#include "Scheduler.h"


namespace OS
{
    class SRTF : public Scheduler
    {
        protected:  

        public:
            SRTF();
            ~SRTF();
            

            void Schedule(std::chrono::milliseconds tick);
            void ScheduleFakeTick(int tick);

            void run(std::chrono::milliseconds tick);
            void runFakeTick(int tick);
            
            int getBestTask();
    };
}