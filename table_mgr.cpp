#include "table_mgr.h"
#include "json\json.h"
#include <stdexcept>
#include "err_msg_mgr.h"
#include <cassert>
#include <string>
#include <iostream>
#include "attr_val_pair.h"
#include "result_list.h"
#include <list>
#include "single_record.h"
#pragma comment(lib,"jsoncpp.lib")

//the keys is seperated by comma and no white space existed in it.  Ex:a,b,c
//attr_val_table table_mgr::make_primary_key_list(inner_structure& val)
//{
//    typedef attr_val_table primary_key_list;
//    assert(val.isString());
//    std::string s = val.asString();
//    assert(!s.empty());
//
//    primary_key_list li;
//    std::string buf;
//    auto iter = current_table_attr.get_column_attr(PRIMARY_KEY).begin();
//    for (size_t i = 0; i < s.size(); i++)
//    {
//        if (s[i]!=',')
//        {
//            buf.push_back(s[i]);
//        }
//        else
//        {
//            li.add_attr_val(attr_val_pair(iter->get_column_name(), result_list(buf), current_type_column_list.get_type_column_pair(iter->get_column_name()).get_type()));
//            buf.clear();
//            ++iter;
//        }
//    }
//    if (!buf.empty())
//    {
//        li.add_attr_val(attr_val_pair(iter->get_column_name(), result_list(buf), current_type_column_list.get_type_column_pair(iter->get_column_name()).get_type()));
//    }
//    return li;
//}

//'arr' is a array containing every data fields.
attr_val_table table_mgr::make_attr_val_table(inner_structure& arr)
{
    assert(arr.isArray());
    attr_val_table a_v_table;
    auto val_iter = arr.begin();
    auto column_iter = current_type_column_list.begin();
    while (val_iter!=arr.end())
    {
        a_v_table.add_attr_val(attr_val_pair(column_iter->first, (*val_iter).asString(), column_iter->second.get_type()));
        ++val_iter;
        ++column_iter;
    }
    return a_v_table;
}

table_mgr::inner_structure table_mgr::record_to_data(single_record& record)
{
    table_mgr::inner_structure single_record;
    for (auto iter = record.begin(); iter != record.end(); iter++)
    {
        if (iter->second.get_val_type()==NULLABLE)
        {
            single_record.append(NULL_VAL);
        }
        else
        {
            single_record.append(iter->second.get_result());
        }
    }
    return single_record;
}

table_mgr::table_mgr():
current_db(db_mgr::get_current_database())
{
}

table_mgr::table_mgr(const table_name& table_name) :
current_table(table_name),
current_db(db_mgr::get_current_database())
{
    open_table(table_name);
}

table_mgr::~table_mgr()
{
}

std::string table_mgr::get_full_table_path(const db_name& db, const table_name& table)
{
    assert(db.size()>0);
    assert(table.size()>0);
    return db + "\\" + table;
}

std::string table_mgr::get_full_table_attr_path(const db_name& db,const table_name& table)
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

void table_mgr::delete_table(const table_name& table_name)
{
    assert(table_name.size()>0);
    std::string full_path(db_mgr::get_current_database() + "\\" + table_name);
    file_mgr::remove_file(full_path);
    file_mgr::remove_file(full_path + ".attr");
}

void table_mgr::open_table(const table_name& table_name)
{
    assert(table_name.size()>0);
    if (!f_mgr.is_open())
    {
        set_current_table(table_name);
        f_mgr.open(get_full_table_path(current_db, current_table), "a+");
        f_attr_mgr.open(get_full_table_attr_path(current_db, current_table), "r+");
        get_table_attr();//该函数依赖f_attr_mgr的打开状态，后期重构。
    }
}

void table_mgr::set_current_table(const table_name& name)
{
    current_table = name;
}

void table_mgr::close_table()
{
    write_back();//writing all the data to table file.
    f_attr_mgr.close();
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

void table_mgr::set_table_type_columns(type_column_list& t_c_list)
{
    assert(!t_c_list.empty());
    current_type_column_list = t_c_list;
}

void table_mgr::set_table_attrs(table_attr& attrs)
{
    assert(!attrs.empty());
    current_table_attr = attrs;
}

bool table_mgr::exist(const table_name& table_name)
{
    return file_mgr::exist(db_mgr::get_current_database()+ "\\" + table_name);
}

std::pair<bool, std::string> table_mgr::verify_primary_key(attr_val_table& li)
{
    column_attr_list key_list = current_table_attr.get_column_attr(PRIMARY_KEY);
    std::string primary_key_val_list;
    for (auto iter = key_list.begin(); iter != key_list.end(); iter++)
    {
        if (!li.contain(iter->get_column_name()))
        {
            return std::pair<bool, std::string>(false, std::string());
        }
        primary_key_val_list.append(li.get_attr_val(iter->get_column_name()).get_result());
        primary_key_val_list.append(",");
    }
    primary_key_val_list.pop_back();//pop the comma in the end.
    return std::pair<bool, std::string>(true, primary_key_val_list);
}

void table_mgr::verify_data_field(attr_val_table& list)
{
    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
        if (!current_type_column_list.contain(iter->first))
        {
            std::cout << err_msg_mgr::invalid_expression("no column %s", iter->first)<<std::endl;
            exit(1);
        }
    }
}

