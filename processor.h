#pragma once
#include <string>

class processor
{
public:
    virtual void execute() = 0;
    int get_processor_type() const;
protected:
    processor();
    virtual ~processor();

protected:
    int type;
};

