#ifndef OBlock_hpp
#define OBlock_hpp

#include "Block.h"

class OBlock: public Block {
    public:
    void clockwise() override;
    void counterclockwise() override;
    OBlock(int, gameInterface *);
    ~OBlock() override;
};

#endif /* OBlock_hpp */
