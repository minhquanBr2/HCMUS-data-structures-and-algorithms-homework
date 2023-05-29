#pragma once
#include "..\DataStructure\PQueue\PQueue.h"

struct PQueue_UI
{
private:
    PQueue *_pQueueHandle;

public:
    // Destructor
    ~PQueue_UI();

    // Menu
    void showProcessingMenu();
    void showInitializingMenu();

    // Processing methods
    void checkEmpty();
    void insert();
    void extract();
    void remove();
    void changePriority();
    void print();
};
