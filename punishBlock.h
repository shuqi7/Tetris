#ifndef punishBlock_hpp
#define punishBlock_hpp

#include "Block.h"

class punishBlock: public Block {
    
public:
    void clockwise() override;
    void counterclockwise() override;
    punishBlock(int level, gameInterface*);
    ~punishBlock() override;

};

#endif /* punishBlock_hpp */
