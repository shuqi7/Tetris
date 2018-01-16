#ifndef JBlock_hpp
#define JBlock_hpp

#include "Block.h"

class JBlock: public Block {
    public:
    void clockwise() override;
    void counterclockwise() override;
    JBlock(int, gameInterface *);
    ~JBlock() override;
};

#endif /* JBlock_hpp */
