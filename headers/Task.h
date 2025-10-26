#pragma once

#include <iostream>
#include "Constants.h"
#include "Enum.h"
#include <vector>
#include <chrono>


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
                    long long startTime;
                    long long duration;
                    long long remainingDuration;
                    
                public:
                    Event(long long strt, long long dur, Enum::TipoEvento t)
                    {
                        eventType = t;
                        active = false;
                        startTime = strt;
                        remainingDuration = duration = dur;
                    }
                    ~Event();

                    Enum::TipoEvento getOpType() {return eventType;};
                    long long getStart() {return startTime;};
                    long long getDuration() {return duration;};
                    long long getRemainingDuration() { return remainingDuration; };
                    void decreaseDuration() { remainingDuration--; };
                    void start() {active = true;};
                    void end() {active = false;}; 
            };
            
            std::vector<Event*> eventList;
            std::vector<Event*> finishedEvents;
            Enum::TaskState curState;
            
            bool eventRunning;
            Event* curEvent;

            const int startingPriority;
            int dynamicPriority;
            long long duration;
            const long long startTime;
            long long lifeTime;
            long long waitTime;
            std::string id;
            

            
        public:
            Task(long long strt, long long dur, int prio, std::string i);
            ~Task();

            long long getStart() const {return startTime;};
            long long getDuration() const {return duration;};
            void lowerDuration() {duration--;}

            long long getLifeTime() {return lifeTime;};
            long long getWaitTime() {return waitTime;};

            void setLifeTime(int lftm) { lifeTime = lftm; };
            void setWaitTime(int wttm) { waitTime = wttm; }; 

            void increaseWaitTime() { waitTime++;};
            void increaseLifetTime() {lifeTime++;};

            void increasePriority() { dynamicPriority++; };
            void increasePriority(int prio) { dynamicPriority+=prio; };

            void changePriority(int prio) {dynamicPriority = prio; };

            int getPriority() {return startingPriority; };
            int getDynamicPriority() {return dynamicPriority; };

            void ChangeState(Enum::TaskState stt = Enum::TaskState::ReadyToExecute) { curState = stt;};

            void createEvent(long long strt, long long dur, Enum::TipoEvento t);
            void addEvent(Event* ev) { eventList.push_back(ev); };
            void runEvent(std::chrono::milliseconds tick);


   }; 
}