#include "../headers/clock.h"

namespace OS
{
    Clock* Clock::instance = nullptr;

    Clock* Clock::getInstance()
    {
        if(instance == nullptr)
        {
            instance = new Clock();
        }
        return instance;
    }

    Clock::Clock() 
    {
        startTime = std::chrono::steady_clock::now();
    }

    Clock::~Clock()
    {
    }


}