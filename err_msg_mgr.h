#pragma once
#include <string>
#include <cstdio>
#include <vadefs.h>
class err_msg_mgr
{
public:
    static std::string invlid_expression(char *format,...)
    {
        char buff[BUFSIZ];
        std::string msg("error:");

        va_list args;
        _crt_va_start(args, format);
        vsnprintf_s(buff, BUFSIZ, format,args);
        msg.append(buff);
        return std::string(msg);
    }
};
