#include "gameInterface.h"
#include <time.h>


gameInterface::~gameInterface(){
    if (this->td != nullptr) {
        delete td;
    }
    if (this->gd != nullptr) {
        delete gd;
    }
}

void gameInterface::newGrid(){
    if(!Grid.empty()){   //clear
        for(int i = 0; i < 20; i++){
            Grid[i].clear();
        }
        Grid.clear();
        delete this->td;
        this->td = nullptr;
        delete this->gd;
        this->gd = nullptr;
    }
    
    this->td = new TextDisplay{20, 11}; // set observer
    
    for (int Row = 0; Row < 20; ++Row) {
        std::vector<Cell> tmp;
        for (int Col = 0; Col < 11; ++Col) {
            Cell aCell{Row, Col};
            aCell.attach(td); // set the TextDisplay observer to each cell
            aCell.notifyObservers();
            tmp.emplace_back(aCell);
        }
        Grid.emplace_back(tmp);
    }
}

void gameInterface::setGame(){
    this->newGrid();
    this->theLevel = startLevel;
    this->noRandom = false;
    generateSequence(this->startSequnce);
    currBlock = generateBlock();
    initialCurrDown();
    nextBlock = generateBlock();
    this->theScore = 0;
    this->punishCount = 0;
}


Block *gameInterface::generateSpecific(char type){
    if (type == 'I') {
        IBlock *newblock = new IBlock{theLevel, this};
        return newblock;
    } else if (type == 'J') {
        JBlock *newblock = new JBlock{theLevel, this};
        return newblock;
    } else if (type == 'S') {
        SBlock *newblock = new SBlock{theLevel, this};
        return newblock;
    } else if (type == 'O') {
        OBlock *newblock = new OBlock{theLevel, this};
        return newblock;
    } else if (type == 'T') {
        TBlock *newblock = new TBlock{theLevel, this};
        return newblock;
    } else if (type == 'Z') {
        ZBlock *newblock = new ZBlock{theLevel, this};
        return newblock;
    } else{
        LBlock *newblock = new LBlock{theLevel, this};
        return newblock;
    }
}

Block *gameInterface::generateBlock() {
    char c;
    if (theLevel == 0) {
        if (this->blockSequence.size() == 0) {
            this->generateSequence(this->startSequnce);
        }
        c = this->blockSequence[0];
        this->blockSequence.erase(this->blockSequence.begin());
    } else if (theLevel == 1) {
        int seed = this->currSeed % 12;
        char listChar[] = {'S','Z','I','I','J','J','L','L','O','O','T','T'};
        c = listChar[seed];
    } else if (theLevel == 2) {
        int seed = this->currSeed % 7;
        char listChar[] = {'S','Z','I','J','L','O','T'};
        c = listChar[seed];
    } else {
        if (noRandom == true) {
            if (this->blockSequence.size() == 0) {
                this->generateSequence(this->randomSequence);
            }
            c = this->blockSequence[0];
            this->blockSequence.erase(this->blockSequence.begin());
        } else {
            int seed = this->currSeed % 9;
            char listChar[] = {'S','S','Z','Z','I','J','L','O','T'};
            c = listChar[seed];
        }
    }
    return this->generateSpecific(c);
}

void gameInterface::generateSequence(std::string aFile){
    std::ifstream seq{aFile};
    this->blockSequence.clear();
    char in;
    while (seq >> in) {
        this->blockSequence.emplace_back(in);
    }
}

//***************************************************
int gameInterface::checkBoard(){
    int i = 0;
    for (int r = 2; r < 20; r++){
        if (checkLine(r)){
            i++;
        }
    }
    return i;
}

bool gameInterface::checkLine(int row){
    for (int i = 0; i <= 10; i++){
        if (Grid[row][i].getParent() == nullptr){
            return false;
        }
    }
    return true;
}

void gameInterface::cleanLine(int row){
    for(int Col = 0; Col < 11; ++Col){
        Grid[row][Col].unset();
    }
}

void gameInterface::moveLine(int workLine){
    for(int Row = workLine ;Row >= 3; Row--){
        for(int Col = 0; Col < 11; ++Col){
            Grid[Row][Col].set(Grid[Row - 1][Col].getParent());
        }
    }
    for (int c = 0; c < 11; c++){
        Grid[2][c].set(nullptr);
    }
}

void gameInterface::addScore(int Score){
    theScore = theScore + Score;
}




//************************************************//



Cell * gameInterface::getCell(Coordinate coord){
    int r = coord.r;
    int c = coord.c;
    Cell *toReturn = &Grid[r][c];
    return toReturn;
}

int gameInterface::getScore() const{
    return theScore;
}

int gameInterface::getHighestScore() const{
    return highestScore;
}

