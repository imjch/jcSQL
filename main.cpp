#include <vld.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include <string>
#include <memory>
using namespace std;
int main(int argc, char* argv[])
{
    try
    {
        lexer lexer(string("(a,(b,c))"));
        parser parser(lexer);
        parser.list();
    }
    catch (std::runtime_error& e)
    {
        cerr << e.what() << endl;
    }
    cout << "compiler success..." << endl;
    getchar();
}