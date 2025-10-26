#pragma once

#include <iostream>
#include <string>
#include "../libraries/imgui/imgui.h"
#include "../headers/Scheduler.h"


struct GLFWwindow;


namespace UserInterface
{
    class UIHandler
    {
        protected:
            static UIHandler* instance;
            GLFWwindow* window;
            
            OS::Scheduler* pSched;
            
            bool active;
            bool showTasks;
            UIHandler();
        public:
            static UIHandler* getInstance();

            ~UIHandler();
            void setSched(OS::Scheduler* pS) {pSched = pS;};
            void InitializeLibraries();
            void ganttChart(OS::Task* tsk);


            void run();
            void end();
    }; 
}