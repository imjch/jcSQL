#include "table_mgr.h"
#include "json\json.h"
#include <stdexcept>
#include "err_msg_mgr.h"
#include <cassert>
#include <string>
#include <list>

#pragma comment(lib,"jsoncpp.lib")
table_mgr::table_mgr()
:current_db(db_mgr::get_current_database() + "\\")
{
}

table_mgr::table_mgr(const std::string& table_name)
:current_db(db_mgr::get_current_database()+"\\"),
current_table(table_name)
{
    open_table(table_name);
}

table_mgr::~table_mgr()
{
}


void table_mgr::create_table(const std::string& table_name)
{
    assert(table_name.size() > 0);
    std::string full(db_mgr::get_current_database() + "\\" + table_name);
    file_mgr::create_file(full);
    file_mgr::create_file(full + ".attr");
    
    file_mgr out;
    out.open(full, "w");
    out.write("{}");
    out.close();
    out.open(full + ".attr", "w");
    out.write("{}");
    out.close();
}

void table_mgr::delete_table(const std::string& table_name)
{
    assert(table_name.size()>0);
    std::string full_path(db_mgr::get_current_database() + "\\" + table_name);
    file_mgr::remove_file(full_path);
    file_mgr::remove_file(full_path + ".attr");
}

void table_mgr::open_table(const std::string& table_name)
{
    assert(table_name.size()>0);
    current_table = table_name;
    f_mgr.open(current_db + "\\" + table_name,"r+");
}

void table_mgr::close_table()
{
    f_mgr.close();
}

void table_mgr::add_attr(const std::string& qualified_id, const std::string& col)
{
    assert(current_table.size()>0&&col.size()>0);
    Json::Reader reader;
    Json::FastWriter writer;
    Json::Value object;
    file_mgr f;
    f.open(current_db + current_table + ".attr", "r+");
    std::string content = f.read();
    reader.parse(content.c_str(), object);
    for (Json::Value::iterator iter = object[qualified_id].begin(); iter != object[qualified_id].end(); iter++)
    {
        if (*iter==col)
        {
            return;
        }
    }
    object[qualified_id].append(col);
    f.write(writer.write(object));
    f.close();
}


void table_mgr::add_attr(const std::string& qualified_id, std::list<std::string>& indexs)
{
    std::list<std::string>::iterator iter = indexs.begin();
    while (iter != indexs.end())
    {
        add_attr(qualified_id,*iter);
        ++iter;
    }
}

bool table_mgr::exist(const std::string& table_name)
{
    return file_mgr::exist(table_name);
}