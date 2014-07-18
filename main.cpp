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
    lexer lexer(string("create <- student string name int age [name primary key,age not null]"));
    parser parser(lexer);
    parser.program();
    cout << "success..." << endl;
    getchar();
}