//********** move Curr Block *************//
void gameInterface::currClockwise(){
    this->currBlock->clockwise();
}
void gameInterface::currCounterclockwise(){
    this->currBlock->counterclockwise();
}

void gameInterface::currDown(){
    this->currBlock->down();
}
void gameInterface::currDrop(){
    this->currBlock->drop();
}
void gameInterface::currLeft(){
    this->currBlock->left();
}
void gameInterface::currRight(){
    this->currBlock->right();
}

void gameInterface::initialCurrDown(){
    this->currBlock->initialDown();
}

//********** curr and next setter ***********//
void gameInterface::setNextasCurr(){
    this->currBlock = this->nextBlock;
    this->nextBlock = nullptr;
}
void gameInterface::setNext(Block * aBlock){
    this->nextBlock = aBlock;
}

//********** move Next Block ************//
void gameInterface::nextDown(){
    this->nextBlock->down();
}


//*********** change Level ****************//
void gameInterface::levelDown(){
    if (this->theLevel >= 2){
        this->theLevel--;
    } else if(this->theLevel == 1){
        this->blockSequence.clear();
        this->theLevel--;
        generateSequence(this->startSequnce);
    }
    Grid[0][0].notifyObservers(); // update Graphics
}

void gameInterface::levelUp(){
    if (this->locked == true) {
        if (this->theLevel < 4) {
            if(this->theLevel == 0){
                this->blockSequence.clear();
            }
            this->theLevel++;
        }
    } else {
        if (this->theLevel < 5) {
            if(this->theLevel == 0){
                this->blockSequence.clear();
            }
        this->theLevel++;
        }
    }
    Grid[0][0].notifyObservers();
}

int gameInterface::currLevel() const{
    return this->theLevel;
}


//********** score setter ******************//
void gameInterface::setHighestScore(){
    if (this->theScore >= this->highestScore){
        this->highestScore = this->theScore;
    }
}

void gameInterface::minusNextBlock(){
    addScore(-(this->nextBlock->getLevel()+1) * (this->nextBlock->getLevel()+1));
    
};


//********** punishCount *************//

void gameInterface::getPunish(){
    this->punishCount++;
    if (this->punishCount == 5){
        punishBlock *newblock = new punishBlock{theLevel, this};
        this->punishCount = 0;
        newblock->drop();
    }
}


//********* command line args *************//
void gameInterface::setSeed(int inputSeed){
    currSeed = inputSeed;
}

void gameInterface::setLevel(int inputLevel){
    startLevel = inputLevel;
}

void gameInterface::setSequence(std::string inputFile){
    startSequnce = inputFile;
}

//*********** overload << **************//
std::ostream &operator<<(std::ostream &out, const gameInterface &theInterface){
    out << "Level:         " << theInterface.currLevel() << std::endl;
    out << "Score:         " << theInterface.getScore() << std::endl;
    out << "Hi Score:      " << theInterface.getHighestScore() << std::endl;
    out << "-----------" << std::endl;
    
    out << *(theInterface.td);
    
    return out;
}

//********* for random in Level 3 & 4 **********//
void gameInterface::setRandom(bool random){
    this->noRandom = random;
}

void gameInterface::setRandomFile(std::string aFile){
    this->blockSequence.clear();
    this->randomSequence = aFile;
    this->generateSequence(randomSequence);
}


// *********** set Observers **************//
void gameInterface::setGraphicsOb(GraphicsDisplay *gd){
    this->gd = gd;
    for (int r = 0; r < 20; r++){
        for (int c = 0; c < 11; c++){
            Grid[r][c].attach(this->gd);;
        }
    }
    for (int r = 0; r < 2; r++){
        for (int c = 0; c < 4; c++){
            Grid[r][c].notifyObservers(); // update Graphics
        }
    }
    for (int r = 5; r < 7; r++){
        for (int c = 0; c < 4; c++){
            Grid[r][c].notifyObservers(); // update Graphics
        }
    }
}

void gameInterface::updateGraphicsInfor(){
    this->gd->notifyInfo(*this);
}



//************ hint ***************//

