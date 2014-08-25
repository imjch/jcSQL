#pragma once
#include <string>
#include <list>
#include <map>
#include "file_mgr.h"
#include "db_mgr.h"
#include "uncopyable.h"
#include "table_attr.h"
#include "attr_val_table.h"
#include "column_attr_pair.h"
#include "type_column_list.h"
#include "logic_conn_table.h"
#include "operators.h"
#include "record_table.h"
#include "val_type.h"
#include "json\json.h"
#pragma comment(lib,"jsoncpp.lib")

class table_mgr:private uncopyable
{
public:
    typedef std::string column_name;
    typedef std::string column_val;
    typedef std::string table_name;
    typedef std::string db_name;
    typedef Json::Value inner_structure;
    typedef Json::FastWriter inner_structure_writer;
    typedef Json::Reader inner_structure_reader;
    typedef Json::StyledWriter inner_structure_styled_writer;
    typedef std::list<column_name> column_list;
    static bool exist(const table_name&);
    static void create_table(const table_name&);
    static void delete_table(const table_name&);

    table_mgr(const std::string&);
    table_mgr();
    ~table_mgr();
    void set_table_attrs(table_attr& attrs);
    void set_table_type_columns(type_column_list&);
    void add_column(type_column_list&);
    void remove_column(type_column_list&);
    void alter_column(type_column_list&);
  //  result_table get_data(column_list&,logic_conn_table&);
    void delete_record(logic_conn_table&);
    void insert_record(attr_val_table&);
    void open_table(const table_name&);
    void close_table();
private:
    inner_structure record_to_data(single_record&);
    void filter_records(logic_conn_table&);
    void set_current_table(const table_name&);
    void get_table_attr();
    void get_table_records();


    std::pair<bool, primary_key> get_primary_key(attr_val_table&);
    void verify_data_field(attr_val_table&);
    std::string get_full_table_path(const db_name&, const table_name&);
    std::string get_full_table_attr_path(const db_name&, const table_name&);
    inner_structure fetch_all_data(file_mgr&);//待优化底层数据获取策略，初始版本暂时以最低效率运行。
    bool contain_attr(inner_structure&, std::string&);
    single_record make_single_record(primary_key&, attr_val_table& list);
    primary_key make_primary_key(inner_structure&);
    attr_val_table make_attr_val_table(inner_structure& arr);
    void write_back();
    void records_write_back();
    void attrs_write_back();
    db_name current_db;
    table_name current_table;
    table_attr  current_table_attr;
    type_column_list current_type_column_list;
    record_table data_record_table;
    file_mgr f_attr_mgr;
    file_mgr f_mgr;
    const int NULL_VAL = -1;
   // db_mgr d_mgr;
};

