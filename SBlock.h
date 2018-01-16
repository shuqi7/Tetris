#ifndef SBlock_hpp
#define SBlock_hpp

#include "Block.h"

class SBlock: public Block {
    public:
    void clockwise() override;
    void counterclockwise() override;
    SBlock(int level, gameInterface*);
    ~SBlock() override;
};

#endif /* SBlock_hpp */
