#include <vld.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include <string>
#include <iterator>
#include "err_collector.h"
using namespace std;

int main(int argc, char* argv[])
{
    lexer lexer(string("create <- student string name [ name primary key]"));
    parser parser(lexer);
    if (err_collector::empty())
    {
        try
        {
            executor(parser.program());
            cout << "success..." << endl;
        }
        catch (std::bad_cast& e)
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