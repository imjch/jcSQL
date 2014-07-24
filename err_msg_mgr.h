#pragma once
#include <string>
#include <cstdio>
#include <vadefs.h>
class err_msg_mgr
{
public:
    static std::string invalid_expression(const char *format,...)
    {
        char buff[BUFSIZ];
        std::string msg("error:");
        va_list list;
        va_start(list, format);
        vsnprintf_s(buff, BUFSIZ, format, list);
        msg.append(buff);
        return std::string(msg);
    }
};
