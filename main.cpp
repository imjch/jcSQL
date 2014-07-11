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
        lexer lexer(string("select <- name age [ name = 'swedgfaeth' age = 30.0asd ]"));
        /*parser parser(lexer);
        parser.execute();*/
        token t = lexer.next_token();
        while (t.get_token_type()!=lexer::EOF_TYPE)
        {
            cout << t.to_string() << endl;
            t = lexer.next_token();
        }

    }
    catch (std::runtime_error& e)
    {
        cerr << e.what() << endl;
    }
    cout << "success..." << endl;
    getchar();
}