#include <iostream>
#include <fstream>
#include <sstream>
#include "controlInput.h"
#include <termio.h>
#include <iostream>


using namespace std;

char scanKeyboard()
{
    char in;
    termios newSet;
    termios ogSet;
    tcgetattr(0,&ogSet);
    newSet = ogSet;
    newSet.c_lflag &= (~ICANON);
    newSet.c_cc[VTIME] = 0;
    newSet.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&newSet);
    cin >> in;
    tcsetattr(0,TCSANOW,&ogSet);
    return in;
}


void commandKeyboard(char keyCommand, std::string & command){
    switch(keyCommand){
        case 'a':    //a
            command = "left";
            break;
        case 'd':   //d
            command = "right";
            break;
        case 'w':   //w
            command = "down";
            break;
        case 's':   //s
            command = "drop";
            break;
        case 'q':   //q
            command = "clockwise";
            break;
        case 'e':   //e
            command = "counterclockwise";
            break;
        case 'h':   //h
            command = "hint";
            break;
        case 'j':   //j
            command = "levelup";
            break;
        case 'k':   //k
            command = "leveldown";
            break;
        case 'l':   //k
            command = "lockLevel5";
            break;
        case 'u':   //k
            command = "unlockLevel5";
            break;
        default:
            command = "invalid-Input";
    }
}

void commandInput(int& times, string& command, string cmd, string & inputFile){
    char c;
    istringstream ss {cmd};
    if(!(ss >> times)){
        ss.clear();
        ss >> c;
        times = 1;
    } else {
        ss >> c;
    }
    switch(c){
        case 'c': //clockwise/counterclockwise
            ss >> c;
            switch(c){
                case 'l':
                    command = "clockwise";  //clockwise
                    break;
                case 'o':
                    command = "counterclockwise"; //counterclockwise
                    break;
                default:
                    command = "invalid-Input";
                    break;
            }
            break;
        case 'd': // down / drop
            ss >> c;
            switch(c){
                case 'o':
                    command = "down"; //down
                    break;
                case 'r':
                    command = "drop"; // drop
                    break;
                default:
                    command = "invalid-Input";
                    break;
            }
            break;
        case 'h':
            command = "hint"; //hint
            break;
        case 'u':
            command = "unlockLevel5";
            break;
        case 'I':
            command = "I"; //I
            break;
        case 'J':
            command = "J"; //J
            break;
        case 'L':
            command = "L";   //L
            break;
        case 'l': //left / leveup / level down
            ss >> c;
            if (c == 'o') {
                command = "lockLevel5";
                return;
            }
            ss >> c;    //every command begins with l, the second char is e
            switch(c){
                case 'f':
                    command = "left"; //left
                    break;
                case 'v':
                    ss >> c; //e
                    ss >> c; //l
                    ss >> c; //u / d
                    if(c == 'u'){
                        command = "levelup"; //levelup
                    }
                    else if(c == 'd'){
                        command = "leveldown"; //leveldown
                    }
                    else{
                        command = "invalid-Input";
                    }
                    break;
                default:
                    command = "invalid-Input";
                    break;
            }
            break;
        case 'n':
            {
                command = "norandom";   //  norandom
                ss >> std::noskipws; // don't ignore space
                while(ss >> c){
                    if(c == ' '){
                        ss >> inputFile;
                        break;
                    }
                }
                break;
            }
        case 'O':
            command = "O";  //O
            break;
        case 'r':
            ss >> c;
            if(c == 'a'){
                command = "random"; // random
                break;
            }
            else if(c == 'e'){
                command = "restart";  //  right
                break;
            }
            else if(c == 'i'){
                command = "right";  //  right
            }
            else {
                command = "invalid-Input";
            }
            break;
        case 'S':
            command = "S";  //S
            break;
        case 's':
            {
                command = "sequence";    //sequnce
                ss >> std::noskipws; // dont ignore space
                while(ss >> c){
                    if(c == ' '){
                        ss >> inputFile;
                        break;
                    }
                }
                break;
            }
        case 'T':
            command = "T";  //T
            break;
        case 'Z':
            command = "Z";   //Z
            break;
        case 'k':
            command = "keyboard"; // keyboard listener
            break;
        default:
            command = "invalid-Input";
    }
}


//********************************************************************

