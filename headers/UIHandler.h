#pragma once
#include <string>




namespace UserInterface
{
    class UIHandler
    {
        protected:
            static UIHandler* instance;

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

    }; 
}