#pragma once

#include <vector>

class Observer {
public:
    virtual ~Observer() {}
    virtual void onNotify(int event) = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;
    int nObserver;
protected:
    void notify(int event);
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
};
