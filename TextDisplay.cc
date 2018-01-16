#include "TextDisplay.h"
#include "Block.h"


TextDisplay::TextDisplay(int r, int c):r{r}, c{c}{
    for (int i = 0; i < r; i++){
        std::vector<char> v;
        for (int j = 0; j < c; j++){
            v.emplace_back(' ');
        }
        this->theDisplay.emplace_back(v);
    }
}

void TextDisplay::notify(Subject &whoNotified){
    int row = whoNotified.getCoord().r;
    int col = whoNotified.getCoord().c;
    if (whoNotified.getParent() == nullptr){
        theDisplay[row][col] = ' ';
    } else {
        char type = whoNotified.getParent()->getType();
        theDisplay[row][col] = type;
    }
}


std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
    
    for (int i = 2; i < td.r; i++){
        for (int j = 0; j < td.c; j++){
            out << td.theDisplay[i][j];
        }
        out << std::endl;
    }
    
    out << "-----------" << std::endl;
    out << "Next:" << std::endl;
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < td.c; j++){
            out << td.theDisplay[i][j];
        }
        out << std::endl;
    }
    
    return out;
}


void TextDisplay::notifyInfo(gameInterface &whoNotified){}
