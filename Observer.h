#ifndef observer_hpp
#define observer_hpp

class Subject;
class Cell;
class gameInterface;

class Observer{
public:
    virtual void notify(Subject &) = 0; // pass the Subject that called the notify method
    virtual void notifyInfo(gameInterface &) = 0;
    virtual ~Observer() = default;
};

#endif /* observer_hpp */
