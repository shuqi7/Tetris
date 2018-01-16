#ifndef TextDisplay_hpp
#define TextDisplay_hpp

#include "Observer.h"
#include "Subject.h"
#include "Cell.h"
#include <vector>
#include <iostream>

class gameInterface;

class TextDisplay: public Observer{
    std::vector<std::vector<char>> theDisplay;
    const int r, c;
    
public:
    TextDisplay(int, int);
    void notify(Subject &whoNotified) override;
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
    void notifyInfo(gameInterface &whoNotified) override;
};

#endif /* TextDisplay_hpp */
