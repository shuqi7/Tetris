#include "GraphicsDisplay.h"
#include "Block.h"
#include <string>
#include "gameInterface.h"

GraphicsDisplay::GraphicsDisplay(const int r,const int c,const int winSizeRow, const int winSizeCol, gameInterface *i):
r{r},c{c},winSizeRow(winSizeRow),winSizeCol(winSizeCol),theInterface(i){
    xw1.fillRectangle(0, 0, winSizeRow, winSizeCol, Xwindow::White);
    xw1.drawString(100, 25, "Welcome to Quadris!", Xwindow::Brown);
    xw1.fillRectangle(0, 210, 330, 10); // a black line
}

void GraphicsDisplay::notify(Subject&whoNotified){

    
    Coordinate coord = whoNotified.getCoord();
    
    char type;
    if (whoNotified.getParent() == nullptr){
        type = ' ';
    } else {
        type = whoNotified.getParent()->getType();
    }
    
    int cellSize = 30;
    
    if (coord.r == 0 || coord.r == 1){ // Next Block
        switch(type) {
            case 'I':
                xw1.fillRectangle(coord.c * cellSize+50, coord.r * cellSize+140, cellSize, cellSize, Xwindow::Red);
                break;
            case 'L':
                xw1.fillRectangle(coord.c * cellSize+50, coord.r * cellSize+140, cellSize, cellSize, Xwindow::Blue);
                break;
            case 'J':
                xw1.fillRectangle(coord.c * cellSize+50, coord.r * cellSize+140, cellSize, cellSize, Xwindow::Green);
                break;
            case 'O':
                xw1.fillRectangle(coord.c * cellSize+50, coord.r * cellSize+140, cellSize, cellSize, Xwindow::Yellow);
                break;
            case 'Z':
                xw1.fillRectangle(coord.c * cellSize+50, coord.r * cellSize+140, cellSize, cellSize, Xwindow::Magenta);
                break;
            case 'S':
                xw1.fillRectangle(coord.c * cellSize+50, coord.r * cellSize+140, cellSize, cellSize, Xwindow::Orange);
                break;
            case 'T':
                xw1.fillRectangle(coord.c * cellSize+50, coord.r * cellSize+140, cellSize, cellSize, Xwindow::Cyan);
                break;
            case 'P':
                xw1.fillRectangle(coord.c * cellSize+50, coord.r * cellSize+140, cellSize, cellSize, Xwindow::Brown);
                break;
            default:
                xw1.fillRectangle(coord.c * cellSize+50, coord.r * cellSize+140, cellSize, cellSize, Xwindow::White);
        }
    } else{
        coord.r -= 2;
        switch(type) {
            case 'I':
                xw1.fillRectangle(coord.c * cellSize, coord.r * cellSize+220, cellSize, cellSize, Xwindow::Red);
                break;
            case 'L':
                xw1.fillRectangle(coord.c * cellSize, coord.r * cellSize+220, cellSize, cellSize, Xwindow::Blue);
                break;
            case 'J':
                xw1.fillRectangle(coord.c * cellSize, coord.r * cellSize+220, cellSize, cellSize, Xwindow::Green);
                break;
            case 'O':
                xw1.fillRectangle(coord.c * cellSize, coord.r * cellSize+220, cellSize, cellSize, Xwindow::Yellow);
                break;
            case 'Z':
                xw1.fillRectangle(coord.c * cellSize, coord.r * cellSize+220, cellSize, cellSize, Xwindow::Magenta);
                break;
            case 'S':
                xw1.fillRectangle(coord.c * cellSize, coord.r * cellSize+220, cellSize, cellSize, Xwindow::Orange);
                break;
            case 'T':
                xw1.fillRectangle(coord.c * cellSize, coord.r * cellSize+220, cellSize, cellSize, Xwindow::Cyan);
                break;
            case 'P':
                xw1.fillRectangle(coord.c * cellSize, coord.r * cellSize+220, cellSize, cellSize, Xwindow::Brown);
                break;
            case '?':
                xw1.fillRectangle(coord.c * cellSize, coord.r * cellSize+220, cellSize, cellSize, Xwindow::Black);
                break;
            default:
                xw1.fillRectangle(coord.c * cellSize, coord.r * cellSize+220, cellSize, cellSize, Xwindow::White);
        }
    }
}


void GraphicsDisplay::notifyInfo(gameInterface &whoNotified){
    // display Level and Score
    std::string levelString = "Level:        " + std::to_string(theInterface->currLevel());
    std::string scoreString = "Score:        " + std::to_string(theInterface->getScore());
    std::string hiScoreString = "Hi Score:     " + std::to_string(theInterface->getHighestScore());
    
    
    xw1.fillRectangle(100,25, 50, 75, Xwindow::White); //cover previous information
    xw1.drawString(25, 50, levelString, Xwindow::Black);
    xw1.drawString(25, 75, scoreString, Xwindow::Black);
    xw1.drawString(25, 100, hiScoreString, Xwindow::Black);
    xw1.drawString(25, 125, "Next: ", Xwindow::Black);
}



