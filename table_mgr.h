#pragma once
#include <string>
#include <list>
#include "file_mgr.h"
#include "db_mgr.h"
#include "uncopyable.h"

class table_mgr:private uncopyable
{
public:
    table_mgr(const std::string&);
    table_mgr();
    ~table_mgr();
    static bool exist(const std::string&);
    static void create_table(const std::string&);
    static void delete_table(const std::string&);
    void add_attr(const std::string&,const std::string&);
    void add_attr(const std::string&, std::list<std::string>&);
  
    void open_table(const std::string&);
    void close_table();
private:
    std::string current_db;
    std::string current_table;
    file_mgr f_mgr;
    db_mgr d_mgr;
};

