#include "Subject.h"
#include "Observer.h"

void Subject::attach(Observer *o){
    theObservers.emplace_back(o);
}

void Subject::notifyObservers(){
    for (auto &ob : theObservers)ob->notify(*this);
}


Subject::~Subject(){
    theObservers.clear();
}
