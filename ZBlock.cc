#include "ZBlock.h"
#include "gameInterface.h"

void ZBlock::clockwise(){
    if (this->level == 5) {
        return;
    }
    std::vector<Coordinate> futureCoord;
    int i = 0;
    if (this->direction == 1) {// direction 1 means the block is parallel with 1 at top left
        for (auto aCell : this->cells){
            if (i == 0 || i == 1){ // 1st, 2nd cells
                Coordinate coord{aCell->getCoord().r-(1-i), aCell->getCoord().c+(1-i)};
                futureCoord.emplace_back(coord);
            } else { // 3rd, 4th cells
                Coordinate coord{aCell->getCoord().r-(3-i), aCell->getCoord().c-(i-1)};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 2) { // direction 2 means the block upright with 1 on right top
        for (auto aCell : this->cells){
            if (i == 0 || i == 1){ // 1st, 2nd cells
                Coordinate coord{aCell->getCoord().r+(2-i), aCell->getCoord().c+(1-i)};
                futureCoord.emplace_back(coord);
            } else { // 3rd, 4th cell
                Coordinate coord{aCell->getCoord().r-(i-2), aCell->getCoord().c+(3-i)};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 3) { // direction 3 means the block parallel with 1 at bottom right
        for (auto aCell : this->cells){
            if (i == 0 || i == 1){ // 1st, 2nd cells
                Coordinate coord{aCell->getCoord().r-i, aCell->getCoord().c-(2-i)};
                futureCoord.emplace_back(coord);
            } else { //3rd, 4th cell
                Coordinate coord{aCell->getCoord().r-(i-2), aCell->getCoord().c+(i-2)};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 4) { // direction 4 means the block upright with 1 at bottom left
        for (auto aCell : this->cells){
            if (i == 0 || i == 1){ // 1st, 2nd cells
                Coordinate coord{aCell->getCoord().r-(1-i), aCell->getCoord().c+i};
                futureCoord.emplace_back(coord);
            } else { //3rd, 4th cell
                Coordinate coord{aCell->getCoord().r+(i-1), aCell->getCoord().c+(i-2)};
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


void ZBlock::counterclockwise(){
    if (this->level == 5) {
        return;
    }
    std::vector<Coordinate> futureCoord;
    int i = 0;
    if (this->direction == 1) {// direction 1 means the block is parallel with 1 at top left
        for (auto aCell : this->cells){
            if (i == 0 || i == 1){ // 1st, 2nd cells
                Coordinate coord{aCell->getCoord().r+(1-i), aCell->getCoord().c-i};
                futureCoord.emplace_back(coord);
            } else { //3rd, 4th cell
                Coordinate coord{aCell->getCoord().r-(i-1), aCell->getCoord().c-(i-2)};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 2) { // direction 2 means the block upright with 1 on right top
        for (auto aCell : this->cells){
            if (i == 0 || i == 1){ // 1st, 2nd cells
                Coordinate coord{aCell->getCoord().r+(1-i), aCell->getCoord().c-(1-i)};
                futureCoord.emplace_back(coord);
            } else { // 3rd, 4th cells
                Coordinate coord{aCell->getCoord().r+(3-i), aCell->getCoord().c+(i-1)};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 3) { // direction 3 means the block parallel with 1 at bottom right
        for (auto aCell : this->cells){
            if (i == 0 || i == 1){ // 1st, 2nd cells
                Coordinate coord{aCell->getCoord().r-(2-i), aCell->getCoord().c-(1-i)};
                futureCoord.emplace_back(coord);
            } else { // 3rd, 4th cell
                Coordinate coord{aCell->getCoord().r+(i-2), aCell->getCoord().c-(3-i)};
                futureCoord.emplace_back(coord);
            }
            i++;
        }
        
    } else if (this->direction == 4) { // direction 4 means the block upright with 1 at bottom left
        for (auto aCell : this->cells){
            if (i == 0 || i == 1){ // 1st, 2nd cells
                Coordinate coord{aCell->getCoord().r+i, aCell->getCoord().c+(2-i)};
                futureCoord.emplace_back(coord);
            } else { //3rd, 4th cell
                Coordinate coord{aCell->getCoord().r+(i-2), aCell->getCoord().c-(i-2)};
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


ZBlock::ZBlock(int level, gameInterface* theInterface):Block(level, theInterface){
    type = 'Z';
    for (int i = 0; i <=3; i++){ // place the first three cells
        if (i <= 1) {
            Coordinate coord{0,i};
            Cell * cellPtr = theInterface->getCell(coord);
            cellPtr->set(this);
            cells.emplace_back(cellPtr);
        } else {
            Coordinate coord{1,(i-1)};
            Cell * cellPtr = theInterface->getCell(coord);
            cellPtr->set(this);
            cells.emplace_back(cellPtr);
        }
    }
}


ZBlock::~ZBlock(){
    theInterface->addScore((this->level+1)*(this->level+1));
};
