#ifndef hintBlock_hpp
#define hintBlock_hpp

#include "Block.h"

class hintBlock: public Block{
    
public:
    void clockwise() override;
    void counterclockwise() override;
    hintBlock(int level, gameInterface*);
    ~hintBlock() override;

};



#endif /* hintBlock_hpp */
