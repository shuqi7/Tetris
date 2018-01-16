#ifndef LBlock_hpp
#define LBlock_hpp

#include "Block.h"

class LBlock: public Block {
    public:
    void clockwise() override;
    void counterclockwise() override;
    LBlock(int, gameInterface *);
    ~LBlock() override;
};

#endif /* LBlock_hpp */
