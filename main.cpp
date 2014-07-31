#include <vld.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include <string>
#include <iterator>
#include "err_collector.h"
#include <memory>
using namespace std;

int main(int argc, char* argv[])
{
    lexer lexer(string("create <- student string name int age [ name primary key,name primary key,age unique,age primary key]"));
    parser parser(lexer);
    if (err_collector::empty())
    {
        try
        {
            operation* o = parser.program();
            executor(o);
            delete o;
            cout << "success..." << endl;
        }
        catch (std::runtime_error& e)
        {
            cout << e.what() << endl;
        }
    }
    else
    {
        err_collector::output_error(std::ostream_iterator<std::string>(cout,"\n"));
    }
    getchar();
}