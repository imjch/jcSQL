#include "file_mgr.h"
#include "err_msg_mgr.h"
#include <Shlwapi.h>
#include <cassert>
#include <cstdio>

file_mgr::~file_mgr()
{
   
} 
file_mgr::file_mgr()
{

}
void file_mgr::close()
{
    if (fp >= NULL)
    {
        ::fclose(fp);
    }
}

file_mgr::file_mgr(const std::string& file_name, const char* fmode)
{
    open(file_name,fmode);
}

bool file_mgr::exist(const std::string& path)
{
    assert(path.size()>0);
    GetFileAttributesA(path.c_str()); // from winbase.h
    if (INVALID_FILE_ATTRIBUTES == GetFileAttributesA(path.c_str()) && GetLastError() == ERROR_FILE_NOT_FOUND)
    {
        return false;
    }
    return true;
}

void file_mgr::open(const std::string& path,const char * fmode)
{
    assert(path.c_str()>0);
    assert(fmode!=NULL);
    file_path = path;
    open_mode = fmode;
    fp = ::fopen(path.c_str(),fmode);
    if (!fp)
    {
        perror(err_msg_mgr::invalid_expression("open file %s failed",path.c_str()).c_str());
    }
}

void file_mgr::clear_content()
{
    remove_file(file_path);
    create_file(file_path);
}

void file_mgr::append(const std::string& content)
{
    if (fseek(fp, 0, SEEK_END))
    {
        perror("error occured in file_mgr::append()");
        ::abort();
    }
    write(content);
}

void file_mgr::write(const std::string& content)
{
    close();
    remove_file(file_path);
    create_file(file_path);
    open(file_path, open_mode.c_str());
    if (::fputs(content.c_str(), fp)<0)
    {
        perror("writing data failed");
        ::abort();
    }
}

void file_mgr::create_file(const std::string& path)
{
    assert(path.size()>0);
    FILE * f;
    if (exist(path))
    {
        remove_file(path);
    }
    if ((f=fopen(path.c_str(), "w")) == NULL)
    {
        perror("creating file failed");
    }
    fclose(f);
}

void file_mgr::remove_file(const std::string& path)
{
    assert(path.size()>0);
    if (exist(path))
    {
        if (remove(path.c_str())!=0)
        {
            perror("removing file %s failed");
        }
    }
}

std::string file_mgr::read()
{
    char buf[4096];
    std::string content;
    while (fgets(buf,4096,fp)!=NULL)
    {
        content.append(buf);
    }
    if (ferror(fp))
    {
        perror("reading data failed");
        ::abort();
    }
    return content;
}
