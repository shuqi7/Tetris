#ifndef board_h
#define board_h

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include "Cell.h"
#include "Observer.h"
#include "TextDisplay.h"
#include "GraphicsDisplay.h"
#include "Block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "ZBlock.h"
#include "TBlock.h"
#include "hintBlock.h"
#include "punishBlock.h"



class gameInterface{
    Block *currBlock;   //the currect Block we are playing
    Block *nextBlock;  //the next Blocks will be initialed on the grid
    
    //graphicsdisplay * GraphicsDisplay;  //link to the graph display file
    int theScore;   //the currect score on THIS game(will be zero after reset the game)
    int highestScore = 0;
    int theLevel;
    std::vector<std::vector<Cell>> Grid;    //the basic grid we are plying on
    std::vector<char>blockSequence;
    
    // for punish Blocks
    int punishCount = 0;
    
    // for command-line arguments
    int currSeed;
    int startLevel;
    std::string startSequnce;
    
    // for Display
    TextDisplay *td = nullptr;
    GraphicsDisplay *gd = nullptr;
    // for randomness in Level 3 and 4
    bool noRandom;
    std::string randomSequence;
    
    // for level 5
    bool locked = true;
    
    
public:
    //***********basic ctor,dtor*********
    ~gameInterface();
    
    void newGrid();    //initial a new grid, call it before again or reset grid
    void setGame();     //set a new game, call it before again or reset game
    
    void generateSequence(std::string);
    Block *generateSpecific(char); // generate a Block according to char
    Block *generateBlock(); // generate a randoem Block
    
    //***********do with Board*********
    int checkBoard();   //return number of lines to be cleared
    bool checkLine(int);    //check and return the lowest full line
    void cleanLine(int);   //clean theLine(modify cell)
    void moveLine(int);    //move every "bolck" above the line 1 line down(modify cell)
    
    //************all the outputs********
    Cell *getCell(Coordinate);
    int getScore() const;
    int getHighestScore() const;
    
    //********** move Curr Block *************//
    void currClockwise();
    void currCounterclockwise();
    void currDown();
    void currDrop();
    void currLeft();
    void currRight();
    void initialCurrDown();
    
    //********** curr and next setter ***********//
    void setNextasCurr();
    void setNext(Block *);
    
    //********** move Next Block ************//
    void nextDown();
    
    //*********** change Level ********//
    void levelDown();
    void levelUp();
    int currLevel() const;
    
    //********** Score setter *********//
    void addScore(int);   //add Score to theScore
    void setHighestScore();
    void minusNextBlock(); // deduct the score when next Block is substituted
    
    //********** punishCount **********//
    void getPunish();
    
    //********** command-line args *******//
    void setSeed(int);
    void setLevel(int);
    void setSequence(std::string);
    
    
    //********** overloading << **********//
    friend std::ostream &operator<<(std::ostream &out, const gameInterface &theInterface);
    
    
    //********* for random in Level 3 & 4 **********//
    void setRandom(bool);
    void setRandomFile(std::string);
    
    // *********** set Observers **************//
    void setGraphicsOb(GraphicsDisplay *);
    void updateGraphicsInfor();
    
    // *********** hint **************//
    std::vector<Coordinate> hint();
    bool reachable(std::vector<Coordinate>);
    void setCells(std::vector<Coordinate>);
    void unsetCells(std::vector<Coordinate>);
    
    // for level 5
    void lockLevel5();
    void unlockLevel5();
};

#endif
