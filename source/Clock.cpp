#include "../headers/clock.h"

namespace OS
{
    Clock::Clock() 
    {
        startTime = std::chrono::steady_clock::now();
    }

    Clock::~Clock()
    {
    }
}