void table_mgr::insert_record(attr_val_table& list)
{
    verify_data_field(list);
    std::pair<bool, std::string> key_pair = verify_primary_key(list);
    if (!key_pair.first)
    {
        throw std::runtime_error("primary key must be specified");
    }
    if (data_record_table.contain(key_pair.second))
    {
        throw std::runtime_error("this record has already existed");
    }
    data_record_table.add_record(make_single_record(key_pair.second, list));
}

single_record table_mgr::make_single_record(const std::string& primary_key, attr_val_table& a_v_table)
{
    single_record record;
    attr_val_table table;
    for (auto iter = current_type_column_list.begin(); iter != current_type_column_list.end();++iter)
    {
        table.add_attr_val(attr_val_pair(iter->first,result_list(),NULLABLE));
    }
    for (auto iter = a_v_table.begin(); iter != a_v_table.end(); ++iter)
    {
        table.get_attr_val(iter->first).set_result(iter->second.get_result());
        table.get_attr_val(iter->first).set_val_type(iter->second.get_val_type());
    }
    record.set_primary_key(primary_key);
    record.set_record(table);
    return record;
}

void table_mgr::get_table_attr()
{
    inner_structure root = fetch_all_data(f_attr_mgr);
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

void table_mgr::add_column(type_column_list& t_c_list)
{
    assert(!t_c_list.empty());
    current_type_column_list.add_type_column(t_c_list.begin(), t_c_list.end());
}

void table_mgr::remove_column(type_column_list& t_c_list)
{
    assert(!t_c_list.empty());
    current_type_column_list.remove_type_column(t_c_list.begin(),t_c_list.end());
}

void table_mgr::alter_column(type_column_list& t_c_list)
{
    assert(!t_c_list.empty());
    current_type_column_list.alter_column_type(t_c_list.begin(), t_c_list.end());
}

table_mgr::inner_structure table_mgr::fetch_all_data(file_mgr& file)
{
    inner_structure_reader reader;
    inner_structure root;
    std::string content = file.read();
    reader.parse(content, root);
    return root;
}

void table_mgr::write_back()
{
   // inner_structure_writer writer;
    attrs_write_back();
    records_write_back();
}

void table_mgr::get_table_records()
{
    inner_structure root= fetch_all_data(f_mgr);
    for (auto iter = root.begin(); iter != root.end(); iter++)
    {
        data_record_table.add_record(make_single_record(iter.key().asString(), make_attr_val_table(*iter)));
    }
}

void table_mgr::attrs_write_back()
{
    inner_structure_styled_writer styled_writer;
    inner_structure root = fetch_all_data(f_attr_mgr);
    inner_structure attr_node = root["attributes"];
    for (auto iter = current_table_attr.begin(); iter != current_table_attr.end(); iter++)
    {
        for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
        {
            attr_node[column_attrs_to_s[iter2->get_attr()]].append(iter2->get_column_name());
        }
    }

    inner_structure column_node = root["columns"];
    for (auto iter = current_type_column_list.begin(); iter != current_type_column_list.end(); iter++)
    {
        column_node[iter->first] = val_type_to_s[iter->second.get_type()];
    }
    root["attributes"] = attr_node;
    root["columns"] = column_node;
    f_attr_mgr.write(styled_writer.write(root));
}

void table_mgr::records_write_back()
{
    auto record_list = data_record_table.get_all_records();
    inner_structure root = fetch_all_data(f_mgr);
    for (auto iter = record_list.begin(); iter != record_list.end(); iter++)
    {
        root[iter->get_primary_key()] = record_to_data(*iter);
    }
    inner_structure_writer writer;
    f_mgr.write(writer.write(root));
}

void table_mgr::union_logic_selector(logic_conn_table& table)
{
    std::map<std::string, std::string, val_type> and_result;
    
    auto and_list = table.get_logic_expr_list(AND);

}

