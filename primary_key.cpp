#include "primary_key.h"
#include <utility>
//primary_key::primary_key(const std::string& attr, primary_key_val& val)
//{
//    keys.insert(std::make_pair(attr, val));
//}

primary_key::primary_key()
{
}

primary_key::~primary_key()
{
}

size_t primary_key::size()
{
    return keys.size();
}

void primary_key::insert(const std::string& attr, primary_key_val& val)
{
    keys.insert(std::make_pair(attr, val));
}

bool primary_key::empty()
{
    return keys.empty();
}

primary_key::primary_key_val primary_key::get_primary_key_val(const std::string& attr)
{
    return keys.at(attr);
}

std::string primary_key::to_string()
{
    std::string str;
    for (auto iter = keys.begin(); iter != keys.end(); ++iter)
    {
        str.append(iter->second);
        str.push_back(',');
    }
    str.pop_back();
    return str;
}