#include "op_tree.h"

operation_tree::operation_tree(const token& tk) :operation_type(tk)
{
    
}
operation_tree::~operation_tree()
{

}
void operation_tree::eval()
{

}
const int operation_tree::get_op_type() const
{
    return operation_type.get_token_type();
}

const std::string& operation_tree::get_op_text() const
{
    return operation_type.get_token_text();
}

void select_tree::execute(){ return; }
void create_tree::execute(){ return; }
void insert_tree::execute(){ return; }
void update_tree::execute(){ return; }
void drop_tree::execute(){ return; }
void alter_tree::execute(){ return; }
