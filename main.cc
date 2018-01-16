#include <iostream>
#include <sstream>

#include "gameInterface.h"
#include "controlInput.h"

using namespace std;

int main(int argc, char *argv[]){
    
    //************* set random number *******//
    
    srand(1);
    
    //************  declare ******************//
    
    int startLevel = 0;
    bool textOnly = false;
    
    //************choose game model******** //
    
    string startFile = "sequence.txt";
    
    for(int i = 1; i < argc; i++){
        string stri = argv[i];
        if(stri == "-text"){
            textOnly = true;
        }
        else if(stri == "-seed"){
            istringstream arg{argv[i + 1]};
            int startSeed;
            arg >> startSeed;
            srand(startSeed);
            i++;
        }
        else if(stri == "-scriptfile"){
            startFile = argv[i + 1];
            i++;
        }
        else if(stri == "-startlevel"){
            istringstream arg{argv[i + 1]};
            arg >> startLevel;
            i++;
        }
        else {
            cout << "invalid arguments" << endl;
            exit(1);
        }
    }
    //************Set game******************
    
    gameInterface theInterface;
    int currSeed = rand()%756; // set a random number for interface to generate Blocks
    theInterface.setSeed(currSeed);
    theInterface.setLevel(startLevel);
    theInterface.setSequence(startFile);
    theInterface.setGame();
    
    // Set Graphics
    if (textOnly == false) {
        GraphicsDisplay *gd = new GraphicsDisplay{20, 11, 330, 760, &theInterface};
        theInterface.setGraphicsOb(gd);
        theInterface.updateGraphicsInfor();
    }
    
    // TextDisplay the game
    std::cout << theInterface;
    
    // ******** operation start **********//
    int times = 1;
    string cmd;
    string command;
    
    // ********* hint **********//
    bool hint = false;
    vector<Coordinate> hintCoord;
    
    
    // interpret the input
    string inputFile;
    while(getline(cin, cmd)){
        commandInput(times, command, cmd, inputFile);
        commandExecution(theInterface, command, times, textOnly, currSeed, hint, hintCoord, inputFile);
    }
}

