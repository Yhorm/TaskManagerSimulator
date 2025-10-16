#pragma once

#include <iostream>
#include "constants.h"
#include "enum.h"
#include <vector>


namespace OS
{
   class Task 
   {
        protected:
            class Operation
            {
                protected:
                    Enum::TipoOperacao opType;
                    const int start;
                    const int duration;
                    const int remainingDuration;

                public:
                    Operation(int strt, int dur, Enum::TipoOperacao t = Enum::TipoOperacao::None);
                    ~Operation();

                    Enum::TipoOperacao getOpType() {return opType;};
                    int getStart() {return start;};
                    int getDuration() {return duration;};
            };
            
            Enum::TaskState curState;
            const int start;
            const int duration;
            int lifeTime;
            int waitTime;
            
            std::vector<Operation*> OperationList;


        public:
            Task(int strt, int dur);
            ~Task();

            int getStart() {return start;};
            int getDuration() {return duration;};

            int getLifeTime() {return lifeTime;};
            int getWaitTime() {return waitTime;};

            void setLifeTime(int lftm) { lifeTime = lftm; };
            void setWaitTime(int wttm) { waitTime = wttm; }; 

            void increaseWaitTime() { waitTime++;};
            void increaseWaitTime() {lifeTime++;};

            void ChangeState(Enum::TaskState stt = Enum::TaskState::ReadyToExecute) { curState = stt;};

            Operation* CreateOperation(int strt, int dur, Enum::TipoOperacao t = Enum::TipoOperacao::None);

   }; 
}
