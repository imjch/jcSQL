#pragma once
#include "operation.h"
#include "type_column_list.h"
#include "table_attr.h"

class create_operation:public operation
{
public:
    create_operation(const std::string&, type_column_list&);
    create_operation(const std::string&, type_column_list&,table_attr&);
  
    ~create_operation();
    void set_type_column_list(type_column_list&);
    void set_table_attr(table_attr&);
    table_attr get_table_attr();
    type_column_list get_type_column_list();
   
private:
    type_column_list t_c_table;
    table_attr t_attr;
};

