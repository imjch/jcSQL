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
    lexer lexer(string("create <- student string name int age [name primary key,age unique,age not null]"));
    parser parser(lexer);
    operation* o = parser.program();
    shared_ptr<operation> op(o);
    if (err_collector::empty())
    {
        try
        {
            executor(op.get());
            cout << "Done..." << endl;
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