#include "char_container.h"


char_container::char_container()
{
}


char_container::~char_container()
{
}

char char_container::last_char()
{
    return items.top();
}

void char_container::discard_last_char()
{
    return items.pop();
}

void char_container::put_char(int c)
{
    items.push(c);
}

bool char_container::is_empty()
{
    if (items.size()==0)
    {
        return true;
    }
    return false;
}

