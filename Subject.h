#ifndef Subject_hpp
#define Subject_hpp

#include <vector>
#include "Coordinate.h"

class Block;
class Observer;

class Subject {
    std::vector<Observer *>theObservers;
public:
    void attach(Observer *o);
    void notifyObservers();
    virtual Coordinate getCoord() = 0;
    virtual Block *getParent() = 0;
    virtual ~Subject();
};

#endif /* Subject_hpp */
