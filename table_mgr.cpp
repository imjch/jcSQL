#include "table_mgr.h"
#include "json\json.h"
#include <stdexcept>
#include "err_msg_mgr.h"
#include <cassert>
#include <string>
#include <iostream>
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

std::string table_mgr::get_full_table_path(const std::string& db,const std::string& table)
{
    assert(db.size()>0);
    assert(table.size()>0);
    return db + "\\" + table;
}

std::string table_mgr::get_full_table_attr_path(const std::string& db, const std::string& table)
{
    return get_full_table_path(db,table) + ".attr";
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
    out.write("{\"attributes\":{},\"columns\":{}}");
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
    auto t = get_full_table_path(current_db, current_table);
    f_mgr.open(t, "a+");
}

void table_mgr::close_table()
{
    f_mgr.close();
}
    
bool table_mgr::contain_attr(inner_structure& val, std::string& v)
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
    f.open(get_full_table_attr_path(current_db, current_table), "r+");
    inner_structure root;
    inner_structure_writer writer;
    root = fetch_all_data(f);
    inner_structure sub_node = root["columns"];
    for (auto iter = t_c_table.begin(); iter != t_c_table.end(); ++iter)
    {
        sub_node[iter->get_column()] = val_type_to_s[iter->get_type()];
    }
    std::cout << root << std::endl;
    std::cout << sub_node << std::endl;
    root["columns"] = sub_node;
    std::cout << root << std::endl;
    f.write(writer.write(root));
    f.close();
}

void table_mgr::set_table_attrs(table_attr& attrs)
{
    file_mgr f;
    f.open(get_full_table_attr_path(current_db, current_table), "r+");
    inner_structure root;
    inner_structure_writer writer;
    root = fetch_all_data(f);
    inner_structure sub_node = root["attributes"];
    if (attrs.size()>0)
    {
        for (auto iter = attrs.begin(); iter !=attrs.end(); iter++)
        {
            for (auto iiter = iter->second.begin(); iiter != iter->second.end(); iiter++)
            {
                if (!contain_attr(sub_node[column_attrs_to_s[iiter->get_attr()]], iiter->get_column_name()))
                {
                    sub_node[column_attrs_to_s[iiter->get_attr()]].append(iiter->get_column_name());
                }
            }
        }
    }
    root["attributes"] = sub_node;
    f.write(writer.write(root));
    f.close();
}

bool table_mgr::exist(const std::string& table_name)
{
    return file_mgr::exist(db_mgr::get_current_database()+ "\\" + table_name);
}

void table_mgr::insert_data(attr_val_list& list)
{
    get_table_attr();
    inner_structure_writer writer;
    inner_structure root = fetch_all_data(f_mgr);
    size_t i = root.size();
    data_record_indicator record = construct_data_record_indicator(list);
    Json::Value null_val(-1);
    for (auto iter = record.begin(); iter != record.end();iter++)
    {
        if (iter->second.first==READLVAL)
        {
            root[std::to_string(i)].append(iter->second.second);
        }
        else
        {
            root[std::to_string(i)].append(null_val);
        }
    }
    f_mgr.write(writer.write(root));
}

table_mgr::data_record_indicator table_mgr::construct_data_record_indicator(attr_val_list& list)
{
    data_record_indicator record;
    for (auto iter = current_type_column_list.begin(); iter != current_type_column_list.end();++iter)
    {
        record[iter->get_column()] = std::make_pair(NULLABLE,"");
    }
    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
        if (record.count(iter->first)<0)
        {
            throw std::runtime_error(err_msg_mgr::invalid_expression("column %s non-exists,please check it again.",iter->first));
        }
        record[iter->first].first=READLVAL;
        record[iter->first].second=*(iter->second.get_result_list().begin());
    }
    return record;
}

void table_mgr::get_table_attr()
{
    file_mgr f(get_full_table_attr_path(current_db, current_table), "r");
    inner_structure root = fetch_all_data(f);
    inner_structure attr_node = root["attributes"];
    for (auto iter = attr_node.begin(); iter != attr_node.end(); iter++)
    {
        for (auto iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
        {
            current_table_attr.add_column_attr(column_attr_pair(column_attrs_to_i.at(iter.key().asString()), (*iter2).asString()));
        }
    }
    inner_structure column_node = root["columns"];
    for (auto iter = column_node.begin(); iter != column_node.end();++iter)
    {
        current_type_column_list.add_type_column(type_column_pair(val_type_to_i.at((*iter).asString()), iter.key().asString()));
    }
}

//void table_mgr::alter_table(operators op, type_column_table& t_c_table)
//{
//    assert(op >= 0);
//    assert(t_c_table.size()>0);
//
//}

//table_mgr::result_table table_mgr::get_data(column_list& li, logic_conn_table& l_c_table)
//{
//  /*  auto l_list=l_c_table.get_logic_expr_list("and");
//    Json::Value root = fetch_all_data();*/
//    return result_table();
//}

Json::Value table_mgr::fetch_all_data(file_mgr& file)
{
    inner_structure_reader reader;
    inner_structure root;
    std::string content = file.read();
    reader.parse(content, root);
    return root;
}


