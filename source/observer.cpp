#include <stdio.h>
#include "observer.h"

void Subject::notify(int event) {
    for (int i = 0; i < nObserver; i++) {
        observers[i]->onNotify(event);
    }
}

void Subject::addObserver(Observer* observer) {
    bool inserted = false;
    for (int i = 0; i < nObserver; i++) {
        if (observers[i] == NULL) {
            observers[i] = observer;
            nObserver++;
            inserted = true;
            break;
        }
    }
    if (!inserted) {
        observers.push_back(observer);
        nObserver++;
    }
}

void Subject::removeObserver(Observer* observer) {
    for (int i = 0; i < nObserver; i++) {
        if (observers[i] == observer) {
            observers[i] = NULL;
            nObserver--;
            break;
        }
    }
}
