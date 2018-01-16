#ifndef controlInput_h
#define controlInput_h


#include <sstream>
#include <vector>
#include "Coordinate.h"

#include "gameInterface.h"

void commandInput(int &times, std::string &command, std::string cmd, std::string &);


void commandExecution(gameInterface &, std::string&, int&, bool&, int &, bool & , std::vector<Coordinate> &, std::string&);

#endif /* Header_h */

