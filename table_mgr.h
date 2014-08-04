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
#pragma comment(lib,"jsoncpp.lib")

class table_mgr:private uncopyable
{
public:
    typedef std::vector<std::vector<std::string>> result_table;
    typedef std::list<std::string> column_list;
    table_mgr(const std::string&);
    table_mgr();
    ~table_mgr();
    static bool exist(const std::string&);
    static void create_table(const std::string&);
    static void delete_table(const std::string&);
    
    void set_table_attrs(table_attr&);
    void set_table_type_columns(type_column_table&);
    void add_attr(column_attr_pair&);
   // void alter_table(operators,type_column_table&);
    result_table get_data(column_list&,logic_conn_table&);
    void insert_data(attr_val_list&);
    void open_table(const std::string&);
    void close_table();
private:
    Json::Value fetch_all_data();//待优化底层数据获取策略，初始版本暂时以最低效率运行。
    bool contain_attr(Json::Value&, std::string&);
    void insert_data_(Json::Value&, attr_val_pair& pair);
    std::string get_full_table_path();
    std::string get_full_table_attr_path();
    std::string current_db;
    std::string current_table;
    file_mgr f_mgr;
   // db_mgr d_mgr;
};

