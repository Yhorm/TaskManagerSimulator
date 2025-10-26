#pragma once

#include <chrono>

namespace OS
{
    class Clock 
    {
        protected:
            std::chrono::milliseconds tickRate;

            std::chrono::steady_clock::time_point startTime;

            static Clock* instance;
            Clock();
        public:
            ~Clock();

            static Clock* getInstance();

            void resetTimer()
            {
                startTime = std::chrono::steady_clock::now();
            }
            
            void setTickRate(long long tRate) { tickRate = std::chrono::milliseconds(tRate); };

            long long getCurTick()
            {
                auto curTick = (std::chrono::steady_clock::now() - startTime)/tickRate;
                return curTick;
            }

            std::chrono::milliseconds getElapsedTime() const
            {
                auto curTime = std::chrono::steady_clock::now();
                return std::chrono::duration_cast<std::chrono::milliseconds>(curTime-startTime);
            }

    };
}