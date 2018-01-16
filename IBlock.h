#ifndef IBlock_hpp
#define IBlock_hpp

#include "Block.h"

class IBlock: public Block {
    public:
    void clockwise() override;
    void counterclockwise() override;
    IBlock(int, gameInterface *);
    ~IBlock() override;
};

#endif /* IBlock_hpp */
