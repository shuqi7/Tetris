#include "IBlock.h"
#include "gameInterface.h"

void IBlock::clockwise(){
    std::vector<Coordinate> futureCoord;
    int i = 0;
    if (this->direction == 1) {// direction 1 means the block is parallel with 1 on left
        
        for (auto aCell : this->cells){
            Coordinate coord{aCell->getCoord().r-(3-i), aCell->getCoord().c-i};
            futureCoord.emplace_back(coord);
            i++;
        }
        
    } else if (this->direction == 2) { // direction 2 means the block parallel with 1 on right
        
        for (auto aCell : this->cells){
            Coordinate coord{aCell->getCoord().r+(3-i), aCell->getCoord().c+(3-i)};
            futureCoord.emplace_back(coord);
            i++;
        }
        
    } else if (this->direction == 3) { // direction 3 means the block upright with 1 at bottom
        
        for (auto aCell : this->cells){
            Coordinate coord{aCell->getCoord().r-i, aCell->getCoord().c-(3-i)};
            futureCoord.emplace_back(coord);
            i++;
        }
        
    } else if (this->direction == 4) { // direction 4 means the block upright with 1 at left
        
        for (auto aCell : this->cells){
            Coordinate coord{aCell->getCoord().r+i, aCell->getCoord().c+i};
            futureCoord.emplace_back(coord);
            i++;
        }
    }
    if (this->moveable(futureCoord)) {
        this->move(futureCoord);
        if (this->direction == 4) {
            this->direction = 1;
        } else {
            this->direction++;
        }
    }
    // check heavy block;
    if (this->isHeavy){
        this->heavyDown();
    }
}

void IBlock::counterclockwise(){
    std::vector<Coordinate> futureCoord;
    int i = 0;
    if (this->direction == 1) {// direction 1 means the block is upright with 1 at top
        
        for (auto aCell : this->cells){
            Coordinate coord{aCell->getCoord().r-i, aCell->getCoord().c-i};
            futureCoord.emplace_back(coord);
            i++;
        }
        
    } else if (this->direction == 2) { // direction 2 means the block parallel with 1 on right
        
        for (auto aCell : this->cells){
            Coordinate coord{aCell->getCoord().r+(3-i), aCell->getCoord().c+i};
            futureCoord.emplace_back(coord);
            i++;
        }
        
    } else if (this->direction == 3) { // direction 3 means the block upright with 1 at bottom
        
        for (auto aCell : this->cells){
            Coordinate coord{aCell->getCoord().r-(3-i), aCell->getCoord().c-(3-i)};
            futureCoord.emplace_back(coord);
            i++;
        }
        
    } else if (this->direction == 4) { // direction 4 means the block upright with 1 at left
        
        for (auto aCell : this->cells){
            Coordinate coord{aCell->getCoord().r+i, aCell->getCoord().c+(3-i)};
            futureCoord.emplace_back(coord);
            i++;
        }
        
    }
    if (this->moveable(futureCoord)) {
        this->move(futureCoord);
        if (this->direction == 1) {
            this->direction = 4;
        } else {
            this->direction--;
        }
    }
    // check heavy block;
    if (this->isHeavy){
        this->heavyDown();
    }
}

IBlock::IBlock(int level, gameInterface *theInterface):Block(level, theInterface){
    type = 'I';
    for (int i = 0; i <=3; i++){
        Coordinate coord{0,i};
        Cell * cellPtr = theInterface->getCell(coord);
        cellPtr->set(this);
        cells.emplace_back(cellPtr);
    }
}

IBlock::~IBlock(){
    theInterface->addScore((this->level+1)*(this->level+1));
};
