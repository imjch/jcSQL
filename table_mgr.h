#pragma once
#include <string>
#include "file_mgr.h"
#include "db_mgr.h"
#include "uncopyable.h"
class table_mgr:private uncopyable
{
public:
    table_mgr();
    ~table_mgr();
    void create_table(const std::string&);
private:
    file_mgr f_mgr;

};

