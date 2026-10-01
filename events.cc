#include "events.hh"

Event::~Event(){

}


ExplosionEvent::~ExplosionEvent(){

}

Enemy::Enemy(const char *name, float x, float y){
    _name = name; 
    _x = x;
    _y = y;        
}

void Enemy::handle_event(Event *event)  { 
    
    if(static_cast<ExplosionEvent*>(event) != nullptr) {
    
        ExplosionEvent* explosion = static_cast<ExplosionEvent*>(event); 
        float dist = sqrt((_x - explosion->x)*(_x - explosion->x) + (_y - explosion->y)*(_y - explosion->y));
    
        if(dist < explosion->radius){
            printf("I'm dead %s!\n", _name);
        }
    }
}

void EventManager::addSubscriber(IEventHandler* subscriber){
    subscribers.push_back(subscriber) ;
}

void EventManager::randomEvent(Event* event) {
    for(auto subscriber : subscribers){
        subscriber->handle_event(event);
    }    
}
