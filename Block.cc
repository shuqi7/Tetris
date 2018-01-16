#include "Block.h"
#include "gameInterface.h"


bool Block::moveable(std::vector<Coordinate> futureCoord){
    // check if out of board
    for (auto coord : futureCoord){
        if (coord.r > 19 || coord.r < 2 ||
            coord.c > 10 || coord.c < 0){
            return false;
        }
    }
    
    // set future cells' location
    std::vector<Cell *> futureCells;
    for (auto coord : futureCoord) {
        Cell *f = theInterface->getCell(coord);
        futureCells.emplace_back(f);
    }
    // check if cells 1, 2 ,3 ,4 are occupied
    for (auto aCell: futureCells){
        if ((aCell->getParent() != nullptr) && (aCell->getParent() != this)) {
            return false;
        }
    }
    return true;
}

void Block::move(std::vector<Coordinate> futureCoord){
    // set future cells' location
    std::vector<Cell *> futureCells;
    for (auto coord : futureCoord) {
        Cell *f = theInterface->getCell(coord);
        futureCells.emplace_back(f);
    }
    // clear current cells
    for (auto cCell : this->cells) {
        numCells++;
        cCell->unset();
    }
    // set future cells' states
    int i = 0;
    for (auto fCell : futureCells) {
        fCell->set(this);
        cells[i] = fCell;
        i++;
    }
    
}

void Block::heavyDown(){
    // future coordinates
    std::vector<Coordinate> futureCoord;
    for (auto aCell : this->cells) {
        Coordinate coords{aCell->getCoord().r+1, aCell->getCoord().c};
        futureCoord.emplace_back(coords);
    }
    
    // change cells
    if (this->moveable(futureCoord)) {
        this->move(futureCoord);
    } else {
        std::string s{"can't be moved down"};
        throw s;
    }
}


void Block::down(){
    
    // future coordinates
    std::vector<Coordinate> futureCoord;
    for (auto aCell : this->cells) {
        Coordinate coords{aCell->getCoord().r+1, aCell->getCoord().c};
        futureCoord.emplace_back(coords);
    }
    
    // change cells
    if (this->moveable(futureCoord)) {
        this->move(futureCoord);
    } else {
        std::string s{"can't be moved down"};
        throw s;
    }
    // check heavy block;
    if (this->isHeavy){
        this->heavyDown();
    }
}

void Block::left(){
    int i = 1;
    if (this->level == 5) {
        i = -1;
    }
    // future coordinates
    std::vector<Coordinate> futureCoord;
    for (auto aCell : this->cells) {
        Coordinate coords{aCell->getCoord().r, aCell->getCoord().c-i};
        futureCoord.emplace_back(coords);
    }
    
    // change cells
    if (this->moveable(futureCoord)) {
        this->move(futureCoord);
    }
    // check heavy block;
    if (this->isHeavy){
        this->heavyDown();
    }
}

void Block::right(){
    int i = 1;
    if (this->level == 5) {
        i = -1;
    }
    // future coordinates
    std::vector<Coordinate> futureCoord;
    for (auto aCell : this->cells) {
        Coordinate coords{aCell->getCoord().r, aCell->getCoord().c+i};
        futureCoord.emplace_back(coords);
    }
    
    // change cells
    if (this->moveable(futureCoord)) {
        this->move(futureCoord);
    }
    // check heavy block;
    if (this->isHeavy){
        this->heavyDown();
    }
}

void Block::drop(){
    while (true) {
        std::vector<Coordinate> futureCoord;
        for (auto aCell : this->cells) {
            Coordinate coords{aCell->getCoord().r+1, aCell->getCoord().c};
            futureCoord.emplace_back(coords);
        }
        if (this->moveable(futureCoord)) {
            this->move(futureCoord);
        } else {
            std::string s{"can't be moved down"};
            throw s;
        }
    }
}


void Block::initialDown(){
    // future coordinates
    std::vector<Coordinate> futureCoord;
    for (auto aCell : this->cells) {
        Coordinate coords{aCell->getCoord().r+5, aCell->getCoord().c};
        futureCoord.emplace_back(coords);
    }
    
    // change cells
    if (this->moveable(futureCoord)) {
        this->move(futureCoord);
    } else {
        std::string s{"can't be moved down"};
        throw s;
    }
}


char Block::getType(){
    return this->type;
}

int Block::getLevel(){
    return this->level;
}


std::vector<Cell *> Block::getCells(){
    return cells;
}


int Block::getNumCells(){
    return this->numCells;
}

void Block::minusNumCells(){
    numCells--;
}


Block::Block(int level, gameInterface *theInterface)
:level(level),theInterface(theInterface){
    
    if (level >= 3) {
        isHeavy = true;
    }
    direction = 1;
    numCells = 4;
 
}


Block::~Block(){} // dtor


gameInterface *Block::getInterface(){
    return theInterface;
}


void Block::updateCellObserver(){
    for (auto aCell : this->cells){
        aCell->notifyObservers();
    }
}