void commandExecution(gameInterface &theInterface, string& command, int & times, bool& textOnly, int &currSeed, bool &hint, vector<Coordinate> & hintCoord, string &inputFile){
    
    for(int i = 0; i < times; i++){
        if (hint == true){
            theInterface.unsetCells(hintCoord);
            hint = false;
        }
        
        if( command ==  "down" || command ==  "drop" ||
           command ==  "left" || command ==  "right" ||
           command == "clockwise" || command == "counterclockwise"){
            try{
                if (command == "down") {
                    theInterface.currDown();
                } else if (command == "drop"){
                    theInterface.currDrop();
                } else if (command == "left"){
                    theInterface.currLeft();
                } else if (command == "right"){
                    theInterface.currRight();
                } else if (command == "clockwise"){
                    theInterface.currClockwise();
                } else {
                    theInterface.currCounterclockwise();
                }
            }
            catch(string s){ // current Block reached the bottom
                if(theInterface.checkBoard() != 0){ // check board, some rows are filled
                    // add score
                    theInterface.addScore((theInterface.checkBoard() + theInterface.currLevel())*       (theInterface.checkBoard() + theInterface.currLevel()));
                    
                    while (theInterface.checkBoard() != 0){ // clear multiple rows
                        for(int i = 19; i >= 2; i--){
                            if(theInterface.checkLine(i)){
                                theInterface.cleanLine(i);
                                theInterface.moveLine(i);
                            }
                        }
                    }
                    
                    if (textOnly == false) {
                        theInterface.updateGraphicsInfor();
                    }
                    
                } else {// without clearing a row, get punished if Level == 4
                    if (theInterface.currLevel() == 4){
                        try {
                            theInterface.getPunish();
                        } catch (string s){
                            if(theInterface.checkBoard() != 0){ // check board, some rows are filled
                                // add score
                                theInterface.addScore((theInterface.checkBoard() + theInterface.currLevel())*       (theInterface.checkBoard() + theInterface.currLevel()));
                                
                                
                                while (theInterface.checkBoard() != 0){ // clear multiple rows
                                    for(int i = 19; i >= 2; i--){
                                        if(theInterface.checkLine(i)){
                                            theInterface.cleanLine(i);
                                            theInterface.moveLine(i);
                                        }
                                    }
                                }
                            }
                            
                            if (textOnly == false) {
                                theInterface.updateGraphicsInfor();
                            }
                            
                        } // catch as drop throws
                    }
                }
                
                theInterface.setNextasCurr();
                
                try{
                    theInterface.initialCurrDown();
                    currSeed = rand()%756; // set a random number for interface to generate Blocks
                    theInterface.setSeed(currSeed);
                    theInterface.setNext(theInterface.generateBlock()); //move next to curr and get a new Block for next
                }
                catch(string s){ // game should restart as no place for the next Block
                    theInterface.setHighestScore();
                    theInterface.setGame();
                    if (textOnly == false) {
                        GraphicsDisplay *gd = new GraphicsDisplay{20, 11, 330, 760, &theInterface};
                        theInterface.setGraphicsOb(gd);
                        theInterface.updateGraphicsInfor();
                    }
                }
            }
        }
        else if( command ==  "I" || command ==  "J" || command ==  "L" || command ==  "O" || command ==  "S" || command ==  "Z" || command ==  "T"){ // generate a Block of a specific type
            
            istringstream type{command};
            char c;
            type >> c;
            theInterface.minusNextBlock(); // deduct marks
            theInterface.cleanLine(0);
            theInterface.cleanLine(1);
            theInterface.setNext(theInterface.generateSpecific(c));
            
        }
        else if( command ==  "leveldown" ){
            theInterface.levelDown();
            if (textOnly == false) {
                theInterface.updateGraphicsInfor();
            }
        }
        else if( command ==  "levelup" ){
            theInterface.levelUp();
            if (textOnly == false) {
                theInterface.updateGraphicsInfor();
            }
        }
        else if( command ==  "norandom" ){
            if(theInterface.currLevel() > 2){
                theInterface.setRandom(true);
                theInterface.setRandomFile(inputFile);
                theInterface.minusNextBlock(); // deduct marks
                theInterface.cleanLine(0);
                theInterface.cleanLine(1);
                theInterface.setNext(theInterface.generateBlock());
            }
        }
        else if( command ==  "random" ){
            if(theInterface.currLevel() > 2){
                theInterface.setRandom(false);
                theInterface.minusNextBlock(); // deduct marks
                theInterface.cleanLine(0);
                theInterface.cleanLine(1);
                currSeed = rand()%756; // set a random number for interface to generate Blocks
                theInterface.setSeed(currSeed);
                theInterface.setNext(theInterface.generateBlock());
            }
        }
        else if( command ==  "restart" ){
            theInterface.setHighestScore();
            theInterface.setGame();
            if (textOnly == false) {
                GraphicsDisplay *gd = new GraphicsDisplay{20, 11, 330, 760, &theInterface};
                theInterface.setGraphicsOb(gd);
                theInterface.updateGraphicsInfor();
            }
        }
        else if( command ==  "sequence" ){
            std::ifstream seq{inputFile};
            int times2 = 1;
            string cmd;
            hint = false;
            while(seq >> cmd){
                commandInput(times2, command, cmd, inputFile);
                if (command == "norandom" || command == "sequence"){
                    seq >> inputFile;
                }
                commandExecution(theInterface, command, times2, textOnly, currSeed, hint, hintCoord, inputFile);
            }
        }
        else if (command == "invalid-Input"){
            std::cout << "Invalid Input! Please enter again" << std::endl;
        }
        else if (command == "keyboard"){
            std::cout << "Keylistener On!" << std::endl;
            std::cout << "a: left" << std::endl;
            std::cout << "d: right" << std::endl;
            std::cout << "w: down" << std::endl;
            std::cout << "s: drop" << std::endl;
            std::cout << "q: clockwise" << std::endl;
            std::cout << "e: conterclockwise" << std::endl;
            std::cout << "h: hint" << std::endl;
            std::cout << "j: levelup" << std::endl;
            std::cout << "k: leveldown" << std::endl;
            std::cout << "l: lock level 5" << std::endl;
            std::cout << "u: unlock level 5" << std::endl;
            std::cout << "p: to quit keylistener" << std::endl;
            while(1){
                char keycommand = scanKeyboard();
                if(keycommand == 'p'){
                    std::cout << std::endl;
                    std::cout << "Keylistener Off!" << std::endl;
                    break;
                }
                commandKeyboard(keycommand, command);
                int times2 = 1;
                std::cout << std::endl;
                commandExecution(theInterface, command, times2, textOnly, currSeed, hint, hintCoord, inputFile);
            }
        }
        else if (command == "hint") {
            hint = true;
            hintCoord.clear();
            hintCoord = theInterface.hint();
            if (hintCoord.empty()){
                std::cout << "No place to put current block anymore!" << std::endl;
            }else {
                theInterface.setCells(hintCoord);
            }
        } else if (command == "lockLevel5"){
            theInterface.lockLevel5();
        } else if (command == "unlockLevel5"){
            theInterface.unlockLevel5();
        }
    }
    std::cout << theInterface;
}


