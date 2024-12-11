#pragma once
#include "Meteorit.h"
class Full :
    public Meteorit
{
public:
    Full(String name, int x, int y);
    ~Full();


    virtual void restart();

private:
    using Meteorit::animation;
};

