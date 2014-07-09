#pragma once
#include "processor.h"
#include <string>
#include <vector>
class selection :
    public processor
{
public:
    selection();
    ~selection();
    void execute();
private:
};

