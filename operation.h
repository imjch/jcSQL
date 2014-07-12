#pragma once
#include <string>

class operation
{
public:
    virtual void execute() = 0;
    int get_operation_type() const;
protected:
    operation();
    virtual ~operation();

protected:
    int type;
};

