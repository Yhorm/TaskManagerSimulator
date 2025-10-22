#pragma once

#include <iostream>
#include "Constants.h"
#include "Enum.h"
#include <vector>


namespace OS
{
   class Task 
   {
        protected:
            class Event
            {
                protected:
                    Enum::TipoEvento eventType;
                    bool active;
                    int startTime;
                    int duration;
                    int remainingDuration;
                    
                public:
                    Event(int strt, int dur, Enum::TipoEvento t)
                    {
                        eventType = t;
                        active = false;
                        startTime = strt;
                        remainingDuration = duration = dur;
                    }
                    ~Event();

                    Enum::TipoEvento getOpType() {return eventType;};
                    int getStart() {return startTime;};
                    int getDuration() {return duration;};
                    int getRemainingDuration() { return remainingDuration; };
                    void decreaseDuration() { remainingDuration--; };
                    void start() {active = true;};
                    void end() {active = false;}; 
            };
            
            std::vector<Event*> eventList;
            Enum::TaskState curState;
            const int startingPriority;
            int dynamicPriority;
            const int totalDuration;
            const int startTime;
            int currentDuration;
            int lifeTime;
            int waitTime;
            std::string id;

        public:
            Task(int strt, int dur, int prio = 0, std::string i);
            ~Task();

            int getStart() {return startTime;};
            int getDuration() {return totalDuration;};

            int getLifeTime() {return lifeTime;};
            int getWaitTime() {return waitTime;};

            void setLifeTime(int lftm) { lifeTime = lftm; };
            void setWaitTime(int wttm) { waitTime = wttm; }; 

            void increaseWaitTime() { waitTime++;};
            void increaseWaitTime() {lifeTime++;};

            void increasePriority() { dynamicPriority++; };
            void increasePriority(int prio) { dynamicPriority+=prio; };

            void changePriority(int prio) {dynamicPriority = prio; };

            void ChangeState(Enum::TaskState stt = Enum::TaskState::ReadyToExecute) { curState = stt;};

            void createEvent(int strt, int dur, Enum::TipoEvento t);
            void addEvent(Event* ev) { eventList.push_back(ev); };

   }; 
}
