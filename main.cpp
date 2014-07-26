#include <vld.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include <string>
#include "log.h"
using namespace std;

int main(int argc, char* argv[])
{
    log::clear();
    lexer lexer(string("create <- student string name [ name primary key]"));
    parser parser(lexer);
    if (log::empty())
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
        log::foreach();
    }
    getchar();
}