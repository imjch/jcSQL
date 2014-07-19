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
    lexer lexer(string("delete <- student [name = \"jiang chuan\"] "));
    parser parser(lexer);
    parser.program();
    cout << "success..." << endl;
    getchar();
}