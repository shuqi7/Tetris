#include "JBlock.h"
#include "gameInterface.h"

void JBlock::clockwise(){
    if (this->level == 5) {
        return;
    }
    std::vector<Coordinate> futureCoord;
    int i = 0;
    if (this->direction == 1) {// direction 1 means the block is parallel with 1 at top left
        for (auto aCell : this->cells){
            if (i != 3){ // 1st, 2nd and 3rd cells
                Coordinate coord{aCell->getCoord().r-i, aCell->getCoord().c-(2-i)};
                futureCoord.emplace_back(coord);
            } else { // 4th cell
                Coordinate coord{aCell->getCoord().r-1, aCell->getCoord().c+1};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 2) { // direction 2 means the block upright with 1 on right top
        for (auto aCell : this->cells){
            if (i != 3){ // 1st, 2nd and 3rd cells
                Coordinate coord{aCell->getCoord().r-(1-i), aCell->getCoord().c+i};
                futureCoord.emplace_back(coord);
            } else { // 4th cell
                Coordinate coord{aCell->getCoord().r+2, aCell->getCoord().c+1};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 3) { // direction 3 means the block parallel with 1 at bottom right
        for (auto aCell : this->cells){
            if (i != 3){ // 1st, 2nd and 3rd cells
                Coordinate coord{aCell->getCoord().r-(1-i), aCell->getCoord().c+(1-i)};
                futureCoord.emplace_back(coord);
            } else { // 4th cell
                Coordinate coord{aCell->getCoord().r, aCell->getCoord().c-2};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 4) { // direction 4 means the block upright with 1 at bottom left
        for (auto aCell : this->cells){
            if (i != 3){ // 1st, 2nd and 3rd cells
                Coordinate coord{aCell->getCoord().r-(i-2), aCell->getCoord().c-(i-1)};
                futureCoord.emplace_back(coord);
            } else { // 4th cell
                Coordinate coord{aCell->getCoord().r-1, aCell->getCoord().c};
                futureCoord.emplace_back(coord);
            }
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




void JBlock::counterclockwise(){
    if (this->level == 5) {
        return;
    }
    std::vector<Coordinate> futureCoord;
    int i = 0;
    if (this->direction == 1) {// direction 1 means the block is parallel with 1 at top left
        for (auto aCell : this->cells){
            if (i != 3){ // 1st, 2nd and 3rd cells
                Coordinate coord{aCell->getCoord().r-(2-i), aCell->getCoord().c-(1-i)};
                futureCoord.emplace_back(coord);
            } else { // 4th cell
                Coordinate coord{aCell->getCoord().r+1, aCell->getCoord().c};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 2) { // direction 2 means the block upright with 1 on right top
        for (auto aCell : this->cells){
            if (i != 3){ // 1st, 2nd and 3rd cells
                Coordinate coord{aCell->getCoord().r+i, aCell->getCoord().c+(2-i)};
                futureCoord.emplace_back(coord);
            } else { // 4th cell
                Coordinate coord{aCell->getCoord().r+1, aCell->getCoord().c-1};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 3) { // direction 3 means the block parallel with 1 at bottom right
        for (auto aCell : this->cells){
            if (i != 3){ // 1st, 2nd and 3rd cells
                Coordinate coord{aCell->getCoord().r+(1-i), aCell->getCoord().c-i};
                futureCoord.emplace_back(coord);
            } else { // 4th cell
                Coordinate coord{aCell->getCoord().r-2, aCell->getCoord().c-1};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 4) { // direction 4 means the block upright with 1 at bottom left
        for (auto aCell : this->cells){
            if (i != 3){ // 1st, 2nd and 3rd cells
                Coordinate coord{aCell->getCoord().r+(1-i), aCell->getCoord().c-(1-i)};
                futureCoord.emplace_back(coord);
            } else { // 4th cell
                Coordinate coord{aCell->getCoord().r, aCell->getCoord().c+2};
                futureCoord.emplace_back(coord);
            }
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



JBlock::JBlock(int level, gameInterface *theInterface):Block(level, theInterface){
    type = 'J';
    for (int i = 0; i <=2; i++){ // place the first three cells
        Coordinate coord{1,(2-i)};
        Cell * cellPtr = theInterface->getCell(coord);
        cellPtr->set(this);
        cells.emplace_back(cellPtr);
    }
    Coordinate coord{0,0}; // place the 4th cell
    Cell * cellPtr = theInterface->getCell(coord);
    cellPtr->set(this);
    cells.emplace_back(cellPtr);
}


JBlock::~JBlock(){
    theInterface->addScore((this->level+1)*(this->level+1));
};
