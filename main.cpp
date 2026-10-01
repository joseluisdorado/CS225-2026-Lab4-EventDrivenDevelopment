#include "events.hh"
#include <cstdlib> 
#include <ctime> 
#include <windows.h>


int main(void){
    std::srand(std::time(nullptr));     

    Enemy enemy1("enemy1",10,20);
    Enemy enemy2("enemy2",90,80);

    EventManager eventManager;
    eventManager.addSubscriber(&enemy1);
    eventManager.addSubscriber(&enemy2);
    
    while(true){
        ExplosionEvent explosion;
        explosion.x = (std::rand() % 100) + 1; 
        explosion.y = (std::rand() % 100) + 1; 
        explosion.radius = (std::rand() % 100) + 1;  

        eventManager.randomEvent(&explosion);

        Sleep(1000);
    }
}

