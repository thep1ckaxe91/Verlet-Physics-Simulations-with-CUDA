#include "engine/exception.hpp"

CoreException::CoreException(const char* msg) : message(msg) {}
CoreException::CoreException(std::string&& msg) : message((std::string&&) msg){}

const char * CoreException::what() const throw()
{
    return message.c_str();
}
