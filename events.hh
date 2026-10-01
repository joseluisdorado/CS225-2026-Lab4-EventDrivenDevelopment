#pragma once

#include <iostream>
#include <cmath>
#include <vector>

class Event
{
    public:
        virtual ~Event();
};

class ExplosionEvent : public Event
{
    public:
        float x;
        float y;
        float radius;           
        ~ExplosionEvent() override;  
};

class IEventHandler
{
    public:
        virtual void handle_event(Event *event) = 0;
};

class Enemy : public IEventHandler
{
    protected:
        const char *_name;
        float _x;
        float _y;

    public:
        Enemy(const char *name, float x, float y);
        void handle_event(Event *event) override;
};

class EventManager
{
    std::vector<IEventHandler*> subscribers;
    
    public:
        void addSubscriber(IEventHandler* subscriber);
        void randomEvent(Event* event);
};

