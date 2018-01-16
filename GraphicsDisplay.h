#ifndef GraphicsDisplay_hpp
#define GraphicsDisplay_hpp

#include <iostream>
#include <vector>
#include "Observer.h"
#include "Subject.h"
#include "window.h"

class gameInterface;
class Cell;

class GraphicsDisplay: public Observer{
    const int r, c, winSizeRow, winSizeCol;
    gameInterface *theInterface;
    Xwindow xw1{330,760}; // for Grid Display
public:
    GraphicsDisplay(const int,const int,const int, const int, gameInterface *);
    
    void notify(Subject &whoNotified) override;
    void notifyInfo(gameInterface &whoNotified) override;
};

#endif /* GraphicsDisplay_hpp */
