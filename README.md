# Lab 4 - Events

## Overview

This lab demonstrates the implementation of a simple **event-driven system** in C++. The system allows objects (subscribers) to be notified when events occur, enabling loose coupling between event producers and consumers.

## Learning Objectives

- Implement polymorphism with virtual functions and inheritance
- Use abstract base classes (interfaces) to define contracts
- Apply the event driven development pattern for event handling

## Architecture

### Class Diagram

```
Event (Base Class)
    └── ExplosionEvent (Derived)
            - x: float
            - y: float  
            - radius: float

IEventHandler (Interface)
    └── Enemy (Concrete Handler)
            - _name: const char*
            - _x: float
            - _y: float
            + handle_event(Event* event)

EventManager
    - subscribers: vector<IEventHandler*>
    + addSubscriber(IEventHandler* subscriber)
    + randomEvent(Event* event)
```

### Key Components

#### 1. **Event** (Base Class)
- Virtual destructor enables polymorphic destruction
- Serves as the base type for all event types

#### 2. **ExplosionEvent** (Derived Event)
- Represents an explosion with coordinates (x, y) and a blast radius
- Inherits from Event to allow polymorphic handling

#### 3. **IEventHandler** (Interface)
- Pure virtual interface defining the `handle_event` contract
- Any class implementing this interface can receive events

#### 4. **Enemy** (Event Handler)
- Implements `IEventHandler` to respond to events
- Contains position data (x, y) and a name
- When handling an ExplosionEvent, calculates distance from explosion
- Prints death message if within explosion radius

#### 5. **EventManager** (Event Dispatcher)
- Maintains a list of subscribers (`IEventHandler*`)
- Provides methods to add subscribers and dispatch events
- When an event occurs, notifies all subscribers

## Implementation Details

### Event Handling Flow

1. **Event Creation**: `ExplosionEvent` is created with random coordinates and radius
2. **Event Dispatch**: `EventManager::randomEvent()` iterates through all subscribers
3. **Event Processing**: Each subscriber's `handle_event()` method is called
4. **Type Checking**: Enemy uses `static_cast` to check if event is `ExplosionEvent`
5. **Distance Calculation**: Enemy computes Euclidean distance to explosion
6. **Condition Check**: If distance < radius, enemy is affected

### Code Highlights

**Polymorphic Event Handling:**
```cpp
// From Enemy::handle_event
if(static_cast<ExplosionEvent*>(event) != nullptr) {
    ExplosionEvent* explosion = static_cast<ExplosionEvent*>(event);
    float dist = sqrt((_x - explosion->x)*(_x - explosion->x) + 
                      (_y - explosion->y)*(_y - explosion->y));
    if(dist < explosion->radius){
        printf("I'm dead %s!\n", _name);
    }
}
```

**Event Dispatch:**
```cpp
// From EventManager::randomEvent
void EventManager::randomEvent(Event* event) {
    for(auto subscriber : subscribers){
        subscriber->handle_event(event);
    }
}
```

## Usage

The `main.cpp` demonstrates the system:

1. Creates two Enemy instances at different positions
2. Registers them with the EventManager
3. Continuously generates random explosions
4. Dispatches each explosion to all subscribers
5. Enemies print death messages when hit

### Running the Program

Compile and run the program:

```bash
# On Windows (using g++)
g++ -o events.exe events.cc main.cpp -std=c++11
./events.exe
```

The program will continuously output messages like:
```
I'm dead enemy1!
I'm dead enemy2!
```

## Design Patterns

This lab implements the **Observer/Subscriber Pattern**:
- **Subject**: `EventManager` maintains list of subscribers
- **Observer**: `IEventHandler` defines the update interface
- **Concrete Observer**: `Enemy` implements the interface
- **Event Object**: `ExplosionEvent` carries event data

## Key Concepts Demonstrated

1. **Polymorphism**: Base Event class with derived ExplosionEvent
2. **Interfaces**: Pure virtual functions in IEventHandler
3. **Dynamic Typing**: Runtime type checking with static_cast
5. **Single Responsibility**: Each class has a clear, focused purpose

## Potential Extensions

- Add more event types (e.g., DamageEvent, HealEvent)
- Implement event filtering in EventManager
- Add removal of subscribers
- Include event prioritization
- Add more sophisticated damage calculation
- Implement event queue for deferred processing

## Files

- `events.hh` - Class declarations and interfaces
- `events.cc` - Class implementations
- `main.cpp` - Demonstration program
- `events.exe` - Compiled executable (Windows)

## Course Context

This lab is part of **CS-225** and demonstrates fundamental C++ concepts including:
- Object-oriented programming
- Polymorphism
- Memory management
- Design patterns
- Event-driven programming

---

**Lab Version**: 2026
**Language**: C++11
**Platform**: Cross-platform (tested on Windows)
