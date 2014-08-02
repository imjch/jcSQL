#include "table_mgr.h"
#include "json\json.h"
#include <stdexcept>
#include "err_msg_mgr.h"
#include <cassert>
#include <string>
#include <list>
#pragma comment(lib,"jsoncpp.lib")

table_mgr::table_mgr():
current_db(db_mgr::get_current_database())
{
}

table_mgr::table_mgr(const std::string& table_name):
current_table(table_name),
current_db(db_mgr::get_current_database())
{
    open_table(table_name);
}

table_mgr::~table_mgr()
{
}

std::string table_mgr::get_full_table_path()
{
    assert(current_db.size()>0);
    assert(current_table.size()>0);
    return current_db + "\\" + current_table;
}

std::string table_mgr::get_full_table_attr_path()
{
    return get_full_table_path() + ".attr";
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
    auto t = get_full_table_path();
    f_mgr.open(t, "r+");
}

void table_mgr::close_table()
{
    f_mgr.close();
}
    
bool table_mgr::contain_attr(Json::Value& val, std::string& v)
{
    assert(val.isArray());
    for (size_t i = 0; i < val.size(); i++)
    {
        if (val[i]==v)
        {
            return true;
        }
    }
    return false;
}

void table_mgr::set_table_type_columns(type_column_table& t_c_table)
{
    file_mgr f;
    f.open(get_full_table_attr_path(), "r+");
    std::string content = f.read();
    Json::Reader reader;
    Json::Value object;
    Json::StyledWriter writer;
    reader.parse(content.c_str(), object);
    for (auto iter = t_c_table.begin(); iter != t_c_table.end(); ++iter)
    {
        object[iter->get_column()] = iter->get_type();
    }
    f.write(writer.write(object));
}

void table_mgr::set_table_attrs(table_attr& attrs)
{
    file_mgr f;
    f.open(get_full_table_attr_path(), "r+");
    std::string content = f.read();
    Json::Reader reader;
    Json::Value object;
    Json::StyledWriter writer;
    reader.parse(content.c_str(), object);

    if (attrs.size()>0)
    {
        for (auto iter = attrs.begin(); iter !=attrs.end(); iter++)
        {
            for (auto iiter = iter->second.begin(); iiter != iter->second.end(); iiter++)
            {
                if (!contain_attr(object[column_attrs[iiter->get_attr()]], iiter->get_column_name()))
                {
                    object[column_attrs[iiter->get_attr()]].append(iiter->get_column_name());
                }
            }
        }
    }
    f.write(writer.write(object));
    f.close();
}

bool table_mgr::exist(const std::string& table_name)
{
    return file_mgr::exist(db_mgr::get_current_database()+ "\\" + table_name);
}

void table_mgr::insert_data(attr_val_list& list)
{
    attr_val_list::iterator iter = list.begin();
    Json::Reader reader;
    Json::FastWriter writer;
    Json::Value root;
    std::string content = f_mgr.read();

    reader.parse(content, root);
    while (iter!=list.end())
    {
        insert_data_(root, iter->second);
        ++iter;
    }
    f_mgr.write(writer.write(root));
}

void table_mgr::insert_data_(Json::Value& root, attr_val_pair& pair)
{
    assert(pair.get_result_list().size()==1);
    root[pair.get_attr_name()].append(*pair.get_result_list().begin());
}