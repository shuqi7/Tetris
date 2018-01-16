#ifndef ZBlock_hpp
#define ZBlock_hpp

#include "Block.h"

class ZBlock: public Block {
    public:
    void clockwise() override;
    void counterclockwise() override;
    ZBlock(int level, gameInterface*);
    ~ZBlock() override;
};


#endif /* ZBlock_hpp */
