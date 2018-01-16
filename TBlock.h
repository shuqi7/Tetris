#ifndef TBlock_hpp
#define TBlock_hpp

#include "Block.h"

class TBlock: public Block {
    public:
    void clockwise() override;
    void counterclockwise() override;
    TBlock(int level, gameInterface*);
    ~TBlock() override;
};

#endif /* TBlock_hpp */
