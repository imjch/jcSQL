#pragma once
#include <string>
#include <cstdio>
#include <vadefs.h>
class err_msg_mgr
{
public:
    static std::string& invlid_token(char *format,...)
    {
        char buff[BUFSIZ];
        std::string msg("invlid token:");

        va_list args;
        _crt_va_start(args, format);
        vsnprintf_s(buff, BUFSIZ, format,args);
        msg.append(buff);
        return std::string(msg);
    }
};
