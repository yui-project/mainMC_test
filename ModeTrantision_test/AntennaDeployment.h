#pragma once
#include "IoExpander.h"
class AntennaDeployment
{
private:
    IoExpander ioExpander;
    int AntennaDeploymentPin = 2;
    int AntennaDeploymentConfirmPin = 4;
    int counter = 0;

public:
    AntennaDeployment();
    void startUp();
    bool isOpen();
};