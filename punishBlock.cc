#include "punishBlock.h"
#include "gameInterface.h"

void punishBlock::clockwise(){}

void punishBlock::counterclockwise(){}

punishBlock::punishBlock(int level, gameInterface* theInterface):Block{level,theInterface}{
    type = 'P';
    Coordinate coord{3,5};
    Cell * cellPtr = theInterface->getCell(coord);
    cellPtr->set(this);
    cells.emplace_back(cellPtr);
}

punishBlock::~punishBlock(){}
