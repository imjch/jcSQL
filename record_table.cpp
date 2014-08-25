#include "record_table.h"
#include <cassert>
#include "operators.h"
record_table::record_table() 
:count(0)
{
}

record_table::~record_table()
{
}

bool record_table::contain(primary_key& key)
{
    return index_table.count(key.to_string()) > 0 ? true : false;
}

single_record record_table::get_record(primary_key& li)
{
    std::string pri_key = li.to_string();
    if (contain(li))
    {
        return records[index_table[pri_key]].second;
    }
    else
    {
        throw std::runtime_error("record_table::get_record:no such record.");
    }
}
/*   switch (logic_expr.get_op())
{
case GT:
break;
case LT:
break;
case GE:
break;
case LE:
break;
case EQ:
break;
case NE:
break;
default:
throw std::runtime_error("record_table::get_record:invalid operators type.");
}*/
std::list<single_record> record_table::get_records(logic_conn_table& table)
{
    //typedef std::unordered_map<std::string, std::list<logic_expr>> unioned_logic_table;
    //unioned_logic_table unioned_and;
    //unioned_logic_table unioned_or;
    //if (table.contain(AND))
    //{
    //    auto and_list = table.get_logic_expr_list(AND);
    //    for (auto and_iter = and_list.begin(); and_iter != and_list.end(); and_iter++)
    //    {
    //        unioned_and[and_iter->get_attr()].push_back(*and_iter);
    //    }
    //}
    //if (table.contain(OR))
    //{
    //    auto or_list = table.get_logic_expr_list(OR);
    //    for (auto or_iter = or_list.begin(); or_iter != or_list.end(); or_iter++)
    //    {
    //        unioned_or[or_iter->get_attr()].push_back(*or_iter);
    //    }
    //}


}


void record_table::add_record(single_record& record)
{
    if (!contain(record.get_primary_key()))
    {
        index_table.insert(std::make_pair(record.get_primary_key().to_string(), count));
        records.push_back(std::make_pair(true, record));
        ++count;
    }
}

void record_table::remove_record(primary_key& li)
{
    if (contain(li))
    {
        records[index_table[li.to_string()]].first = false;
    }
}

void record_table::remove_record(logic_conn_table& table)
{

}

std::list<single_record> record_table::get_all_records()
{
    std::list<single_record> record_list;
    for (size_t i = 0; i < records.size(); i++)
    {
        if (records[i].first)
            record_list.push_back(records[i].second);
    }
    return record_list;
}

std::list<single_record> record_table::GT_FILTER(attr_val_pair& expr)
{

}

std::list<single_record>  record_table::LT_FILTER(attr_val_pair& expr)
{

}

std::list<single_record>  record_table::GE_FILTER(attr_val_pair& expr)
{

}

std::list<single_record> record_table::LE_FILTER(attr_val_pair& expr)
{

}

std::list<single_record>  record_table::EQ_FILTER(attr_val_pair& expr)
{

}

std::list<single_record>  record_table::NE_FILTER(attr_val_pair& expr)
{

}