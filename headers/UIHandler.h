#pragma once


#include <string>
#include "imgui.h"

namespace UserInterface
{
    class UIHandler
    {
        protected:
            static UIHandler* instance;
            GLFWwindow* window;

            UIHandler();
        public:
            static UIHandler* getInstance() 
            {
                if(instance == nullptr)
                {
                    instance = new UIHandler;
                }
                return instance;
            }

            ~UIHandler();
            
            void InitializeLibraries();

            void run();
            void end();
    }; 
}