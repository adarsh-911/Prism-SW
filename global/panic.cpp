#include "panic.hpp"

#include <fstream>

void do_panic(const std::string& panic_msg, size_t line_no, const char* file_name, const char* function)
{
    std::cerr << "Panic at " << file_name << " in function " << function << " at line " << line_no << ":\n";
    std::cerr << "\t" << panic_msg;
}

void init_error_manager()
{
    ;
}
