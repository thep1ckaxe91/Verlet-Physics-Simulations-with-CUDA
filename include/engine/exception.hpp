#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include<exception>
#include<string>
class CoreException : public std::exception { 
private: 
    std::string message; 
  
public: 
    CoreException(const char* msg);
    CoreException(std::string&& msg);
    
    const char* what() const throw();
}; 

#endif