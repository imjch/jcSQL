#include <vld.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include <string>
#include <memory>
using namespace std;

int main(int argc, char* argv[])
{
    lexer lexer(string("select <- students string name int age [ name != \"aa']"));
    parser parser(lexer);
    parser.program();
    /* token t = lexer.next_token();
     while (t.get_token_type()!=tag::EOF_TYPE)
     {
     cout << t.to_string() << endl;
     t = lexer.next_token();
     }*/
    cout << "success..." << endl;
    getchar();
}