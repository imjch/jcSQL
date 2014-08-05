#pragma once
#include <string>
#include <list>
#include "file_mgr.h"
#include "db_mgr.h"
#include "uncopyable.h"
#include "table_attr.h"
#include "attr_val_list.h"
#include "column_attr_pair.h"
#include "type_column_table.h"
#include "json\json.h"
#include "logic_conn_table.h"
#include "operators.h"
#include "val_type.h"
#pragma comment(lib,"jsoncpp.lib")

class table_mgr:private uncopyable
{
public:
    typedef std::vector<std::vector<std::string>> result_table;
    typedef std::list<std::string> column_list;
    typedef Json::Value inner_structure;
    typedef Json::FastWriter inner_structure_writer;
    typedef Json::Reader inner_structure_reader;
    table_mgr(const std::string&);
    table_mgr();
    ~table_mgr();
    static bool exist(const std::string&);
    static void create_table(const std::string&);
    static void delete_table(const std::string&);
  
    void set_table_attrs(table_attr& attrs);
    void set_table_type_columns(type_column_table&);
    void add_attr(column_attr_pair&);
   // void alter_table(operators,type_column_table&);
    result_table get_data(column_list&,logic_conn_table&);
    void insert_data(attr_val_list&);
    void open_table(const std::string&);
    void close_table();
private:
    typedef std::string column_name;
    typedef std::string column_val;
    typedef std::unordered_map<column_name,std::pair<int,std::string>> data_record_indicator;
    void get_table_attr();
    std::string get_full_table_path(const std::string& db, const std::string& table);
    std::string get_full_table_attr_path(const std::string& db, const std::string& table);
    Json::Value fetch_all_data(file_mgr&);//待优化底层数据获取策略，初始版本暂时以最低效率运行。
    bool contain_attr(inner_structure&, std::string&);
    data_record_indicator construct_data_record_indicator(attr_val_list& list);

    const int NULLABLE = 0;
    const int READLVAL = 1;
    std::string current_db;
    std::string current_table;
    table_attr  current_table_attr;
    type_column_table current_type_column_list;
    file_mgr f_mgr;
   // db_mgr d_mgr;
};

