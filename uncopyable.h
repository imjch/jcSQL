#pragma once

class uncopyable
{
public:
    uncopyable()
    {
    }
    ~uncopyable()
    {
    }
private:
    uncopyable(uncopyable&)
    {
    }
    uncopyable& operator=(uncopyable&)
    {
    }
};
