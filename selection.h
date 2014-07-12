#pragma once
#include "operation.h"
#include <string>
#include <vector>
class selection :
    public operation
{
public:
    selection();
    ~selection();
    void execute();
private:
};