std::vector<Coordinate> gameInterface::hint(){
    char type = currBlock->getType();
    std::vector<Coordinate> hintCoord;
    for(int r = 19; r >= 2;r--){
        for (int c = 0; c <= 10; c++){
            if(Grid[r][c].getParent() == nullptr){
                
                Coordinate coords{r, c};
                hintCoord.emplace_back(coords); // 1st cell
                
                if(type == 'J'){
                    for (int i = 1; i <4; i ++){    //dir 1
                        if (i < 3){ // 2nd and 3rd cells
                            Coordinate coord{hintCoord[i-1].r, hintCoord[i-1].c+1};
                            hintCoord.emplace_back(coord);
                        } else { // 4th cell
                            Coordinate coord{hintCoord[0].r-1, hintCoord[0].c};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                    
                    for (int i = 1; i <4; i ++){    //dir 4
                        if (i == 1){ // 2nd cell
                            Coordinate coord{hintCoord[i-1].r, hintCoord[i-1].c+1};
                            hintCoord.emplace_back(coord);
                        } else { // 3th and 4th cells
                            Coordinate coord{hintCoord[i-1].r-1, hintCoord[i-1].c};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                    for (int i = 1; i <4; i ++){    //dir 3
                        if (i == 1){ // 2nd cell
                            Coordinate coord{hintCoord[i-1].r-1, hintCoord[i-1].c};
                            hintCoord.emplace_back(coord);
                        } else { // 3rd and 4th cells
                            Coordinate coord{hintCoord[i-1].r, hintCoord[i-1].c-1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                    for (int i = 1; i <4; i ++){    //dir 2
                        if (i < 3){ //  2nd and 3rd cells
                            Coordinate coord{hintCoord[i-1].r-1, hintCoord[i-1].c};
                            hintCoord.emplace_back(coord);
                        } else { // 4th cell
                            Coordinate coord{hintCoord[i-1].r, hintCoord[i-1].c+1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                }
                else if(type == 'L'){
                    for (int i = 1; i <4; i ++){    //dir 1
                        if (i < 3){ // 2nd and 3rd cells
                            Coordinate coord{hintCoord[i-1].r, hintCoord[i-1].c+1};
                            hintCoord.emplace_back(coord);
                        } else { // 4th cell
                            Coordinate coord{hintCoord[i-1].r-1, hintCoord[i-1].c};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                    for (int i = 1; i <4; i ++){    //dir 2
                        if (i < 3){ // 2nd and 3th cells
                            Coordinate coord{hintCoord[i-1].r - 1, hintCoord[i-1].c};
                            hintCoord.emplace_back(coord);
                        } else { // 4th cell
                            Coordinate coord{hintCoord[0].r, hintCoord[i-2].c + 1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                    for (int i = 1; i <4; i ++){    //dir 3
                        if (i == 1){ // 2nd cells
                            Coordinate coord{hintCoord[i-1].r-1, hintCoord[i-1].c};
                            hintCoord.emplace_back(coord);
                        } else { // 3rd and 4th cells
                            Coordinate coord{hintCoord[i-1].r, hintCoord[i-1].c+1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                    for (int i = 1; i <4; i ++){    //dir 4
                        if (i  < 3 ){ // 2nd and 3rd cells
                            Coordinate coord{hintCoord[i-1].r - 1, hintCoord[i-1].c};
                            hintCoord.emplace_back(coord);
                        } else { // 4th cell
                            Coordinate coord{hintCoord[i-1].r, hintCoord[i-1].c-1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                }
                else if(type == 'S'){
                    for (int i = 1; i <4; i ++){    //dir 1 and 3
                        if (i == 1){ // 2nd cell
                            Coordinate coord{hintCoord[i-1].r, hintCoord[i-1].c + 1};
                            hintCoord.emplace_back(coord);
                        } else { // 3th and 4th cell
                            Coordinate coord{hintCoord[i-2].r - 1, hintCoord[i-2].c + 1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                        
                    }
                    for (int i = 1; i <4; i ++){    //dir 2 and 4
                        if (i == 1){ // 2nd cell
                            Coordinate coord{hintCoord[i-1].r -1, hintCoord[i-1].c};
                            hintCoord.emplace_back(coord);
                        } else { // 3th and 4th cell
                            Coordinate coord{hintCoord[i-2].r - 1, hintCoord[i-2].c - 1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                }
                else if(type == 'Z'){
                    for (int i = 1; i <4; i ++){    //dir 1 and 3
                        if (i == 1){ // 2nd cell
                            Coordinate coord{hintCoord[i-1].r, hintCoord[i-1].c + 1};
                            hintCoord.emplace_back(coord);
                        } else { // 3th and 4th cell
                            Coordinate coord{hintCoord[i-2].r - 1, hintCoord[i-2].c - 1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                    for (int i = 1; i <4; i ++){    //dir 2 and 4
                        if (i == 1){ // 2nd cell
                            Coordinate coord{hintCoord[i-1].r -1, hintCoord[i-1].c};
                            hintCoord.emplace_back(coord);
                        } else { // 3th and 4th cell
                            Coordinate coord{hintCoord[i-2].r -  1, hintCoord[i-2].c + 1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                }
                else if(type == 'T'){
                    for (int i = 1; i <4; i ++){    //dir 3
                        if (i < 3){ //  2nd and 3rd cells
                            Coordinate coord{hintCoord[i-1].r, hintCoord[i-1].c + 1};
                            hintCoord.emplace_back(coord);
                        } else { // 4th cell
                            Coordinate coord{hintCoord[0].r - 1, hintCoord[0].c+1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                    for (int i = 1; i <4; i ++){    //dir 2
                        if (i < 3){ //  2nd and 3rd cells
                            Coordinate coord{hintCoord[i-1].r-1, hintCoord[i-1].c};
                            hintCoord.emplace_back(coord);
                        } else { // 4th cell
                            Coordinate coord{hintCoord[0].r - 1, hintCoord[0].c - 1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                    for (int i = 1; i <4; i ++){    //dir 1
                        if (i == 1){ // 2nd cell
                            Coordinate coord{hintCoord[0].r - 1, hintCoord[0].c - 1};
                            hintCoord.emplace_back(coord);
                        } else { // 3st and 4th cells
                            Coordinate coord{hintCoord[i - 1].r, hintCoord[i - 1].c + 1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                    for (int i = 1; i <4; i ++){    //dir 4
                        if (i < 3){ //  2nd and 3rd cells
                            Coordinate coord{hintCoord[i-1].r-1, hintCoord[i-1].c};
                            hintCoord.emplace_back(coord);
                        } else { // 4th cell
                            Coordinate coord{hintCoord[0].r - 1, hintCoord[0].c+1};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                }
                else if(type == 'I'){
                    for (int i = 1; i <4; i ++){    //dir 1 and 3
                        Coordinate coord{hintCoord[i-1].r, hintCoord[i-1].c + 1};
                        hintCoord.emplace_back(coord);
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                        
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                    for (int i = 1; i <4; i ++){    //dir 2 and 4
                        Coordinate coord{hintCoord[i-1].r - 1, hintCoord[i-1].c};
                        hintCoord.emplace_back(coord);
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                }
                else{ //}(type == O)
                    for (int i = 1; i <4; i ++){
                        if (i == 1){ // 2nd cell
                            Coordinate coord{hintCoord[i-1].r , hintCoord[i-1].c + 1};
                            hintCoord.emplace_back(coord);
                        } else { // 3th and 4th cell
                            Coordinate coord{hintCoord[i-2].r -  1, hintCoord[i-2].c};
                            hintCoord.emplace_back(coord);
                        }
                    }
                    if(this->reachable(hintCoord)){
                        return hintCoord;
                    }
                    else{
                        hintCoord.clear();
                        hintCoord.emplace_back(coords); // 1st cell
                    }
                }
                
                hintCoord.clear();
            }
        }
    }
    hintCoord.clear();
    return hintCoord;
}

bool gameInterface::reachable(std::vector<Coordinate> hintCoords){
    
    int maxRow = 19;
    int maxCol = 0;
    
    std::vector<Coordinate> rowCoords;
    for (auto aCell : currBlock->getCells()){
        rowCoords.emplace_back(aCell->getCoord());
    }
    
    for (auto aCoord : hintCoords){
        maxCol = aCoord.c > maxCol ? aCoord.c : maxCol;
    }
    
    for (auto aCoord : rowCoords){
        maxRow = aCoord.r < maxRow ? aCoord.r : maxRow;
    }
    
    while (true){ // check if the columns have blocks above
        if (hintCoords[0].r == maxRow || hintCoords[1].r ==  maxRow ||
            hintCoords[2].r ==  maxRow || hintCoords[3].r ==  maxRow){//reach top
            break;
        }
        if (currBlock->moveable(hintCoords)){
            for (auto &aCoord : hintCoords){
                aCoord.r -= 1;
            }
        } else {
            return false;
        }
    }
    
    
    while (true) { // check if the row has block preventing current block from moving
        if (rowCoords[0].c == maxCol || rowCoords[1].c == maxCol ||
            rowCoords[2].c == maxCol || rowCoords[3].c == maxCol){
            break;
        }
        if (currBlock->moveable(rowCoords)){
            for (auto &aCoord : rowCoords){
                aCoord.c += 1;
            }
        } else {
            return false;
        }
    }
    return true;
}


void gameInterface::setCells(std::vector<Coordinate> hintCoords){
    hintBlock *hBlock = new hintBlock{theLevel, this};
    for (auto n : hintCoords){
        int r = n.r;
        int c = n.c;
        Grid[r][c].set(hBlock);
    }
}

void gameInterface::unsetCells(std::vector<Coordinate> hintCoords){
    for (auto n : hintCoords){
        int r = n.r;
        int c = n.c;
        Grid[r][c].unset();
    }
}


// ******** for level 5 ************
void gameInterface::lockLevel5(){
    this->locked = true;
}
void gameInterface::unlockLevel5() {
    this->locked = false;
}





