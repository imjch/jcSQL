#pragma once
#include "lexer.h"
#include <string>


class operation_tree
{
public:
    operation_tree(const token&);
    ~operation_tree();
    const int get_op_type()const;
    const std::string& get_op_text() const;
    virtual void eval();
private:
    token operation_type;
};

class select_tree :public operation_tree
{
public:
    void execute();
private:

};
class create_tree :public operation_tree
{
public:
    void execute();
private:

};
class insert_tree :public operation_tree
{
public:
    void execute();
private:

};
class update_tree :public operation_tree
{
public:
    void execute();
private:

};
class drop_tree :public operation_tree
{
public:
    void execute();
private:

};
class alter_tree :public operation_tree
{
public:
    void execute();
private:

};

