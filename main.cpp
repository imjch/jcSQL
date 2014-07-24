#include <vld.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include <string>
#include "log.h"
using namespace std;

int main(int argc, char* argv[])
{
    log::clear();
    lexer lexer(string("select <- student name [sdfsasd af "));
    parser parser(lexer);
    parser.program();
    if (log::empty())
    {
        cout << "success..." << endl;
    }
    else
    {
        log::foreach();
    }
    getchar();
}