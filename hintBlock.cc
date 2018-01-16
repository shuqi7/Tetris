#include "hintBlock.h"


void hintBlock::clockwise(){}

void hintBlock::counterclockwise(){}

hintBlock::hintBlock(int level, gameInterface* theInterface):Block{level,theInterface}{
    type = '?';
}

hintBlock::~hintBlock(){}
