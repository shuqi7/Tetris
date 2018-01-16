#ifndef Cell_hpp
#define Cell_hpp

#include <string>
#include <iostream>
#include "Coordinate.h"
#include <memory>
#include "Observer.h"
#include "Subject.h"

class Block;

class Cell: public Subject{
    int r, c;
    Block *parentBlock;

public:
    void set(Block *);
    void unset();
    Coordinate getCoord() override;
    Block *getParent() override;
    Cell(int r, int c); // ctor
    ~Cell() override; // dtor useful when restart, observers must be notified of the change
};


#endif /* Cell_hpp */
