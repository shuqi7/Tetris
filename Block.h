#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Coordinate.h"
#include "Cell.h"


class gameInterface;

class Block {
    
protected:
    std::vector<Cell *> cells;
    int level;
    bool isHeavy = false; 
    char type;
    gameInterface *theInterface;
    int direction;
    int numCells; // record the number of cells the Block still holds
    
public:
    void down();
    void left();
    void right();
    void drop();
    void initialDown(); // shift block from buffer region to the board
    void heavyDown(); // move one extra row downwards
    char getType();
    int getLevel();
    std::vector<Cell *> getCells();
    int getNumCells(); // return reference in order to change it
    void minusNumCells();
    virtual void clockwise() = 0;
    virtual void counterclockwise() = 0;
    bool moveable(std::vector<Coordinate>); // determine if next move is doable
    void move(std::vector<Coordinate>); //move blocks to targets cells
    Block(int, gameInterface *); // ctor
    virtual ~Block();
    gameInterface *getInterface();
    void updateCellObserver(); //
};

#endif
